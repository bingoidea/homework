#include "symtab.h"
#include "globals.h"
#include <vector>
#include <set>
#include <iostream>
using namespace std;

/* 符号 */
struct SYMBOL
{
    char* name;
    int type;
    bool isID; //是否是变量，true为变量，false为函数
    bool isArray; //是否是数组，true为是，false为否
    int line;
    set<int> locations; //用到的地方
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
/* 单个符号表 */
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
/* 多个符号表 */
vector<SYMTABLE> SYMTABLEs;

vector<SYMBOL> temp[100];//二维数组，一层代表深度（作用域）

int deep = 0; //在哪个作用域内
vector<SYMBOL> lazySYMBOL; //惰性存储空间

/* 找到定义的位置，并加入使用的行数 */
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

/* 生成符号表 */
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
            case ComK://混合语句{...}
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
                if (strcmp(tree->attr.name,"input") && strcmp(tree->attr.name, "output")) //排除掉系统函数
                    findDefined(tree->attr.name, false, deep, tree->lineno);
                break;
            default:
                break;
            }
        }
        else if (tree->nodekind==DecK)   //如果是声明类型
        {
            switch (tree->kind.dec)
            {
            case VarINTK:
                if (tree->num == -1) temp[deep].push_back(SYMBOL(tree->attr.name, INT, true, false, tree->lineno));//数组
                else temp[deep].push_back(SYMBOL(tree->attr.name, INT, true, true, tree->lineno));//不是数组
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
            case ParINTK://函数的参数
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
        else if (tree->nodekind==ExpK)  //如果是表示类型
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

        //这里要先处理好自己，再去子集
        for (i=0; i<MAXCHILDREN; i++)
            createSYMTAB(tree->child[i]);
        if (flag)  //如果到了}就说要推进表啦
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
    SYMTABLEs.push_back(SYMTABLE(0, temp[0]));//最后一层全局域的这里加
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

/* 获得对应符号定义是否的类型 */
Type getType(char* name, int line)
{
    if (!strcmp(name, "input") || !strcmp(name, "output")) return Integer; //系统函数
    for (int i=0; i<SYMTABLEs.size(); i++)
    {
        SYMTABLE tempSYMTABLE = SYMTABLEs[i];
        vector<SYMBOL> mSYMTABLE = tempSYMTABLE.mSYMTABLE;
        for(int j=0; j<mSYMTABLE.size(); j++)
        {
            if (!strcmp(name, mSYMTABLE[j].name))  //如果名字相同
            {
                for(set<int>::iterator it=mSYMTABLE[j].locations.begin(); it!=mSYMTABLE[j].locations.end(); it++)
                {
                    if (line == *it)    //如果对应行相同，查看是否对应标签
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
/* 往子集深搜找到函数返回语句 */
Type findReturnKType(TreeNode * t, int deep)
{
    if (t == NULL) return TError;
    /*cout<<"--------------------"<<endl;
    printTree(t);
    cout<<"--------------------"<<endl;*/
    if (t->nodekind == StmtK && t->kind.stmt == ReturnK) return t->type;//return 的那块
    Type resultType = TError;
    //先找子集
    for (int i=0; i<MAXCHILDREN; i++)
    {
        Type temp = findReturnKType(t->child[i], deep+1);
        if (temp != TError)
        {
            if (resultType == TError) resultType = temp; //还未得到一个返回值
            else if (resultType != temp)   //多个返回值类型不同
            {
                printf("return type error.\n");
                return TError;
            }
        }
    }
    //再找兄弟集
    if (deep && t->sibling != NULL)
    {
        Type temp = findReturnKType(t->sibling, deep);
        if (temp != TError)
        {
            if (resultType == TError) resultType = temp; //还未得到一个返回值
            else if (resultType != temp)   //多个返回值类型不同
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
    for (int i=0; i<MAXCHILDREN; i++) //这要要先去子集，因为类型在最里面产生，一层层往外扩展确认
        checkNode(t->child[i]);
    Type type = TError;
    switch(t->nodekind)
    {
    case ExpK:
        switch(t->kind.exp)
        {
        case OpK: //运算符符号，左右两边类型需要相等
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
        case ComK://{...}这种的直接深搜找到return那句
            t->type = findReturnKType(t, 0);
            break;
        case ReturnK:
            if (t->child[0] != NULL) //有返回值
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
            if (t->child[1]->type != Integer)//1 是函数体，0是参数
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



