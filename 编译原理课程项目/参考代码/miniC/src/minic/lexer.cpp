#include "lexer.h"
#include "token.h"
#include "error.h"
#include "compiler.h"

/*******************************************************************************
                                   ɨ����
*******************************************************************************/

Scanner::Scanner(char* name)
{
    file=fopen(name,"r");//��ָ���Ĵ�ɨ���ļ�
    if(!file)
    {
        printf(FATAL"�ļ�%s��ʧ�ܣ������ļ�����·����\n",name);
        Error::errorNum++;//�������ۼ�
    }
    fileName=name;
    //��ʼ��ɨ��״̬
    lineLen=0;
    readPos=-1;
    lastch= '\n';
    lineNum=0;
    colNum=0;
}

Scanner::~Scanner()
{
    if(file)
    {
        PDEBUG(WARN"�ļ�δȫ��ɨ�裡\n");
        Error::warnNum++;//�������ۼ�
        fclose(file);
    }
}

/*
	��ʾ�ַ�
*/
void Scanner::showChar(char ch)
{

    if(ch==-1)
        printf("EOF\n");
    else if(ch=='\n')
        printf("\\n");
    else if(ch=='\t')
        printf("\\t");
    else if(ch==' ')
        printf("<b>");
    else
        printf("%c",ch);

    printf("  ");
}

/*
	���ڻ��������ַ�ɨ���㷨,�ļ�ɨ����ܺ��Զ��ر��ļ�
	��������ʹ��fread��ȡЧ�ʸ��ߣ����ݸ�����
	�ַ����ӻ�������������ȡ
*/
int Scanner::scan()
{
    if(!file)//û���ļ�
        return -1;
    if(readPos==lineLen-1)//��������ȡ���
    {
        lineLen=fread(line,1,BUFLEN,file);//���¼��ػ���������
        if(lineLen==0)//û��������
        {
            //����ļ�����,�����ļ��������-1
            lineLen=1;
            line[0]=-1;
        }
        readPos=-1;//�ָ���ȡλ��
    }
    readPos++;//�ƶ���ȡ��
    char ch=line[readPos];//��ȡ�µ��ַ�

    if(lastch=='\n')//����
    {
        lineNum++;//�к��ۼ�
        colNum=0;//�к����

    }

    if(Args::showChar)
    {
        if(colNum == 0) printf("<%d>   ",lineNum);
        showChar(ch);
        if(ch == '\n')
        {
            printf("\n\n");
        }
    }
    if(Args::showToken && colNum == 0) printf("\n");
    if(ch==-1)//�ļ��������Զ��ر�
    {
        fclose(file);
        file=NULL;
    }
    else if(ch!='\n')//���ǻ���
        colNum++;//�кŵ���
    lastch=ch;//��¼�ϸ��ַ�

    return ch;
}

/*
	��ȡ�ļ���
*/
char* Scanner::getFile()
{
    return fileName;
}

/*
	��ȡ�к�
*/
int Scanner::getLine()
{
    return lineNum;
}

/*
	��ȡ�к�
*/
int Scanner::getCol()
{
    return colNum;
}

/*******************************************************************************
                                   �ؼ��ֱ�
*******************************************************************************/

/*
	�ؼ����б��ʼ��
*/
Keywords::Keywords()
{
    //add keyword mapping here ~
    keywords["int"]=KW_INT;
    keywords["char"]=KW_CHAR;
    keywords["void"]=KW_VOID;
    keywords["extern"]=KW_EXTERN;
    keywords["if"]=KW_IF;
    keywords["else"]=KW_ELSE;
    keywords["switch"]=KW_SWITCH;
    keywords["case"]=KW_CASE;
    keywords["default"]=KW_DEFAULT;
    keywords["while"]=KW_WHILE;
    keywords["do"]=KW_DO;
    keywords["for"]=KW_FOR;
    keywords["break"]=KW_BREAK;
    keywords["continue"]=KW_CONTINUE;
    keywords["return"]=KW_RETURN;
}
/*
	�����Ƿ��ǹؼ���
*/
Tag Keywords::getTag(string name)
{
    return keywords.find(name)!=keywords.end()?keywords[name]:ID;
}

/*******************************************************************************
                                   �ʷ�������
*******************************************************************************/

Keywords Lexer::keywords;

Lexer::Lexer (Scanner&sc):scanner(sc)
{
    token=NULL;//��ʼ���ʷ��Ǻż�¼���ñ���������
    ch=' ';//��ʼ��Ϊ�ո�
}

Lexer::~Lexer ()
{
    if(!token)//ɾ���Ѿ���¼�Ĵʷ��Ǻű������ڴ棬��ֹ�ڴ����
    {
        delete token;
    }
}

/*
	��װ��ɨ�跽��
*/
bool Lexer::scan(char need)
{
    ch=scanner.scan();//ɨ����ַ�
    if(need)
    {
        if(ch!=need)//��Ԥ�ڲ��Ǻ�
            return false;
        ch=scanner.scan();//��Ԥ���Ǻϣ�ɨ����һ��
        return true;
    }
    return true;
}

//��ӡ�ʷ�����
#define LEXERROR(code) Error::lexError(code)

/*
	�����Զ���ƥ�䣬�ʷ��ǺŽ���
*/
Token* Lexer::tokenize()
{
    for(; ch!=-1;) //���˵���Ч�Ĵʷ��Ǻţ�ֻ���������ʷ��ǺŻ���NULL
    {
        Token*t=NULL;//��ʼ��һ���ʷ��Ǻ�ָ��
        while(ch==' '||ch=='\n'||ch=='\t')//���Կհ׷�
            scan();
        //��ʶ�� �ؼ���
        if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'||ch=='_')
        {
            string name="";
            do
            {
                name.push_back(ch);//��¼�ַ�
                scan();
            }
            while(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'||ch=='_'||ch>='0'&&ch<='9');
            //ƥ�����
            Tag tag=keywords.getTag(name);
            if(tag==ID)//�����ı�־��
                t=new Id(name);
            else//�ؼ���
                t=new Token(tag);
        }
        //�ַ���
        else if(ch=='"')
        {
            string str="";
            while(!scan('"'))
            {
                if(ch=='\\') //ת��
                {
                    scan();
                    if(ch=='n')
                        str.push_back('\n');
                    else if(ch=='\\')
                        str.push_back('\\');
                    else if(ch=='t')
                        str.push_back('\t');
                    else if(ch=='"')
                        str.push_back('"');
                    else if(ch=='0')
                        str.push_back('\0');
                    else if(ch=='\n');//ʲôҲ�������ַ�������
                    else if(ch==-1)
                    {
                        LEXERROR(STR_NO_R_QUTION);
                        t=new Token(ERR);
                        break;
                    }
                    else
                        str.push_back(ch);
                }
                else if(ch=='\n'||ch==-1) //�ļ�����
                {
                    LEXERROR(STR_NO_R_QUTION);
                    t=new Token(ERR);
                    break;
                }
                else
                    str.push_back(ch);
            }
            //�����ַ���
            if(!t)
                t=new Str(str);
        }
        //����
        else if(ch>='0'&&ch<='9')
        {
            int val=0;
            if(ch!='0') //10����
            {
                do
                {
                    val=val*10+ch-'0';
                    scan();
                }
                while(ch>='0'&&ch<='9');
            }
            else
            {
                scan();
                if(ch=='x') //16����
                {
                    scan();
                    if(ch>='0'&&ch<='9'||ch>='A'&&ch<='F'||ch>='a'&&ch<='f')
                    {
                        do
                        {
                            val=val*16+ch;
                            if(ch>='0'&&ch<='9')
                                val-='0';
                            else if(ch>='A'&&ch<='F')
                                val+=10-'A';
                            else if(ch>='a'&&ch<='f')
                                val+=10-'a';
                            scan();
                        }
                        while(ch>='0'&&ch<='9'||ch>='A'&&ch<='F'||ch>='a'&&ch<='f');
                    }
                    else
                    {
                        LEXERROR(NUM_HEX_TYPE);//0x��������
                        t=new Token(ERR);
                    }
                }
                else if(ch=='b') //2����
                {
                    scan();
                    if(ch>='0'&&ch<='1')
                    {
                        do
                        {
                            val=val*2+ch-'0';
                            scan();
                        }
                        while(ch>='0'&&ch<='1');
                    }
                    else
                    {
                        LEXERROR(NUM_BIN_TYPE);//0b��������
                        t=new Token(ERR);
                    }
                }
                else if(ch>='0'&&ch<='7') //8����
                {
                    do
                    {
                        val=val*8+ch-'0';
                        scan();
                    }
                    while(ch>='0'&&ch<='7');
                }
            }
            //��������
            if(!t)
                t=new Num(val);
        }
        //�ַ�
        else if(ch=='\'')
        {
            char c;
            scan();//ͬ�ַ���
            if(ch=='\\') //ת��
            {
                scan();
                if(ch=='n')
                    c='\n';
                else if(ch=='\\')
                    c='\\';
                else if(ch=='t')
                    c='\t';
                else if(ch=='0')
                    c='\0';
                else if(ch=='\'')
                    c='\'';
                else if(ch==-1||ch=='\n') //�ļ����� ����
                {
                    LEXERROR(CHAR_NO_R_QUTION);
                    t=new Token(ERR);
                }
                else
                    c=ch;//û��ת��
            }
            else if(ch=='\n'||ch==-1) //�� �ļ�����
            {
                LEXERROR(CHAR_NO_R_QUTION);
                t=new Token(ERR);
            }
            else if(ch=='\'') //û������
            {
                LEXERROR(CHAR_NO_DATA);
                t=new Token(ERR);
                scan();//��������
            }
            else
                c=ch;//�����ַ�
            if(!t)
            {
                if(scan('\'')) //ƥ���Ҳ�����,��������
                {
                    t=new Char(c);
                }
                else
                {
                    LEXERROR(CHAR_NO_R_QUTION);
                    t=new Token(ERR);
                }
            }
        }
        else
        {
            switch(ch)//���
            {
            case '#'://�����У����Ժ궨�壩
                while(ch!='\n' && ch!= -1)
                    scan();//�� �ļ�������
                t=new Token(ERR);
                break;
            case '+':
                t=new Token(scan('+')?INC:ADD);
                break;
            case '-':
                t=new Token(scan('-')?DEC:SUB);
                break;
            case '*':
                t=new Token(MUL);
                scan();
                break;
            case '/':
                scan();
                if(ch=='/') //����ע��
                {
                    while(ch!='\n' && ch!= -1)
                        scan();//�� �ļ�������
                    t=new Token(ERR);
                }
                else if(ch=='*') //����ע��,������Ƕ��ע��
                {
                    while(!scan(-1)) //һֱɨ��
                    {
                        if(ch=='*')
                        {
                            if(scan('/'))
                                break;
                        }
                    }
                    if(ch==-1)//û��������ע��
                        LEXERROR(COMMENT_NO_END);
                    t=new Token(ERR);
                }
                else
                    t=new Token(DIV);
                break;
            case '%':
                t=new Token(MOD);
                scan();
                break;
            case '>':
                t=new Token(scan('=')?GE:GT);
                break;
            case '<':
                t=new Token(scan('=')?LE:LT);
                break;
            case '=':
                t=new Token(scan('=')?EQU:ASSIGN);
                break;
            case '&':
                t=new Token(scan('&')?AND:LEA);
                break;
            case '|':
                t=new Token(scan('|')?OR:ERR);
                if(t->tag==ERR)
                    LEXERROR(OR_NO_PAIR);//||û��һ��
                break;
            case '!':
                t=new Token(scan('=')?NEQU:NOT);
                break;
            case ',':
                t=new Token(COMMA);
                scan();
                break;
            case ':':
                t=new Token(COLON);
                scan();
                break;
            case ';':
                t=new Token(SEMICON);
                scan();
                break;
            case '(':
                t=new Token(LPAREN);
                scan();
                break;
            case ')':
                t=new Token(RPAREN);
                scan();
                break;
            case '[':
                t=new Token(LBRACK);
                scan();
                break;
            case ']':
                t=new Token(RBRACK);
                scan();
                break;
            case '{':
                t=new Token(LBRACE);
                scan();
                break;
            case '}':
                t=new Token(RBRACE);
                scan();
                break;
            case -1:
                scan();
                break;
            default:
                t=new Token(ERR);//����Ĵʷ��Ǻ�
                LEXERROR(TOKEN_NO_EXIST);
                scan();
            }
        }
        //�ʷ��Ǻ��ڴ����
        if(token)
            delete token;
        token=t;//ǿ�Ƽ�¼
        if(token&&token->tag!=ERR)//��Ч,ֱ�ӷ���
            return token;
        else
            continue;//����һֱɨ��ֱ������
    }
    //�ļ�����
    if(token)
        delete token;
    return token=new Token(END);
}





















