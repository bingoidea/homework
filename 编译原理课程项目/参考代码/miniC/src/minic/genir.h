#pragma once 
#include "common.h"
/*
	�м����������
*/
class GenIR
{
	static int lbNum;//��ǩ���룬���ڲ���Ψһ�ı�ǩ
	
	SymTab &symtab;//���ű�
	
	//break continue������ǩ�б�
	vector< InterInst* > heads;
	vector< InterInst* > tails;
	void push(InterInst*head,InterInst*tail);//���һ��������
	void pop();//ɾ��һ��������
	
	
	//��������
	void genPara(Var*arg);//�����������
	
	//˫Ŀ����
	Var* genAssign(Var*lval,Var*rval);//��ֵ���
	
	Var* genOr(Var*lval,Var*rval);//���������
	Var* genAnd(Var*lval,Var*rval);//���������
	Var* genGt(Var*lval,Var*rval);//�������
	Var* genGe(Var*lval,Var*rval);//���ڵ������
	Var* genLt(Var*lval,Var*rval);//С�����
	Var* genLe(Var*lval,Var*rval);//С�ڵ������
	Var* genEqu(Var*lval,Var*rval);//�������
	Var* genNequ(Var*lval,Var*rval);//���������
	Var* genAdd(Var*lval,Var*rval);//�ӷ����
	Var* genSub(Var*lval,Var*rval);//�������
	Var* genMul(Var*lval,Var*rval);//�˷����
	Var* genDiv(Var*lval,Var*rval);//�������
	Var* genMod(Var*lval,Var*rval);//ȡģ
	
	//��Ŀ����
	Var* genNot(Var*val);//��
	Var* genMinus(Var*val);//��
	Var* genIncL(Var*val);//���Լ����
	Var* genDecL(Var*val);//���Լ����
	Var* genLea(Var*val);//ȡַ���
	Var* genPtr(Var*val);//ָ��ȡֵ���	
	Var* genIncR(Var*val);//���Լ����
	Var* genDecR(Var*val);//���Լ�
	
public:

	GenIR(SymTab &tab);//�����ڲ�����

	Var* genAssign(Var*val);//����������ֵ������ָ����ֵ���úͱ�������
	
	//�������ź����
	Var* genArray(Var*array,Var*index);//�����������
	Var* genCall(Fun*function,vector<Var*> & args);//�����������
	Var* genTwoOp(Var*lval,Tag opt,Var*rval);//˫Ŀ�������	
	Var* genOneOpLeft(Tag opt,Var*val);//��Ŀ�������	
	Var* genOneOpRight(Var*val,Tag opt);//�ҵ�Ŀ�������
	
	//�����������
	void genWhileHead(InterInst*& _while,InterInst*& _exit);//whileѭ��ͷ��
	void genWhileCond(Var*cond,InterInst* _exit);//while����
	void genWhileTail(InterInst*& _while,InterInst*& _exit);//whileβ��
	void genDoWhileHead(InterInst*& _do,InterInst*& _exit);//do-whileͷ��
	void genDoWhileTail(Var*cond,InterInst* _do,InterInst* _exit);//do-whileβ��
	void genForHead(InterInst*& _for,InterInst*& _exit);//forѭ��ͷ��
	void genForCondBegin(Var*cond,InterInst*& _step,InterInst*& _block,InterInst* _exit);//for������ʼ
	void genForCondEnd(InterInst* _for,InterInst* _block);//forѭ��������������
	void genForTail(InterInst*& _step,InterInst*& _exit);//forѭ��β��
	void genIfHead(Var*cond,InterInst*& _else);//ifͷ��
	void genIfTail(InterInst*& _else);//ifβ��
	void genElseHead(InterInst* _else,InterInst*& _exit);//elseͷ��
	void genElseTail(InterInst*& _exit);//elseβ��
	void genSwitchHead(InterInst*& _exit);//switchͷ��
	void genSwitchTail(InterInst* _exit);//switchβ��
	void genCaseHead(Var*cond,Var*lb,InterInst*& _case_exit);//caseͷ��
	void genCaseTail(InterInst* _case_exit);//caseβ��	
	
	//�����������
	void genBreak();//����break���
	void genContinue();//����continue���
	void genReturn(Var*ret);//����return���
	bool genVarInit(Var*var);//����������ʼ�����
	void genFunHead(Fun*function);//��������������
	void genFunTail(Fun*function);//���������������
	
	//ȫ�ֺ���
	static string genLb();//����Ψһ�ı�ǩ	
	static bool typeCheck(Var*lval,Var*rval);//��������Ƿ����ת��
};

