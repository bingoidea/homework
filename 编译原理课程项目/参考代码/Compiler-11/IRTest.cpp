#include <iostream>
#include"global.h"
#include"Parser.h"
using namespace std;

/** \brief �м���뵥Ԫ����
 *
 * \param 2018.4.30
 * \param James Bond
 * \return ���м�������д�ӡ�������鿴�Ƿ���ȷ.
 *���⣺���ʽ�м�����������������û�м�¼��ֵ����û��Ӱ��
 *���ʽ�м���������������ʲô����
 *
 */
int main___()
{
    filename = "test5.txt";
    Parser *parser = new Parser(filename);
    parser->analyze();
    symtab->ShowIR();
}
