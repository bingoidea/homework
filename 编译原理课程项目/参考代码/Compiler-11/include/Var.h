#ifndef VAR_H
#define VAR_H
#include<vector>
#include<string>
#include"TokenType.h"
#include"Token.h"
#include"global.h"
#include"Lex.h"
using namespace std;


class Var
{
    public:
        bool literal;
        vector<int> scopepath;
        bool externed;
        _TokenType type;
        string name;
        bool isPtr;
        bool isPara;
        bool isArray;
        int arraySize;
        bool isLeft;
        Var* initdata;/**< ��ʼ�����ʽ�Ľ������ */
        bool inited;
        union{
            int intVal;
            char charVal;
        };
        string strVal;
        string ptrVal;
        Var *ptr;/**< ��ǰ������ָ���������ָ�����ı��� */
        Var *pointTo;/**< �����ǰ������ָ�����������ָ��ı��� */
        int _size;
        int offset;/**< ջ֡ƫ�� */

        //------------------------------------------------method
        Var(vector<int> scopepath,bool ext,_TokenType _type,string name,bool isPtr,bool isArray,int arraySize,bool isLeft,Var *initdata,bool inited);
        Var(Token *token);
        Var(vector<int> scopepath, _TokenType _type,bool isPtr);
        Var(vector<int> scopepath,Var *val);
        Var();
        void _clear();
        bool isBase();
        void setType(_TokenType type);
        void setArray(int len);
        bool setInit();
        bool isVoid();
        static Var* getStep(Var* val);
        string getRawStr();
        static Var* getVoid();
        static Var* getTrue();
    protected:

    private:
};

#endif // VAR_H
