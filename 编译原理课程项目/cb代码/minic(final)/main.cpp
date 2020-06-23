/****************************************************/
/* File: main.c                                     */
/* Main program for TINY compiler                   */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include<iostream>

using namespace std;
/* set NO_PARSE to TRUE to get a scanner-only compiler */
#define NO_PARSE FALSE
/* set NO_ANALYZE to TRUE to get a parser-only compiler */
#define NO_ANALYZE FALSE

extern "C" {
#include "util.h"
#if NO_PARSE
#include "scan.h"
#else
#include "parse.h"
#endif
}

#include "symtab.h"
/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = TRUE;
int TraceScan = TRUE;
int TraceParse = TRUE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;
int Error = FALSE;

int main()
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
                printf("-------c-minus analyis-------\n");
                printf("--open file: \n");
                printf("1.SOURCE1.C\n");
                printf("2.SOURCE2.C\n");
                printf("3.SOURCE3.C\n");
                printf("4.exit program \n");
                printf("\n");printf("\n");
                printf("please select (1-4): ");
                scanf("%d",&n);
                while(n<1||n>4)
                {
                    printf("-----wrong input, please input again: \n");
                    scanf("%d",&n);
                }
                switch(n)
                {
                case 1:
                    {
                        source=fopen("SOURCE1.C","r");
                        strcpy(pgm,"SOURCE1.C"); // 文件名
                        if (source == NULL)
                        {
                            fprintf(stderr, "File %s not found\n", pgm);
                            exit(1);
                        }
                        break;
                    }
                case 2:
                    {
                        source=fopen("SOURCE2.C","r");
                        strcpy(pgm,"SOURCE2.C"); // 文件名
                        if (source == NULL)
                        {
                            fprintf(stderr, "File %s not found\n", pgm);
                            exit(1);
                        }
                        break;
                    }
                case 3:
                    {
                        source=fopen("SOURCE3.C","r");
                        strcpy(pgm,"SOURCE3.C"); // 文件名
                        if (source == NULL)
                        {
                            fprintf(stderr, "File %s not found\n", pgm);
                            exit(1);
                        }
                        break;
                    }
                case 4: // 结束程序
                default:
                    fclose(source);//关闭文件
                    exit(0);
                }
            }
        case 2:
            {
                printf("\n*******load source code succeed!*******\n");
                printf("*******1.check source code\n"); // 查看源文件
                printf("*******2.check grammer tree\n"); // 查看语法树
                printf("*******3.语义分析\n"); // 返回上一级
                printf("*******4.return\n"); // 返回上一级
                printf("please select (1-3): ");
                scanf("%d",&n);
                while(n<1||n>4)
                {
                    printf("-----wrong input, please input again: \n");
                    scanf("%d",&n);
                }
                if(n==4)
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
                    case 1: // 打开源程序
                        {
                            while(!feof(source))
                            {
                                if(fgets(ch,120,source)!=0)
                                    printf("%s",ch);
                            }
                            fseek(source,0L,0);
                            break;//读取结束，将文件指针指向头位置
                        }
                    case 2: // 查看生成树
                        {
                            //listing = fopen("test.txt", "w");
                            listing = stdout;
                            fprintf(listing, "\nTINY COMPILATION: %s\n\n", pgm);
//                            // 进行重置
//                            linepos = 0; /* current position in LineBuf */
//                            bufsize = 0; /* current size of buffer string */
//                            EOF_flag = FALSE; /* corrects ungetNextChar behavior on EOF */
                            syntaxTree = parse(); // 生成
                            fprintf(listing, "Syntax tree:\n\n");
                            printTree(syntaxTree);
                            fseek(source,0L,0);
                            //fclose(listing);
                            break;//读取结束，将文件指针指向头位置
                        }
                    case 3: // 语义分析
                        {
                            createSYMTAB(syntaxTree);
                            printSYMTAB();
                            checkNode(syntaxTree);
                            break;//读取结束，将文件指针指向头位置
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

