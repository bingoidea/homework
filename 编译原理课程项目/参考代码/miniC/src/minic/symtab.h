#pragma once
#include "common.h"
#include <ext/hash_map>
using namespace __gnu_cxx;
/*
	���ű�
*/
class SymTab
{
	//����˳���¼
	vector<string>varList;//��¼���������˳��
	vector<string>funList;//��¼���������˳��
	
	//hash����
	struct string_hash{
		size_t operator()(const string& str) const{
			return __stl_hash_string(str.c_str());
		}
	};
	//�ڲ����ݽṹ
	hash_map<string, vector< Var* > *, string_hash> varTab;//������,ÿ��Ԫ����ͬ������������
	hash_map<string, Var*, string_hash> strTab;//�ַ���������
	hash_map<string, Fun*, string_hash> funTab;//������,ȥ��������������
	
	//�����������ݼ�¼
	Fun*curFun;//��ǰ�����ĺ���
	int scopeId;//������Ψһ���
	vector<int>scopePath;//��̬��¼�������·����ȫ��Ϊ0,0 1 2-��һ�������ĵ�һ���ֲ���

	//�м����������
	GenIR* ir;
  
public:

	static Var* voidVar;//�������
	static Var* zero;//�������
	static Var* one;//�������
	static Var* four;//�������

	SymTab();//��ʼ�����ű�
	~SymTab();//����ڴ�
	
	//���ű����������
	void enter();//����ֲ�������
	void leave();//�뿪�ֲ�������
	
	//��������
	void addVar(Var* v);//���һ������
	void addStr(Var* v);//���һ���ַ�������
	Var* getVar(string name);//��ȡһ������
	vector<Var*> getGlbVars();//��ȡ����ȫ�ֱ���
	
	//��������
	void decFun(Fun*fun);//����һ������
	void defFun(Fun*fun);//����һ������
	void endDefFun();//��������һ������
	Fun* getFun(string name,vector<Var*>& args);//���ݵ������ͣ���ȡһ������
	void addInst(InterInst*inst);//���һ���м����
	
	//�ⲿ���ýӿ�
	void setIr(GenIR*ir);//�����м����������
	vector<int>& getScopePath();//��ȡscopePath
	Fun*getCurFun();//��ȡ��ǰ�����ĺ���
	void toString();//�����Ϣ
	void printInterCode();//����м�ָ��
	void optimize();//ִ���Ż�����
	void printOptCode();//����м�ָ��
	void genData(FILE*file);//�������
	void genAsm(char*fileName);//�������ļ�
};
























