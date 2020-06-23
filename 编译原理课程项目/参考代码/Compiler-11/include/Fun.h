#ifndef FUN_H
#define FUN_H
#include"InterInst.h"
#include"Lex.h"
#include"global.h"
class Fun
{
    public:
       Fun(bool ext,_TokenType type,string n,vector<Var*> &paraList);
       Fun();

       bool externed;
       bool IODepthflag;
       _TokenType type;
       string name;
       vector<Var*> paraVar;/**< �βα����б� */
       int maxDepth;/**< ջ�������ȣ����ۼ� */
       int curEsp;/**< ��ǰջָ��λ��esp */
       vector<int> ScopeEsp;/**<��̬��¼ÿ��������Ĵ�С  */
       vector<InterInst*> interCode;/**<   Ŀ�����*/
        InterInst *returnPoint;/**< ���ص�λ�� */
        void enterScope();
        void leaveScope();
        void locate(Var *var);
        bool match(Fun *fun);
        bool match(vector<Var*> &args);
        void define(Fun *def);
    protected:

    private:
};

#endif // FUN_H
