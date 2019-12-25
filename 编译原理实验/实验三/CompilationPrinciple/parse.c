/****************************************************/
/* File: parse.c                                    */
/* The parser implementation for the TINY compiler  */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

/* parse.c用于完成语法分析 */
#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

static TokenType token; /* holds current token */

/* function prototypes for recursive calls */
static TreeNode * stmt_sequence(void);   /* 语句序列 */
static TreeNode * statement(void);       /* 语句 */
static TreeNode * if_stmt(void);         /* if语句 */
static TreeNode * repeat_stmt(void);     /* 循环语句 */
static TreeNode * assign_stmt(void);     /* 赋值语句 */
static TreeNode * read_stmt(void);       /* 输入语句 */
static TreeNode * write_stmt(void);      /* 输出语句 */
static TreeNode * exp(void);             /* 表达式 */
static TreeNode * simple_exp(void);      /* 简单表达式 */
static TreeNode * term(void);            /* 乘法项 */
static TreeNode * factor(void);          /* 因子 */
// 新增静态成员函数定义
static TreeNode * while_stmt(void);
static TreeNode * dowhile_stmt(void);
static TreeNode * for_stmt(void);


static void syntaxError(char * message)
{
    fprintf(listing,"\n>>> ");
    fprintf(listing,"Syntax error at line %d: %s",lineno,message);
    Error = TRUE;
}

static void match(TokenType expected)
{
    if (token == expected)
        token = getToken();
    else
    {
        syntaxError("unexpected token -> ");
        printToken(token,tokenString);
        fprintf(listing,"      ");
    }
}

TreeNode * stmt_sequence(void)
{
    TreeNode * t = statement();
    TreeNode * p = t;
    // 增加stmt_sequence文法的follow集，添加增加条件(token != ENDWHILE) && (token != WHILE)&&(token != ENDDO)
    while ((token != ENDFILE) && (token != END) &&
        (token != ELSE) && (token != UNTIL)&&
        (token != ENDWHILE) && (token != WHILE)&&
        (token != ENDDO))
    {
        TreeNode * q;
        match(SEMI);
        q = statement();
        if (q!=NULL)
        {
            if (t==NULL)
                t = p = q;
            else /* now p cannot be NULL either */
            {
                p->sibling = q;
                p = q;
            }
        }
    }
    return t;
}


//P394
//lineno: 961
TreeNode * statement(void)
{
    TreeNode * t = NULL;
    // 在 TreeNode * statement(void)函数中 switch (token)模块下增加状态DO,WHILE,FOR
    switch (token)
    {
    case IF :
        t = if_stmt();
        break;
    case REPEAT :
        t = repeat_stmt();
        break;
    case ID :
        t = assign_stmt();
        break;
    case READ :
        t = read_stmt();
        break;
    case WRITE :
        t = write_stmt();
        break;
    case WHILE:
        t = while_stmt();
        break;
    case DO:
        t = dowhile_stmt();
        break;
    case FOR:
        t = for_stmt();
        break;
    default :
        syntaxError("unexpected token -> ");
        printToken(token,tokenString);
        token = getToken();
        break;
    } /* end case */
    return t;
}


////P394
////lineno: 977
//// 原有的if_stmt文法(if_stmt-->if exp then stmt-sequence end | | if exp then stmt-sequence else stmt-sequence end)
//TreeNode * if_stmt(void)
//{
//    TreeNode * t = newStmtNode(IfK);
//    match(IF);
//    if (t!=NULL)
//        t->child[0] = exp();
//    match(THEN);
//    if (t!=NULL)
//        t->child[1] = stmt_sequence();
//    if (token==ELSE)
//    {
//        match(ELSE);
//        if (t!=NULL)
//            t->child[2] = stmt_sequence();
//    }
//    match(END);
//    return t;
//}

// 更改后的if_stmt文法(if_stmt-->if(exp) stmt-sequence else stmt-sequence | if(exp) stmt-sequence)
TreeNode * if_stmt(void)
{
    TreeNode * t = newStmtNode(IfK);
    match(IF);
    match(LPAREN);
    if (t != NULL) t->child[0] = exp();
    match(RPAREN);
    if (t != NULL) t->child[1] = stmt_sequence();
    if (token == ELSE)
    {
        match(ELSE);
        if (t != NULL) t->child[2] = stmt_sequence();
    }
    return t;
}

//P394
//lineno:991
TreeNode * repeat_stmt(void)
{
    TreeNode * t = newStmtNode(RepeatK);
    match(REPEAT);
    if (t!=NULL)
        t->child[0] = stmt_sequence();
    match(UNTIL);
    if (t!=NULL)
        t->child[1] = exp();
    return t;
}

TreeNode * assign_stmt(void)
{
    TreeNode * t = newStmtNode(AssignK);
    if ((t!=NULL) && (token==ID))
        t->attr.name = copyString(tokenString);
    match(ID);
    //match(ASSIGN);
    // +=类比:=
    if(token == ASSIGN) {
        match(ASSIGN);
    }
    else {
        t->kind.stmt = AddtoK;
        match(ADDTO);
    }
    if (t!=NULL)
        t->child[0] = exp();
    return t;
}

TreeNode * read_stmt(void)
{
    TreeNode * t = newStmtNode(ReadK);
    match(READ);
    if ((t!=NULL) && (token==ID))
        t->attr.name = copyString(tokenString);
    match(ID);
    return t;
}

TreeNode * write_stmt(void)
{
    TreeNode * t = newStmtNode(WriteK);
    match(WRITE);
    if (t!=NULL)
        t->child[0] = exp();
    return t;
}

// 新增while_stmt文法(While-stmt --> while  exp  do  stmt-sequence  endwhile)
TreeNode * while_stmt(void)
{
    TreeNode * t = newStmtNode(WhileK);
    match(WHILE);
    if (t != NULL) t->child[0] = exp();
    match(DO);
    if (t != NULL) t->child[1] = stmt_sequence();
    match(ENDWHILE);
    return t;
}

// 新增dowhile_stmt文法(Dowhile-stmt-->do  stmt-sequence  while(exp))
TreeNode * dowhile_stmt(void)
{
    TreeNode * t = newStmtNode(DoWhileK);
    match(DO);
    if (t != NULL) t->child[0] = stmt_sequence();
    match(WHILE);
    match(LPAREN); // 左括号
    if (t != NULL) t->child[1] = exp();
    match(RPAREN); // 右括号
    return t;
}

// 新增for_stmt文法
// for-stmt-->for identifier:=simple-exp  to  simple-exp  do  stmt-sequence enddo    步长递增1
// for-stmt-->for identifier:=simple-exp  downto  simple-exp  do  stmt-sequence enddo    步长递减1
TreeNode * for_stmt(void)
{
    TreeNode * t = newStmtNode(ForK);
    match(FOR);
    if ((t != NULL) && (token == ID))
    {
        t->attr.name = copyString(tokenString);
    }
    match(ID);
    match(ASSIGN);
    if (t != NULL)
    {
        t->child[0] = simple_exp();
    }
    if (token == TO)
    { // 步长+1
        match(TO);
    }
    if (token == DOWNTO)
    { // 步长-1
        match(DOWNTO);
    }
    if (t != NULL)
    {
        t->child[1] = simple_exp();
    }
    match(DO);
    if (t != NULL)
    {
        t->child[2] = stmt_sequence();
    }
    match(ENDDO);
    return t;
}

TreeNode * exp(void)
{
    TreeNode * t = simple_exp();
    if ((token==LT)||(token==EQ))
    {
        TreeNode * p = newExpNode(OpK);
        if (p!=NULL)
        {
            p->child[0] = t;
            p->attr.op = token;
            t = p;
        }
        match(token);
        if (t!=NULL)
            t->child[1] = simple_exp();
    }
    return t;
}

TreeNode * simple_exp(void)
{
    TreeNode * t = term();
    while ((token==PLUS)||(token==MINUS))
    {
        TreeNode * p = newExpNode(OpK);
        if (p!=NULL)
        {
            p->child[0] = t;
            p->attr.op = token;
            t = p;
            match(token);
            t->child[1] = term();
        }
    }
    return t;
}

TreeNode * term(void)
{
    TreeNode * t = factor();
    // 在 TreeNode * term(void)函数中的 while 条件增加代码（pow乘方）
    while ((token==TIMES)||(token==OVER)||(token==POW))
    {
        TreeNode * p = newExpNode(OpK);
        if (p!=NULL)
        {
            p->child[0] = t;
            p->attr.op = token;
            t = p;
            match(token);
            p->child[1] = factor();
        }
    }
    return t;
}

TreeNode * factor(void)
{
    TreeNode * t = NULL;
    switch (token)
    {
    case NUM :
        t = newExpNode(ConstK);
        if ((t!=NULL) && (token==NUM))
            t->attr.val = atoi(tokenString);
        match(NUM);
        break;
    case ID :
        t = newExpNode(IdK);
        if ((t!=NULL) && (token==ID))
            t->attr.name = copyString(tokenString);
        match(ID);
        break;
    case LPAREN :
        match(LPAREN);
        t = exp();
        match(RPAREN);
        break;
    default:
        syntaxError("unexpected token -> ");
        printToken(token,tokenString);
        token = getToken();
        break;
    }
    return t;
}

/****************************************/
/* the primary function of the parser   */
/****************************************/
/* Function parse returns the newly
 * constructed syntax tree
 */
TreeNode * parse(void)
{
    TreeNode * t;
    token = getToken();
    t = stmt_sequence();
    if (token!=ENDFILE)
        syntaxError("Code ends before file\n");
    return t;
}
