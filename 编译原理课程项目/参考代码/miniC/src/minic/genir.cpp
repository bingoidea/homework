#include "genir.h"
#include <sstream>
#include "symbol.h"
#include "symtab.h"
#include "error.h"


//��ӡ�������
#define SEMERROR(code) Error::semError(code)

int GenIR::lbNum=0;

/*
	��ʼ��
*/
GenIR::GenIR(SymTab&tab):symtab(tab)
{
	symtab.setIr(this);//�������ű��������������һһ��ϵ
	lbNum=0;
	push(NULL,NULL);//��ʼ��������
}

/*
	��ȡΨһ���ֵı�ǩ
*/
string GenIR::genLb()
{
	lbNum++;
	string lb=".L";//Ϊ�˺ͻ�ౣ��һ�£�
	stringstream ss;
	ss<<lbNum;
	return lb+ss.str();
}

/*
	�����������
*/
Var* GenIR::genArray(Var*array,Var*index)
{
	if(!array || !index)return NULL;
	if(array->isVoid()||index->isVoid()){
		SEMERROR(EXPR_IS_VOID);//void��������ֵ���ܳ����ڱ��ʽ��
		return NULL;
	}
	if(array->isBase() || !index->isBase()){
		SEMERROR(ARR_TYPE_ERR);
		return index;
	}
	return genPtr(genAdd(array,index));
}

/*
	ʵ�ʲ�������
*/
void GenIR::genPara(Var*arg)
{
	/*
		ע�Ͳ���Ϊɾ�����룬������ջ����ͨ��������ֻ��push��
	*/
	if(arg->isRef())arg=genAssign(arg);
	//���������Ʋ�����������ֵ���������ã�����
	//Var*newVar=new Var(symtab.getScopePath(),arg);//������������
	//symtab.addVar(newVar);//�����Ч������ռ��ջ֡����
	InterInst*argInst=new InterInst(OP_ARG,arg);//push arg!!!
	//argInst->offset=newVar->getOffset();//�������ĵ�ַ��argָ���ַ��������û���Ż���ַҲ����
	//argInst->path=symtab.getScopePath();//��¼·��������Ϊ�˼Ĵ�������ʱ�����ַ
	symtab.addInst(argInst);
}

/*
	�����������
*/
Var* GenIR::genCall(Fun*function,vector<Var*>& args)
{
	if(!function)return NULL;//ֻҪfunction��Ч�����������һ�����ͨ��
	for(int i=args.size()-1;i>=0;i--){//���򴫵�ʵ�ʲ���
		genPara(args[i]);
	}
	if(function->getType()==KW_VOID){
		//�м����fun()
		symtab.addInst(new InterInst(OP_PROC,function));
		return Var::getVoid();//����void�������
	}
	else{		
		Var*ret=new Var(symtab.getScopePath(),function->getType(),false);
		//�м����ret=fun()
		symtab.addInst(new InterInst(OP_CALL,function,ret));
		symtab.addVar(ret);//������ֵ�����ӳٵ���������֮�󣡣���
		return ret;
	}
}

/*
	˫Ŀ�������
*/
Var* GenIR::genTwoOp(Var*lval,Tag opt,Var*rval)
{
	if(!lval || !rval)return NULL;
	if(lval->isVoid()||rval->isVoid()){
		SEMERROR(EXPR_IS_VOID);//void��������ֵ���ܳ����ڱ��ʽ��
		return NULL;
	}
	//��ֵ��������
	if(opt==ASSIGN)return genAssign(lval,rval);//��ֵ
	//�ȴ���(*p)����
	if(lval->isRef())lval=genAssign(lval);
	if(rval->isRef())rval=genAssign(rval);
	if(opt==OR)return genOr(lval,rval);//��
	if(opt==AND)return genAnd(lval,rval);//��
	if(opt==EQU)return genEqu(lval,rval);//����
	if(opt==NEQU)return genNequ(lval,rval);//������
	if(opt==ADD)return genAdd(lval,rval);//��
	if(opt==SUB)return genSub(lval,rval);//��	
	if(!lval->isBase() || !rval->isBase())
	{
		SEMERROR(EXPR_NOT_BASE);//���ǻ�������
		return lval;
	}	
	if(opt==GT)return genGt(lval,rval);//����
	if(opt==GE)return genGe(lval,rval);//���ڵ���
	if(opt==LT)return genLt(lval,rval);//С��
	if(opt==LE)return genLe(lval,rval);//С�ڵ���
	if(opt==MUL)return genMul(lval,rval);//��
	if(opt==DIV)return genDiv(lval,rval);//��
	if(opt==MOD)return genMod(lval,rval);//ȡģ
	return lval;
}

/*
	��ֵ���
*/
Var* GenIR::genAssign(Var*lval,Var*rval)
{
	//����ֵ�����������ֵ
	if(!lval->getLeft()){
		SEMERROR(EXPR_NOT_LEFT_VAL);//��ֵ����
		return rval;
	}
	//���ͼ��
	if(!typeCheck(lval,rval)){
		SEMERROR(ASSIGN_TYPE_ERR);//��ֵ���Ͳ�ƥ��
		return rval;
	}
	//������ֵ(*p)
	if(rval->isRef()){
		if(!lval->isRef()){
			//�м����lval=*(rval->ptr)
			symtab.addInst(new InterInst(OP_GET,lval,rval->getPointer()));
			return lval;
		}
		else{
			//�м����*(lval->ptr)=*(rval->ptr),�ȴ�����ֵ
			rval=genAssign(rval);
		}
	}
	//��ֵ����
	if(lval->isRef()){
		//�м����*(lval->ptr)=rval
		symtab.addInst(new InterInst(OP_SET,rval,lval->getPointer()));
	}
	else{
		//�м����lval=rval
		symtab.addInst(new InterInst(OP_AS,lval,rval));
	}	
	return lval;
}

/*
	������ֵ���,����ȡ*pֵ�����
*/
Var* GenIR::genAssign(Var*val)
{
	Var*tmp=new Var(symtab.getScopePath(),val);//����������Ϣ
	symtab.addVar(tmp);
	if(val->isRef()){
		//�м����tmp=*(val->ptr)
		symtab.addInst(new InterInst(OP_GET,tmp,val->getPointer()));
	}
	else
		symtab.addInst(new InterInst(OP_AS,tmp,val));//�м����tmp=val
	return tmp;
}

/*
	���������
*/
Var* GenIR::genOr(Var*lval,Var*rval)
{
	Var*tmp=new Var(symtab.getScopePath(),KW_INT,false);//��������
	symtab.addVar(tmp);
	symtab.addInst(new InterInst(OP_OR,tmp,lval,rval));//�м����tmp=lval||rval
	return tmp;
}

/*
	���������
*/
Var* GenIR::genAnd(Var*lval,Var*rval)
{
	Var*tmp=new Var(symtab.getScopePath(),KW_INT,false);//��������
	symtab.addVar(tmp);
	symtab.addInst(new InterInst(OP_AND,tmp,lval,rval));//�м����tmp=lval&&rval
	return tmp;
}

/*
	�������
*/
Var* GenIR::genGt(Var*lval,Var*rval)
{
	Var*tmp=new Var(symtab.getScopePath(),KW_INT,false);//��������
	symtab.addVar(tmp);
	symtab.addInst(new InterInst(OP_GT,tmp,lval,rval));//�м����tmp=lval>rval
	return tmp;
}

/*
	���ڵ������
*/
Var* GenIR::genGe(Var*lval,Var*rval)
{
	Var*tmp=new Var(symtab.getScopePath(),KW_INT,false);//��������
	symtab.addVar(tmp);
	symtab.addInst(new InterInst(OP_GE,tmp,lval,rval));//�м����tmp=lval>=rval
	return tmp;
}

/*
	С�����
*/
Var* GenIR::genLt(Var*lval,Var*rval)
{
	Var*tmp=new Var(symtab.getScopePath(),KW_INT,false);//��������
	symtab.addVar(tmp);
	symtab.addInst(new InterInst(OP_LT,tmp,lval,rval));//�м����tmp=lval<rval
	return tmp;
}

/*
	С�ڵ������
*/
Var* GenIR::genLe(Var*lval,Var*rval)
{
	Var*tmp=new Var(symtab.getScopePath(),KW_INT,false);//��������
	symtab.addVar(tmp);
	symtab.addInst(new InterInst(OP_LE,tmp,lval,rval));//�м����tmp=lval<=rval
	return tmp;
}

/*
	�������
*/
Var* GenIR::genEqu(Var*lval,Var*rval)
{
	Var*tmp=new Var(symtab.getScopePath(),KW_INT,false);//��������
	symtab.addVar(tmp);
	symtab.addInst(new InterInst(OP_EQU,tmp,lval,rval));//�м����tmp=lval==rval
	return tmp;
}

/*
	���������
*/
Var* GenIR::genNequ(Var*lval,Var*rval)
{
	Var*tmp=new Var(symtab.getScopePath(),KW_INT,false);//��������
	symtab.addVar(tmp);
	symtab.addInst(new InterInst(OP_NE,tmp,lval,rval));//�м����tmp=lval!=rval
	return tmp;
}

/*
	�ӷ����
*/
Var* GenIR::genAdd(Var*lval,Var*rval)
{
	Var*tmp=NULL;
	//ָ�������ֻ�ܺͻ����������
	if((lval->getArray()||lval->getPtr())&&rval->isBase()){
		tmp=new Var(symtab.getScopePath(),lval);
		rval=genMul(rval,Var::getStep(lval));
	}
	else if(rval->isBase()&&(rval->getArray()||rval->getPtr())){
		tmp=new Var(symtab.getScopePath(),rval);
		lval=genMul(lval,Var::getStep(rval));
	}
	else if(lval->isBase() && rval->isBase()){//��������
		tmp=new Var(symtab.getScopePath(),KW_INT,false);//��������
	}
	else{
		SEMERROR(EXPR_NOT_BASE);//�ӷ����Ͳ�����
		return lval;
	}
	//�ӷ�����
	symtab.addVar(tmp);
	symtab.addInst(new InterInst(OP_ADD,tmp,lval,rval));//�м����tmp=lval+rval
	return tmp;
}

/*
	�������
*/
Var* GenIR::genSub(Var*lval,Var*rval)
{
	Var*tmp=NULL;
	if(!rval->isBase())
	{
		SEMERROR(EXPR_NOT_BASE);//���Ͳ�����,�������ǻ�������
		return lval;
	}
	//ָ�������
	if((lval->getArray()||lval->getPtr())){
		tmp=new Var(symtab.getScopePath(),lval);
		rval=genMul(rval,Var::getStep(lval));
	}
	else{//��������
		tmp=new Var(symtab.getScopePath(),KW_INT,false);//��������
	}
	//��������
	symtab.addVar(tmp);
	symtab.addInst(new InterInst(OP_SUB,tmp,lval,rval));//�м����tmp=lval-rval
	return tmp;
}

/*
	�˷����
*/
Var* GenIR::genMul(Var*lval,Var*rval)
{
	Var*tmp=new Var(symtab.getScopePath(),KW_INT,false);//��������
	symtab.addVar(tmp);
	symtab.addInst(new InterInst(OP_MUL,tmp,lval,rval));//�м����tmp=lval*rval
	return tmp;
}

/*
	�������
*/
Var* GenIR::genDiv(Var*lval,Var*rval)
{
	Var*tmp=new Var(symtab.getScopePath(),KW_INT,false);//��������
	symtab.addVar(tmp);
	symtab.addInst(new InterInst(OP_DIV,tmp,lval,rval));//�м����tmp=lval/rval
	return tmp;
}

/*
	ģ���
*/
Var* GenIR::genMod(Var*lval,Var*rval)
{
	Var*tmp=new Var(symtab.getScopePath(),KW_INT,false);//��������
	symtab.addVar(tmp);
	symtab.addInst(new InterInst(OP_MOD,tmp,lval,rval));//�м����tmp=lval%rval
	return tmp;
}

/*
	��Ŀ�������
*/
Var* GenIR::genOneOpLeft(Tag opt,Var*val)
{
	if(!val)return NULL;
	if(val->isVoid()){
		SEMERROR(EXPR_IS_VOID);//void��������ֵ���ܳ����ڱ��ʽ��
		return NULL;
	}
	//&x *p ���㵥������
	if(opt==LEA)return genLea(val);//ȡַ���
	if(opt==MUL)return genPtr(val);//ָ��ȡֵ���
	//++ --
	if(opt==INC)return genIncL(val);//���Լ����
	if(opt==DEC)return genDecL(val);//���Լ����
	//not minus ++ --
	if(val->isRef())val=genAssign(val);//����(*p)
	if(opt==NOT)return genNot(val);//not���
	if(opt==SUB)return genMinus(val);//ȡ�����
	return val;
}

/*
	ȡ��
*/
Var* GenIR::genNot(Var*val)
{
	Var*tmp=new Var(symtab.getScopePath(),KW_INT,false);//��������
	symtab.addVar(tmp);
	symtab.addInst(new InterInst(OP_NOT,tmp,val));//�м����tmp=-val
	return tmp;
}

/*
	ȡ��
*/
Var* GenIR::genMinus(Var*val)
{
	if(!val->isBase()){
		SEMERROR(EXPR_NOT_BASE);//��������ǻ�������
		return val;
	}
	Var*tmp=new Var(symtab.getScopePath(),KW_INT,false);//��������
	symtab.addVar(tmp);
	symtab.addInst(new InterInst(OP_NEG,tmp,val));//�м����tmp=-val
	return tmp;
}

/*
	���Լ�
*/
Var* GenIR::genIncL(Var*val)
{
	if(!val->getLeft()){
		SEMERROR(EXPR_NOT_LEFT_VAL);
		return val;
	}
	if(val->isRef()){//++*p��� => t1=*p t2=t1+1 *p=t2
		Var* t1=genAssign(val);//t1=*p
		Var* t2=genAdd(t1,Var::getStep(val));//t2=t1+1
		return genAssign(val,t2);//*p=t2
	}
	symtab.addInst(new InterInst(OP_ADD,val,val,Var::getStep(val)));//�м����++val
	return val;
}

/*
	���Լ�
*/
Var* GenIR::genDecL(Var*val)
{
	if(!val->getLeft()){
		SEMERROR(EXPR_NOT_LEFT_VAL);
		return val;
	}
	if(val->isRef()){//--*p��� => t1=*p t2=t1-1 *p=t2
		Var* t1=genAssign(val);//t1=*p
		Var* t2=genSub(t1,Var::getStep(val));//t2=t1-1
		return genAssign(val,t2);//*p=t2
	}
	symtab.addInst(new InterInst(OP_SUB,val,val,Var::getStep(val)));//�м����--val
	return val;
}

/*
	ȡַ���
*/
Var* GenIR::genLea(Var*val)
{
	if(!val->getLeft()){
		SEMERROR(EXPR_NOT_LEFT_VAL);//����ȡ��ַ
		return val;
	}
	if(val->isRef())//����&*p����
		return val->getPointer();//ȡ��������ָ��,&*(val->ptr)�ȼ���ptr
	else{//һ��ȡ��ַ����
		Var* tmp=new Var(symtab.getScopePath(),val->getType(),true);//�����ֲ�����tmp
		symtab.addVar(tmp);//��������
		symtab.addInst(new InterInst(OP_LEA,tmp,val));//�м����tmp=&val
		return tmp;
	}
}

/*
	ָ��ȡֵ���
*/
Var* GenIR::genPtr(Var*val)
{
	if(val->isBase()){
		SEMERROR(EXPR_IS_BASE);//�������Ͳ���ȡֵ
		return val; 
	}
	Var*tmp=new Var(symtab.getScopePath(),val->getType(),false);
	tmp->setLeft(true);//ָ��������Ϊ��ֵ
	tmp->setPointer(val);//����ָ�����
	symtab.addVar(tmp);//�������ʽ��Ҫ����ʹ�����жϣ��Ƴ٣�
	return tmp;
}

/*
	�ҵ�Ŀ�������
*/
Var* GenIR::genOneOpRight(Var*val,Tag opt)
{
	if(!val)return NULL;
	if(val->isVoid()){
		SEMERROR(EXPR_IS_VOID);//void��������ֵ���ܳ����ڱ��ʽ��
		return NULL;
	}
	if(!val->getLeft()){
		SEMERROR(EXPR_NOT_LEFT_VAL);
		return val;
	}
	if(opt==INC)return genIncR(val);//���Լ����
	if(opt==DEC)return genDecR(val);//���Լ����
	return val;
}

/*
	���Լ�
*/
Var* GenIR::genIncR(Var*val)
{
	Var*tmp=genAssign(val);//����
	symtab.addInst(new InterInst(OP_ADD,val,val,Var::getStep(val)));//�м����val++
	return tmp;
}

/*
	���Լ�
*/
Var* GenIR::genDecR(Var*val)
{
	Var*tmp=genAssign(val);//����
	symtab.addInst(new InterInst(OP_SUB,val,val,Var::getStep(val)));//val--
	return tmp;
}


/*
	��������Ƿ����ת��
*/
bool GenIR::typeCheck(Var*lval,Var*rval)
{
	bool flag=false;
	if(!rval)return false;
	if(lval->isBase()&&rval->isBase())//���ǻ�������
		flag=true;
	else if(!lval->isBase() && !rval->isBase())//�����ǻ�������
		flag=rval->getType()==lval->getType();//ֻҪ��������ͬ
	return flag;
}

/*
	����whileѭ��ͷ��
*/
void GenIR::genWhileHead(InterInst*& _while,InterInst*& _exit)
{

	// InterInst* _blank=new InterInst();//_blank��ǩ
	// symtab.addInst(new InterInst(OP_JMP,_blank));//goto _blank
	

	_while=new InterInst();//����while��ǩ
	symtab.addInst(_while);//���while��ǩ

	// symtab.addInst(_blank);//���_blank��ǩ

	_exit=new InterInst();//����exit��ǩ
	push(_while,_exit);//����while
}

/*
	����while����
*/
void GenIR::genWhileCond(Var*cond,InterInst* _exit)
{
	if(cond){
		if(cond->isVoid())cond=Var::getTrue();//����ձ��ʽ
		else if(cond->isRef())cond=genAssign(cond);//while(*p),while(a[0])
		symtab.addInst(new InterInst(OP_JF,_exit,cond));
	}
}

/*
	����whileβ��
*/
void GenIR::genWhileTail(InterInst*& _while,InterInst*& _exit)
{
	symtab.addInst(new InterInst(OP_JMP,_while));//���jmpָ��
	symtab.addInst(_exit);//���exit��ǩ
	pop();//�뿪while
}

/*
	����do-whileѭ��ͷ��
*/
void GenIR::genDoWhileHead(InterInst*& _do,InterInst*& _exit)
{
	_do=new InterInst();//����do��ǩ
	_exit=new InterInst();//����exit��ǩ
	symtab.addInst(_do);
	push(_do,_exit);//����do-while
}

/*
	����do-whileβ��
*/
void GenIR::genDoWhileTail(Var*cond,InterInst* _do,InterInst* _exit)
{
	if(cond){
		if(cond->isVoid())cond=Var::getTrue();//����ձ��ʽ
		else if(cond->isRef())cond=genAssign(cond);//while(*p),while(a[0])
		symtab.addInst(new InterInst(OP_JT,_do,cond));
	}
	symtab.addInst(_exit);
	pop();
}

/*
	����forѭ��ͷ��
*/
void GenIR::genForHead(InterInst*& _for,InterInst*& _exit)
{
	_for=new InterInst();//����for��ǩ
	_exit=new InterInst();//����exit��ǩ
	symtab.addInst(_for);
}

/*
	����for������ʼ����
*/
void GenIR::genForCondBegin(Var*cond,InterInst*& _step,InterInst*& _block,InterInst* _exit)
{
	_block=new InterInst();//����block��ǩ
	_step=new InterInst();//����ѭ��������ǩ
	if(cond){
		if(cond->isVoid())cond=Var::getTrue();//����ձ��ʽ
		else if(cond->isRef())cond=genAssign(cond);//for(*p),for(a[0])
		symtab.addInst(new InterInst(OP_JF,_exit,cond));
		symtab.addInst(new InterInst(OP_JMP,_block));//ִ��ѭ����
	}
	symtab.addInst(_step);//���ѭ��������ǩ
	push(_step,_exit);//����for
}

/*
	����for������������
*/
void GenIR::genForCondEnd(InterInst* _for,InterInst* _block)
{
	symtab.addInst(new InterInst(OP_JMP,_for));//����ѭ��
	symtab.addInst(_block);//���ѭ�����ǩ
}

/*
	����forβ��
*/
void GenIR::genForTail(InterInst*& _step,InterInst*& _exit)
{
	symtab.addInst(new InterInst(OP_JMP,_step));//��ת��ѭ������
	symtab.addInst(_exit);//���_exit��ǩ
	pop();//�뿪for
}

/*
	����ifͷ��
*/
void GenIR::genIfHead(Var*cond,InterInst*& _else)
{
	_else=new InterInst();//����else��ǩ
	if(cond){
		if(cond->isRef())cond=genAssign(cond);//if(*p),if(a[0])
		symtab.addInst(new InterInst(OP_JF,_else,cond));
	}
}

/*
	����ifβ��
*/
void GenIR::genIfTail(InterInst*& _else)
{
	symtab.addInst(_else);
}

/*
	����elseͷ��
*/
void GenIR::genElseHead(InterInst* _else,InterInst*& _exit)
{
	_exit=new InterInst();//����exit��ǩ
	symtab.addInst(new InterInst(OP_JMP,_exit));
	symtab.addInst(_else);
}

/*
	����elseβ��
*/
void GenIR::genElseTail(InterInst*& _exit)
{
	symtab.addInst(_exit);
}

/*
	����switchͷ��
*/
void GenIR::genSwitchHead(InterInst*& _exit)
{
	_exit=new InterInst();//����exit��ǩ
	push(NULL,_exit);//����switch��������continue�����head=NULL
}

/*
	����switchβ��
*/
void GenIR::genSwitchTail(InterInst* _exit)
{
	symtab.addInst(_exit);//���exit��ǩ
	pop();
}

/*
	����caseͷ��
*/
void GenIR::genCaseHead(Var*cond,Var*lb,InterInst*& _case_exit)
{
	_case_exit=new InterInst();//����case��exit��ǩ
	if(lb)symtab.addInst(new InterInst(OP_JNE,_case_exit,cond,lb));//if(cond!=lb)goto _case_exit
}

/*
	����caseβ��
*/
void GenIR::genCaseTail(InterInst* _case_exit)
{
	symtab.addInst(_case_exit);//���case��exit��ǩ
	// InterInst * _case_exit_append=new InterInst();//����case��exit���ӱ�ǩ
	// symtab.addInst(new InterInst(OP_JMP,_case_exit_append));//goto _case_exit_append
	// symtab.addInst(_case_exit);//���case��exit��ǩ
	// symtab.addInst(_case_exit_append);//���case��exit���ӱ�ǩ
}

/*
	���һ��������
*/
void GenIR::push(InterInst*head,InterInst*tail)
{
	heads.push_back(head);
	tails.push_back(tail);
}

/*
	ɾ��һ��������
*/
void GenIR::pop()
{
	heads.pop_back();
	tails.pop_back();
}

/*
	����break���
*/
void GenIR::genBreak()
{
	InterInst*tail=tails.back();//ȡ��������ǩ
	if(tail)symtab.addInst(new InterInst(OP_JMP,tail));//goto tail
	else SEMERROR(BREAK_ERR);//break����ѭ����switch-case��
}

/*
	����continue���
*/
void GenIR::genContinue()
{
	InterInst*head=heads.back();//ȡ��������ǩ
	if(head)symtab.addInst(new InterInst(OP_JMP,head));//goto head
	else SEMERROR(CONTINUE_ERR);//continue����ѭ����
}

/*
	����return���
*/
void GenIR::genReturn(Var*ret)
{
	if(!ret)return;
	Fun*fun=symtab.getCurFun();
	if(ret->isVoid()&&fun->getType()!=KW_VOID||ret->isBase()&&fun->getType()==KW_VOID){//���Ͳ�����
		SEMERROR(RETURN_ERR);//return���ͺ�������ֵ���Ͳ�ƥ��
		return;
	}
	InterInst* returnPoint=fun->getReturnPoint();//��ȡ���ص�
	if(ret->isVoid())symtab.addInst(new InterInst(OP_RET,returnPoint));//return returnPoint
	else{
		if(ret->isRef())ret=genAssign(ret);//����ret��*p���
		symtab.addInst(new InterInst(OP_RETV,returnPoint,ret));//return returnPoint ret
	}
}

/*
	����������ʼ�����
*/
bool GenIR::genVarInit(Var*var)
{
	if(var->getName()[0]=='<')return 0;
	symtab.addInst(new InterInst(OP_DEC,var));//��ӱ�������ָ��
	if(var->setInit())//��ʼ�����
		genTwoOp(var,ASSIGN,var->getInitData());//������ֵ���ʽ��� name=init->name
	return 1;
}

/*
	��������������
*/
void GenIR::genFunHead(Fun*function)
{
	function->enterScope();//���뺯��������
	symtab.addInst(new InterInst(OP_ENTRY,function));//��Ӻ������ָ��
	function->setReturnPoint(new InterInst);//���������ķ��ص�
}

/*
	���������������
*/
void GenIR::genFunTail(Fun*function)
{
	symtab.addInst(function->getReturnPoint());//��Ӻ������ص㣬return��Ŀ�ı��
	symtab.addInst(new InterInst(OP_EXIT,function));//��Ӻ�������ָ��
	function->leaveScope();//�˳�����������
}
