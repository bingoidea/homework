#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = FALSE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;
int Error = FALSE;

int main( int argc, char * argv[] )
{
    TreeNode * syntaxTree;
    char pgm[120],ch[120];
    int n, flag = 1;
    while(flag)
    {
        switch(flag)
        {
        case 1:
            {
                printf("-------TINY analyis-------\n");
                printf("--open file: \n");
                printf("1.WhileSample.tiny\n");
                printf("2.DoWhileSample.tiny\n");
                printf("3.ForSample.tiny\n");
                printf("4.TestSample.tiny\n");
                printf("5.exit program \n");
                printf("\n");printf("\n");
                printf("please select (1-5): ");
                scanf("%d",&n);
                while(n<1||n>5)
                {
                    printf("-----wrong input, please input again: \n");
                    scanf("%d",&n);
                }
                switch(n)
                {
                case 1: // ���ļ�WhileSample.tiny
                    {
                        source=fopen("WhileSample.tiny","r");
                        strcpy(pgm,"WhileSample.tiny"); // �ļ���
                        if (source == NULL)
                        {
                            fprintf(stderr, "File %s not found\n", pgm);
                            exit(1);
                        }
                        break;
                    }
                case 2: // ���ļ�DoWhileSample.tiny
                    {
                        source=fopen("DoWhileSample.tiny","r");
                        strcpy(pgm,"DoWhileSample.tiny"); // �ļ���
                        if (source == NULL)
                        {
                            fprintf(stderr, "File %s not found\n", pgm);
                            exit(1);
                        }
                        break;
                    }
                case 3: // ���ļ�ForSample.tiny
                    {
                        source=fopen("ForSample.tiny","r");
                        strcpy(pgm,"ForSample.tiny"); // �ļ���
                        if (source == NULL)
                        {
                            fprintf(stderr, "File %s not found\n", pgm);
                            exit(1);
                        }
                        break;
                    }
                case 4: // ���ļ�TestSample.tiny
                    {
                        source=fopen("TestSample.tiny","r");
                        strcpy(pgm,"TestSample.tiny"); // �ļ���
                        if (source == NULL)
                        {
                            fprintf(stderr, "File %s not found\n", pgm);
                            exit(1);
                        }
                        break;
                    }
                case 5: // ��������
                default:
                    fclose(source);//�ر��ļ�
                    exit(0);
                }
            }
        case 2:
            {
                printf("*******load source code succeed!*******\n");
                printf("*******1.check source code\n"); // �鿴Դ�ļ�
                printf("*******2.check grammer tree\n"); // �鿴�﷨��
                printf("*******3.return\n"); // ������һ��
                printf("please select (1-3): ");
                scanf("%d",&n);
                while(n<1||n>3)
                {
                    printf("-----wrong input, please input again: \n");
                    scanf("%d",&n);
                }
                if(n==3)
                {
                    flag = 1;
                    fclose(source);
                    break;
                }
                else
                {
                    flag = 2;
                    switch(n)
                    {
                    case 1: // ��Դ����
                        {
                            while(!feof(source))
                            {
                                if(fgets(ch,120,source)!=0)
                                    printf("%s",ch);
                            }
                            fseek(source,0L,0);
                            break;//��ȡ���������ļ�ָ��ָ��ͷλ��
                        }
                    case 2: // �鿴������
                        {
                            //listing = fopen("test.txt", "w");
                            listing = stdout;
                            fprintf(listing, "\nTINY COMPILATION: %s\n\n", pgm);
                            // ��������
                            linepos = 0; /* current position in LineBuf */
                            bufsize = 0; /* current size of buffer string */
                            EOF_flag = FALSE; /* corrects ungetNextChar behavior on EOF */
                            syntaxTree = parse(); // ����
                            fprintf(listing, "Syntax tree:\n\n");
                            printTree(syntaxTree);
                            fseek(source,0L,0);
                            //fclose(listing);
                            break;//��ȡ���������ļ�ָ��ָ��ͷλ��
                        }
                    }
                }
            }
        case 3:
            {
                printf("\n");
                printf("*****1.return\n");
                printf("*****2.exit program\n");
                printf("please select (1-2): ");
                scanf("%d",&n);
                while(n<1||n>2)
                {
                    printf("*****wrong input, please input again: \n");
                    scanf("%d",&n);
                }
                if(n==1)
                    flag=2;
                else if(n==2)
                    flag=0;
            }
        }
    }
    fclose(source);
    fclose(listing);

    return 0;
}
