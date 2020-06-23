#include "symtab.h"
#include "globals.h"
#include <vector>
#include <set>
#include <iostream>
using namespace std;

/* ���� */
struct SYMBOL
{
    char* name;
    int type;
    bool isID; //�Ƿ��Ǳ�����trueΪ������falseΪ����
    bool isArray; //�Ƿ������飬trueΪ�ǣ�falseΪ��
    int line;
    set<int> locations; //�õ��ĵط�
    SYMBOL() {}
    SYMBOL(char* name, int type, bool isID, bool isArray, int line)
    {
        this->name = name;
        this->type = type;
        this->isID = isID;
        this->isArray = isArray;
        this->line = line;
        locations.clear();
    }
    void addLocations(int line)
    {
        locations.insert(line);
    }
    void SYMBOLPrint()
    {
        fprintf(listing, "name:%-6s\ttype:%-5s\t%-5s\tisArray:%-2d\tline:%-3dlocations:", this->name, typeToString(this->type), (this->isID)?"ID":"FUNC", this->isArray, this->line);
        for (set<int>::iterator it = locations.begin(); it != locations.end(); it++) fprintf(listing, "%-3d", *it);
        //for (int i=0; i<locations.size(); i++) printf("%-3d", locations[i]);
        //putchar('\n');
        fprintf(listing, "\n");
    }
    char* typeToString(int type)
    {
        if (type == 262) return "INT";
        else if (type == 263) return "VOID";
        return "UNDEFINED";
    }
};
/* �������ű� */
struct SYMTABLE
{
    int deep;
    vector<SYMBOL> mSYMTABLE;
    SYMTABLE() {}
    SYMTABLE(int deep, vector<SYMBOL> mSYMTABLE)
    {
        this->deep = deep;
        this->mSYMTABLE = mSYMTABLE;
    }
};
/* ������ű� */
vector<SYMTABLE> SYMTABLEs;

vector<SYMBOL> temp[100];//��ά���飬һ�������ȣ�������

int deep = 0; //���ĸ���������
vector<SYMBOL> lazySYMBOL; //���Դ洢�ռ�

/* �ҵ������λ�ã�������ʹ�õ����� */
bool findDefined(char* name, bool isID, int deep, int line)
{
    for (int i=deep; i>=0; i--)
    {
        for (int j=0; j<temp[i].size(); j++)
        {
            if (!strcmp(temp[i][j].name, name) && isID == temp[i][j].isID)
            {
                temp[i][j].addLocations(line);
                return true;
            }
        }
    }
    fprintf(listing, "line %d: %s is used but not be defined.\n", line, name);
    return false;
}

/* ���ɷ��ű� */
void createSYMTAB(TreeNode* tree)
{
    int i;
    bool flag = false, isDefined = false;
    while (tree != NULL)
    {
        flag = false;
        if (tree->nodekind==StmtK)
        {
            switch (tree->kind.stmt)
            {
            case ComK://������{...}
                // cout<<"line:"<<tree->lineno<<endl;
                deep++;
                flag = true;
//                cout<<"lazy:"<<endl;
//                for(auto lazy : lazySYMBOL)
//                    lazy.SYMBOLPrint();
                temp[deep] = lazySYMBOL;
                lazySYMBOL.clear();
                break;
            case CallK:
                if (strcmp(tree->attr.name,"input") && strcmp(tree->attr.name, "output")) //�ų���ϵͳ����
                    findDefined(tree->attr.name, false, deep, tree->lineno);
                break;
            default:
                break;
            }
        }
        else if (tree->nodekind==DecK)   //�������������
        {
            switch (tree->kind.dec)
            {
            case VarINTK:
                if (tree->num == -1) temp[deep].push_back(SYMBOL(tree->attr.name, INT, true, false, tree->lineno));//����
                else temp[deep].push_back(SYMBOL(tree->attr.name, INT, true, true, tree->lineno));//��������
                break;
            case FunINTK:
                temp[deep].push_back(SYMBOL(tree->attr.name, INT, false, false, tree->lineno));
                break;
            case VarVOIDK:
                if (tree->num == -1) temp[deep].push_back(SYMBOL(tree->attr.name, VOID, true, false, tree->lineno));
                else temp[deep].push_back(SYMBOL(tree->attr.name, VOID, true, true, tree->lineno));
                break;
            case FunVOIDK:
                temp[deep].push_back(SYMBOL(tree->attr.name, VOID, false, false, tree->lineno));
                break;
            case ParINTK://�����Ĳ���
                //cout<<"ParINTK"<<tree->attr.name<<" "<<tree->lineno<<endl;
                if (tree->num == -1) lazySYMBOL.push_back(SYMBOL(tree->attr.name, INT, true, false, tree->lineno));
                else lazySYMBOL.push_back(SYMBOL(tree->attr.name, INT, true, true, tree->lineno));
                break;
            case ParVOIDK:
                // cout<<"ParVOIDK"<<tree->attr.name<<" "<<tree->lineno<<endl;
                if (tree->num == -1) lazySYMBOL.push_back(SYMBOL(tree->attr.name, VOID, true, false, tree->lineno));
                else lazySYMBOL.push_back(SYMBOL(tree->attr.name, VOID, true, true, tree->lineno));
                break;
            case VarK:
                findDefined(tree->attr.name, true, deep, tree->lineno);
                break;
            default:
                //fprintf(listing,"Unknown DecNode kind\n");
                break;
            }
        }
        else if (tree->nodekind==ExpK)  //����Ǳ�ʾ����
        {
            switch (tree->kind.exp)
            {
            case IdK:
                findDefined(tree->attr.name, true, deep, tree->lineno);
                break;
            default:
                break;
            }
        }
        //else fprintf(listing,"Unknown node kind\n");

        //����Ҫ�ȴ�����Լ�����ȥ�Ӽ�
        for (i=0; i<MAXCHILDREN; i++)
            createSYMTAB(tree->child[i]);
        if (flag)  //�������}��˵Ҫ�ƽ�����
        {
            SYMTABLEs.push_back(SYMTABLE(deep, temp[deep]));
            //cout<<"push"<<endl;
//            for(auto lazy : temp[deep])
//                lazy.SYMBOLPrint();
            deep--;
        }
        tree = tree->sibling;
    }
}

void printSYMTAB()
{
    SYMTABLEs.push_back(SYMTABLE(0, temp[0]));//���һ��ȫ����������
    for(int i=0; i<SYMTABLEs.size(); i++)
    {
        SYMTABLE tempSYMTABLE = SYMTABLEs[i];
        vector<SYMBOL> mSYMTABLE = tempSYMTABLE.mSYMTABLE;
        fprintf(listing, "Deep is %d\n", tempSYMTABLE.deep);
        for(int j=0; j<mSYMTABLE.size(); j++)
        {
            mSYMTABLE[j].SYMBOLPrint();
        }
    }
}

void typeError(TreeNode * t, char * message)
{
    fprintf(listing, "Type error at line %d: %s\n", t->lineno, message);
}

/* ��ö�Ӧ���Ŷ����Ƿ������ */
Type getType(char* name, int line)
{
    if (!strcmp(name, "input") || !strcmp(name, "output")) return Integer; //ϵͳ����
    for (int i=0; i<SYMTABLEs.size(); i++)
    {
        SYMTABLE tempSYMTABLE = SYMTABLEs[i];
        vector<SYMBOL> mSYMTABLE = tempSYMTABLE.mSYMTABLE;
        for(int j=0; j<mSYMTABLE.size(); j++)
        {
            if (!strcmp(name, mSYMTABLE[j].name))  //���������ͬ
            {
                for(set<int>::iterator it=mSYMTABLE[j].locations.begin(); it!=mSYMTABLE[j].locations.end(); it++)
                {
                    if (line == *it)    //�����Ӧ����ͬ���鿴�Ƿ��Ӧ��ǩ
                    {
                        //cout<<name<<" "<<line<<" "<<mSYMTABLE[j].type<<endl;
                        if (mSYMTABLE[j].type == 262)
                        {
                            //cout<<"INt"<<endl;
                            return Integer;
                        }
                        else if (mSYMTABLE[j].type == 263)
                        {
                            //cout<<"VOID"<<endl;
                            return Void;
                        }

                    }
                }
            }
        }
    }
    return TError;
}
extern "C" {
#include "util.h"
}
/* ���Ӽ������ҵ������������ */
Type findReturnKType(TreeNode * t, int deep)
{
    if (t == NULL) return TError;
    /*cout<<"--------------------"<<endl;
    printTree(t);
    cout<<"--------------------"<<endl;*/
    if (t->nodekind == StmtK && t->kind.stmt == ReturnK) return t->type;//return ���ǿ�
    Type resultType = TError;
    //�����Ӽ�
    for (int i=0; i<MAXCHILDREN; i++)
    {
        Type temp = findReturnKType(t->child[i], deep+1);
        if (temp != TError)
        {
            if (resultType == TError) resultType = temp; //��δ�õ�һ������ֵ
            else if (resultType != temp)   //�������ֵ���Ͳ�ͬ
            {
                printf("return type error.\n");
                return TError;
            }
        }
    }
    //�����ֵܼ�
    if (deep && t->sibling != NULL)
    {
        Type temp = findReturnKType(t->sibling, deep);
        if (temp != TError)
        {
            if (resultType == TError) resultType = temp; //��δ�õ�һ������ֵ
            else if (resultType != temp)   //�������ֵ���Ͳ�ͬ
            {
                printf("return type error.\n");
                return TError;
            }
        }
    }
    return resultType;
}

Type getexptype(TreeNode * t)
{
    TreeNode *p1,*p2;
    if(t->kind.exp == ConstK)
    {
        t->type  = Integer;

        // type1 = p1->type;
        //cout<<"yes1"<<endl;
    }
    else if(t->kind.exp == IdK)
    {
        t->type = getType(t->attr.name, t->lineno);
        if (t->type == TError)  printf("line %d: %s is used but not be defined.\n", t->lineno, t->attr.name);
    }
    else
    {
        p1 = t->child[0];
        p2 = t->child[1];
        p1->type = getexptype(p1);
        p2->type = getexptype(p2);
        if (p1->type != p2->type)
        {
            typeError(t, "Op applied to different type.");
        }
        t->type = p1->type;
    }
    return t->type;

}

void checkNode(TreeNode * t)
{
    TreeNode *p1,*p2;
    if (t == NULL) return;
    for (int i=0; i<MAXCHILDREN; i++) //��ҪҪ��ȥ�Ӽ�����Ϊ�����������������һ���������չȷ��
        checkNode(t->child[i]);
    Type type = TError;
    switch(t->nodekind)
    {
    case ExpK:
        switch(t->kind.exp)
        {
        case OpK: //��������ţ���������������Ҫ���
//            p1 = t->child[0];
//            p2 = t->child[1];
//            //Type type1,type2;
//            if(p1->kind.exp == ConstK)
//            {
//                p1->type  = Integer;
//                // type1 = p1->type;
//                //cout<<"yes1"<<endl;
//            }
//            else if(p1->kind.exp == IdK)
//                p1->type = getType(p1->attr.name, p1->lineno);
////            else
////            {
////
////            }
//            //cout<<"type1 "<<p1->type <<endl;
//            if(p2->kind.exp == ConstK)
//            {
//
//                p2->type  = Integer;
//                //type2 = p2->type;
//               // cout<<"yes2"<<endl;
//            }
//            else if(p2->kind.exp == IdK)
//                p2->type = getType(p2->attr.name, p2->lineno);
////            else
////            {
////
////            }
//            //cout<<"type2 "<<p2->type <<endl;
//            if (p1->type != p2->type)
//            {
//                typeError(t, "Op applied to different type.");
//            }
            t->type = getexptype(t);
            if ((t->attr.op == EQ)
                    ||(t->attr.op == NEQ)
                    ||(t->attr.op == LT)
                    ||(t->attr.op == LET)
                    ||(t->attr.op == GT)
                    ||(t->attr.op == GET))
                t->type = Boolean;
            else
                t->type = t->child[0]->type;
            break;
        case ConstK:
            t->type = Integer;
            break;
        case IdK:
            t->type = getType(t->attr.name, t->lineno);
            if (t->type == TError)  fprintf(listing, "line %d: %s is used but not be defined.\n", t->lineno, t->attr.name);

            break;
        default:
            break;
        }
        break;
    case StmtK:
        switch(t->kind.stmt)
        {
        case IfK:
            if (t->child[0]->type != Boolean)
                typeError(t->child[0], "If test is not Boolean.");
            break;
        case WhileK:
            if (t->child[0]->type != Boolean)
                typeError(t->child[0], "While test is not Boolean.");
            break;
        case ComK://{...}���ֵ�ֱ�������ҵ�return�Ǿ�
            t->type = findReturnKType(t, 0);
            break;
        case ReturnK:
            if (t->child[0] != NULL) //�з���ֵ
                t->type = t->child[0]->type;
            else
                t->type = Void;
            break;
        case AssignK:
            if (t->child[0]->type != t->child[1]->type)
                typeError(t, "Assign applied to different type.");
            break;
        case CallK:
            type = getType(t->attr.name, t->lineno);
            if (type != TError) t->type = type;
            else fprintf(listing, "line %d: %s is used but not be defined.\n", t->lineno, t->attr.name);
            break;
        default:
            break;
        }
        break;
    case DecK:
        switch(t->kind.dec)
        {
        case VarINTK:
            t->type = Integer;
            //cout<<"name "<<t->attr.name<<endl;
            break;
        case FunINTK:
            if (t->child[1]->type != Integer)//1 �Ǻ����壬0�ǲ���
                typeError(t, "Integer Func's return is not Integer.");
            break;
        case VarVOIDK:
            t->type = Void;
            break;
        case FunVOIDK:
            if (t->child[1]->type != Void)
                typeError(t, "Void Func's return is not Void.");
            break;
        case ParINTK:
            t->type = Integer;
            break;
        case ParVOIDK:
            t->type = Void;
            break;
        case VarK:
            type = getType(t->attr.name, t->lineno);
            if (type != TError) t->type = type;
            else fprintf(listing, "line %d: %s is used but not be defined.\n", t->lineno, t->attr.name);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    if (t->sibling != NULL)
        checkNode(t->sibling);

}



