#pragma once
#include"common.h"
#include "set.h"

/*
	�ײ���ָ�x86��ʽ
*/
struct x86
{
	bool dead;//��ʶ�����Ƿ���Ч
	string opcode;//������
	string result;//���
	string arg1;//������1
	string arg2;//������2
	string addition;//������Ϣ
	x86(string op,string rs="",string a1="",string a2="",string add="");
	void replace(string op,string rs="",string a1="",string a2="",string add="");
	void setDead();//������Ч
	string outPut();//�������
};

/*
	�ײ�������
*/
class ILoc
{
	list<x86*> code;//��������
	/*
		�������ַ������
	*/
	string toStr(int num,int flag=true);//#123
	/*
		ldr str
	*/
	void ldr_imm(string rsReg,int num);//���������� ldr r0,=#100
	void ldr_lb(string rsReg,string name);//���ط���ֵ ldr r0,=g ldr r0,[r0]
	void leaStack(string rsReg,int off);//����ջ�ڱ�����ַ
public:
	//��ַѰַ ldr r0,[fp,#100]
	void ldr_base(string rsReg,string base,int disp,bool isChar);
	//��ַѰַ str r0,[fp,#100]
	void str_base(string srcReg,string base,int disp,string tmpReg,bool isChar);
	/*
		label ע�� һ��ָ��
	*/
	void label(string name);//������ǩ
	void comment(string str);//����ע��
	void inst(string op);
	void inst(string op,string rs);//0��������
	void inst(string op,string rs,string arg1);//һ��������
	void inst(string op,string rs,string arg1,string arg2);//����������
	/*
		��������
	*/
	void init_var(Var*var,string initReg,string tmpReg);//�����ĳ�ʼ��
	void ldr_var(string rsReg,Var*var);//���ر������Ĵ���
	void lea_var(string rsReg,Var*var);//���ر�����ַ���Ĵ���
	void str_var(string srcReg,Var*var,string addrReg);//����Ĵ���������
	/*
		��������
	*/
	void call_lib(string fun,string rsReg,string reg1,string reg2);//���ÿ⺯��
	void call_fun(Fun*fun,string tmpReg);//���ú���fun
	/*
		ջ����
	*/
	void allocStack(Fun*fun,string tmpReg);//����ջ֡
	void ldr_args(Fun*fun);//���غ����Ĳ������Ĵ���
	/*
		�߼�����
	*/
	void logic_and(string rsReg,string reg1,string reg2);//�߼���
	void logic_or(string rsReg,string reg1,string reg2);//�߼���
	void logic_not(string rsReg,string reg1);//�߼���
	void cmp(string cmp,string cmpnot,string rsReg,string reg1,string reg2);//�Ƚ�
	/*
		ռλָ�����������Ż����Է������޷���ȷ��ֵ
	*/
	void nop();//ռλ
	/*
		���ܺ���
	*/
	void outPut(FILE*file);//������
	list<x86*>& getCode();//��ȡ����
	~ILoc();
};



