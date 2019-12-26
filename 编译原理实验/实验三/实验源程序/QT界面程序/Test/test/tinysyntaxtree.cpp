//#include "globals.h"
//#include "util.h"
//#include "scan.h"
//#include "parse.h"
//#include "tinysyntaxtree.h"
//#include "mainwindow.h"
//#include <QDebug>

///* allocate global variables */
//int lineno = 0;
//FILE * source;
//FILE * listing;
//FILE * code;

///* allocate and set tracing flags */
//int EchoSource = FALSE;
//int TraceScan = FALSE;
//int TraceParse = FALSE;
//int TraceAnalyze = FALSE;
//int TraceCode = FALSE;
//int Error = FALSE;

//bool tinySyntaxTree()
//{
//    qDebug() << MainWindow().getFileName();
//    return true;
//}

//void tinySyntaxTree()
//{
//    TreeNode * syntaxTree;
//    char pgm[120],ch[120];
//    int n, flag = 1;
//    while(flag)
//    {
//        switch(flag)
//        {
//        case 1:
//            {
//                printf("-------TINY analyis-------\n");
//                printf("--open file: \n");
//                printf("1.WhileSample.tiny\n");
//                printf("2.DoWhileSample.tiny\n");
//                printf("3.ForSample.tiny\n");
//                printf("4.exit program \n");
//                printf("\n");printf("\n");
//                printf("please select (1-4): ");
//                scanf("%d",&n);
//                while(n<1||n>4)
//                {
//                    printf("-----wrong input, please input again: \n");
//                    scanf("%d",&n);
//                }
//                switch(n)
//                {
//                case 1: // 打开文件WhileSample.tiny
//                    {
//                        source=fopen("WhileSample.tiny","r");
//                        strcpy(pgm,"WhileSample.tiny"); // 文件名
//                        if (source == NULL)
//                        {
//                            fprintf(stderr, "File %s not found\n", pgm);
//                            exit(1);
//                        }
//                        break;
//                    }
//                case 2: // 打开文件DoWhileSample.tiny
//                    {
//                        source=fopen("DoWhileSample.tiny","r");
//                        strcpy(pgm,"DoWhileSample.tiny"); // 文件名
//                        if (source == NULL)
//                        {
//                            fprintf(stderr, "File %s not found\n", pgm);
//                            exit(1);
//                        }
//                        break;
//                    }
//                case 3: // 打开文件ForSample.tiny
//                    {
//                        source=fopen("ForSample.tiny","r");
//                        strcpy(pgm,"ForSample.tiny"); // 文件名
//                        if (source == NULL)
//                        {
//                            fprintf(stderr, "File %s not found\n", pgm);
//                            exit(1);
//                        }
//                        break;
//                    }
//                case 4: // 结束程序
//                default:
//                    fclose(source);//关闭文件
//                    exit(0);
//                }
//            }
//        case 2:
//            {
//                printf("*******load source code succeed!*******\n");
//                printf("*******1.check source code\n"); // 查看源文件
//                printf("*******2.check grammer tree\n"); // 查看语法树
//                printf("*******3.return\n"); // 返回上一级
//                printf("please select (1-3): ");
//                scanf("%d",&n);
//                while(n<1||n>3)
//                {
//                    printf("-----wrong input, please input again: \n");
//                    scanf("%d",&n);
//                }
//                if(n==3)
//                {
//                    flag = 1;
//                    fclose(source);
//                    break;
//                }
//                else
//                {
//                    flag = 2;
//                    switch(n)
//                    {
//                    case 1: // 打开源程序
//                        {
//                            while(!feof(source))
//                            {
//                                if(fgets(ch,120,source)!=0)
//                                    printf("%s",ch);
//                            }
//                            fseek(source,0L,0);
//                            break;//读取结束，将文件指针指向头位置
//                        }
//                    case 2: // 查看生成树
//                        {
//                            //listing = fopen("test.txt", "w");
//                            listing = stdout;
//                            fprintf(listing, "\nTINY COMPILATION: %s\n\n", pgm);
//                            // 进行重置
//                            linepos = 0; /* current position in LineBuf */
//                            bufsize = 0; /* current size of buffer string */
//                            EOF_flag = FALSE; /* corrects ungetNextChar behavior on EOF */
//                            syntaxTree = parse(); // 生成
//                            fprintf(listing, "Syntax tree:\n\n");
//                            printTree(syntaxTree);
//                            fseek(source,0L,0);
//                            //fclose(listing);
//                            break;//读取结束，将文件指针指向头位置
//                        }
//                    }
//                }
//            }
//        case 3:
//            {
//                printf("\n");
//                printf("*****1.return\n");
//                printf("*****2.exit program\n");
//                printf("please select (1-2): ");
//                scanf("%d",&n);
//                while(n<1||n>2)
//                {
//                    printf("*****wrong input, please input again: \n");
//                    scanf("%d",&n);
//                }
//                if(n==1)
//                    flag=2;
//                else if(n==2)
//                    flag=0;
//            }
//        }
//    }
//    fclose(source);
//    fclose(listing);
//}
