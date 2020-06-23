#pragma once

#include"common.h"
#include"x86-regtypes.h"

/*
	�Ĵ������࣬����ѡ��һ��δ��ռ�õĵļĴ���
*/
class RegPool
{
	static unsigned int reg_used;//�Ĵ���ʹ��λͼ
public:
	static int getReg();//��ȡһ�����еļĴ���,���غϷ��ļĴ������,�޿��мĴ�������-NOMOREREG
	static void putReg(int reg_num);//����һ���Ĵ���,Ҫ���źϷ��������getReg���ʹ��
	static void putAll();//�Ż����мĴ���
	static bool isEmpty();//�жϼĴ������Ƿ�Ϊ��
	static int inUse(unsigned int reg_id);//�ж�ĳ���Ĵ����Ƿ�����ʹ�ã����ɱ�����
	static bool useReg(unsigned int reg_id);//����ʹ��ĳ���Ĵ���
	static unsigned int regnum_id(int reg_num);//�Ĵ������ת��Ϊλͼ
	static int regid_num(unsigned int reg_id);//�Ĵ���λͼת��Ϊ���
};

//��ʼ���Ĵ���λͼ
unsigned int RegPool::reg_used=R_USABLE;

/*
	���³�ʼ���Ĵ���λͼ
*/
void RegPool::putAll()
{
	reg_used=R_USABLE;
}

/*
	���ռĴ�����Ŵ�С�����˳���üĴ������
	��ŷ�Χ��R_USABLE������
	û�п��еļĴ�������-NOMOREREG��
*/
int RegPool::getReg()
{
	unsigned int regs=reg_used;
	unsigned int reg_id=1;//�Ĵ�����λͼ
	int reg_num=0;//�Ĵ����ı��
	while(regs&1)
	{
		reg_id<<=1;
		reg_num++;
		regs>>=1;
	}
	if(!reg_id)//�Ƿ����뵽�Ĵ���
		reg_num=-NOMOREREG;//��ֹ������
	else
		reg_used|=reg_id;//���¼Ĵ���λͼ
	return reg_num;
}

/*
	���Ĵ������ת��Ϊλͼ����Ҫ��֤��ŵĺϷ���
*/
unsigned int RegPool::regnum_id(int reg_num)
{
	#ifdef DEBUG
	if(reg_num<0||reg_num>=MAXBIT)
	{
		PDEBUG(ERROR"�Ĵ������%dԽ��.\n",reg_num);
		return 0;
	}
	#endif
	unsigned int reg_id = 1<<reg_num;
	#ifdef DEBUG
	if(reg_id&R_LEGAL)//�Ƿ�λͼ
	{
		PDEBUG(ERROR"�Ĵ������%d���ڷǷ�����.\n",reg_num);
		return 0;
	}
	#endif
	return reg_id;
}

/*
	����Ŷ�Ӧ�ļĴ���λͼ��0
*/
void RegPool::putReg(int reg_num)
{
	unsigned int reg_id=regnum_id(reg_num);
	#ifdef DEBUG
	if(!reg_id)//��Ч���
		return;
	if(!(reg_id&reg_used))
	{
		PDEBUG(WARN"�Ĵ���R%dδ��ʹ��.\n",reg_num);
		return;
	}
	#endif
	reg_used &= ~reg_id;
}

/*
	�жϼĴ������Ƿ�Ϊ��
*/
bool RegPool::isEmpty()
{
	return !(reg_used^0xffffffff);//�������мĴ���λ
}

/*
	���Ĵ���λͼת��Ϊ���,��Ҫ��֤λͼ�ĺϷ���
	�Ĵ���λͼ��������R_LEGAL���ƣ�����ֻ����һλΪ1
*/
int RegPool::regid_num(unsigned int reg_id)
{
	#ifdef DEBUG
	if(!reg_id||(reg_id&R_LEGAL))//�Ƿ�λͼ
	{
		PDEBUG(ERROR"�Ĵ���λͼ0x%08x���ڷǷ�����.\n",reg_id);
		return -WRONGARGS;
	}
	#endif
	int reg_num=0;
	unsigned int temp=reg_id;
	while(!(temp&1))//ת��
	{
		temp>>=1;
		reg_num++;
	}
	#ifdef DEBUG
	if((1<<reg_num)!=reg_id)//��0λ����
	{
		PDEBUG(ERROR"�Ĵ���λͼ0x%08x��Ϣ����.\n",reg_id);
		reg_num = -WRONGARGS;
	}
	#endif
	return reg_num;
}

/*
	����һ���Ĵ���λͼ��Ӧ�ļĴ����Ƿ��Ѿ���ռ�ã�����ʹ�ú���Ϊ����
*/
int RegPool::inUse(unsigned int reg_id)
{
	#ifdef DEBUG
	if(regid_num(reg_id) == -WRONGARGS)
	{
		return -WRONGARGS;
	}
	#endif
	return !!(reg_used&reg_id);//���ԼĴ���λ
}

/*
	Ҫ��ʹ��һ���ض��ļĴ�����ָ���üĴ�����λͼ������ʹ�ú���Ϊ����
*/
bool RegPool::useReg(unsigned int reg_id)
{
	int stats=inUse(reg_id);
	if(!stats)
	{
		reg_used|=reg_id;
		return true;
	}
	else if(stats==1)
	{
		PDEBUG(WARN"�Ĵ���(λͼ=0x%08x)�Ѿ���ռ��.\n",reg_id);
	}
	return false;
}






