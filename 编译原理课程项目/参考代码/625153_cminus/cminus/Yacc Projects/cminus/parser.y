%{
/****************************************************************************
parser.y
ParserWizard generated YACC file.

Date: 2003Äê10ÔÂ20ÈÕ
****************************************************************************/

#include <fstream>
#include <string>

using namespace ::std;

#include "common.h"
#include "lexer.h"
#include "symbol.h"
#include "tree.h"

extern symbol_table symtbl;
extern tree parse_tree;

%}

/////////////////////////////////////////////////////////////////////////////
// declarations section

// parser name
%name parser

// class definition
{
	// place any extra class members here
}

// constructor
{
	// place any extra initialisation code here
}

// destructor
{
	// place any extra cleanup code here
}

// attribute type
%include {
#ifndef YYSTYPE
#define YYSTYPE Node *
#endif
}

// place any declarations here
%token INT CHAR IF ELSE WHILE INPUT PRINT
%token ID NUM CONSTCHAR MAIN
%token AND OR NOT ASSIGN EQ LT LE GT GE NE PLUS MINUS TIMES OVER LPAREN RPAREN SEMICOLON COMMA LBRACE RBRACE
%token ERROR ENDFILE


%%

/////////////////////////////////////////////////////////////////////////////
// rules section

// place your YACC rules here (there must be at least one)

program             : MAIN LPAREN RPAREN compound_stmt
                        { $$ = $4; }
                    ;
var_declaration     : type_specifier idlist SEMICOLON
                      {
						Node *p;
						$$ = parse_tree.NewRoot(DECL_NODE, VAR_DECL, 0, Notype, $1, $2);
						for (p = $2; p; p = p->sibling)
						{
							p->type = $1->type;
							symtbl.set_type(p->attr.symtbl_seq, p->type);
						}
                      }
                    ;
idlist				: idlist COMMA id
						{
							YYSTYPE t = $1;
							if (t!=NULL){
								while (t->sibling!=NULL)
									t=t->sibling;
								t->sibling = $3;
								$$ = $1;
							}
							else 
								$$ = $3;
						}
					| id
						{
							$$ = $1;
						}
										;
type_specifier      : INT 
                      {
						$$ = parse_tree.NewRoot(EXPR_NODE, TYPE_EXPR, 0, Integer);
                      }
                    | CHAR
                      { 
						$$ = parse_tree.NewRoot(EXPR_NODE, TYPE_EXPR, 0, Char);
                      }
                    ;
id					: ID
						{
							$$ = parse_tree.NewRoot(EXPR_NODE, ID_EXPR, $1->attr.symtbl_seq, $1->type);
						}
										;
compound_stmt       : LBRACE local_declarations statement_list RBRACE
                      {
                        YYSTYPE t = $2;
                        if (t != NULL)
                        { 
                          while (t->sibling != NULL)
                            t = t->sibling;
                          t->sibling = $3;
                          $$ = parse_tree.NewRoot(STMT_NODE, COMP_STMT, 0, Notype, $2);
                        }
                        else 
                        {
						  $$ = parse_tree.NewRoot(STMT_NODE, COMP_STMT, 0, Notype, $3);
                        }
                      }
                    | LBRACE statement_list RBRACE
                      {
						$$ = parse_tree.NewRoot(STMT_NODE, COMP_STMT, 0, Notype, $2);
                      }
                    ;
local_declarations  : local_declarations var_declaration
                      { 
                        YYSTYPE t = $1;
                        if (t != NULL)
                        { 
                          while (t->sibling != NULL)
                            t = t->sibling;
                          t->sibling = $2;
                          $$ = $1; 
                        }
                        else 
                          $$ = $2;
                      }
                    | var_declaration
                      { $$ = $1; }
                    ;
statement_list      : statement_list statement
                      { 
                        YYSTYPE t = $1;
                        if (t != NULL)
                        { 
                          while (t->sibling != NULL)
                            t = t->sibling;
                          t->sibling = $2;
                          $$ = $1; 
                        }
                        else 
                          $$ = $2;
                      }
                    | statement
                      { $$ = $1; }
                    ;
statement           : expression_stmt
                      {
                        $$ = $1;
                      }
                    | compound_stmt
                      {
                        $$ = $1;
                      }
                    | selection_stmt
                      {
                        $$ = $1;
                      }
                    | while_stmt
                      {
                        $$ = $1;
                      }
                    | input_stmt
                      {
						$$ = $1;
					  }
                    | print_stmt
                      {
						$$ = $1;
					  }
                    ;
expression_stmt     : expression SEMICOLON
                      {
                        $$ = $1;
                      }
                    | SEMICOLON
                      {
                        $$ = NULL;
                      }
                    ;
selection_stmt      : IF LPAREN expression RPAREN statement ELSE statement
                      {
						$$ = parse_tree.NewRoot(STMT_NODE, IF_STMT, 0, Notype, $3, $5, $7);
                      }
                    | IF LPAREN expression RPAREN statement
                      {
						$$ = parse_tree.NewRoot(STMT_NODE, IF_STMT, 0, Notype, $3, $5);
                      }
                    ;
while_stmt          : WHILE LPAREN expression RPAREN statement
                      {
						$$ = parse_tree.NewRoot(STMT_NODE, WHILE_STMT, 0, Notype, $3, $5);
                      }
                    ;
input_stmt          : INPUT LPAREN var RPAREN
                      {
						$$ = parse_tree.NewRoot(STMT_NODE, INPUT_STMT, 0, Notype, $3);
                      }
                    ;
print_stmt          : PRINT LPAREN var RPAREN
                      {
						$$ = parse_tree.NewRoot(STMT_NODE, PRINT_STMT, 0, Notype, $3);
                      }
                    ;
expression          : var ASSIGN expression
                      {
						$$ = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, ASSIGN, Notype, $1, $3);
                      }
                    | or_expression
                      {
                        $$ = $1;
                      }
                    ;
var                 : ID
                      {
						$$ = parse_tree.NewRoot(EXPR_NODE, ID_EXPR, $1->attr.symtbl_seq, $1->type);
                      }
                    ;
or_expression       : or_expression OR and_expression
                      {
						$$ = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, OR, Notype, $1, $3);
                      }
                    | and_expression
                      { $$ = $1; }
                    ;
and_expression      : and_expression AND additive_expression
                      {
						$$ = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, AND, Notype, $1, $3);
                      }
                    | additive_expression
                      { $$ = $1; }
                    ;
additive_expression : additive_expression EQ rel_expression
	 				{
						$$ = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, EQ, Notype, $1, $3);
					}
					| additive_expression LT rel_expression	
					{
						$$ = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, LT, Notype, $1, $3);
					}
					| additive_expression GT rel_expression	
					{
						$$ = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, GT, Notype, $1, $3);
					}
					| additive_expression LE rel_expression	
					{
						$$ = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, LE, Notype, $1, $3);
					}
					| additive_expression GE rel_expression	
					{
						$$ = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, GE, Notype, $1, $3);
					}
					| additive_expression NE rel_expression	
					{
						$$ = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, NE, Notype, $1, $3);
					}
					| rel_expression
					{
						$$ = $1;
					}
					;
rel_expression : rel_expression PLUS term
                      {
						$$ = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, PLUS, Notype, $1, $3);
                      }
                    | rel_expression MINUS term
                      {
						$$ = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, MINUS, Notype, $1, $3);
                      }
                    | term
                      { $$ = $1; }
                    ;
term                : term TIMES factor
                      {
						$$ = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, TIMES, Notype, $1, $3);
                      }
                    | term OVER factor
                      {
						$$ = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, OVER, Notype, $1, $3);
                      }
                    | factor
                      { $$ = $1; }
                    ;
factor              : LPAREN expression RPAREN 
                      { $$ = $2; }
                    | var
                      { $$ = $1; }
                    | NUM
                      { 
						$$ = parse_tree.NewRoot(EXPR_NODE, CONST_EXPR, $1->attr.vali, Integer);
                      }
                    | CONSTCHAR
                      {
						$$ = parse_tree.NewRoot(EXPR_NODE, CONST_EXPR, $1->attr.valc, Char);
                   	  }
                    | NOT factor
                      { 
						$$ = parse_tree.NewRoot(EXPR_NODE, NOT_EXPR, NOT, Notype, $2);
                      }
                    ;

%%

/////////////////////////////////////////////////////////////////////////////
// programs section

int main(int argc, char *argv[])
{
	int n = 1;
	lexer lexer;
	parser parser;
	if (parser.yycreate(&lexer)) {
		if (lexer.yycreate(&parser)) {
			lexer.yyin = new ifstream(argv[1]);
			lexer.yyout = new ofstream(argv[2]);
			n = parser.yyparse();
			parse_tree.get_label();
			parse_tree.gen_code(*lexer.yyout);
		}
	}
	
	getchar();
	return n;
}
