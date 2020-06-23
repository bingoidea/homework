/****************************************************************************
*                         A C A D E M I C   C O P Y
* 
* This file was produced by an ACADEMIC COPY of Parser Generator. It is for
* use in non-commercial software only. An ACADEMIC COPY of Parser Generator
* can only be used by a student, or a member of an academic community. If
* however you want to use Parser Generator for commercial purposes then you
* will need to purchase a license. For more information see the online help or
* go to the Bumble-Bee Software homepage at:
* 
* http://www.bumblebeesoftware.com
* 
* This notice must remain present in the file. It cannot be removed.
****************************************************************************/

/****************************************************************************
* lexer.cpp
* C++ source file generated from lexer.l.
* 
* Date: 12/10/03
* Time: 20:17:51
* 
* ALex Version: 2.06
****************************************************************************/

#include <yyclex.h>

// namespaces
#ifdef YYSTDCPPLIB
using namespace std;
#endif
#ifdef YYNAMESPACE
using namespace yl;
#endif

#line 1 ".\\lexer.l"

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

#line 63 "lexer.cpp"
// repeated because of possible precompiled header
#include <yyclex.h>

// namespaces
#ifdef YYSTDCPPLIB
using namespace std;
#endif
#ifdef YYNAMESPACE
using namespace yl;
#endif

#include ".\lexer.h"

/////////////////////////////////////////////////////////////////////////////
// constructor

YYLEXERNAME::YYLEXERNAME()
{
	yytables();
#line 39 ".\\lexer.l"

	// place any extra initialisation code here

#line 87 "lexer.cpp"
}

/////////////////////////////////////////////////////////////////////////////
// destructor

YYLEXERNAME::~YYLEXERNAME()
{
#line 44 ".\\lexer.l"

	// place any extra cleanup code here

#line 99 "lexer.cpp"
}

#ifndef YYTEXT_SIZE
#define YYTEXT_SIZE 100
#endif
#ifndef YYUNPUT_SIZE
#define YYUNPUT_SIZE YYTEXT_SIZE
#endif
#ifndef YYTEXT_MAX
#define YYTEXT_MAX 0
#endif
#ifndef YYUNPUT_MAX
#define YYUNPUT_MAX YYTEXT_MAX
#endif

/****************************************************************************
* N O T E
* 
* If the compiler generates a YYLEXERNAME error then you have not declared
* the name of the lexical analyser. The easiest way to do this is to use a
* name declaration. This is placed in the declarations section of your Lex
* source file and is introduced with the %name keyword. For instance, the
* following name declaration declares the lexer mylexer:
* 
* %name mylexer
* 
* For more information see help.
****************************************************************************/

// backwards compatability with lex
#ifdef input
int YYLEXERNAME::yyinput()
{
	return input();
}
#else
#define input yyinput
#endif

#ifdef output
void YYLEXERNAME::yyoutput(int ch)
{
	output(ch);
}
#else
#define output yyoutput
#endif

#ifdef unput
void YYLEXERNAME::yyunput(int ch)
{
	unput(ch);
}
#else
#define unput yyunput
#endif

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn -rch		// <warning: unreachable code> off
#endif
#endif

int YYLEXERNAME::yyaction(int action)
{
#line 60 ".\\lexer.l"

	// extract yylval for use later on in actions
	YYSTYPE YYFAR& yylval = *(YYSTYPE YYFAR*)yyparserptr->yylvalptr;

#line 170 "lexer.cpp"
	yyreturnflg = yytrue;
	switch (action) {
	case 1:
		{
#line 66 ".\\lexer.l"
print_token(INT, yytext); return INT;
#line 177 "lexer.cpp"
		}
		break;
	case 2:
		{
#line 67 ".\\lexer.l"
print_token(CHAR, yytext); return CHAR;
#line 184 "lexer.cpp"
		}
		break;
	case 3:
		{
#line 68 ".\\lexer.l"
print_token(IF, yytext); return IF;
#line 191 "lexer.cpp"
		}
		break;
	case 4:
		{
#line 69 ".\\lexer.l"
print_token(ELSE, yytext); return ELSE;
#line 198 "lexer.cpp"
		}
		break;
	case 5:
		{
#line 70 ".\\lexer.l"
print_token(WHILE, yytext); return WHILE;
#line 205 "lexer.cpp"
		}
		break;
	case 6:
		{
#line 71 ".\\lexer.l"
print_token(INPUT, yytext); return INPUT;
#line 212 "lexer.cpp"
		}
		break;
	case 7:
		{
#line 72 ".\\lexer.l"
print_token(PRINT, yytext); return PRINT;
#line 219 "lexer.cpp"
		}
		break;
	case 8:
		{
#line 73 ".\\lexer.l"
print_token(MAIN, yytext); return MAIN;
#line 226 "lexer.cpp"
		}
		break;
	case 9:
		{
#line 74 ".\\lexer.l"
print_token(EQ, yytext); return EQ;
#line 233 "lexer.cpp"
		}
		break;
	case 10:
		{
#line 75 ".\\lexer.l"
print_token(LE, yytext); return LE;
#line 240 "lexer.cpp"
		}
		break;
	case 11:
		{
#line 76 ".\\lexer.l"
print_token(GE, yytext); return GE;
#line 247 "lexer.cpp"
		}
		break;
	case 12:
		{
#line 77 ".\\lexer.l"
print_token(NE, yytext); return NE;
#line 254 "lexer.cpp"
		}
		break;
	case 13:
		{
#line 78 ".\\lexer.l"
print_token(ASSIGN, yytext); return ASSIGN;
#line 261 "lexer.cpp"
		}
		break;
	case 14:
		{
#line 79 ".\\lexer.l"
print_token(LT, yytext); return LT;
#line 268 "lexer.cpp"
		}
		break;
	case 15:
		{
#line 80 ".\\lexer.l"
print_token(GT, yytext); return GT;
#line 275 "lexer.cpp"
		}
		break;
	case 16:
		{
#line 81 ".\\lexer.l"
print_token(PLUS, yytext); return PLUS;
#line 282 "lexer.cpp"
		}
		break;
	case 17:
		{
#line 82 ".\\lexer.l"
print_token(MINUS, yytext); return MINUS;
#line 289 "lexer.cpp"
		}
		break;
	case 18:
		{
#line 83 ".\\lexer.l"
print_token(TIMES, yytext); return TIMES;
#line 296 "lexer.cpp"
		}
		break;
	case 19:
		{
#line 84 ".\\lexer.l"
print_token(OVER, yytext); return OVER;
#line 303 "lexer.cpp"
		}
		break;
	case 20:
		{
#line 85 ".\\lexer.l"
print_token(SEMICOLON, yytext); return SEMICOLON;
#line 310 "lexer.cpp"
		}
		break;
	case 21:
		{
#line 86 ".\\lexer.l"
print_token(COMMA, yytext); return COMMA;
#line 317 "lexer.cpp"
		}
		break;
	case 22:
		{
#line 87 ".\\lexer.l"
print_token(LPAREN, yytext); return LPAREN;
#line 324 "lexer.cpp"
		}
		break;
	case 23:
		{
#line 88 ".\\lexer.l"
print_token(RPAREN, yytext); return RPAREN;
#line 331 "lexer.cpp"
		}
		break;
	case 24:
		{
#line 89 ".\\lexer.l"
print_token(LBRACE, yytext); return LBRACE;
#line 338 "lexer.cpp"
		}
		break;
	case 25:
		{
#line 90 ".\\lexer.l"
print_token(RBRACE, yytext); return RBRACE;
#line 345 "lexer.cpp"
		}
		break;
	case 26:
		{
#line 91 ".\\lexer.l"
print_token(OR, yytext); return OR;
#line 352 "lexer.cpp"
		}
		break;
	case 27:
		{
#line 92 ".\\lexer.l"
print_token(AND, yytext); return AND;
#line 359 "lexer.cpp"
		}
		break;
	case 28:
		{
#line 93 ".\\lexer.l"
print_token(NOT, yytext); return NOT;
#line 366 "lexer.cpp"
		}
		break;
	case 29:
		{
#line 94 ".\\lexer.l"

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
            
#line 393 "lexer.cpp"
		}
		break;
	case 30:
		{
#line 115 ".\\lexer.l"

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
			
#line 412 "lexer.cpp"
		}
		break;
	case 31:
		{
#line 128 ".\\lexer.l"

				print_token(NUM, yytext, atoi(yytext));
				yylval = &dummy;
				yylval->attr.vali = atoi(yytext);
				return NUM;
#line 423 "lexer.cpp"
		}
		break;
	case 32:
		{
#line 133 ".\\lexer.l"

				print_token(CONSTCHAR, yytext);
				yylval = &dummy;
				yylval->attr.valc = yytext[0];
				return CONSTCHAR;
#line 434 "lexer.cpp"
		}
		break;
	case 33:
		{
#line 138 ".\\lexer.l"

				lineno++;
#ifdef LEX_DEBUG
				cout << "lineno: " << lineno << endl;
#endif
			
#line 446 "lexer.cpp"
		}
		break;
	case 34:
		{
#line 144 ".\\lexer.l"
/* skip whitespace */
#line 453 "lexer.cpp"
		}
		break;
	case 35:
		{
#line 145 ".\\lexer.l"

#ifdef LEX_DEBUG
				cout << "error!" << endl;
#endif
				return ERROR;
			
#line 465 "lexer.cpp"
		}
		break;
	default:
		yyassert(0);
		break;
	}
	yyreturnflg = yyfalse;
	return 0;
}

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn .rch		// <warning: unreachable code> to the old state
#endif
#endif

void YYLEXERNAME::yytables()
{
	yystext_size = YYTEXT_SIZE;
	yysunput_size = YYUNPUT_SIZE;
	yytext_max = YYTEXT_MAX;
	yyunput_max = YYUNPUT_MAX;

	static const yymatch_t YYNEARFAR YYBASED_CODE match[] = {
		0
	};
	yymatch = match;

	yytransitionmax = 202;
	static const yytransition_t YYNEARFAR YYBASED_CODE transition[] = {
		{ 0, 0 },
		{ 4, 1 },
		{ 5, 1 },
		{ 4, 4 },
		{ 36, 36 },
		{ 36, 36 },
		{ 36, 36 },
		{ 36, 36 },
		{ 36, 36 },
		{ 36, 36 },
		{ 36, 36 },
		{ 36, 36 },
		{ 36, 36 },
		{ 36, 36 },
		{ 17, 17 },
		{ 17, 17 },
		{ 17, 17 },
		{ 17, 17 },
		{ 17, 17 },
		{ 17, 17 },
		{ 17, 17 },
		{ 17, 17 },
		{ 17, 17 },
		{ 51, 43 },
		{ 4, 1 },
		{ 6, 1 },
		{ 4, 4 },
		{ 52, 43 },
		{ 32, 6 },
		{ 37, 19 },
		{ 7, 1 },
		{ 8, 1 },
		{ 9, 1 },
		{ 10, 1 },
		{ 11, 1 },
		{ 12, 1 },
		{ 13, 1 },
		{ 14, 1 },
		{ 38, 20 },
		{ 15, 1 },
		{ 16, 1 },
		{ 17, 1 },
		{ 17, 1 },
		{ 17, 1 },
		{ 17, 1 },
		{ 17, 1 },
		{ 17, 1 },
		{ 17, 1 },
		{ 17, 1 },
		{ 17, 1 },
		{ 39, 21 },
		{ 18, 1 },
		{ 19, 1 },
		{ 20, 1 },
		{ 21, 1 },
		{ 40, 23 },
		{ 41, 24 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 33, 7 },
		{ 44, 26 },
		{ 45, 27 },
		{ 46, 28 },
		{ 22, 1 },
		{ 47, 30 },
		{ 22, 1 },
		{ 22, 1 },
		{ 23, 1 },
		{ 22, 1 },
		{ 24, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 25, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 26, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 27, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 28, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 22, 1 },
		{ 29, 1 },
		{ 30, 1 },
		{ 31, 1 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 48, 34 },
		{ 0, 8 },
		{ 49, 40 },
		{ 50, 41 },
		{ 0, 14 },
		{ 53, 44 },
		{ 54, 45 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 55, 46 },
		{ 56, 49 },
		{ 57, 50 },
		{ 58, 51 },
		{ 22, 64 },
		{ 59, 53 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 22, 64 },
		{ 42, 25 },
		{ 60, 54 },
		{ 61, 55 },
		{ 62, 58 },
		{ 63, 60 },
		{ 64, 61 },
		{ 35, 15 },
		{ 0, 0 },
		{ 43, 25 }
	};
	yytransition = transition;

	static const yystate_t YYNEARFAR YYBASED_CODE state[] = {
		{ 0, 0, 0 },
		{ -3, -8, 0 },
		{ 1, 0, 0 },
		{ 0, 0, 35 },
		{ 0, -6, 34 },
		{ 0, 0, 33 },
		{ 0, -33, 28 },
		{ 0, 45, 35 },
		{ -34, 119, 35 },
		{ 0, 0, 22 },
		{ 0, 0, 23 },
		{ 0, 0, 18 },
		{ 0, 0, 16 },
		{ 0, 0, 21 },
		{ 17, 84, 17 },
		{ 0, 157, 19 },
		{ 0, 0, 31 },
		{ 36, -35, 31 },
		{ 0, 0, 20 },
		{ 0, -32, 14 },
		{ 0, -23, 13 },
		{ 0, -11, 15 },
		{ 64, 0, 30 },
		{ 64, -49, 30 },
		{ 64, -52, 30 },
		{ 64, 91, 30 },
		{ 64, -13, 30 },
		{ 64, -29, 30 },
		{ 64, -18, 30 },
		{ 0, 0, 24 },
		{ 0, -36, 35 },
		{ 0, 0, 25 },
		{ 0, 0, 12 },
		{ 0, 0, 27 },
		{ 0, 89, 0 },
		{ 0, 0, 29 },
		{ 0, -44, 31 },
		{ 0, 0, 10 },
		{ 0, 0, 9 },
		{ 0, 0, 11 },
		{ 64, 33, 30 },
		{ 64, 16, 30 },
		{ 64, 0, 3 },
		{ 64, -89, 30 },
		{ 64, 28, 30 },
		{ 64, 29, 30 },
		{ 64, 56, 30 },
		{ 0, 0, 26 },
		{ 0, 0, 32 },
		{ 64, 48, 30 },
		{ 64, 62, 30 },
		{ 64, 47, 30 },
		{ 64, 0, 1 },
		{ 64, 56, 30 },
		{ 64, 84, 30 },
		{ 64, 87, 30 },
		{ 64, 0, 2 },
		{ 64, 0, 4 },
		{ 64, 80, 30 },
		{ 64, 0, 8 },
		{ 64, 81, 30 },
		{ 64, 97, 30 },
		{ 64, 0, 6 },
		{ 64, 0, 7 },
		{ 0, 70, 5 }
	};
	yystate = state;

	static const yybackup_t YYNEARFAR YYBASED_CODE backup[] = {
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	};
	yybackup = backup;
}
#line 152 ".\\lexer.l"


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
