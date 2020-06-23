%{
/****************************************************************************
lexer.l
ParserWizard generated Lex file.

Date: 2003Äê10ÔÂ20ÈÕ
****************************************************************************/

#include <string>

using namespace ::std;

#include "common.h"
#include "parser.h"
#include "symbol.h"
#include "tree.h"

extern symbol_table symtbl;

Node dummy;

int lineno = 1;

static void print_token(int token, char *lexeme, int attr = 0);
%}

/////////////////////////////////////////////////////////////////////////////
// declarations section

// lexical analyser name
%name lexer

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

// place any declarations here
id          [a-zA-Z_]+[a-zA-Z0-9_]*
num         (-?[1-9]+[0-9]*)|(-?[1-9])|0
constchar	'.'
newline     \n
whitespace  [ \t]+

%%

/////////////////////////////////////////////////////////////////////////////
// rules section

%{
	// extract yylval for use later on in actions
	YYSTYPE YYFAR& yylval = *(YYSTYPE YYFAR*)yyparserptr->yylvalptr;
%}

// place your Lex rules here
"int"       {print_token(INT, yytext); return INT;}
"char"      {print_token(CHAR, yytext); return CHAR;}
"if"        {print_token(IF, yytext); return IF;}
"else"      {print_token(ELSE, yytext); return ELSE;}
"while"     {print_token(WHILE, yytext); return WHILE;}
"input"		{print_token(INPUT, yytext); return INPUT;}
"print"		{print_token(PRINT, yytext); return PRINT;}
"main"		{print_token(MAIN, yytext); return MAIN;}
"=="        {print_token(EQ, yytext); return EQ;}
"<="        {print_token(LE, yytext); return LE;}
">="        {print_token(GE, yytext); return GE;}
"!="        {print_token(NE, yytext); return NE;}
"="         {print_token(ASSIGN, yytext); return ASSIGN;}
"<"         {print_token(LT, yytext); return LT;}
">"         {print_token(GT, yytext); return GT;}
"+"         {print_token(PLUS, yytext); return PLUS;}
"-"         {print_token(MINUS, yytext); return MINUS;}
"*"         {print_token(TIMES, yytext); return TIMES;}
"/"         {print_token(OVER, yytext); return OVER;}
";"         {print_token(SEMICOLON, yytext); return SEMICOLON;}
","         {print_token(COMMA, yytext); return COMMA;}
"("         {print_token(LPAREN, yytext); return LPAREN;}
")"         {print_token(RPAREN, yytext); return RPAREN;}
"{"         {print_token(LBRACE, yytext); return LBRACE;}
"}"         {print_token(RBRACE, yytext); return RBRACE;}
"||"        {print_token(OR, yytext); return OR;}
"&&"        {print_token(AND, yytext); return AND;}
"!"         {print_token(NOT, yytext); return NOT;}
"/*"        {
                char c;
                LABEL:
                do
                {
                    c = input();
                    if( c == '\n')
                    	lineno++;
                }while(c != '*');
                
                do
                {
                    c = input();
                    if(c == '/')
                        break;
                    if( c == '\n')
                    	lineno++;
                    if(c != '*')
                        goto LABEL;
                }while(c == '*');
            }
{id}        {
				int p;
				
				p = symtbl.lookup(yytext);
				if (p == -1)
					p = symtbl.insert(yytext, ID);
				else
					dummy.type = symtbl.get_type(p);
				print_token(symtbl.gettoken(yytext), yytext, p);
				yylval = &dummy;
				yylval->attr.symtbl_seq = p;
				return ID;
			}
{num}       {
				print_token(NUM, yytext, atoi(yytext));
				yylval = &dummy;
				yylval->attr.vali = atoi(yytext);
				return NUM;}
{constchar}	{
				print_token(CONSTCHAR, yytext);
				yylval = &dummy;
				yylval->attr.valc = yytext[0];
				return CONSTCHAR;}
{newline}   {
				lineno++;
#ifdef LEX_DEBUG
				cout << "lineno: " << lineno << endl;
#endif
			}
{whitespace} {/* skip whitespace */}
.           {
#ifdef LEX_DEBUG
				cout << "error!" << endl;
#endif
				return ERROR;
			}

%%

/////////////////////////////////////////////////////////////////////////////
// programs section

static void print_token(int token, char *lexeme, int attr)
{
#ifdef LEX_DEBUG
	cout << "token: " << token << ",\tlexeme: " << lexeme;
	if (token == ID)
		cout << ",\tsymbol table pos: " << attr;
	else if (token == NUM)
		cout << ",\tvalue: " << attr;
	cout << endl;
#endif
}