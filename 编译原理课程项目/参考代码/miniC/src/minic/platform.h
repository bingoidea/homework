#pragma once
#include"common.h"
/*
	x86ƽ̨��Ϣ
*/
class Plat
{
	static void roundLeftShiftTwoBit(unsigned int& num);//ѭ��������λ
	static bool __constExpr(unsigned int num);//�ж�num�Ƿ��ǳ������ʽ��8λ����ѭ������ż��λ�õ�
public:
	static bool constExpr(int num);//ͬʱ���������͸���
	static bool isDisp(int num);//�ж��Ƿ��ǺϷ���ƫ��
	static bool isReg(string s);//�ж��Ƿ��ǺϷ��ļĴ�����
	/*
		��ջָ������:
			mov ip,sp
			stmfd sp!,{fp,ip,lr,pc}
			sub fp,ip,#4
		��ջָ�����У�
			ldmea fp,{fp,sp,pc}
		ջ��ַfpָ��pc��������ջ��Ҫ��ƫ��12�ֽڻ���֮�ϣ�
	*/
	static const int regNum=8;//��ʹ�õ�ͨ�üĴ����ĸ���r0-r7
	static const char* regName[regNum];//����ʹ�õ�ͨ�üĴ����ĸ���
	static const int stackBase=12;//���ӱ����ֳ���ջ��ַ=12
	static const int stackBase_protect=12+regNum*4;//�ӱ����ֳ���ջ��ַ=12+sizeof({r0-r7})=44
};

