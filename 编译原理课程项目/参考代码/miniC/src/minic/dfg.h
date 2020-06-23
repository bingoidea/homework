#pragma once
#include"common.h"
#include"set.h"

/*
	��������
*/
class Block
{

public:
	
	//������Ϣ�͹�ϵ
	list<InterInst*> insts;//�������ָ������
	list<Block*>prevs;//�������ǰ������
	list<Block*>succs;//������ĺ������
	bool visited;//���ʱ��
	bool canReach;//��ɴ���,���ɴ�鲻��Ϊ�������������

	//������������Ϣ
	vector<double> inVals;//������������ֵ����
	vector<double> outVals;//�����������ֵ����
	RedundInfo info;//����ɾ����������Ϣ
	CopyInfo copyInfo;//��д������������Ϣ
	LiveInfo liveInfo;//��Ծ������������Ϣ
	
	//�������ʼ��
	Block(vector<InterInst*>&codes);

	//�ⲿ���ýӿ�
	void toString();//���������ָ��
};

/*
	������ͼ��
*/
class DFG
{
	void createBlocks();//����������
	void linkBlocks();//���ӻ�����

	void resetVisit();//���÷��ʱ��
	bool reachable(Block*block);//���Կ��Ƿ�ɴ�
	void release(Block*block);//����鲻�ɴ��ɾ�����к�̣��������������к��


public:

	vector<InterInst*> codeList;//�м��������
	vector<Block*>blocks;//��ͼ�����л�����
	vector<InterInst*> newCode;//�Ż����ɵ��м�������У��ڴ����

	//�������ʼ��
	DFG(InterCode&code);//��ʼ��
	~DFG();//�������
	void delLink(Block*begin,Block*end);//ɾ�������ϵ������鲻�ɴ��ɾ�����к����ϵ

	//����ʵ��
	void toCode(list<InterInst*>& opt);//����������ͼΪ�м����

	//�ⲿ���ýӿ�
	void toString();//���������
};



