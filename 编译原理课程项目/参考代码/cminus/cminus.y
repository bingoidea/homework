%{ 
#define YYPARSER /* distinguishes Yacc output from other code files */ 
#include "globals.h" 
#include "util.h" 
#include "scan.h" 
#include "parse.h" 
 
TreeNode * parseTree; /* stores syntax tree for later return */ 
 
void yyerror (const char *s); 
 
%}
%start /*非终结符*/
%union { TreeNode * tnode; 
         TokenType tok; } 
%type /*定义文法符号的语义值类型*/
%type <tnode> program declaration_list declaration var_declaration 
%type <tnode> fun_declaration params param_list param compound_stmt  
%type <tnode> local_declarations statement_list statement  
%type <tnode> expression_stmt selection_stmt iteration_stmt 
%type <tnode> return_stmt expression var simple_expression 
%type <tnode> additive_expression term factor call args arg_list 
%type <tok> type_specifier relop addop mulop 
%token DIGIT LETTER 
%token BEGIN 100 
%token ENDFILE,ERROR, 
%token IF,ELSE,INT,RETURN,VOID,WHILE, 
%token ID,NUM, 
%token ASSIGN, 
%token EQ,NOTEQ,LTEQ,GTEQ,LT,GT, 
%token PLUS,MINUS,TIMES,OVER, 
%token LPAREN,RPAREN,LBRACK,RBRACK,LCURL,RCURL, 
%token SEMI,COMMA 
stat : IF bexp THEN stat 
IF bexp THEN stat ELSE stat ; 
program : declaration_list 
     { parseTree = $1; 
       YYACCEPT; 
     } 
   ; 
 
declaration_list : declaration_list declaration 
     { TreeNode * t = $1; 
                            if (t != NULL) 
                            {           while (t->sibling != NULL) 
        t = (TreeNode *) t->sibling; 
                              t->sibling = $2; 
                              $$ = $1;  
       } 
                            else $$ = $2; 
     } 
   | declaration 
     { $$ = $1;} 
   ; 
 
declaration  : var_declaration 
     { $$ = $1; } 
   | fun_declaration 
     { $$ = $1; } 
   ; 
 
var_declaration  : type_specifier ID SEMI 
     { $$ = (TreeNode *) newNode(VarDeclK); 
       $$->attr.op = $1; 
       $$->child[0] = (TreeNode *) newNode(IdK); 
       $$->child[0]->attr.name = (char *) copyString(lastid); 
       // add to symbol table 
      } 
   | type_specifier ID LBRACK NUM  
     { $<tnode>$ = (TreeNode *) newNode(VarDeclK); 
       $<tnode>$->attr.op = $1; 
       $<tnode>$->child[0] = (TreeNode *) newNode(IdK); 
       $<tnode>$->child[0]->attr.name = (char *) copyString(lastid); 
       $<tnode>$->child[0] = (TreeNode *) newNode(ConstK); 
       $<tnode>$->child[0]->attr.val = atoi(curToken.tokString);  
        // add to symbol table 
     } 
     RBRACK SEMI 
     {  
       $$ = $<tnode>5; 
     } 
   ; 
 
type_specifier  : INT 
     {$$ = INT;}    | VOID 
     {$$ = VOID;} 
   ; 

fun_declaration  : type_specifier ID  
     { $<tnode>$ = (TreeNode *) newNode(FunDeclK); 
       $<tnode>$->attr.op = $1; 
       $<tnode>$->child[0] = (TreeNode *) newNode(IdK); 
       $<tnode>$->child[0]->attr.name = (char *) copyString(lastid); 
     } 
     LPAREN params RPAREN compound_stmt 
     { $$ = $<tnode>3; 
       $$->child[1] = $5; 
       $$->child[2] = $7; 
           } 
   ; 
 
params   : param_list 
     { $$ = $1; } 
   | VOID 
     { $$ = NULL; } 
   ; 
 
param_list  : param_list COMMA param 
     { TreeNode * t = $1; 
                            if (t != NULL) 
                            {  
         while (t->sibling != NULL) 
        t = (TreeNode *) t->sibling; 
                              t->sibling = $3; 
                              $$ = $1;  
       } 
                            else $$ = $3; 
     } 
   | param 
     { $$ = $1; } 
   ; 
 
param   : type_specifier ID 
     { $$ = (TreeNode *) newNode(VarDeclK); 
       $$->attr.op = $1;        $$->child[0] = (TreeNode *) newNode(IdK); 
       $$->child[0]->attr.name = (char *) copyString(lastid); 
       // add to symbol table 
     } 
   | type_specifier ID  
     { $<tnode>$ = (TreeNode *) newNode(VarDeclK); 
       $<tnode>$->attr.op = $1; 
       $<tnode>$->child[0] = (TreeNode *) newNode(IdK); 
       $<tnode>$->child[0]->attr.name = (char *) copyString(lastid); 
       // add to symbol table 
     } 
     LBRACK RBRACK 
     { $$ = $<tnode>3; } 
   ; 

compound_stmt  : LCURL local_declarations statement_list RCURL 
     { TreeNode * t = $2; 
                            if (t != NULL) 
                            {  
         while (t->sibling != NULL) 
        t = (TreeNode *) t->sibling; 
                              t->sibling = $3; 
                              $$ = $2;  
       } 
                            else $$ = $3; 
     } 
   ; 

local_declarations : local_declarations var_declaration 
     { TreeNode * t = $1; 
                            if (t != NULL) 
                            {  
         while (t->sibling != NULL) 
        t = (TreeNode *) t->sibling; 
                              t->sibling = $2;                               $$ = $1;  
       } 
                            else $$ = $2; 
     } 
   |  
     { $$ = NULL; } 
   ; 
 
statement_list  : statement_list statement 
     { TreeNode * t = $1; 
                            if (t != NULL) 
                            {  
         while (t->sibling != NULL) 
        t = (TreeNode *) t->sibling; 
                              t->sibling = $2; 
                              $$ = $1;  
       } 
                            else $$ = $2; 
     } 
   |  
     { $$ = NULL; } 
   ; 

statement  : expression_stmt 
     { $$ = $1; } 
   | compound_stmt 
     { $$ = $1; } 
   | selection_stmt 
     { $$ = $1; } 
   | iteration_stmt 
     { $$ = $1; } 
   | return_stmt 
     { $$ = $1; } 
   ; 
 
expression_stmt  : expression SEMI 
     { $$ = $1; } 
   | SEMI 
     { $$ = NULL; } 
   ; 

 selection_stmt  : IF LPAREN expression RPAREN statement 
     { $$ = (TreeNode *) newNode(IfK); 
       $$->child[0] = $3; 
       $$->child[1] = $5; 
     } 
   | IF LPAREN expression RPAREN statement ELSE statement 
     { $$ = (TreeNode *) newNode(IfK); 
       $$->child[0] = $3; 
       $$->child[1] = $5; 
       $$->child[2] = $7; 
     } 
   ; 

iteration_stmt  : WHILE LPAREN expression RPAREN statement 
     { $$ = (TreeNode *) newNode(WhileK); 
       $$->child[0] = $3; 
       $$->child[1] = $5; 
     } 
   ; 

return_stmt  : RETURN SEMI 
     { $$ = (TreeNode *) newNode(ReturnK); } 
   | RETURN expression SEMI 
     { $$ = (TreeNode *) newNode(ReturnK);  
       $$->child[0] = $2; 
     } 
   ; 

expression  : var ASSIGN expression 
     { $$ = (TreeNode *) newNode(AssignK); 
       $$->child[0] = $1; 
	$$->child[1] = $3;
     } 
   | simple_expression 
     { $$ = $1; } 
   ; 
 var   : ID 
     { $$ = (TreeNode *) newNode(IdK); 
       $$->attr.name = (char *) copyString(lastid); 
     } 
   | ID  
     { $<tnode>$ = (TreeNode *) newNode(IdK); 
       $<tnode>$->attr.name = (char *) copyString(lastid); 
     } 
     LBRACK expression RBRACK 
     { $$ = $<tnode>2; 
       $$->child[0] = $4; 
     } 
   ; 

simple_expression : additive_expression relop additive_expression 
     { $$ = (TreeNode *) newNode(OpK); 
       $$->attr.op = $2; 
       $$->child[0] = $1; 
       $$->child[1] = $3; 
     } 
   | additive_expression 
     { $$ = $1; } 
   ; 
 
relop   : EQ 
     { $$ = EQ; } 
   | NOTEQ 
     { $$ = NOTEQ; } 
   | LTEQ 
     { $$ = LTEQ; } 
   | GTEQ 
     { $$ = GTEQ; } 
   | LT 
     { $$ = LT; } 
   | GT 
     { $$ = GT; } 
   ; 

additive_expression: additive_expression addop term 
     { $$ = (TreeNode *) newNode(OpK); 
       $$->attr.op = $2; 
       $$->child[0] = $1; 
       $$->child[2] = $3; 
     } 
   | term 
     { $$ = $1; } 
   ; 
 
addop   : PLUS 
     { $$ = PLUS; } 
   | MINUS 
     { $$ = MINUS; } 
   ; 
 
term   : term mulop factor 
     { $$ = (TreeNode *) newNode(OpK); 
       $$->attr.op = $2; 
       $$->child[0] = $1; 
       $$->child[2] = $3; 
     } 
   | factor 
     { $$ = $1; } 
   ; 
 
mulop   : TIMES 
     { $$ = TIMES; } 
   | OVER 
     { $$ = OVER; } 
   ; 

factor   : LPAREN expression RPAREN 
     { $$ = $2; } 
   | var 
     { $$ = $1; } 
   | call 
     { $$ = $1; } 
   | NUM 
     { $$ = (TreeNode *) newNode(ConstK);        $$->attr.val = atoi(curToken.tokString); 
     } 
   ; 

call   : ID  
     { $<tnode>$ = (TreeNode *) newNode(CallK); 
       $<tnode>$->child[0] = (TreeNode *) newNode(IdK); 
       $<tnode>$->child[0]->attr.name = (char *) copyString(lastid); 
     } 
     LPAREN args RPAREN 
     { $$ = $<tnode>2;  
       $$->child[1] = $4; 
     } 
   ; 
 
args   : arg_list 
     { $$ = $1; } 
   |  
     { $$ = NULL; } 
   ; 
 
arg_list  : arg_list COMMA expression 
     { TreeNode * t = $1; 
                            if (t != NULL) 
                            {  
         while (t->sibling != NULL) 
        t = (TreeNode *) t->sibling; 
                              t->sibling = $3; 
                              $$ = $1;  
       } 
                            else $$ = $3; 
     } 
   | expression   
     { $$ = $1; } 
;
%%
void yyerror(char * message) 
{
printf("Error at line %d: %s\n",lineno,message); 
} 
