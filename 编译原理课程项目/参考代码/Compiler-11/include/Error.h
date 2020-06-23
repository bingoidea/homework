#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED
#include"global.h"

#include<iostream>
using namespace std;

enum LexError
{
    STR_NO_R_QUTION,
    NUM_BIN_TYPE,
    NUM_HEX_TYPE,
    CHAR_NO_R_QUTION,
    CHAR_NO_DATA,
    OR_NO_PAIR,
    COMMMENT_NO_END,
    TOKEN_NO_EXIST
};
enum SynError{
    TYPE_LOST,    TYPE_WRONG,
    ID_LOST, ID_WRONG,
    NUM_LOST,NUM_WRONG,
    LITERAL_LOST,LITERAL_WRONG,
    COMMMA_LOST,COMMMA_WRONG,
    SEMICON_LOST,SEMICON_WRONG,
    ASSIGN_LOST,ASSIGN_WRONG,
    COLON_LOST,COLON_WRONG,
    WHILE_LOST,WHILE_WRONG,
    LPAREN_LOST,LPAREN_WRONG,
    RPAREN_LOST,RPAREN_WRONG,
    LBRACK_LOST,LBRACK_WRONG,
    RBRACK_LOST,RBRACK_WRONG,
    LBRACE_LOST,LBRACE_WRONG,
    RBRACE_LOST,RBRACE_WRONG
};

enum SemError{
    VAR_RE_DEF,
    FUN_RE_DEF,
    VAR_UN_DEC,
    FUN_UN_DEC,
    FUN_DEC_ERR,
    FUN_CALL_ERR,
    DEC_INIT_DENY,
    EXTERN_FUN_DEF,
    ARRAY_LEN_INVALID,
    VAR_INIT_ERR,
    GLB_INIT_ERR,
    VOID_VAR,
    EXPR_NOT_LEFT_VAL,
    ASSIGN_TYPE_ERR,
    EXPR_IS_BASE,
    EXPR_NOT_BASE,
    ARR_TYPE_ERR,
    EXPR_IS_VOID,
    BREAK_ERR,
    CONTINUE_ERR,
    RETURN_ERR
};

enum SemWarn{
    FUN_DEC_CONFLICT,
    FUN_RET_CONFLICT,
    PTR_SEG_FAULT
};
class Error
{
public:
    static void LexError(int code)
    {
        static const char *lexErrorTable[]=
        {
            "�ַ�����ʧ����",
            "��������û��ʵ������",
            "ʮ����������û��ʵ������",
            "�ַ���ʧ�ҵ�����",
            "��֧�ֿ��ַ�",
            "�����'|'�����",
            "����ע��û����������",
            "�ʷ��ǺŲ�����"
        };
        errorNum++;
        highlight("",ERRORCOLOR);
        cerr<<lex->getFileName(true)<<" <"<<lex->getLineNum()<<"��,"<<lex->getColNum()<<"��> �ʷ�����:"<<lexErrorTable[code]<<".\n";
        highlight("",NORMAL);
    }
    static void SynError(int code,Token* t)
    {
        static const char *synErrorTable[] =
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
        highlight("",ERRORCOLOR);
        if(code%2==0)  {cerr<<lex->getFileName(true)<<" <"<<lex->getLineNum()<<"��> �﷨����: �� ";
                        cerr<< t->toString()<<" ֮ǰ��ʧ"<<synErrorTable[code/2]<<endl;}

        else cerr<<lex->getFileName(true)<<" <"<<lex->getLineNum()<<"��> �﷨����: �� "<< t->toString()<<" ��û����ȷƥ��"<<synErrorTable[code/2]<<endl;
        highlight("",NORMAL);
    }
    static void SemError(int code,string name)
    {
        static const char *SemErrorTable[]={
            "�����ض���",
            "�����ض���",
            "����δ����",
            "����δ����",
            "���������붨�岻ƥ��",
            "�����β���ʵ�β�ƥ��",
            "��������ʱ�������ʼ��",
            "�������岻��ʹ�ñ�����extern",
            "���鳤��Ӧ����������",
            "������ʼ�����ʹ���",
            "ȫ�ֱ�����ʼ�����ǳ���",
            "������������Ϊvoid����",
            "��Ч����ֵ���ʽ",
            "��ֵ���ʽ������",
            "���ʽ�����������ǻ�������",
            "���ʽ���������ǻ�������",
            "���������������ʹ���",
            "void�ĺ�������ֵ���ܲ�����ʽ����",
            "break��䲻�ܳ�����ѭ����switch���֮��",
            "continue��䲻�ܳ�����ѭ��֮��",
            "return���ͺ�������ֵ���Ͳ�ƥ��"
        };
        errorNum++;
        highlight("",ERRORCOLOR);
        cerr<<lex->getFileName(true)<<" <"<<lex->getLineNum()<<"��> �������: "<< name<<" "<<SemErrorTable[code]<<endl;
        highlight("",NORMAL);
    }
    static void SemWarn(int code,string name)
    {
        static const char *SemWarnTable[]={
            "���������б����ͳ�ͻ",
            "��������ֵ���Ͳ���ȷƥ��",
            "���п��ܷ���Segmentation Fault"
        };
        warnNum++;
        highlight("",WARNINGCOLOR);
        cout<<lex->getFileName(true)<<" <"<<lex->getLineNum()<<"��> ���徯��: "<< name<<" "<<SemWarnTable[code]<<endl;
        highlight("",NORMAL);
    }
};
#define LEXERROR Error::LexError
#define SYNERROR Error::SynError
#define SEMERROR Error::SemError
#define SEMWARN Error::SemWarn
#endif // ERROR_H_INCLUDED
