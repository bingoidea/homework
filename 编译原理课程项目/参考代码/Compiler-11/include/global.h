#ifndef GLOBA_H_INCLUDED
#define GLOBA_H_INCLUDED

#include"Lex.h"
#include"Scanner.h"
#include"SymTab.h"
#include"GenIR.h"
#include"InterInst.h"
#include<stdio.h>
#include<windows.h>
#include<string>
using namespace std;
class GenIR;
class Lex;
class SymTab;
enum TextColor{
        KEYWORDS,
    PARAMETER,
    EXPLANATION,
    NORMAL,
    ERRORCOLOR,
    WARNINGCOLOR
};
extern Lex *lex;
extern SymTab *symtab;
extern GenIR *ir;
extern InterInst *inst;
extern char* filename;/**< Դ�����ļ� */
extern char* targetFile;/**< Ŀ��������ļ� */
extern char* lexFile;/**< �ʷ������м����洢�ļ� */
extern char* parseFile;/**< �﷨������ �洢�ļ� */
extern char* intercodeFile;/**< �м���� �洢�ļ� */
extern int errorNum;
extern int warnNum;

extern FILE* file;/**< Ŀ�����ļ�ָ�� */
extern FILE* source;/**< Դ�ļ�ָ��Ϊ����ļ��Ƿ���� */
/**<  extern Fun* global;/**< Ϊ�洢ȫ�ֱ��� */
extern void highlight(char* text, TextColor _color);
extern char* trim(char* str);
extern bool startWith(char* source,char* start);
extern char* getRawFileName(char* externFile);
extern string getRawString(string str);
extern bool deleteWith(char* &source,char* start,int len);
extern void trimVetor(vector<int> &temp);
extern vector<int> IOflag;/**< 1 for putchar ;2 for puts ; 3 for printf;*/
//extern void _remove(char* source,char* start);
#endif // GLOBA_H_INCLUDED
