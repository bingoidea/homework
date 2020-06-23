#pragma once

#include "common.h"
#include "intercode.h"
#include "set.h"

/*******************************************************************************
                                   �����ṹ��
*******************************************************************************/

class Var
{
	//������
	bool literal;//�Ƿ�������,���������Գ�ʼ������ı���
	vector<int>scopePath;//������·��
	
	//����������ʽ
	bool externed;//extern��������
	Tag type;//��������
	string name;//��������
	bool isPtr;//�Ƿ���ָ��
	bool isArray;//�Ƿ�������
	int arraySize;//���鳤��
	
	//��ʼֵ����
	bool isLeft;//�Ƿ������Ϊ��ֵ
	Var* initData;//�����ֵ���ݣ��ӳٴ��ô���
	bool inited;//�Ƿ��ʼ�����ݣ�������һ���ǳ�ʼ���˵��������
	union{
		int intVal;
		char charVal;
	};
	string ptrVal;//��ʼ���ַ�ָ�볣���ַ���������
	string strVal;//�ַ���������ֵ
	Var*ptr;//ָ��ǰ����ָ�����
	
	//������Ϣ
	int size;//�����Ĵ�С
	int offset;//�ֲ�����������������ջ֡ƫ�ƣ�Ĭ��ֵ0Ϊ��Чֵ������ʾȫ�ֱ���

	//�ڲ�ʹ�ú���
	void setExtern(bool ext);//����extern
	void setType(Tag t);//��������
	void setPtr(bool ptr);//����ָ��
	void setName(string n);//��������
	void setArray(int len);//�趨����
	void clear();//����ؼ��ֶ���Ϣ

public:

	//�������1,4-����
	static Var*getStep(Var* v);//��ȡ��������
	static Var*getVoid();//��ȡvoid�������
	static Var*getTrue();//��ȡtrue����
	
	//���캯��
	Var(vector<int>&sp,bool ext,Tag t,bool ptr,string name,Var*init=NULL);//����
	Var(vector<int>&sp,bool ext,Tag t,string name,int len);//����
	Var(Token*lt);//�趨������
	Var(int val);//��������
	Var(vector<int>&sp,Tag t,bool ptr);//��ʱ����
	Var(vector<int>&sp,Var*v);//��������
	Var();//void����

	//�����ýӿ�
	bool setInit();//�趨��ʼ�����ɵ����߾�����ʼ����ʽ��˳��
	Var* getInitData();//��ȡ��ʼ����������
	vector<int>& getPath();//��ȡscopePath
	bool getExtern();//��ȡextern
	Tag getType();//��ȡ����
	bool isChar();//�ж��Ƿ����ַ�����
	bool isCharPtr();//�ж��ַ�ָ��
	bool getPtr();//��ȡָ��
	bool getArray();//��ȡ����	
	string getName();//��ȡ����
	string getPtrVal();//��ȡָ�����
	string getRawStr();//��ȡԭʼ�ַ���ֵ
	Var* getPointer();//��ȡָ��
	void setPointer(Var* p);//����ָ�����
	string getStrVal();//��ȡ�ַ�����������
	void setLeft(bool lf);//���ñ�������ֵ����
	bool getLeft();//��ȡ��ֵ����
	void setOffset(int off);//����ջ֡ƫ��
	int getOffset();//��ȡջ֡ƫ��
	int getSize();//��ȡ������С
	void toString();//�����Ϣ
	void value();//����������м������ʽ
	bool isVoid();//��void����Ψһ��̬�洢������getVoid()ʹ��
	bool isBase();//�ǻ�������
	bool isRef();//����������	
	bool isLiteral();//�ǻ������ͳ������ַ������⣩��û�д洢�ڷ��ű���Ҫ�����ڴ����

	//�����������ӿ�
	int index;//�б�����
	bool unInit();//�Ƿ��ʼ��
	bool notConst();//�Ƿ��ǳ���
	int getVal();//��ȡ����ֵ
	bool live;//��¼�����Ļ�Ծ��

	//�Ĵ���������Ϣ
	int regId;//����ļĴ�����ţ�-1��ʾ���ڴ棬ƫ�Ƶ�ַΪoffset!!!
	bool inMem;//��ȡ��ַ�ı����ı�ǣ�������Ĵ�����
};


/*******************************************************************************
                                   �����ṹ
*******************************************************************************/

class Fun
{	
	//������Ϣ
	bool externed;//��������
	Tag type;//��������
	string name;//��������
	vector<Var*>paraVar;//�βα����б�
	
	//��ʱ������ַ����
	int maxDepth;//ջ�������ȣ���ʼ0,��ʶ����ջ��������ռ�
	int curEsp;//��ǰջָ��λ�ã���ʼ��Ϊ0����ebp�洢��
	bool relocated;//ջ֡�ض�λ���
	
	//���������
	vector<int>scopeEsp;//��ǰ�������ʼesp����̬����������ķ�����ͷ�
	InterCode interCode;//�м����
	InterInst* returnPoint;//���ص�
	DFG* dfg;//������ͼָ��
	list<InterInst*> optCode;//�Ż�����м����
	
public:
	
	//���캯������������
	Fun (bool ext,Tag t,string n,vector<Var*>&paraList);
	~Fun();
	
	//����������ʹ��
	bool match(Fun*f);//��������ƥ��
	bool match(vector<Var*>&args);//�в�ʵ��ƥ��
	void define(Fun*def);//����������ת��Ϊ���壬��Ҫ���������б��趨extern
	
	//����������ֲ�������ַ����
	void enterScope();//����һ���µ�������
	void leaveScope();//�뿪��ǰ������
	void locate(Var*var);//��λ�ֲ�����ջ֡ƫ��
	
	//�м����
	void addInst(InterInst*inst);//���һ���м����
	void setReturnPoint(InterInst*inst);//���ú������ص�
	InterInst* getReturnPoint();//��ȡ�������ص�
	int getMaxDep();//��ȡ���ջ֡���
	void setMaxDep(int dep);//�������ջ֡���
	void optimize(SymTab*tab);//ִ���Ż�����
	
	//�ⲿ���õ���
	bool getExtern();//��ȡextern
	void setExtern(bool ext);//����extern
	Tag getType();//��ȡ��������
	string& getName();//��ȡ����
	bool isRelocated();//ջ֡�ض�λ�ˣ�
	vector<Var*>& getParaVar();//��ȡ�����б�����Ϊ�������ɼ��ش���
	void toString();//�����Ϣ
	void printInterCode();//����м����
	void printOptCode();//����Ż�����м����
	void genAsm(FILE*file);//���������
};
