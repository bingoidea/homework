#pragma once
#include "common.h"
#include "set.h"
/*
	��Ծ�����������������
*/
class LiveVar
{
	SymTab* tab;//���ű�
	DFG*dfg;//������ͼָ��
	//bool direct;//���������ⷽ������
	list<InterInst*>optCode;//��¼ǰ��׶��Ż���Ĵ���
	vector<Var*>varList;//�����б�
	Set U;//ȫ��
	Set E;//�ռ�
	Set G;//ȫ�ֱ�����
	bool translate(Block*block);//��Ծ�������ݺ���
public:
	void analyse();//��Ծ��������������
	LiveVar(DFG*g,SymTab*t,vector<Var*>&paraVar);//���캯��
	void elimateDeadCode(int stop=false);//����������
	Set& getE();//���ؿռ�
	vector<Var*> getCoVar(Set liveout);//�����ṩ��liveout������ȡ�Ż���ı������ϡ�����ͻ����
};
