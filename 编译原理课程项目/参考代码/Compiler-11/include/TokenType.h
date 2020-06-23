#ifndef TOKENTYPE_H_INCLUDED
#define TOKENTYPE_H_INCLUDED
#include<string>
using namespace std;

 static string TokenTypeArray[66]  = {"double","int","float","char","typedef","enum","register","signed","void","extern","const","if","else","switch","case","default","do","for","break","continue","return","read","while","printf","write",

    //������
    "+","-","*","/","%","&","|","!","&&","||",
    //���
    "++","--","=",">",">=","<","<=","==","!=",",",":",";","(",")","{","}","[","]",
    "TIPS",
    "/*","+=","-=","*=","/=",
    //����
    "ERR","END","_EOF",
    "ID",
    "NUM","CH","STR"};

enum _TokenType
{
    //�ؼ���
    _DOUBLE,_INT,_FLOAT,_CHAR,_TYPEDEF,_ENUM,_REGISTER,_SIGNED,_VOID,_EXTERN,_CONST,
    _IF,_ELSE,_SWITCH,_CASE,_DEFAULT,_DO,_FOR,_BREAK,_CONTINUE,_RETURN,_READ,_WHILE,_PRINTF,_WRITE,
    //������
    PLUS,MINUS,TIMES,DIV,MOD,BIT_AND,BIT_OR,BIT_NOT,LOGICAL_AND,LOGICAL_OR,//& | ! && ||
    //���
    INC/*++*/,DEC/*--*/,ASSIGN/*=*/,GT/*>*/,GE/*>=*/,LT/*<*/,LE/*<=*/,EQU/*==*/,NEQU/* !=*/,COMMA/*,*/,COLON/*:*/,SEMICON/*;*/,LPAREN/*(*/,RPAREN/*)*/,LBRACE/*{*/,RBRACE/*}*/,LBRACK/* ['*/,RBRACK/* ]*/,
    TIPS,//
    LONG_TIPS/* */,PLUS_ASSIGN/*+=*/,MINUS_ASSIGN/*-=*/,TIMES_ASSIGN/* *=*/,DIV_ASSIGN,/* /=*/
    //����
    ERR,END,_EOF,
    ID/*��ʶ��*/,
    NUM,CH,STR//����
};
#endif // TOKENTYPE_H_INCLUDED
