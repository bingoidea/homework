#include "parser.h"
#include "token.h"
#include "lexer.h"
#include "symbol.h"
#include "symtab.h"
#include "genir.h"
#include "error.h"
#include "compiler.h"

/*******************************************************************************
                                   �﷨������
*******************************************************************************/

Parser::Parser(Lexer&lex,SymTab&tab,GenIR&inter)
	:lexer(lex),symtab(tab),ir(inter)
{}


/*
	�﷨����������
*/
void Parser::analyse()
{
	move();//Ԥ�ȶ���
	program();
}

/*
	�ƽ�
*/
void Parser::move()
{
	look=lexer.tokenize();
	if(Args::showToken) printf("%s   ",look->toString().c_str());//����ʷ��Ǻš�������
}

/*
	ƥ��,�鿴���ƶ�
*/
bool Parser::match(Tag need)
{
	if(look->tag==need){
		move();
		return true;
	}
	else
		return false;
}

//��ӡ�﷨����
#define SYNERROR(code,t) Error::synError(code,t)

/*
	�����޸�
*/
#define _(T) ||look->tag==T
#define F(C) look->tag==C
void Parser::recovery(bool cond,SynError lost,SynError wrong)
{
	if(cond)/*�ڸ�����Follow������*/
		SYNERROR(lost,look);
	else{
		SYNERROR(wrong,look);
		move();
	}
}

//����
#define TYPE_FIRST F(KW_INT)_(KW_CHAR)_(KW_VOID)
//���ʽ
#define EXPR_FIRST F(LPAREN)_(NUM)_(CH)_(STR)_(ID)_(NOT)_(SUB)_(LEA)_(MUL)_(INC)_(DEC)
//��ֵ����
#define LVAL_OPR F(ASSIGN)_(OR)_(AND)_(GT)_(GE)_(LT)_(LE)_(EQU)_(NEQU)_(ADD)_(SUB)_(MUL)_(DIV)\
_(MOD)_(INC)_(DEC)
//��ֵ����
#define RVAL_OPR F(OR)_(AND)_(GT)_(GE)_(LT)_(LE)_(EQU)_(NEQU)_(ADD)_(SUB)_(MUL)_(DIV)\
_(MOD)
//���
#define STATEMENT_FIRST (EXPR_FIRST)_(SEMICON)_(KW_WHILE)_(KW_FOR)_(KW_DO)_(KW_IF)\
_(KW_SWITCH)_(KW_RETURN)_(KW_BREAK)_(KW_CONTINUE)

/*
	<program>			->	<segment><program>|^
*/
void Parser::program()
{
	if(F(END)){//��������

		return ;
	}
	else{
		segment();
		program();
	}
}

/*
	<segment>			->	rsv_extern <type><def>|<type><def>
*/
void Parser::segment()
{
	bool ext=match(KW_EXTERN);//��¼��������
	Tag t=type();
	def(ext,t);
}

/*
	<type>				->	rsv_int|rsv_char|rsv_bool|rsv_void
*/
Tag Parser::type()
{
	Tag tmp=KW_INT;//Ĭ������
	if(TYPE_FIRST){
		tmp=look->tag;//��¼����
		move();//�ƽ�
	}
	else//����
		recovery(F(ID)_(MUL),TYPE_LOST,TYPE_WRONG);
	return tmp;//��¼����
}

/*
	<defdata>			->	ident <varrdef>|mul ident <init>
*/
Var* Parser::defdata(bool ext,Tag t)
{
	string name="";
	if(F(ID)){
		name=(((Id*)look)->name);
		move();
		return varrdef(ext,t,false,name);
	}
	else if(match(MUL)){
		if(F(ID)){
			name=(((Id*)look)->name);
			move();
		}
		else
			recovery(F(SEMICON)_(COMMA)_(ASSIGN),ID_LOST,ID_WRONG);
		return init(ext,t,true,name);
	}
	else{
		recovery(F(SEMICON)_(COMMA)_(ASSIGN)_(LBRACK),ID_LOST,ID_WRONG);
		return varrdef(ext,t,false,name);
	}
}

/*
	<deflist>			->	comma <defdata> <deflist>|semicon
*/
void Parser::deflist(bool ext,Tag t)
{
	if(match(COMMA)){//��һ������
		symtab.addVar(defdata(ext,t));
		deflist(ext,t);
	}
	else if(match(SEMICON))//���һ������
		return;
	else{//������
		if(F(ID)_(MUL)){//����
			recovery(1,COMMA_LOST,COMMA_WRONG);
			symtab.addVar(defdata(ext,t));
			deflist(ext,t);
		}
		else
			recovery(TYPE_FIRST||STATEMENT_FIRST||F(KW_EXTERN)_(RBRACE),
				SEMICON_LOST,SEMICON_WRONG);
	}
}

/*
	<varrdef>			->	lbrack num rbrack | <init>
*/
Var* Parser::varrdef(bool ext,Tag t,bool ptr,string name)
{
	if(match(LBRACK)){
		int len=0;
		if(F(NUM)){
			len=((Num*)look)->val;
			move();
		}
		else
			recovery(F(RBRACK),NUM_LOST,NUM_WRONG);
		if(!match(RBRACK))
			recovery(F(COMMA)_(SEMICON),RBRACK_LOST,RBRACK_WRONG);
		return new Var(symtab.getScopePath(),ext,t,name,len);//�µ�����
	}
	else
		return init(ext,t,ptr,name);
}

/*
	<init>				->	assign <expr>|^
*/
Var* Parser::init(bool ext,Tag t,bool ptr,string name)
{
	Var* initVal=NULL;
	if(match(ASSIGN)){
		initVal=expr();
	}
	return new Var(symtab.getScopePath(),ext,t,ptr,name,initVal);//�µı�������ָ��
}

/*
	<def>					->	mul id <init><deflist>|ident <idtail>
*/
void Parser::def(bool ext,Tag t)
{
	string name="";
	if(match(MUL)){//ָ��
		if(F(ID)){
			name=(((Id*)look)->name);
			move();
		}
		else
			recovery(F(SEMICON)_(COMMA)_(ASSIGN),ID_LOST,ID_WRONG);
		symtab.addVar(init(ext,t,true,name));//�½�һ��ָ�����
		deflist(ext,t);
	}
	else{
		if(F(ID)){//���� ���� ����
			name=(((Id*)look)->name);
			move();
		}
		else
			recovery(F(SEMICON)_(COMMA)_(ASSIGN)_(LPAREN)_(LBRACK),ID_LOST,ID_WRONG);
		idtail(ext,t,false,name);
	}
}

/*
	<idtail>			->	<varrdef><deflist>|lparen <para> rparen <funtail>
*/
void Parser::idtail(bool ext,Tag t,bool ptr,string name)
{
	if(match(LPAREN)){//����
		symtab.enter();
		vector<Var*>paraList;//�����б�
		para(paraList);
		if(!match(RPAREN))
			recovery(F(LBRACK)_(SEMICON),RPAREN_LOST,RPAREN_WRONG);
		Fun* fun=new Fun(ext,t,name,paraList);
		funtail(fun);
		symtab.leave();
	}
	else{
		symtab.addVar(varrdef(ext,t,false,name));
		deflist(ext,t);
	}
}

/*
	<paradatatail>->	lbrack rbrack|lbrack num rbrack|^
*/
Var* Parser::paradatatail(Tag t,string name)
{
	if(match(LBRACK)){
		int len=1;//����������Գ���
		if(F(NUM)){
			len=((Num*)look)->val;
			move();
		}//����û��ָ������
		if(!match(RBRACK))
			recovery(F(COMMA)_(RPAREN),RBRACK_LOST,RBRACK_WRONG);
		return new Var(symtab.getScopePath(),false,t,name,len);
	}
	return new Var(symtab.getScopePath(),false,t,false,name);
}


/*
	<paradata>		->	mul ident|ident <paradatatail>
*/
Var* Parser::paradata(Tag t)
{
	string name="";
	if(match(MUL)){
		if(F(ID)){
			name=((Id*)look)->name;
			move();
		}
		else
			recovery(F(COMMA)_(RPAREN),ID_LOST,ID_WRONG);
		return new Var(symtab.getScopePath(),false,t,true,name);
	}
	else if(F(ID)){
		name=((Id*)look)->name;
		move();
		return paradatatail(t,name);
	}
	else{
		recovery(F(COMMA)_(RPAREN)_(LBRACK),ID_LOST,ID_WRONG);
		return new Var(symtab.getScopePath(),false,t,false,name);
	}
}

/*
	<para>				->	<type><paradata><paralist>|^
*/
void Parser::para(vector<Var*>&list)
{
	if(F(RPAREN))
		return;
	Tag t=type();
	Var*v=paradata(t);
	symtab.addVar(v);//������������ű�
	list.push_back(v);
	paralist(list);
}

/*
	<paralist>		->	comma<type><paradata><paralist>|^
*/
void Parser::paralist(vector<Var*>&list)
{
	if(match(COMMA)){//��һ������
		Tag t=type();
		Var*v=paradata(t);
		symtab.addVar(v);
		list.push_back(v);
		paralist(list);
	}
}

/*
	<funtail>			->	<block>|semicon
*/
void Parser::funtail(Fun*f)
{
	if(match(SEMICON)){//��������
		symtab.decFun(f);
	}
	else{//��������
		symtab.defFun(f);
		block();
		symtab.endDefFun();//������������
	}
}

/*
	<block>				->	lbrac<subprogram>rbrac
*/

void Parser::block()
{
	if(!match(LBRACE))
		recovery(TYPE_FIRST||STATEMENT_FIRST||F(RBRACE),LBRACE_LOST,LBRACE_WRONG);
	subprogram();
	if(!match(RBRACE))
		recovery(TYPE_FIRST||STATEMENT_FIRST||F(KW_EXTERN)_(KW_ELSE)_(KW_CASE)_(KW_DEFAULT),
			RBRACE_LOST,RBRACE_WRONG);
}

/*
	<subprogram>	->	<localdef><subprogram>|<statements><subprogram>|^
*/
void Parser::subprogram()
{
	if(TYPE_FIRST){//�ֲ�����
		localdef();
		subprogram();
	}
	else if(STATEMENT_FIRST){//���
		statement();
		subprogram();
	}
}

/*
	<localdef>		->	<type><defdata><deflist>
*/
void Parser::localdef()
{
	Tag t=type();
	symtab.addVar(defdata(false,t));
	deflist(false,t);
}

/*
	<statement>		->	<altexpr>semicon
										|<whilestat>|<forstat>|<dowhilestat>
										|<ifstat>|<switchstat>
										|rsv_break semicon
										|rsv_continue semicon
										|rsv_return<altexpr>semicon
*/
void Parser::statement()
{
	switch(look->tag)
	{
	case KW_WHILE:whilestat();break;
	case KW_FOR:forstat();break;
	case KW_DO:dowhilestat();break;
	case KW_IF:ifstat();break;
	case KW_SWITCH:switchstat();break;
	case KW_BREAK:
		ir.genBreak();//����break���
		move();
		if(!match(SEMICON))
			recovery(TYPE_FIRST||STATEMENT_FIRST||F(RBRACE),SEMICON_LOST,SEMICON_WRONG);
		break;
	case KW_CONTINUE:
		ir.genContinue();//����continue���
		move();
		if(!match(SEMICON))
			recovery(TYPE_FIRST||STATEMENT_FIRST||F(RBRACE),SEMICON_LOST,SEMICON_WRONG);
		break;
	case KW_RETURN:
		move();
		ir.genReturn(altexpr());//����return���
		if(!match(SEMICON))
			recovery(TYPE_FIRST||STATEMENT_FIRST||F(RBRACE),SEMICON_LOST,SEMICON_WRONG);
		break;
	default:
		altexpr();
		if(!match(SEMICON))
			recovery(TYPE_FIRST||STATEMENT_FIRST||F(RBRACE),SEMICON_LOST,SEMICON_WRONG);
	}
}

/*
	<whilestat>		->	rsv_while lparen<altexpr>rparen<block>
	<block>				->	<block>|<statement>
*/
void Parser::whilestat()
{
	symtab.enter();
	InterInst* _while,*_exit;//��ǩ
	ir.genWhileHead(_while,_exit);//whileѭ��ͷ��
	match(KW_WHILE);
	if(!match(LPAREN))
		recovery(EXPR_FIRST||F(RPAREN),LPAREN_LOST,LPAREN_WRONG);
	Var*cond=altexpr();
	ir.genWhileCond(cond,_exit);//while����
	if(!match(RPAREN))
		recovery(F(LBRACE),RPAREN_LOST,RPAREN_WRONG);
	if(F(LBRACE))block();
	else statement();
	ir.genWhileTail(_while,_exit);//whileβ��
	symtab.leave();
}

/*
	<dowhilestat> -> 	rsv_do <block> rsv_while lparen<altexpr>rparen semicon
	<block>				->	<block>|<statement>
*/
void Parser::dowhilestat()
{
	symtab.enter();
	InterInst* _do,* _exit;//��ǩ
	ir.genDoWhileHead(_do,_exit);//do-whileͷ��
	match(KW_DO);
	if(F(LBRACE))block();
	else statement();
	if(!match(KW_WHILE))
		recovery(F(LPAREN),WHILE_LOST,WHILE_WRONG);
	if(!match(LPAREN))
		recovery(EXPR_FIRST||F(RPAREN),LPAREN_LOST,LPAREN_WRONG);
	symtab.leave();
	Var*cond=altexpr();
	if(!match(RPAREN))
		recovery(F(SEMICON),RPAREN_LOST,RPAREN_WRONG);
	if(!match(SEMICON))
		recovery(TYPE_FIRST||STATEMENT_FIRST||F(RBRACE),SEMICON_LOST,SEMICON_WRONG);
	ir.genDoWhileTail(cond,_do,_exit);//do-whileβ��
}

/*
	<forstat> 		-> 	rsv_for lparen <forinit> semicon <altexpr> semicon <altexpr> rparen <block>
	<block>				->	<block>|<statement>
*/
void Parser::forstat()
{
	symtab.enter();
	InterInst *_for,*_exit,*_step,*_block;//��ǩ
	match(KW_FOR);
	if(!match(LPAREN))
		recovery(TYPE_FIRST||EXPR_FIRST||F(SEMICON),LPAREN_LOST,LPAREN_WRONG);
	forinit();//��ʼ���
	ir.genForHead(_for,_exit);//forѭ��ͷ��
	Var*cond=altexpr();//ѭ������
	ir.genForCondBegin(cond,_step,_block,_exit);//forѭ��������ʼ����
	if(!match(SEMICON))
		recovery(EXPR_FIRST,SEMICON_LOST,SEMICON_WRONG);
	altexpr();
	if(!match(RPAREN))
		recovery(F(LBRACE),RPAREN_LOST,RPAREN_WRONG);
	ir.genForCondEnd(_for,_block);//forѭ��������������
	if(F(LBRACE))block();
	else statement();
	ir.genForTail(_step,_exit);//forѭ��β��
	symtab.leave();
}

/*
	<forinit> 		->  <localdef> | <altexpr>
*/
void Parser::forinit()
{
	if(TYPE_FIRST)
		localdef();
	else{
		altexpr();
		if(!match(SEMICON))
			recovery(EXPR_FIRST,SEMICON_LOST,SEMICON_WRONG);
	}
}

/*
	<ifstat>			->	rsv_if lparen<expr>rparen<block><elsestat>
*/
void Parser::ifstat()
{
	symtab.enter();
	InterInst* _else,*_exit;//��ǩ
	match(KW_IF);
	if(!match(LPAREN))
		recovery(EXPR_FIRST,LPAREN_LOST,LPAREN_WRONG);
	Var*cond=expr();
	ir.genIfHead(cond,_else);//ifͷ��
	if(!match(RPAREN))
		recovery(F(LBRACE),RPAREN_LOST,RPAREN_WRONG);
	if(F(LBRACE))block();
	else statement();
	symtab.leave();

	ir.genElseHead(_else,_exit);//elseͷ��
	if(F(KW_ELSE)){//��else
		elsestat();
	}
	ir.genElseTail(_exit);//elseβ��
	//����if-else��else�����Ż�����������ɾ���㷨��Ч��
	// if(F(KW_ELSE)){//��else
	// 	ir.genElseHead(_else,_exit);//elseͷ��
	// 	elsestat();
	// 	ir.genElseTail(_exit);//elseβ��
	// }
	// else{//��else
	// 	ir.genIfTail(_else);
	// }
}

/*
	<elsestat>		-> 	rsv_else<block>|^
*/
void Parser::elsestat()
{
	if(match(KW_ELSE)){
		symtab.enter();
		if(F(LBRACE))block();
		else statement();
		symtab.leave();
	}
}

/*
	<switchstat>	-> 	rsv_switch lparen <expr> rparen lbrac <casestat> rbrac
*/
void Parser::switchstat()
{
	symtab.enter();
	InterInst*_exit;//��ǩ
	ir.genSwitchHead(_exit);//switchͷ��
	match(KW_SWITCH);
	if(!match(LPAREN))
		recovery(EXPR_FIRST,LPAREN_LOST,LPAREN_WRONG);
	Var*cond=expr();
	if(cond->isRef())cond=ir.genAssign(cond);//switch(*p),switch(a[0])
	if(!match(RPAREN))
		recovery(F(LBRACE),RPAREN_LOST,RPAREN_WRONG);
	if(!match(LBRACE))
		recovery(F(KW_CASE)_(KW_DEFAULT),LBRACE_LOST,LBRACE_WRONG);
	casestat(cond);
	if(!match(RBRACE))
		recovery(TYPE_FIRST||STATEMENT_FIRST,RBRACE_LOST,RBRACE_WRONG);
	ir.genSwitchTail(_exit);//switchβ��
	symtab.leave();
}

/*
	<casestat> 		-> 	rsv_case <caselabel> colon <subprogram><casestat>
										|rsv_default colon <subprogram>
*/
void Parser::casestat(Var*cond)
{
	if(match(KW_CASE)){
		InterInst*_case_exit;//��ǩ
		Var*lb=caselabel();
		ir.genCaseHead(cond,lb,_case_exit);//caseͷ��
		if(!match(COLON))
			recovery(TYPE_FIRST||STATEMENT_FIRST,COLON_LOST,COLON_WRONG);
		symtab.enter();
		subprogram();
		symtab.leave();
		ir.genCaseTail(_case_exit);//caseβ��
		casestat(cond);
	}
	else if(match(KW_DEFAULT)){//defaultĬ��ִ��
		if(!match(COLON))
			recovery(TYPE_FIRST||STATEMENT_FIRST,COLON_LOST,COLON_WRONG);
		symtab.enter();
		subprogram();
		symtab.leave();
	}
}

/*
	<caselabel>		->	<literal>
*/
Var* Parser::caselabel()
{
	return literal();
}

/*
	<altexpr>			->	<expr>|^
*/
Var* Parser::altexpr()
{
	if(EXPR_FIRST)
		return expr();
	return Var::getVoid();//��������VOID����
}

/*
	<expr> 				-> 	<assexpr>
*/
Var* Parser::expr()
{
	return assexpr();
}

/*
	<assexpr>			->	<orexpr><asstail>
*/
Var* Parser::assexpr()
{
	Var*lval=orexpr();
	return asstail(lval);
}

/*
	<asstail>			->	assign<assexpr>|^
*/
Var* Parser::asstail(Var*lval)
{
	if(match(ASSIGN)){
		Var*rval=assexpr();
		Var*result=ir.genTwoOp(lval,ASSIGN,rval);
		return asstail(result);
	}
	return lval;
}

/*
	<orexpr> 			-> 	<andexpr><ortail>
*/
Var* Parser::orexpr()
{
	Var*lval=andexpr();
	return ortail(lval);
}

/*
	<ortail> 			-> 	or <andexpr> <ortail>|^
*/
Var* Parser::ortail(Var*lval)
{
	if(match(OR)){
		Var*rval=andexpr();
		Var*result=ir.genTwoOp(lval,OR,rval);
		return ortail(result);
	}
	return lval;
}

/*
	<andexpr> 		-> 	<cmpexpr><andtail>
*/
Var* Parser::andexpr()
{
	Var*lval=cmpexpr();
	return andtail(lval);
}

/*
	<andtail> 		-> 	and <cmpexpr> <andtail>|^
*/
Var* Parser::andtail(Var*lval)
{
	if(match(AND)){
		Var*rval=cmpexpr();
		Var*result=ir.genTwoOp(lval,AND,rval);
		return andtail(result);
	}
	return lval;
}

/*
	<cmpexpr>			->	<aloexpr><cmptail>
*/
Var* Parser::cmpexpr()
{
	Var*lval=aloexpr();
	return cmptail(lval);
}

/*
	<cmptail>			->	<cmps><aloexpr><cmptail>|^
*/
Var* Parser::cmptail(Var*lval)
{
	if(F(GT)_(GE)_(LT)_(LE)_(EQU)_(NEQU)){
		Tag opt=cmps();
		Var*rval=aloexpr();
		Var* result=ir.genTwoOp(lval,opt,rval);
		return cmptail(result);
	}
	return lval;
}

/*
	<cmps>				->	gt|ge|ls|le|equ|nequ
*/
Tag Parser::cmps()
{
	Tag opt=look->tag;
	move();
	return opt;
}

/*
	<aloexpr>			->	<item><alotail>
*/
Var* Parser::aloexpr()
{
	Var*lval=item();
	return alotail(lval);
}

/*
	<alotail>			->	<adds><item><alotail>|^
*/
Var* Parser::alotail(Var*lval)
{
	if(F(ADD)_(SUB)){
		Tag opt=adds();
		Var* rval=item();
		Var*result=ir.genTwoOp(lval,opt,rval);//˫Ŀ����
		return alotail(result);
	}
	return lval;
}

/*
	<adds>				->	add|sub
*/
Tag Parser::adds()
{
	Tag opt=look->tag;
	move();
	return opt;
}

/*
	<item>				->	<factor><itemtail>
*/
Var* Parser::item()
{
	Var*lval=factor();
	return itemtail(lval);
}

/*
	<itemtail>		->	<muls><factor><itemtail>|^
*/
Var* Parser::itemtail(Var*lval)
{
	if(F(MUL)_(DIV)_(MOD)){
		Tag opt=muls();
		Var*rval=factor();
		Var*result=ir.genTwoOp(lval,opt,rval);//˫Ŀ����
		return itemtail(result);
	}
	return lval;
}

/*
	<muls>				->	mul|div|mod
*/
Tag Parser::muls()
{
	Tag opt=look->tag;
	move();
	return opt;
}

/*
	<factor> 			-> 	<lop><factor>|<val>
*/
Var* Parser::factor()
{
	if(F(NOT)_(SUB)_(LEA)_(MUL)_(INC)_(DEC)){
		Tag opt=lop();
		Var*v=factor();
		return ir.genOneOpLeft(opt,v);//��Ŀ�����
	}
	else
		return val();
}

/*
	<lop> 				-> 	not|sub|lea|mul|incr|decr
*/
Tag Parser::lop()
{
	Tag opt=look->tag;
	move();
	return opt;
}

/*
	<val>					->	<elem><rop>
*/
Var* Parser::val()
{
	Var*v=elem();
	if(F(INC)_(DEC)){
		Tag opt=rop();
		v=ir.genOneOpRight(v,opt);
	}
	return v;
}

/*
	<rop>					->	incr|decr|^
*/
Tag Parser::rop()
{
	Tag opt=look->tag;
	move();
	return opt;
}

/*
	<elem>				->	ident<idexpr>|lparen<expr>rparen|<literal>
*/
Var* Parser::elem()
{
	Var*v=NULL;
	if(F(ID)){//���������飬��������
		string name=((Id*)look)->name;
		move();
		v=idexpr(name);
	}
	else if(match(LPAREN)){//���ű��ʽ
		v=expr();
		if(!match(RPAREN)){
			recovery(LVAL_OPR,RPAREN_LOST,RPAREN_WRONG);
		}
	}
	else//����
		v=literal();
	return v;
}

/*
	<literal>			->	number|string|chara
*/
Var* Parser::literal()
{
	Var *v =NULL;
	if(F(NUM)_(STR)_(CH)){
		v = new Var(look);
		if(F(STR))
			symtab.addStr(v);//�ַ���������¼
		else
			symtab.addVar(v);//��������Ҳ��¼�����ű�
		move();
	}
	else
		recovery(RVAL_OPR,LITERAL_LOST,LITERAL_WRONG);
	return v;
}

/*
	<idexpr>			->	lbrack <expr> rbrack|lparen<realarg>rparen|^
*/
Var* Parser::idexpr(string name)
{
	Var*v=NULL;
	if(match(LBRACK)){
		Var* index=expr();
		if(!match(RBRACK))
			recovery(LVAL_OPR,LBRACK_LOST,LBRACK_WRONG);
		Var* array=symtab.getVar(name);//��ȡ����
		v=ir.genArray(array,index);//��������������ʽ
	}
	else if(match(LPAREN)){
		vector<Var*> args;
		realarg(args);
		if(!match(RPAREN))
			recovery(RVAL_OPR,RPAREN_LOST,RPAREN_WRONG);
		Fun* function=symtab.getFun(name,args);//��ȡ����
		v=ir.genCall(function,args);//�����������ô���
	}
	else
		v=symtab.getVar(name);//��ȡ����
	return v;
}

/*
	<realarg>			->	<arg><arglist>|^
*/
void Parser::realarg(vector<Var*> &args)
{
	if(EXPR_FIRST){
		args.push_back(arg());//ѹ�����
		arglist(args);
	}
}

/*
	<arglist>			->	comma<arg><arglist>|^
*/
void Parser::arglist(vector<Var*> &args)
{
	if(match(COMMA)){
		args.push_back(arg());
		arglist(args);
	}
}

/*
	<arg> 				-> 	<expr>
*/
Var* Parser::arg()
{
	//���һ��ʵ�ʲ���
	return expr();
}
