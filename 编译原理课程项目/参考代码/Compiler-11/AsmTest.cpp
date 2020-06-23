#include <iostream>
#include"global.h"
#include"Parser.h"
#include<stdio.h>
using namespace std;
/** \brief 汇编代码单元测试
 *
 * \param 2018.4.30
 * \param James Bond
 * \return 要求汇编代码为可以使用的方式，放在已有汇编器可以运行的版本
 *如何实现 printf write read 函数？？？？？？？？？？？？？？
 *
 */
int main________________()
{
    filename = "test5.txt";
    targetFile = "targetasm.txt";
    Parser *parser = new Parser(filename);
    parser->analyze();
    symtab->ShowIR();
    if((file = fopen(targetFile,"w"))==NULL) {cout<<"cannot create the file"<<endl;exit(0);}
    symtab->genAsm();
}
