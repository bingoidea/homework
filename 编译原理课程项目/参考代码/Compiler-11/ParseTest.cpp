#include <iostream>
#include"global.h"
#include"Parser.h"
using namespace std;
/** \brief 语法分析及语法制导的语义分析单元测试
 *
 * \param 2018.4.29
 * \param James Bond
 * \return
 *已通过部分测试4.30
 *问题：scopeLen_print 最后的结果与开始不一致是正常吗？？？？？？？？
 */

int main____()
{
    filename = "test5.txt";
    Parser *parser = new Parser(filename);
    parser->analyze();

}
