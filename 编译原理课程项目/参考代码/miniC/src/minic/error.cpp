#include "error.h"
#include "token.h"
#include "lexer.h"

int Error::errorNum=0;//������
int Error::warnNum=0;//���������
Scanner* Error::scanner=NULL;

/*
	��ʼ���������
*/
Error::Error(Scanner*sc)
{
	scanner=sc;//ɨ����
}


/*
	��ӡ�ʷ�����
*/
void Error::lexError(int code)
{
	//�ʷ�������Ϣ��
	static const char *lexErrorTable[]=
	{
		"�ַ�����ʧ������",
		"��������û��ʵ������",
		"ʮ��������û��ʵ������",
		"�ַ���ʧ�ҵ�����",
		"��֧�ֿ��ַ�",
		"����Ļ������",
		"����ע��û����������",
		"�ʷ��ǺŲ�����"
	};
	errorNum++;
	printf("%s<%d��,%d��> �ʷ����� : %s.\n",scanner->getFile(),
		scanner->getLine(),scanner->getLine(),lexErrorTable[code]);
}

/*
	��ӡ�﷨����
*/
void Error::synError(int code,Token*t)
{
	//�﷨������Ϣ��
	static const char *synErrorTable[]=
	{
		"����",
		"��ʶ��",
		"���鳤��",
		"����",
		"����",
		"�ֺ�",
		"=",
		"ð��",
		"while",
		"(",
		")",
		"[",
		"]",
		"{",
		"}"
	};
	errorNum++;
	if(code%2==0)//lost
		printf("%s<��%d��> �﷨���� : �� %s ֮ǰ��ʧ %s .\n",scanner->getFile(),scanner->getLine()
			,t->toString().c_str(),synErrorTable[code/2]);
	else//wrong
		printf("%s<��%d��> �﷨���� : �� %s ��û����ȷƥ�� %s .\n",scanner->getFile(),scanner->getLine()
			,t->toString().c_str(),synErrorTable[code/2]);
}

/*
	��ӡ�������
*/
void Error::semError(int code,string name)
{
	//���������Ϣ��
	static const char *semErrorTable[]=
	{
		"�����ض���",										//����������Ϣ
		"�����ض���",
		"����δ����",
		"����δ����",
		"���������붨�岻ƥ��",
		"�����в�ʵ�β�ƥ��",
		"��������ʱ�������ʼ��",
		"�������岻������extern",
		"���鳤��Ӧ����������",
		"������ʼ�����ʹ���",
		"ȫ�ֱ�����ʼ��ֵ���ǳ���",
		"������������Ϊvoid����",					//û��������Ϣ
		"��Ч����ֵ���ʽ",
		"��ֵ���ʽ���Ͳ�����",
		"���ʽ����������ǻ�������",
		"���ʽ��������ǻ�������",
		"���������������ʹ���",
		"void�ĺ�������ֵ���ܲ�����ʽ����",
		"break��䲻�ܳ�����ѭ����switch���֮��",
		"continue���ܳ�����ѭ��֮��",
		"return���ͺ�������ֵ���Ͳ�ƥ��"
	};
	errorNum++;
	printf("%s<��%d��> ������� : %s %s.\n",scanner->getFile(),scanner->getLine(),
		name.c_str(),semErrorTable[code]);
}

/*
	��ӡ���徯��
*/
void Error::semWarn(int code,string name)
{
	//���徯����Ϣ��
	static const char *semWarnTable[]=
	{
		"���������б����ͳ�ͻ",					//����������Ϣ
		"��������ֵ���Ͳ���ȷƥ��"
	};
	warnNum++;
	printf("%s<��%d��> ���徯�� : %s %s.\n",scanner->getFile(),scanner->getLine(),
		name.c_str(),semWarnTable[code]);
}

/*
	��ȡ�������
*/
int Error::getErrorNum()
{
	return errorNum;
}

/*
	��ȡ�������
*/
int Error::getWarnNum()
{
	return warnNum;
}

