#pragma once
#include "common.h"
#include "set.h"

/*
	���ʽ����
*/
class Expr
{
	Var* newRs;//�µĽ������
	Var* rs;//�����������Ϊ�����½�������Ĳο�
	Var* genResult(SymTab*tab);//�������ؽ��
public:
	Operator op;//������
	Var*arg1;//������1
	Var*arg2;//������2
	int index;//����λ��
	InterInst* genInst(SymTab*tab,DFG*dfg);//��������ָ��
	InterInst* genDec(DFG*dfg);//��������ָ��
	Var* getNewRs();//��ȡ���ʽ����ʱ������������뱣֤�Ѿ��ڴ�������ʱ�����˽����
	Expr(Var*r,Operator o,Var*a1,Var*a2);
	bool operator==(Expr&e);
	bool use(Var*v);
};

/*
	�ֲ����������㷨
*/
class RedundElim
{
	//������Ϣ
	SymTab*symtab;//���ű�ָ��
	DFG*dfg;//������ͼָ��
	list<InterInst*>optCode;//��¼ǰ��׶��Ż���Ĵ���

	//���ʽ��Ϣ
	vector<Expr>exprList;//���еı��ʽ
	Set U;//ȫ��
	Set E;//�ռ�
	Set BU;//��ȫ��
	Set BE;//��ռ�
	int findExpr(Expr&e);//��ѯ���ʽλ��

	//��������������
	bool translate_anticipated(Block*block);//��Ԥ��ִ�б��ʽ���ݺ���
	bool translate_available(Block*block);//���ñ��ʽ���ݺ���
	bool translate_postponable(Block*block);//�ɺ��ӱ��ʽ���ݺ���
	bool translate_used(Block*block);//��ʹ�ñ��ʽ���ݺ���
	bool translate_dom(Block*block);//֧��ڵ㴫�ݺ���
	void analyse_anticipated();//��Ԥ��ִ�б��ʽ����������
	void analyse_available();//���ñ��ʽ����������
	void analyse_postponable();//�ɺ��ӱ��ʽ����������
	void analyse_used();//��ʹ�ñ��ʽ����������
	void analyse_dom();//֧��ڵ�����������

public:

	//�������ʼ��
	RedundElim(DFG*g,SymTab*tab);
	void elimate();//��������
};

