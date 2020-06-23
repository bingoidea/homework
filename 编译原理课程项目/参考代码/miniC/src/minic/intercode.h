#pragma once
#include "common.h"
#include "set.h"

/*
	��Ԫʽ�࣬�������м�����ָ�����ʽ
*/
class InterInst
{
private:
	string label;//��ǩ
	Operator op;//������
	//union{
	Var *result;//������
	InterInst*target;//��ת���
	//};
	//union{
	Var*arg1;//����1
	Fun*fun;//����
	//};
	Var *arg2;//����2

	bool first;//�Ƿ�����ָ��
	void init();//��ʼ��

public:	

	//��ʼ��
	Block*block;//ָ�����ڵĻ�����ָ��

	//��������Ϣ
	vector<double>inVals;//��������in����
	vector<double>outVals;//��������out����
	Set e_use;//ʹ�õı��ʽ����
	Set e_kill;//ɱ���ı��ʽ����
	RedundInfo info;//����ɾ����������Ϣ
	CopyInfo copyInfo;//��д������������Ϣ
	LiveInfo liveInfo;//��Ծ������������Ϣ
	bool isDead;//��ʶָ���Ƿ���������

	//������ͨ����������ͨ��push��ջ
	//ָ���ڵ�������·��
	//vector<int>path;//���ֶ�ΪARGָ��׼����ARG�Ĳ�����������ARG��λ�ã����������ǳ���������
	//int offset;//������ջ֡ƫ��
	
	//����
	InterInst (Operator op,Var *rs,Var *arg1,Var *arg2=NULL);//һ������ָ��
	InterInst (Operator op,Fun *fun,Var *rs=NULL);//��������ָ��,ENTRY,EXIT
	InterInst (Operator op,Var *arg1=NULL);//������ջָ��,NOP
	InterInst ();//����Ψһ���
	InterInst (Operator op,InterInst *tar,Var *arg1=NULL,Var *arg2=NULL);//������תָ��,return
	void replace(Operator op,Var *rs,Var *arg1,Var *arg2=NULL);//�滻���ʽָ����Ϣ�����ڳ������ʽ����
	void replace(Operator op,InterInst *tar,Var *arg1=NULL,Var *arg2=NULL);//�滻��תָ����Ϣ��������ת�Ż�
	~InterInst();//�������ڴ�
	
	//�ⲿ���ýӿ�
	void setFirst();//�����ָ��
	
	bool isJcond();//�Ƿ�����ת��ָ��JT,JF,Jcond
	bool isJmp();//�Ƿ�ֱ��ת��ָ��JMP,return
	bool isFirst();//����ָ��
	bool isLb();//�Ƿ��Ǳ�ǩ
	bool isDec();//�Ƿ�������
	bool isExpr();//�ǻ������ͱ��ʽ����,���Զ�ָ��ȡֵ
	bool unknown();//��ȷ��������Ӱ�������(ָ�븳ֵ����������)
	
	Operator getOp();//��ȡ������
	void callToProc();//�滻�����������ڽ�CALLת��ΪPROC
	InterInst* getTarget();//��ȡ��תָ���Ŀ��ָ��
	Var* getResult();//��ȡ����ֵ
	Var* getArg1();//��ȡ��һ������
	Var* getArg2();//��ȡ�ڶ�������
	string getLabel();//��ȡ��ǩ
	Fun* getFun();//��ȡ��������
	void setArg1(Var*arg1);//���õ�һ������
	void toString();//���ָ��
};

/*
	�м����
*/
class InterCode
{
	vector<InterInst*>code;

public:
	//�ڴ����
	~InterCode();//����ڴ�
	
	//�������
	void addInst(InterInst*inst);//���һ���м����
	
	//�ؼ�����
	void markFirst();//��ʶ����ָ�

	//�ⲿ���ýӿ�
	void toString();//���ָ��
	vector<InterInst*>& getCode();//��ȡ�м��������
};

