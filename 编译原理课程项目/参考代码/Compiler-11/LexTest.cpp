#include<iostream>
#include"global.h"

using namespace std;
/** \brief  �ʷ�������Ԫ����
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
    cout<<"���\t"<<"�к�\t"<<"�к�\t"<<"��������\t"<<"����"<<endl;
    Token *token = lex->tokenize();
    while(token->type!=END)
    {
        lex->LexShow(token);
        token = lex->tokenize();
    }
}
