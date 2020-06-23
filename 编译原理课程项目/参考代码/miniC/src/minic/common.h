#pragma once

#include <stdio.h>
#include <vector>
#include <list>
#include <string>
using namespace std;


/*******************************************************************************
                                   �ʷ��Ǻŵı�ǩ
*******************************************************************************/

/*
	�ʷ��Ǻű�ǩ
*/
enum Tag
{
	ERR,																					//�����쳣
	END,																					//�ļ��������
	ID,																						//��ʶ��
	KW_INT,KW_CHAR,KW_VOID,												//��������
	KW_EXTERN,																		//extern
	NUM,CH,STR,																		//������
	NOT,LEA,																			//��Ŀ���� ! - & *
	ADD,SUB,MUL,DIV,MOD,													//���������
	INC,DEC,
	GT,GE,LT,LE,EQU,NEQU,													//�Ƚ������
	AND,OR,																				//�߼�����
	LPAREN,RPAREN,																//()
	LBRACK,RBRACK,																//[]
	LBRACE,RBRACE,																//{}
	COMMA,COLON,SEMICON,													//����,ð��,�ֺ�
	ASSIGN,																				//��ֵ
	KW_IF,KW_ELSE,																//if-else
	KW_SWITCH,KW_CASE,KW_DEFAULT,									//swicth-case-deault
	KW_WHILE,KW_DO,KW_FOR,												//ѭ��
	KW_BREAK,KW_CONTINUE,KW_RETURN								//break,continue,return
};

/*
	�м���������ö������
*/
enum Operator
{
	//ռλָ��,Ĭ��ֵ
	OP_NOP,
	//����ָ��
	OP_DEC, //eg: DEC arg1 => (int/char */[]) arg1
	//������ںͳ���
	OP_ENTRY,OP_EXIT,
	//��ֵ����
	OP_AS,//��ֵ eg: AS result,arg1 => result=arg1
	//��������
	OP_ADD,OP_SUB,OP_MUL,OP_DIV,OP_MOD,//�Ӽ��˳�ģ eg: ADD result,arg1,arg2 => result=arg1 + arg2
	OP_NEG,//�� eg: NEG result,arg1 => result = -arg1
	//�Ƚ�����
	OP_GT,OP_GE,OP_LT,OP_LE,OP_EQU,OP_NE,//��С�� eg: GT result,arg1,arg2 => result=arg1 > arg2
	//�߼�����
	OP_NOT,//�� eg: NOT result,arg1 => result=!arg1
	OP_AND,OP_OR,//��� eg: AND result,arg1,arg2 => result=arg1 && arg2
	//��������
	//OP_INDL,//������Ϊ��ֵ eg: INDL result,arg1,arg2 => arg1[arg2]=result
	//OP_INDR,//������Ϊ��ֵ eg: INDR result,arg1,arg2 => result=arg1[arg2]
	//ָ������
	OP_LEA,//ȡַ eg: LEA result,arg1 => result=&arg1
	OP_SET,//������ֵ eg: SET result,arg1 => *arg1=result
	OP_GET,//ȡ��ֵ eg: GET result,arg1 => result=*arg1
	//��ת
	OP_JMP,//��������ת eg: JMP result => goto result
	OP_JT,//����ת	 eg: JT result,arg1 => if(arg1) goto result
	OP_JF,//����ת	 eg: JF result,arg1 => if(!arg1) goto result
	/*OP_JG,OP_JGE,OP_JL,OP_JLE,OP_JE,*/OP_JNE,//��ת eg:JG result,arg1,arg2 => if(arg1 > arg2) goto result
	//��������
	OP_ARG,//�������� eg: ARG arg1 => ���ݲ���arg1
	OP_PROC,//���ù��� eg: PROC fun => ����fun����,fun()
	OP_CALL,//���ú��� eg: CALL result,fun => ����fun����,����ֵresult=fun()
	OP_RET,//ֱ�ӷ��� eg: RET => return
	OP_RETV//�����ݷ��� eg:RET arg1 => return arg1
};

/*
	�ʷ�������
*/
enum LexError
{
	STR_NO_R_QUTION,		//�ַ���û��������
	NUM_BIN_TYPE,				//2������û��ʵ������
	NUM_HEX_TYPE,				//16������û��ʵ������
	CHAR_NO_R_QUTION,		//�ַ�û��������
	CHAR_NO_DATA,				//�ַ�û������
	OR_NO_PAIR,					//||ֻ��һ��|
	COMMENT_NO_END,			//����ע��û����������
	TOKEN_NO_EXIST			//�����ڵĴʷ��Ǻ�
};

/*
	�﷨������
*/
enum SynError
{
	TYPE_LOST,					//����
	TYPE_WRONG,					
	ID_LOST,						//��־��
	ID_WRONG,						
	NUM_LOST,						//���鳤��
	NUM_WRONG,
	LITERAL_LOST,				//����
	LITERAL_WRONG,
	COMMA_LOST,					//����
	COMMA_WRONG,
	SEMICON_LOST,				//�ֺ�
	SEMICON_WRONG,
	ASSIGN_LOST,				//=
	ASSIGN_WRONG,
	COLON_LOST,					//ð��
	COLON_WRONG,
	WHILE_LOST,					//while
	WHILE_WRONG,
	LPAREN_LOST,				//(
	LPAREN_WRONG,
	RPAREN_LOST,				//)
	RPAREN_WRONG,
	LBRACK_LOST,				//[
	LBRACK_WRONG,
	RBRACK_LOST,				//]
	RBRACK_WRONG,
	LBRACE_LOST,				//{
	LBRACE_WRONG,
	RBRACE_LOST,				//}
	RBRACE_WRONG
};

/*
	���������
*/
enum SemError
{
	VAR_RE_DEF,					//�����ض���
	FUN_RE_DEF,					//�����ض���
	VAR_UN_DEC,					//����δ����
	FUN_UN_DEC,					//����δ����
	FUN_DEC_ERR,				//���������붨�岻ƥ��
	FUN_CALL_ERR,				//�в�ʵ�β�ƥ��
	DEC_INIT_DENY,			//�����������ʼ��
	EXTERN_FUN_DEF,			//������������ʹ��extern
	ARRAY_LEN_INVALID,	//���鳤����Ч
	VAR_INIT_ERR,				//������ʼ�����ʹ���
	GLB_INIT_ERR,				//ȫ�ֱ�����ʼ��ֵ���ǳ���
	VOID_VAR,						//void����
	EXPR_NOT_LEFT_VAL,	//��Ч����ֵ���ʽ
	ASSIGN_TYPE_ERR,		//��ֵ���Ͳ�ƥ��
	EXPR_IS_BASE,				//���ʽ�����ǻ�������
	EXPR_NOT_BASE,			//���ʽ���ǻ�������
	ARR_TYPE_ERR,				//�����������ʹ���
	EXPR_IS_VOID,				//���ʽ������VOID����
	BREAK_ERR,					//break����ѭ����switch-case��
	CONTINUE_ERR,				//continue����ѭ����
	RETURN_ERR					//return���ͺ�������ֵ���Ͳ�ƥ��
};

/*
	���徯����
*/
enum SemWarn
{
	FUN_DEC_CONFLICT,		//���������б����ͳ�ͻ
	FUN_RET_CONFLICT		//��������ֵ���ͳ�ͻ
};

extern const char * tokenName[];

class Token;
class Scanner;
class Error;
class Lexer;
class Parser;
class SymTab;
class GenIR;
class Var;
class Fun;
class InterInst;
class InterCode;
class Compiler;
class Args;
class Block;
class DFG;
class LiveVar;

#define CONST
#define RED
#define DEAD
#define REG
#define PEEP









