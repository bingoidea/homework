#pragma once
#include "common.h"

/*
	������������
*/
class Args
{
public:
	static bool showChar;//��ʾ�ַ�
	static bool showToken;//��ʾ�ʷ��Ǻ�
	static bool showSym;//��ʾ���ű�
	static bool showmc;//��ʾ�м����
	static bool showOr;//��ʾ�Ż�����м����
	static bool showBlock;//��ʾ���������ͼ��ϵ
	static bool showHelp;//��ʾ����
	static bool opt;//�Ƿ�ִ���Ż�
};

/*
	��������
*/
class Compiler
{

public:

	//���ĺ���
	void compile(char*file);//����һ���ļ�
};

