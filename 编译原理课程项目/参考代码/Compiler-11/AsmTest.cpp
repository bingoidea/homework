#include <iostream>
#include"global.h"
#include"Parser.h"
#include<stdio.h>
using namespace std;
/** \brief �����뵥Ԫ����
 *
 * \param 2018.4.30
 * \param James Bond
 * \return Ҫ�������Ϊ����ʹ�õķ�ʽ���������л�����������еİ汾
 *���ʵ�� printf write read ��������������������������������
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
