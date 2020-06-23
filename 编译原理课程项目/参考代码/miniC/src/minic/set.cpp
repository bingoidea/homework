#include "set.h"

/*
	���캯��
*/
Set::Set()
{
	count=0;
}

Set::Set(int size,bool val)
{
	init(size,val);
}

/*
	����һ������size��Ԫ�صļ��ϣ�����ʼ��
*/
void Set::init(int size,bool val)
{
	count=size;//��¼��С
	size=size/32+(size%32!=0);//������Ҫ���ٸ�32λλͼ
	unsigned int v=val?0xffffffff:0;
	for(int i=0;i<size;i++)bmList.push_back(v);//��ʼ��λͼ
}

/*
	��������
*/
Set Set::operator &(Set val)
{
	Set ret(count,0);
	for(unsigned int i=0;i<bmList.size();i++)
	{
		ret.bmList[i]=bmList[i]&val.bmList[i];
	}
	return ret;
}

/*
	��������
*/
Set Set::operator |(Set val)
{
	Set ret(count,0);
	for(unsigned int i=0;i<bmList.size();i++)
	{
		ret.bmList[i]=bmList[i]|val.bmList[i];
	}
	return ret;
}

/*
	�����
*/
Set Set::operator -(Set val)
{
	Set ret(count,0);
	for(unsigned int i=0;i<bmList.size();i++)
	{
		ret.bmList[i]=bmList[i]&~val.bmList[i];
	}
	return ret;
}

/*
	�������
*/
Set Set::operator ^(Set val)
{
	Set ret(count,0);
	for(unsigned int i=0;i<bmList.size();i++)
	{
		ret.bmList[i]=bmList[i]^val.bmList[i];
	}
	return ret;
}

/*
	��������
*/
Set Set::operator ~()
{
	Set ret(count,0);
	for(unsigned int i=0;i<bmList.size();i++)
	{
		ret.bmList[i]=~bmList[i];
	}
	return ret;
}

/*
	�Ƚ�����
*/
bool Set::operator ==(Set& val)
{
	if(count!=val.count)
		return false;
	for(unsigned int i=0;i<bmList.size();i++)
	{
		if(bmList[i]!=val.bmList[i])
			return false;
	}
	return true;
}

/*
	�Ƚ�����
*/
bool Set::operator !=(Set& val)
{
	if(count!=val.count)
		return true;
	for(unsigned int i=0;i<bmList.size();i++)
	{
		if(bmList[i]!=val.bmList[i])
			return true;
	}
	return false;
}


/*
	��������
*/
bool Set::get(int i)
{
	if(i<0 || i>= count){
		//printf("��������ʧ�ܣ�\n");
		return false;
	}
	return !!(bmList[i/32]&(1<<(i%32)));
}

/*
	��λ����
*/
void Set::set(int i)
{
	if(i<0 || i>= count){
		//printf("��������ʧ�ܣ�\n");
		return;
	}
	bmList[i/32]|=(1<<(i%32));
}

/*
	��λ����
*/
void Set::reset(int i)
{
	if(i<0 || i>= count){
		//printf("��������ʧ�ܣ�\n");
		return;
	}
	bmList[i/32]&=~(1<<(i%32));
}

/*
	�������λ��1������
*/
int Set::max()
{
	for(int i=bmList.size()-1;i>=0;--i){
		unsigned int n=0x80000000;
		int index=31;
		while(n){
			if(bmList[i]&n)break;
			--index;
			n>>=1;
		}
		if(index>=0){//����1
			return i*32+index;
		}
	}
	return -1;
}

/*
	�����������
*/
void Set::p()
{
		int num=count;//������
		// if(bmList.size()==0){
		// 	while(num--)printf("- ");
		// }
		for(unsigned int i=0;i<bmList.size();++i)
		{
			unsigned int n=0x1;
			while(n){
				printf("%d ",!!(bmList[i]&n));
				if(!--num)break;
				n<<=1;
			}
			if(!--num)break;
		}
		fflush(stdout);
}