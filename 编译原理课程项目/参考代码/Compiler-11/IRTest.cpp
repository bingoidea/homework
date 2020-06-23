#include <iostream>
#include"global.h"
#include"Parser.h"
using namespace std;

/** \brief 中间代码单元测试
 *
 * \param 2018.4.30
 * \param James Bond
 * \return 将中间代码逐行打印出来，查看是否正确.
 *问题：表达式中间变量存入变量表是有没有记录其值，有没有影响
 *表达式中间变量存入变量表有什么作用
 *
 */
int main___()
{
    filename = "test5.txt";
    Parser *parser = new Parser(filename);
    parser->analyze();
    symtab->ShowIR();
}
