#include <iostream>
#include"global.h"
#include"Parser.h"
using namespace std;
/** \brief �﷨�������﷨�Ƶ������������Ԫ����
 *
 * \param 2018.4.29
 * \param James Bond
 * \return
 *��ͨ�����ֲ���4.30
 *���⣺scopeLen_print ���Ľ���뿪ʼ��һ���������𣿣�������������
 */

int main____()
{
    filename = "test5.txt";
    Parser *parser = new Parser(filename);
    parser->analyze();

}
