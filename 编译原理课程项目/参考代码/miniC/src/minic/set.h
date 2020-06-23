#pragma once
#include"common.h" 

/*
	�����ࡪ��ʹ��λͼ��Ｏ������
*/
class Set
{
	vector<unsigned int>bmList;//λͼ�б�λͼ���ȴ���32ʱ

public:
	int count;//��¼����Ԫ�ظ���

	//�������ʼ��
	Set();
	Set(int size,bool val);//����һ������size��Ԫ�صļ��ϣ�����ʼ��
	void init(int size,bool val);
	void p();//�����������

	//���ϻ�������
	Set operator &(Set val);//��������
	Set operator |(Set val);//��������
	Set operator -(Set val);//�����
	Set operator ^(Set val);//�������
	Set operator ~();//��������
	bool operator ==(Set& val);//�Ƚ�����
	bool operator !=(Set& val);//�Ƚ�����
	bool get(int i);//��������
	void set(int i);//��λ����
	void reset(int i);//��λ����
	int max();//�������λ��1������
	bool empty()
	{
		return bmList.size()==0;
	}
};


/*
	������������Ϣ
*/
struct TransInfo
{
	Set in;//���뼯��
	Set out;//�������
};

/*
	����������������Ϣ
*/
struct RedundInfo
{
	TransInfo anticipated;//��Ԥ��ִ�б��ʽ����
	TransInfo available;//���ñ��ʽ����
	TransInfo postponable;//�ɺ��ӱ��ʽ����
	TransInfo used;//��ʹ�ñ��ʽ����
	Set earliest;//��ǰ���ñ��ʽ���ϣ�earliest(B)=anticipated(B).in-available(B).in
	Set latest;//�����ñ��ʽ���ϣ�latest(B)=(earliest(B) | postponable(B).in) &
						 //	(e_use(B) | ~(&( earliest(B.succ[i]) | postponable(B.succ[i]).in )))
	TransInfo dom;//�������ǰ������
	int index;//�����������
};

/*
	��д��������������Ϣ
*/
struct CopyInfo
{
	Set in;//���뼯��
	Set out;//�������
	Set gen;//������д���ʽ����
	Set kill;//ɱ����д���ʽ����
};

/*
	��Ծ��������������Ϣ
*/
struct LiveInfo
{
	Set in;//���뼯��
	Set out;//�������
	Set use;//ʹ�ñ������ϡ���������ʹ�����붨ֵ
	Set def;//��ֵ�������ϡ��������Ķ�ֵ����ʹ��
};