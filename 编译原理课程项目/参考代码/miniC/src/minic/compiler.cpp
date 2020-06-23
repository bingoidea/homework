#include "compiler.h"
#include "lexer.h"
#include "error.h"
#include "symtab.h"
#include "genir.h"
#include "parser.h"

/*
	���������ʼ��
*/
bool Args::showChar=false;
bool Args::showToken=false;
bool Args::showSym=false;
bool Args::showmc=false;
bool Args::showHelp=false;

/*
	����һ���ļ�
*/
void Compiler::compile(char*file)
{
	//׼��
	Scanner scanner(file);//ɨ����
	Error error(&scanner);//������
	Lexer lexer(scanner);//�ʷ�������
	SymTab symtab;//���ű�
	GenIR ir(symtab);//�м����������
	Parser parser(lexer,symtab,ir);//�﷨������
	//����
	parser.analyse();//����
	//����
	if(Error::getErrorNum()+Error::getWarnNum())return;//�������к�������
	//�м���
	if(Args::showSym)symtab.toString();//������ű�
	if(Args::showmc)symtab.printInterCode();//����м����
	//�Ż�
	//symtab.optimize();//ִ���Ż�
	//if(Args::showOr)symtab.printOptCode();//����Ż�����м����
	//���ɻ�����
	symtab.genAsm(file);
}







