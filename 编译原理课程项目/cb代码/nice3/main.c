/****************************************************/
/* File: main.c                                     */
/* main file for  C-  compiler                      */
/* C- Compiler Project				    */
/* ZEBRA 	                                    */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"
#include "analyze.h"
#include "cgen.h"


/* allocate global variables */
int lineno = 0;
int HighScope=0;
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = TRUE;
int TraceScan = TRUE;
int TraceParse = TRUE;
int TraceAnalyze = TRUE;
int TraceCode = TRUE;

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
                printf("-------c-minus analyis-------\n");
                printf("--open file: \n");
                printf("1.test1.cm\n");
                printf("2.test2.cm\n");
                printf("3.exit program \n");
                printf("\n");printf("\n");
                printf("please select (1-3): ");
                scanf("%d",&n);
                while(n<1||n>3)
                {
                    printf("-----wrong input, please input again: \n");
                    scanf("%d",&n);
                }
                switch(n)
                {
                case 1: // ���ļ�WhileSample.tiny
                    {
                        source=fopen("test1.cm","r");
                        strcpy(pgm,"test1.cm"); // �ļ���
                        if (source == NULL)
                        {
                            fprintf(stderr, "File %s not found\n", pgm);
                            exit(1);
                        }
                        break;
                    }
                case 2: // ���ļ�DoWhileSample.tiny
                    {
                        source=fopen("test2.cm","r");
                        strcpy(pgm,"test2.cm"); // �ļ���
                        if (source == NULL)
                        {
                            fprintf(stderr, "File %s not found\n", pgm);
                            exit(1);
                        }
                        break;
                    }
                case 3: // ��������
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
                printf("*******3.anaylsis\n"); // �鿴�﷨��
                printf("*******4.cgen\n"); // �鿴�﷨��
                printf("*******5.return\n"); // ������һ��
                printf("please select (1-5): ");
                scanf("%d",&n);
                while(n<1||n>5)
                {
                    printf("-----wrong input, please input again: \n");
                    scanf("%d",&n);
                }
                if(n==5)
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
                    case 3: // �������(��һ���bug����ò�Ҫ�ظ�����)
                        {
                            listing = stdout;
                            scope_a=0;
                            int i;
                            for(i = 0; i < MAX_SCOPE; i++) location[i] = 0;
                            No_change=0;

                            fprintf(listing,"\nBuilding Symbol Table...\n");
                            buildSymtab(syntaxTree);
                            fprintf(listing,"\nChecking Types...\n");
                            typeCheck(syntaxTree);
                            fprintf(listing,"\nType Checking Finished\n");
                            break;
                        }
                    case 4: // �м����
                        {
                            if (! Error)
                            {
                                char * codefile;
                                int fnlen = strcspn(pgm,".");
                                codefile = (char *) calloc(fnlen+4, sizeof(char));
                                strncpy(codefile,pgm,fnlen);
                                strcat(codefile,".tm");
                                code = fopen(codefile,"w");
                                if (code == NULL)
                                {
                                    printf("Unable to open %s\n",codefile);
                                    exit(1);
                                }
                                codeGen(syntaxTree,codefile);
                                if (TraceCode)
                                    fprintf(listing,"\nCode generated in file %s\n",codefile);
                                fclose(code);
                            }
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

//    TreeNode * syntaxTree;
//    char *pgm; /* source code file name */
////  if (argc != 2)
////    { fprintf(stderr,"usage: %s <filename>\n",argv[0]);
////      exit(1);
////    }
////  strcpy(pgm,argv[1]) ;
//    pgm = "test2.cm";
//    if (strchr (pgm, '.') == NULL)
//        strcat(pgm,".tny");
//    source = fopen(pgm,"r");
//    if (source==NULL)
//    {
//        fprintf(stderr,"File %s not found\n",pgm);
//        exit(1);
//    }
//    listing = stdout; /* send listing to screen */
//    fprintf(listing,"\nC- COMPILATION: %s\n",pgm);
//#if NO_PARSE
//    while (getToken()!=ENDFILE);
//#else
//    syntaxTree = parse();
//    if (TraceParse)
//    {
//        fprintf(listing,"\nSyntax tree:\n");
//        printTree(syntaxTree);
//    }
//#if !NO_ANALYZE
//    if (! Error)
//    {
//        if (TraceAnalyze) fprintf(listing,"\nBuilding Symbol Table...\n");
//        buildSymtab(syntaxTree);
//        if (TraceAnalyze) fprintf(listing,"\nChecking Types...\n");
//        typeCheck(syntaxTree);
//        if (TraceAnalyze) fprintf(listing,"\nType Checking Finished\n");
//    }
//
//
//#if !NO_CODE
//    if (! Error)
//    {
//        char * codefile;
//        int fnlen = strcspn(pgm,".");
//        codefile = (char *) calloc(fnlen+4, sizeof(char));
//        strncpy(codefile,pgm,fnlen);
//        strcat(codefile,".tm");
//        code = fopen(codefile,"w");
//        if (code == NULL)
//        {
//            printf("Unable to open %s\n",codefile);
//            exit(1);
//        }
//        codeGen(syntaxTree,codefile);
//        if (TraceCode)
//            fprintf(listing,"\nCode generated in file %s\n",codefile);
//        fclose(code);
//    }
//#endif
//#endif
//#endif
//    fclose(source);
    return 0;
}

