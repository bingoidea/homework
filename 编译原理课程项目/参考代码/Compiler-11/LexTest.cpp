#include<iostream>
#include"global.h"

using namespace std;
/** \brief  词法分析单元测试
 *
 * \param 2018.4.29
 * \param James Bond
 * \return
 *
 */

int _main_()
{
    filename = "test_cmp.txt";
    lex = new Lex(filename);
    cout<<"序号\t"<<"行号\t"<<"列号\t"<<"符号类型\t"<<"符号"<<endl;
    Token *token = lex->tokenize();
    while(token->type!=END)
    {
        lex->LexShow(token);
        token = lex->tokenize();
    }
}
