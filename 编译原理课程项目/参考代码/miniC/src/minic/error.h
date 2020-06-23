#pragma once
#include "common.h"

/*
	������
*/
class Error
{	
	
	static Scanner *scanner;//��ǰʹ�õ�ɨ����
	
public:
	
	//�������ʼ��
	Error(Scanner*sc);
	
	static int errorNum;//�������
	static int warnNum;	//�������
	//���ӿ�
	static int getErrorNum();
	static int getWarnNum();
	
	//����ӿ�
	static void lexError(int code);//��ӡ�ʷ�����
	static void synError(int code,Token*t);//��ӡ�﷨����
	static void semError(int code,string name="");//��ӡ�������
	static void semWarn(int code,string name="");//��ӡ���徯��
	
};

//���󼶱�,��ѡ���������δ�����Ϣͷ��
#define FATAL "<fatal>:"
#define ERROR "<error>:"
#define WARN	"<warn>:"

//�������
#ifdef DEBUG
#define PDEBUG(fmt, args...) printf(fmt, ##args)
#else
#define PDEBUG(fmt, args...)
#endif	//DEBUG




void SEMWARN(int code);//��ӡ���徯��




