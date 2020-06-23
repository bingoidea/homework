#include "platform.h"

const char* Plat::regName[regNum]={
		"r0","r1","r2","r3","r4","r5","r6","r7"
		//,"r8"//���ڼ��ز�����1,������ʽ���
		//,"r9"//���ڼ��ز�����2,д�ر��ʽ���,����������ǩ��ַ
		//,"r10"//���ڱ���˷��������Ȼmul r8,r8,r9Ҳ������ִ�У����Ǳ��⽻�������ʾ����
		//,"fp"//r11,�ֲ�����Ѱַ
		//,"ip"//"r12"����ʱ�Ĵ���
		//,"sp"//r13��ջָ��
		//,"lr"//r14�����ӼĴ���
		//,"pc"//r15�����������
	};

/*
	ѭ��������λ
*/
void Plat::roundLeftShiftTwoBit(unsigned int& num)
{
	unsigned int overFlow=num & 0xc0000000;//ȡ���Ƽ����������λ
	num=(num<<2) | (overFlow>>30);//���������׷�ӵ�β��
}

/*
	�ж�num�Ƿ��ǳ������ʽ��8λ����ѭ������ż��λ�õ�
*/
bool Plat::__constExpr(unsigned int num)
{
	for(int i=0;i<16;i++){
		if(num<=0xff)return true;//��Чλͼ
		else roundLeftShiftTwoBit(num);//ѭ������2λ
	}
}

/*
	ͬʱ���������͸���
*/
bool Plat::constExpr(int num)
{
	return __constExpr(num)||__constExpr(-num);
}

/*
	�ж��Ƿ��ǺϷ���ƫ��(-4096,4096)
*/
bool Plat::isDisp(int num)
{
	return num<4096 && num >-4096;
}

/*
	�ж��Ƿ��ǺϷ��ļĴ�����
*/
bool Plat::isReg(string s)
{
	return s=="r0" || s=="r1" || s=="r2" || s=="r3" || s=="r4"
			|| s=="r5" || s=="r6" || s=="r7" || s=="r8" || s=="r9"
			|| s=="r10" || s=="fp" || s=="ip" || s=="sp" || s=="lr"
			|| s=="pc";
}