#pragma once
#include "common.h"
#include "set.h"
/*******************************************************************************
                            Ϊ��������Ĵ�������ջ֡ƫ��
*******************************************************************************/

/*
	��ͻͼ�ڵ�����
*/
struct Node
{
	Var*var;//�ڵ��Ӧ�ı���
	int degree;//�ڵ�Ķȣ����ٽڵ�ߵĸ�����Ϊͼ��ɫ�㷨�ṩѡ������
	int color;//�ڵ���ɫ����var->regId��Ӧ��-1Ϊ��Чֵ���޷�/������ɫ��
	Set exColors;//�ڵ��ų����ɫ���������ڽڵ���ͬɫ���䲹���е�һ����ЧԪ��Ϊcolor��
	vector<Node*> links;//�ڵ�����ӱߣ�����������룬ʹ�ö��ֲ����Ƿ���������ھ�
	Node(Var*v,Set& E);//����v��Ӧ�Ľڵ㣬��ʼ��
	void addLink(Node*node);//���һ���ߣ�������룬��+1����֤���ֲ���
	void addExColor(int color);//���һ���ų�ɫ
	void paint(Set& colorBox);//����exColorsѡ���һ����Ч����ɫ����=-1
};

/*
	����������
*/
struct Scope
{
	struct scope_less
	{
		bool operator()(Scope*left,Scope*right){
			return left->id<right->id;//����idȷ���ڵ��С
		}
	};
	int id;
	int esp;
	vector<Scope*> children;//��������
	Scope(int i,int addr);
	~Scope();
	Scope* find(int i);//����i�����򣬲����������һ����������id=i��esp�̳е�ǰ��esp
	//�����Ϣ���ƣ�|--��ʼλ��
	int x;//��λ�ã�ʵ��δ�õ�
	int y;//��λ��
	Scope*parent;//��¼���׽ڵ�
};

/*
	��ͻͼ����
*/
class CoGraph
{
	struct node_less
	{
		bool operator()(Node*left,Node*right){
			return left->degree<=right->degree;//���ն�ȷ���ڵ��С,���ϸ�С�ڣ���������ƶ�����
		}
	};
	list<InterInst*> optCode;//�м����
	LiveVar* lv;//��Ծ������������ʹ�øö����ṩ���϶�Ӧ�ı�����Ϣ
	vector<Node*> nodes;//ͼ�ڵ����飬ͼ��ɫѡ�����Ƚڵ�ʱ��ʹ�ö�����
	vector<Var*>varList;//�����б�����������Ҫ����ı���
	Set U;//��ɫ����ȫ��
	Set E;//��ɫ���Ͽռ�
	Scope* scRoot;//��������ָ��
	Fun* fun;//��������
	Node* pickNode();//ѡ�������δ����ڵ㣬�������Ѹ��ݽڵ�ȶ�����
	void regAlloc();//�Ĵ�������ͼ��ɫ�㷨,��regNum���Ĵ�����ɫ��ͼ��
	int& getEsp(vector<int>& path);//���ݵ�ǰ������������·����ȡջ֡ƫ�Ƶ�ַ
	void stackAlloc();//Ϊ������ɫ�ı�������ջ֡��ַ
	void __printTree(Scope*root,int blk,int x,int& y);//�������������
	void printTree(Scope*root,bool tree_style=true);//��װ�ĺ���
public:
	//�����б��ֲ�����DEC�����������б�����Node�� 
	//�����������������ڼĴ����ڣ���Ҫ�ں�����ʼ�����loadָ��
	//ȫ�ֱ��������Ĵ����Ż�������
	CoGraph(list<InterInst*>&optCode,vector<Var*>&para,LiveVar*lv,Fun*f);
	~CoGraph();
	void alloc();//�����㷨
};