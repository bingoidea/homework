#include "Lex.h"
#include<Scanner.h>
#include<stdio.h>
#include<string>
#include<Keywords.h>
#include<Token.h>
#include<Id.h>
#include<Num.h>
#include<Error.h>
#include"Str.h"
#include"Char.h"
#include <iostream>
#include<iomanip>
#include<ostream>
#include<fstream>
#include<direct.h>
#include<windows.h>
#include<shlwapi.h>
#include"global.h"
using namespace std;
Lex::Lex(char* file)
{
    if(!(fp = fopen(file,"r+")))
    {
        //cerr<<"No such file or dictionary!"<<endl;
        return;
    }
    scanner = new Scanner();
}
Lex::Lex()
{

}
bool Lex::scan(char need)
{
    ch = scanner->scan(fp);
    if(need)
    {
        if(ch!=need) return false;
        charLen++;
        ch = scanner->scan(fp);
        return true;
    }
    return true;
}

int Lex::getColNum()
{
    if(ch =='\n'||ch==-1) return scanner->lastCol - charLen;
    return scanner->getCol()-charLen;
}
int Lex::getLineNum()
{
    if(ch=='\n') return scanner->getLine()-1;
    return scanner->getLine();
}

Token* Lex::tokenize()
{
    Token *sub;
    charLen = 0;

    if(ch==0)
        ch = scanner->scan(fp);
    if(ch==-1)
    {
        sub = new Token(END);
        return sub;
    }
    while(ch ==' '||ch=='\n'||ch=='\t')
        ch = scanner->scan(fp);
    charLen++;
    if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'||ch=='_')
    {
        string name="";
        while(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'||ch=='_'||ch>='0'&&ch<='9')
        {
            name.push_back(ch);
            ch = scanner->scan(fp);
            if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'||ch=='_'||ch>='0'&&ch<='9')
                charLen++;
        }
        Keywords key;
        _TokenType type = key.getTag(name);

        if(type==ID)
            sub = new Id(name);
        else
            sub = new Token(type);

        return sub;
    }

    else if(ch>='0'&&ch<='9')
    {
        sub = NULL;
        int val =0;
        if(ch!='0')
        {
            do
            {
                val = val*10+ch-'0';
                ch = scanner->scan(fp);
                if(ch>='0'&&ch<='9')
                    charLen++;
            }
            while(ch>='0'&&ch<='9');
        }
        else
        {
            ch = scanner->scan(fp);
            if(ch=='x')
            {
                ch = scanner->scan(fp);
                charLen++;
                if(ch>='0'&&ch<='9'||ch>='A'&&ch<='F'||ch>='a'&&ch<='f')
                {
                    do
                    {
                        val = val*16+ch;
                        if(ch>='0'&&ch<='9') val-='0';
                        else if(ch>='A'&&ch<='F') val+=10-'A';
                        else if(ch>='a'&&ch<='f') val+=10-'a';
                        ch = scanner->scan(fp);
                        if(ch>='0'&&ch<='9'||ch>='A'&&ch<='F'||ch>='a'&&ch<='f')
                            charLen++;
                    }
                    while(ch>='0'&&ch<='9'||ch>='A'&&ch<='F'||ch>='a'&&ch<='f');
                }
                else
                {
                    LEXERROR(NUM_HEX_TYPE);
                    sub = new Token(ERR);
                }
            }
            else if(ch=='b')
            {
                ch = scanner->scan(fp);
                if(ch>='0'&&ch<='1')
                {
                    do
                    {
                        val = val*2+ch-'0';
                        ch = scanner->scan(fp);
                        if(ch>='0'&&ch<='1')
                            charLen++;
                    }
                    while(ch>='0'&&ch<='1');
                }
                else
                {
                    LEXERROR(NUM_BIN_TYPE);
                    sub = new Token(ERR);
                }
            }
            else if(ch>'0'&&ch<='7')
            {
                do
                {
                    val = val*8+ch-'0';
                    ch = scanner->scan(fp);
                    if(ch>='0'&&ch<='7')
                        charLen++;
                }
                while(ch>='0'&&ch<='7');
            }
        }
        if(!sub)
        {
            sub = new Num(val);
        }

        return sub;
    }
    else if(ch =='\'')
    {
        char c;
        sub = NULL;
        ch = scanner->scan(fp);
        charLen++;
        if(ch=='\\')
        {
            ch = scanner->scan(fp);
            charLen++;
            if(ch=='n') c = '\n';
            else if(ch == '\\') c = '\\';
            else if(ch=='t') c = '\t';
            else if(ch=='0') c = '\0';
            else if(ch=='\'') c = '\'';
            else if(ch ==-1||ch=='\n')
            {
                LEXERROR(CHAR_NO_R_QUTION);
                sub = new Token(ERR);
            }
            else c = ch;
        }
        else if(ch =='\n'||ch==-1)
        {
            LEXERROR(CHAR_NO_R_QUTION);
            sub = new Token(ERR);
        }
        else if(ch=='\'')
        {
            LEXERROR(CHAR_NO_DATA);
            sub = new Token(ERR);
            ch = scanner->scan(fp);
            charLen++;
        }
        else c = ch;
        if(!sub)
        {
            ch = scanner->scan(fp);
            charLen++;
            if(ch=='\'')
            {
                sub = new Char(c);
                ch = scanner->scan(fp);
            }
            else
            {
                LEXERROR(CHAR_NO_R_QUTION);
                sub = new Token(ERR);
            }
        }

        return sub;
    }
    else if(ch=='"')
    {
        sub = NULL;
        string str="";
        ch = scanner->scan(fp);
        while(ch!='"')
        {
            if(ch=='\\')
            {
                ch = scanner->scan(fp);
                charLen++;
                if(ch=='n') str.push_back('\n');
                else if(ch=='t') str.push_back('\t');
                else if(ch=='"') str.push_back('"');
                else if(ch=='0') str.push_back('\0');
                else if(ch=='\n');
                else if(ch ==-1)
                {
                    LEXERROR(STR_NO_R_QUTION);
                    sub = new Token(ERR);
                    break;
                }
                else str.push_back(ch);
            }
            else if(ch=='\n'|ch==-1)
            {
                LEXERROR(STR_NO_R_QUTION);
                sub = new Token(ERR);
                break;
            }
            else
            {
                str.push_back(ch);
                charLen++;
            }
            ch = scanner->scan(fp);
        }
        if(!sub)
        {
            sub= new Str(str);
        }
        ch = scanner->scan(fp);

        return sub;
    }
    switch(ch)
    {
    case '+':
        ch = scanner->scan(fp);
        if(ch=='+'){
            sub = new Token(INC);
            ch = scanner->scan(fp);
        }
        else if(ch=='='){
            sub = new Token(PLUS_ASSIGN);
            ch = scanner->scan(fp);
        }
        else{
            sub = new Token(PLUS);
        }
        break;
    case '-':
        ch = scanner->scan(fp);
        if(ch=='-'){
            sub = new Token(DEC);
            ch = scanner->scan(fp);
        }
        else if(ch=='='){
            sub = new Token(MINUS_ASSIGN);
            ch = scanner->scan(fp);
        }
        else{
            sub = new Token(MINUS);
        }
        break;
    case '*':
        sub = new Token(scan('=')?TIMES_ASSIGN:TIMES);
        break;
    case '/':
        ch = scanner->scan(fp);
        if(ch =='/')
        {
            while(!(ch=='\n'||ch==-1))
            {
                ch = scanner->scan(fp);
            }
            sub = new Token(ERR);
        }
        else if(ch=='*')
        {
            charLen++;
            ch = scanner->scan(fp);
            while(ch!=-1)
            {
                if(ch=='*')
                {
                    ch = scanner->scan(fp);
                    while(ch=='*')
                    {
                        ch = scanner->scan(fp);
                    }
                    if(ch='/')
                    {
                        sub = new Token(ERR);
                        ch = scanner->scan(fp);
                        break;
                    }
                }
                ch = scanner->scan(fp);
            }
            if(!sub&&ch==-1)
            {
                LEXERROR(COMMMENT_NO_END);
                sub = new Token(ERR);
            }
        }
        else
        {
            if(ch=='=')
            {
                sub = new Token(DIV_ASSIGN);
                ch = scanner->scan(fp);
            }
            else sub = new Token(DIV);
        }
        break;
    case '%':
        sub = new Token(MOD);
        ch = scanner->scan(fp);
        break;
    case '>':
        sub = new Token(scan('=')?GE:GT);
        break;
    case '<':
        sub = new Token(scan('=')?LE:LT);
        break;
    case '=':
        sub = new Token(scan('=')?EQU:ASSIGN);
        break;
    case '&':
        sub = new Token(scan('&')?LOGICAL_AND:BIT_AND);
        break;
    case '|':
        sub = new Token(scan('|')?LOGICAL_OR:BIT_OR);
        break;
    case '!':
        sub = new Token(scan('=')?NEQU:BIT_NOT);
        break;
    case ',':
        sub = new Token(COMMA);
        ch = scanner->scan(fp);
        break;
    case ':':
        sub = new Token(COLON);
        ch = scanner->scan(fp);
        break;
    case ';':
        sub = new Token(SEMICON);
        ch = scanner->scan(fp);
        break;
    case '(':
        sub = new Token(LPAREN);
        ch = scanner->scan(fp);
        break;
    case ')':
        sub = new Token(RPAREN);
        ch = scanner->scan(fp);
        break;
    case '[':
        sub = new Token(LBRACK);
        ch = scanner->scan(fp);
        break;
    case ']':
        sub = new Token(RBRACK);
        ch = scanner->scan(fp);
        break;
    case '{':
        sub = new Token(LBRACE);
        ch = scanner->scan(fp);
        break;
    case '}':
        sub = new Token(RBRACE);
        ch = scanner->scan(fp);
        break;
    case -1:
        sub = new Token(END);
        ch = scanner->scan(fp);
        break;
    default:
        sub = new Token(ERR);
        LEXERROR(TOKEN_NO_EXIST);
        ch = scanner->scan(fp);
    }

    return sub;
}
char* Lex::getFileName(bool outOpt)
{
    char *backup = (char*)malloc(100);
    strcpy(backup,filename);
    int flag=2;/**< �ļ�·����ʶ��0�������·����1�������·����2�����������·��ֻ���ļ���*/
    filename = trim(filename);
    if(startWith(filename,"C:\\")||startWith(filename,"D:\\")||startWith(filename,"E:\\")||startWith(filename,"F:\\"))
        flag=0;
    else if(startWith(filename,".\\")||startWith(filename,"..\\"))
        flag = 1;
    else flag=2;
    if(outOpt==false)/**< ����ļ�����������׺�� */
    {
        char *tokenPtr=strtok(filename,"\\");
        char* pre;
        while(tokenPtr!=NULL)
        {
            pre = tokenPtr;
            tokenPtr=strtok(NULL,"\\");
        }
        filename = backup;
        return getRawFileName(pre);
    }
    else if(outOpt==true)/**< ���Ե�ַ����׺�� */
    {
        if(flag==0) return filename;
        else if(flag==2)
        {
            //TCHAR szPath[MAX_PATH] = {0};
            //if ( GetModuleFileName( NULL, szPath,MAX_PATH ) )
            //{
            //    (_tcsrchr(szPath,_T('\\')))[1] = 0;
            // }
            char buffer[MAX_PATH];
            getcwd(buffer, MAX_PATH);
            string strPath = buffer;
            strPath = strPath +"\\"+ filename;
            filename = backup;
            return (char*)strPath.c_str();
        }
        else if(flag==1)
        {
            char buffer[MAX_PATH];
            getcwd(buffer, MAX_PATH);
            while(startWith(filename,".\\")||startWith(filename,"..\\"))
            {
                if(startWith(filename,".\\"))
                    deleteWith(filename,".\\",2);
                else if(startWith(filename,"..\\")){
                    deleteWith(filename,"..\\",3);
                    (_tcsrchr(buffer,_T('\\')))[1] = 0;
                    buffer[strlen(buffer)-1]='\0';
                }
            }
            string strPath =buffer;
                    strPath=strPath+"\\"+filename;
                    filename = backup;
                    return (char*)strPath.c_str();
        }
    }
}

void Lex::LexShow(Token *token,bool outOpt)
{
    Id *id = new Id("");
    Char *ch = new Char(' ');
    Num *num = new Num(0);
    Str *str = new Str("");
    streambuf* coutbackup;
    ofstream fout(lexFile,ios::app);
    if(outOpt==1)
        coutbackup=cout.rdbuf(fout.rdbuf());//��rdbuf()�ض���
    if(token->type==ID)
    {
        id = static_cast<Id*>(token);
        cout<<setw(8)<<setiosflags(ios::left)<<number;
        cout<<setw(8)<<setiosflags(ios::left)<<lex->getLineNum();
        cout<<setw(8)<<setiosflags(ios::left)<<lex->getColNum();
        cout<<setw(16)<<setiosflags(ios::left)<<"��ʶ��";
        cout<<id->name<<endl;
    }
    else if(token->type==NUM)
    {
        num = static_cast<Num*>(token);
        cout<<setw(8)<<setiosflags(ios::left)<<number;
        cout<<setw(8)<<setiosflags(ios::left)<<lex->getLineNum();
        cout<<setw(8)<<setiosflags(ios::left)<<lex->getColNum();
        cout<<setw(16)<<setiosflags(ios::left)<<"���ֳ���";
        cout<<num->val<<endl;
    }
    else if(token->type==CH)
    {
        ch = static_cast<Char*>(token);
        cout<<setw(8)<<setiosflags(ios::left)<<number;
        cout<<setw(8)<<setiosflags(ios::left)<<lex->getLineNum();
        cout<<setw(8)<<setiosflags(ios::left)<<lex->getColNum();
        cout<<setw(16)<<setiosflags(ios::left)<<"�ַ�����";
        cout<<ch->ch<<endl;
    }
    else if(token->type==STR)
    {
        str = static_cast<Str*>(token);
        cout<<setw(8)<<setiosflags(ios::left)<<number;
        cout<<setw(8)<<setiosflags(ios::left)<<lex->getLineNum();
        cout<<setw(8)<<setiosflags(ios::left)<<lex->getColNum();
        cout<<setw(16)<<setiosflags(ios::left)<<"�ַ�������";
        cout<<getRawString(str->str)<<endl;
    }
    else  if(token->type<=58&&token->type>=25)
    {
        cout<<setw(8)<<setiosflags(ios::left)<<number;
        cout<<setw(8)<<setiosflags(ios::left)<<lex->getLineNum();
        cout<<setw(8)<<setiosflags(ios::left)<<lex->getColNum();
        cout<<setw(16)<<setiosflags(ios::left)<<"���";
        cout<<TokenTypeArray[token->type]<<endl;
    }
    else if(token->type!=ERR)
    {
        cout<<setw(8)<<setiosflags(ios::left)<<number;
        cout<<setw(8)<<setiosflags(ios::left)<<lex->getLineNum();
        cout<<setw(8)<<setiosflags(ios::left)<<lex->getColNum();
        cout<<setw(16)<<setiosflags(ios::left)<<"�ؼ���";
        cout<<TokenTypeArray[token->type]<<endl;
    }
    number++;
    if(outOpt==1)
    {
        cout.rdbuf(coutbackup);
    }
}
void Lex::LexShowData(Token* token,int row,int col,bool outOpt)
{
    Id *id = new Id("");
    Char *ch = new Char(' ');
    Num *num = new Num(0);
    Str *str = new Str("");
    streambuf* coutbackup;
    ofstream fout(lexFile,ios::app);
    if(outOpt==1)
        coutbackup=cout.rdbuf(fout.rdbuf());//��rdbuf()�ض���
    if(token->type==ID)
    {
        id = static_cast<Id*>(token);
        cout<<setw(8)<<setiosflags(ios::left)<<number;
        cout<<setw(8)<<setiosflags(ios::left)<<row;
        cout<<setw(8)<<setiosflags(ios::left)<<col;
        cout<<setw(16)<<setiosflags(ios::left)<<"��ʶ��";
        cout<<id->name<<endl;
    }
    else if(token->type==NUM)
    {
        num = static_cast<Num*>(token);
        cout<<setw(8)<<setiosflags(ios::left)<<number;
        cout<<setw(8)<<setiosflags(ios::left)<<row;
        cout<<setw(8)<<setiosflags(ios::left)<<col;
        cout<<setw(16)<<setiosflags(ios::left)<<"���ֳ���";
        cout<<num->val<<endl;
    }
    else if(token->type==CH)
    {
        ch = static_cast<Char*>(token);
        cout<<setw(8)<<setiosflags(ios::left)<<number;
        cout<<setw(8)<<setiosflags(ios::left)<<row;
        cout<<setw(8)<<setiosflags(ios::left)<<col;
        cout<<setw(16)<<setiosflags(ios::left)<<"�ַ�����";
        cout<<ch->ch<<endl;
    }
    else if(token->type==STR)
    {
        str = static_cast<Str*>(token);
        cout<<setw(8)<<setiosflags(ios::left)<<number;
        cout<<setw(8)<<setiosflags(ios::left)<<row;
        cout<<setw(8)<<setiosflags(ios::left)<<col;
        cout<<setw(16)<<setiosflags(ios::left)<<"�ַ�������";
        cout<<getRawString(str->str)<<endl;
    }
    else  if(token->type<=58&&token->type>=25)
    {
        cout<<setw(8)<<setiosflags(ios::left)<<number;
        cout<<setw(8)<<setiosflags(ios::left)<<row;
        cout<<setw(8)<<setiosflags(ios::left)<<col;
        cout<<setw(16)<<setiosflags(ios::left)<<"���";
        cout<<TokenTypeArray[token->type]<<endl;
    }
    else if(token->type!=ERR)
    {
        cout<<setw(8)<<setiosflags(ios::left)<<number;
        cout<<setw(8)<<setiosflags(ios::left)<<row;
        cout<<setw(8)<<setiosflags(ios::left)<<col;
        cout<<setw(16)<<setiosflags(ios::left)<<"�ؼ���";
        cout<<TokenTypeArray[token->type]<<endl;
    }
    number++;
    if(outOpt==1)
    {
        cout.rdbuf(coutbackup);
    }
}
void Lex::LexShow(bool outOpt)
{
    if(outOpt==true)
    {
        ofstream out;
        out.open(lexFile);
        out<<"���\t"<<"�к�\t"<<"�к�\t"<<"��������\t"<<"����"<<endl;
    }
    else cout<<"���\t"<<"�к�\t"<<"�к�\t"<<"��������\t"<<"����"<<endl;
    for(int i=0; i<result.size(); i++)
    {
        Token* token = result[i]->token;
        int row = result[i]->row;
        int col = result[i]->col;
        LexShowData(token,row,col,outOpt);
    }
}
void Lex::analysis()
{
    Token* token = tokenize();
    while(token->type!=END)
    {
        LexData* newData = new LexData(token,lex->getLineNum(),lex->getColNum());
        if(token->type!=ERR)
            result.push_back(newData);
        token = lex->tokenize();
    }
}

