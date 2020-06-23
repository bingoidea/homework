#pragma once
#include "common.h"

/*******************************************************************************
                                   �﷨������
*******************************************************************************/

class Parser
{
	//�ķ���ʼ
	void program();
	void segment();
	Tag type();
	
	//�����붨��
	Var* defdata(bool ext,Tag t);
	void deflist(bool ext,Tag t);
	Var* varrdef(bool ext,Tag t,bool ptr,string name);
	Var* init(bool ext,Tag t,bool ptr,string name);
	void def(bool ext,Tag t);
	void idtail(bool ext,Tag t,bool ptr,string name);
	
	//����
	Var* paradatatail(Tag t,string name);
	Var* paradata(Tag t);
	void para(vector<Var*>&list);
	void paralist(vector<Var*>&list);
	void funtail(Fun*f);
	void block();
	void subprogram();
	void localdef();
	
	//���
	void statement();
	void whilestat();
	void dowhilestat();
	void forstat();
	void forinit();
	void ifstat();
	void elsestat();
	void switchstat();
	void casestat(Var*cond);
	Var* caselabel();
	
	//���ʽ
	Var* altexpr();
	Var* expr();
	Var* assexpr();
	Var* asstail(Var*lval);
	Var* orexpr();
	Var* ortail(Var*lval);
	Var* andexpr();
	Var* andtail(Var*lval);
	Var* cmpexpr();
	Var* cmptail(Var*lval);
	Tag cmps();
	Var* aloexpr();
	Var* alotail(Var*lval);
	Tag adds();
	Var* item();
	Var* itemtail(Var*lval);
	Tag muls();
	Var* factor();
	Tag lop();
	Var* val();
	Tag rop();
	Var* elem();
	Var* literal();
	Var* idexpr(string name);
	void realarg(vector<Var*> &args);
	void arglist(vector<Var*> &args);
	Var* arg();
	
	//�ʷ�����
	Lexer &lexer;//�ʷ�������
	Token*look;//��ǰ�鿴���ַ�
	
	//���ű�
	SymTab &symtab;
	
	//�м����������
	GenIR &ir;
	
	//�﷨����������޸�
	void move();//�ƽ�
	bool match(Tag t);//ƥ��,�ɹ����ƽ�
	void recovery(bool cond,SynError lost,SynError wrong);//�����޸�

public:
	
	//�������ʼ��
	Parser(Lexer&lex,SymTab&tab,GenIR&inter);
	
	//�ⲿ���ýӿ�
	void analyse();//�﷨����������
};


































