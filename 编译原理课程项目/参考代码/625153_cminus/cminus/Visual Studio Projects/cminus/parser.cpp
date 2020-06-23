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
* parser.cpp
* C++ source file generated from parser.y.
* 
* Date: 12/10/03
* Time: 20:17:51
* 
* AYACC Version: 2.06
****************************************************************************/

#include <yycpars.h>

// namespaces
#ifdef YYSTDCPPLIB
using namespace std;
#endif
#ifdef YYNAMESPACE
using namespace yl;
#endif

#line 1 ".\\parser.y"

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


#line 60 "parser.cpp"
// repeated because of possible precompiled header
#include <yycpars.h>

// namespaces
#ifdef YYSTDCPPLIB
using namespace std;
#endif
#ifdef YYNAMESPACE
using namespace yl;
#endif

#include ".\parser.h"

/////////////////////////////////////////////////////////////////////////////
// constructor

YYPARSERNAME::YYPARSERNAME()
{
	yytables();
#line 36 ".\\parser.y"

	// place any extra initialisation code here

#line 84 "parser.cpp"
}

/////////////////////////////////////////////////////////////////////////////
// destructor

YYPARSERNAME::~YYPARSERNAME()
{
	// allows virtual functions to be called properly for correct cleanup
	yydestroy();
#line 41 ".\\parser.y"

	// place any extra cleanup code here

#line 98 "parser.cpp"
}

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#ifndef YYSTACK_SIZE
#define YYSTACK_SIZE 100
#endif
#ifndef YYSTACK_MAX
#define YYSTACK_MAX 0
#endif

/****************************************************************************
* N O T E
* 
* If the compiler generates a YYPARSERNAME error then you have not declared
* the name of the parser. The easiest way to do this is to use a name
* declaration. This is placed in the declarations section of your YACC
* source file and is introduced with the %name keyword. For instance, the
* following name declaration declares the parser myparser:
* 
* %name myparser
* 
* For more information see help.
****************************************************************************/

// yyattribute
#ifdef YYDEBUG
void YYFAR* YYPARSERNAME::yyattribute1(int index) const
{
	YYSTYPE YYFAR* p = &((YYSTYPE YYFAR*)yyattributestackptr)[yytop + index];
	return p;
}
#define yyattribute(index) (*(YYSTYPE YYFAR*)yyattribute1(index))
#else
#define yyattribute(index) (((YYSTYPE YYFAR*)yyattributestackptr)[yytop + (index)])
#endif

void YYPARSERNAME::yystacktoval(int index)
{
	yyassert(index >= 0);
	*(YYSTYPE YYFAR*)yyvalptr = ((YYSTYPE YYFAR*)yyattributestackptr)[index];
}

void YYPARSERNAME::yyvaltostack(int index)
{
	yyassert(index >= 0);
	((YYSTYPE YYFAR*)yyattributestackptr)[index] = *(YYSTYPE YYFAR*)yyvalptr;
}

void YYPARSERNAME::yylvaltoval()
{
	*(YYSTYPE YYFAR*)yyvalptr = *(YYSTYPE YYFAR*)yylvalptr;
}

void YYPARSERNAME::yyvaltolval()
{
	*(YYSTYPE YYFAR*)yylvalptr = *(YYSTYPE YYFAR*)yyvalptr;
}

void YYPARSERNAME::yylvaltostack(int index)
{
	yyassert(index >= 0);
	((YYSTYPE YYFAR*)yyattributestackptr)[index] = *(YYSTYPE YYFAR*)yylvalptr;
}

void YYFAR* YYPARSERNAME::yynewattribute(int count)
{
	yyassert(count >= 0);
	return new YYFAR YYSTYPE[count];
}

void YYPARSERNAME::yydeleteattribute(void YYFAR* attribute)
{
	delete[] (YYSTYPE YYFAR*)attribute;
}

void YYPARSERNAME::yycopyattribute(void YYFAR* dest, const void YYFAR* src, int count)
{
	for (int i = 0; i < count; i++) {
		((YYSTYPE YYFAR*)dest)[i] = ((YYSTYPE YYFAR*)src)[i];
	}
}

#ifdef YYDEBUG
void YYPARSERNAME::yyinitdebug(void YYFAR** p, int count) const
{
	yyassert(p != NULL);
	yyassert(count >= 1);

	YYSTYPE YYFAR** p1 = (YYSTYPE YYFAR**)p;
	for (int i = 0; i < count; i++) {
		p1[i] = &((YYSTYPE YYFAR*)yyattributestackptr)[yytop + i - (count - 1)];
	}
}
#endif

void YYPARSERNAME::yyaction(int action)
{
	switch (action) {
	case 0:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 67 ".\\parser.y"
 (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(4 - 4); 
#line 208 "parser.cpp"
			}
		}
		break;
	case 1:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 70 ".\\parser.y"

						Node *p;
						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(DECL_NODE, VAR_DECL, 0, Notype, yyattribute(1 - 3), yyattribute(2 - 3));
						for (p = yyattribute(2 - 3); p; p = p->sibling)
						{
							p->type = yyattribute(1 - 3)->type;
							symtbl.set_type(p->attr.symtbl_seq, p->type);
						}
                      
#line 229 "parser.cpp"
			}
		}
		break;
	case 2:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 81 ".\\parser.y"

							YYSTYPE t = yyattribute(1 - 3);
							if (t!=NULL){
								while (t->sibling!=NULL)
									t=t->sibling;
								t->sibling = yyattribute(3 - 3);
								(*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 3);
							}
							else 
								(*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(3 - 3);
						
#line 252 "parser.cpp"
			}
		}
		break;
	case 3:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 93 ".\\parser.y"

							(*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 1);
						
#line 267 "parser.cpp"
			}
		}
		break;
	case 4:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 98 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, TYPE_EXPR, 0, Integer);
                      
#line 282 "parser.cpp"
			}
		}
		break;
	case 5:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 102 ".\\parser.y"
 
						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, TYPE_EXPR, 0, Char);
                      
#line 297 "parser.cpp"
			}
		}
		break;
	case 6:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 107 ".\\parser.y"

							(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, ID_EXPR, yyattribute(1 - 1)->attr.symtbl_seq, yyattribute(1 - 1)->type);
						
#line 312 "parser.cpp"
			}
		}
		break;
	case 7:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 112 ".\\parser.y"

                        YYSTYPE t = yyattribute(2 - 4);
                        if (t != NULL)
                        { 
                          while (t->sibling != NULL)
                            t = t->sibling;
                          t->sibling = yyattribute(3 - 4);
                          (*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(STMT_NODE, COMP_STMT, 0, Notype, yyattribute(2 - 4));
                        }
                        else 
                        {
						  (*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(STMT_NODE, COMP_STMT, 0, Notype, yyattribute(3 - 4));
                        }
                      
#line 338 "parser.cpp"
			}
		}
		break;
	case 8:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 127 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(STMT_NODE, COMP_STMT, 0, Notype, yyattribute(2 - 3));
                      
#line 353 "parser.cpp"
			}
		}
		break;
	case 9:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 132 ".\\parser.y"
 
                        YYSTYPE t = yyattribute(1 - 2);
                        if (t != NULL)
                        { 
                          while (t->sibling != NULL)
                            t = t->sibling;
                          t->sibling = yyattribute(2 - 2);
                          (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 2); 
                        }
                        else 
                          (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(2 - 2);
                      
#line 377 "parser.cpp"
			}
		}
		break;
	case 10:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 145 ".\\parser.y"
 (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 1); 
#line 390 "parser.cpp"
			}
		}
		break;
	case 11:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 148 ".\\parser.y"
 
                        YYSTYPE t = yyattribute(1 - 2);
                        if (t != NULL)
                        { 
                          while (t->sibling != NULL)
                            t = t->sibling;
                          t->sibling = yyattribute(2 - 2);
                          (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 2); 
                        }
                        else 
                          (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(2 - 2);
                      
#line 414 "parser.cpp"
			}
		}
		break;
	case 12:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 161 ".\\parser.y"
 (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 1); 
#line 427 "parser.cpp"
			}
		}
		break;
	case 13:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 164 ".\\parser.y"

                        (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 1);
                      
#line 442 "parser.cpp"
			}
		}
		break;
	case 14:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 168 ".\\parser.y"

                        (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 1);
                      
#line 457 "parser.cpp"
			}
		}
		break;
	case 15:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 172 ".\\parser.y"

                        (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 1);
                      
#line 472 "parser.cpp"
			}
		}
		break;
	case 16:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 176 ".\\parser.y"

                        (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 1);
                      
#line 487 "parser.cpp"
			}
		}
		break;
	case 17:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 180 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 1);
					  
#line 502 "parser.cpp"
			}
		}
		break;
	case 18:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 184 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 1);
					  
#line 517 "parser.cpp"
			}
		}
		break;
	case 19:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 189 ".\\parser.y"

                        (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 2);
                      
#line 532 "parser.cpp"
			}
		}
		break;
	case 20:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 193 ".\\parser.y"

                        (*(YYSTYPE YYFAR*)yyvalptr) = NULL;
                      
#line 547 "parser.cpp"
			}
		}
		break;
	case 21:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
#line 198 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(STMT_NODE, IF_STMT, 0, Notype, yyattribute(3 - 7), yyattribute(5 - 7), yyattribute(7 - 7));
                      
#line 562 "parser.cpp"
			}
		}
		break;
	case 22:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 202 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(STMT_NODE, IF_STMT, 0, Notype, yyattribute(3 - 5), yyattribute(5 - 5));
                      
#line 577 "parser.cpp"
			}
		}
		break;
	case 23:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
#line 207 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(STMT_NODE, WHILE_STMT, 0, Notype, yyattribute(3 - 5), yyattribute(5 - 5));
                      
#line 592 "parser.cpp"
			}
		}
		break;
	case 24:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 212 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(STMT_NODE, INPUT_STMT, 0, Notype, yyattribute(3 - 4));
                      
#line 607 "parser.cpp"
			}
		}
		break;
	case 25:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 217 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(STMT_NODE, PRINT_STMT, 0, Notype, yyattribute(3 - 4));
                      
#line 622 "parser.cpp"
			}
		}
		break;
	case 26:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 222 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, ASSIGN, Notype, yyattribute(1 - 3), yyattribute(3 - 3));
                      
#line 637 "parser.cpp"
			}
		}
		break;
	case 27:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 226 ".\\parser.y"

                        (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 1);
                      
#line 652 "parser.cpp"
			}
		}
		break;
	case 28:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 231 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, ID_EXPR, yyattribute(1 - 1)->attr.symtbl_seq, yyattribute(1 - 1)->type);
                      
#line 667 "parser.cpp"
			}
		}
		break;
	case 29:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 236 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, OR, Notype, yyattribute(1 - 3), yyattribute(3 - 3));
                      
#line 682 "parser.cpp"
			}
		}
		break;
	case 30:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 240 ".\\parser.y"
 (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 1); 
#line 695 "parser.cpp"
			}
		}
		break;
	case 31:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 243 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, AND, Notype, yyattribute(1 - 3), yyattribute(3 - 3));
                      
#line 710 "parser.cpp"
			}
		}
		break;
	case 32:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 247 ".\\parser.y"
 (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 1); 
#line 723 "parser.cpp"
			}
		}
		break;
	case 33:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 250 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, EQ, Notype, yyattribute(1 - 3), yyattribute(3 - 3));
					
#line 738 "parser.cpp"
			}
		}
		break;
	case 34:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 254 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, LT, Notype, yyattribute(1 - 3), yyattribute(3 - 3));
					
#line 753 "parser.cpp"
			}
		}
		break;
	case 35:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 258 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, GT, Notype, yyattribute(1 - 3), yyattribute(3 - 3));
					
#line 768 "parser.cpp"
			}
		}
		break;
	case 36:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 262 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, LE, Notype, yyattribute(1 - 3), yyattribute(3 - 3));
					
#line 783 "parser.cpp"
			}
		}
		break;
	case 37:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 266 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, GE, Notype, yyattribute(1 - 3), yyattribute(3 - 3));
					
#line 798 "parser.cpp"
			}
		}
		break;
	case 38:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 270 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, NE, Notype, yyattribute(1 - 3), yyattribute(3 - 3));
					
#line 813 "parser.cpp"
			}
		}
		break;
	case 39:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 274 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 1);
					
#line 828 "parser.cpp"
			}
		}
		break;
	case 40:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 279 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, PLUS, Notype, yyattribute(1 - 3), yyattribute(3 - 3));
                      
#line 843 "parser.cpp"
			}
		}
		break;
	case 41:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 283 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, MINUS, Notype, yyattribute(1 - 3), yyattribute(3 - 3));
                      
#line 858 "parser.cpp"
			}
		}
		break;
	case 42:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 287 ".\\parser.y"
 (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 1); 
#line 871 "parser.cpp"
			}
		}
		break;
	case 43:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 290 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, TIMES, Notype, yyattribute(1 - 3), yyattribute(3 - 3));
                      
#line 886 "parser.cpp"
			}
		}
		break;
	case 44:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 294 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, OP_EXPR, OVER, Notype, yyattribute(1 - 3), yyattribute(3 - 3));
                      
#line 901 "parser.cpp"
			}
		}
		break;
	case 45:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 298 ".\\parser.y"
 (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 1); 
#line 914 "parser.cpp"
			}
		}
		break;
	case 46:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 301 ".\\parser.y"
 (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(2 - 3); 
#line 927 "parser.cpp"
			}
		}
		break;
	case 47:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 303 ".\\parser.y"
 (*(YYSTYPE YYFAR*)yyvalptr) = yyattribute(1 - 1); 
#line 940 "parser.cpp"
			}
		}
		break;
	case 48:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 305 ".\\parser.y"
 
						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, CONST_EXPR, yyattribute(1 - 1)->attr.vali, Integer);
                      
#line 955 "parser.cpp"
			}
		}
		break;
	case 49:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 309 ".\\parser.y"

						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, CONST_EXPR, yyattribute(1 - 1)->attr.valc, Char);
                   	  
#line 970 "parser.cpp"
			}
		}
		break;
	case 50:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 313 ".\\parser.y"
 
						(*(YYSTYPE YYFAR*)yyvalptr) = parse_tree.NewRoot(EXPR_NODE, NOT_EXPR, NOT, Notype, yyattribute(2 - 2));
                      
#line 985 "parser.cpp"
			}
		}
		break;
	default:
		yyassert(0);
		break;
	}
}

void YYPARSERNAME::yytables()
{
	yyattribute_size = sizeof(YYSTYPE);
	yysstack_size = YYSTACK_SIZE;
	yystack_max = YYSTACK_MAX;

#ifdef YYDEBUG
	static const yysymbol_t YYNEARFAR YYBASED_CODE symbol[] = {
		{ "$end", 0 },
		{ "error", 256 },
		{ "INT", 257 },
		{ "CHAR", 258 },
		{ "IF", 259 },
		{ "ELSE", 260 },
		{ "WHILE", 261 },
		{ "INPUT", 262 },
		{ "PRINT", 263 },
		{ "ID", 264 },
		{ "NUM", 265 },
		{ "CONSTCHAR", 266 },
		{ "MAIN", 267 },
		{ "AND", 268 },
		{ "OR", 269 },
		{ "NOT", 270 },
		{ "ASSIGN", 271 },
		{ "EQ", 272 },
		{ "LT", 273 },
		{ "LE", 274 },
		{ "GT", 275 },
		{ "GE", 276 },
		{ "NE", 277 },
		{ "PLUS", 278 },
		{ "MINUS", 279 },
		{ "TIMES", 280 },
		{ "OVER", 281 },
		{ "LPAREN", 282 },
		{ "RPAREN", 283 },
		{ "SEMICOLON", 284 },
		{ "COMMA", 285 },
		{ "LBRACE", 286 },
		{ "RBRACE", 287 },
		{ NULL, 0 }
	};
	yysymbol = symbol;

	static const char* const YYNEARFAR YYBASED_CODE rule[] = {
		"$accept: program",
		"program: MAIN LPAREN RPAREN compound_stmt",
		"var_declaration: type_specifier idlist SEMICOLON",
		"idlist: idlist COMMA id",
		"idlist: id",
		"type_specifier: INT",
		"type_specifier: CHAR",
		"id: ID",
		"compound_stmt: LBRACE local_declarations statement_list RBRACE",
		"compound_stmt: LBRACE statement_list RBRACE",
		"local_declarations: local_declarations var_declaration",
		"local_declarations: var_declaration",
		"statement_list: statement_list statement",
		"statement_list: statement",
		"statement: expression_stmt",
		"statement: compound_stmt",
		"statement: selection_stmt",
		"statement: while_stmt",
		"statement: input_stmt",
		"statement: print_stmt",
		"expression_stmt: expression SEMICOLON",
		"expression_stmt: SEMICOLON",
		"selection_stmt: IF LPAREN expression RPAREN statement ELSE statement",
		"selection_stmt: IF LPAREN expression RPAREN statement",
		"while_stmt: WHILE LPAREN expression RPAREN statement",
		"input_stmt: INPUT LPAREN var RPAREN",
		"print_stmt: PRINT LPAREN var RPAREN",
		"expression: var ASSIGN expression",
		"expression: or_expression",
		"var: ID",
		"or_expression: or_expression OR and_expression",
		"or_expression: and_expression",
		"and_expression: and_expression AND additive_expression",
		"and_expression: additive_expression",
		"additive_expression: additive_expression EQ rel_expression",
		"additive_expression: additive_expression LT rel_expression",
		"additive_expression: additive_expression GT rel_expression",
		"additive_expression: additive_expression LE rel_expression",
		"additive_expression: additive_expression GE rel_expression",
		"additive_expression: additive_expression NE rel_expression",
		"additive_expression: rel_expression",
		"rel_expression: rel_expression PLUS term",
		"rel_expression: rel_expression MINUS term",
		"rel_expression: term",
		"term: term TIMES factor",
		"term: term OVER factor",
		"term: factor",
		"factor: LPAREN expression RPAREN",
		"factor: var",
		"factor: NUM",
		"factor: CONSTCHAR",
		"factor: NOT factor"
	};
	yyrule = rule;
#endif

	static const yyreduction_t YYNEARFAR YYBASED_CODE reduction[] = {
		{ 0, 1, -1 },
		{ 1, 4, 0 },
		{ 2, 3, 1 },
		{ 3, 3, 2 },
		{ 3, 1, 3 },
		{ 4, 1, 4 },
		{ 4, 1, 5 },
		{ 5, 1, 6 },
		{ 6, 4, 7 },
		{ 6, 3, 8 },
		{ 7, 2, 9 },
		{ 7, 1, 10 },
		{ 8, 2, 11 },
		{ 8, 1, 12 },
		{ 9, 1, 13 },
		{ 9, 1, 14 },
		{ 9, 1, 15 },
		{ 9, 1, 16 },
		{ 9, 1, 17 },
		{ 9, 1, 18 },
		{ 10, 2, 19 },
		{ 10, 1, 20 },
		{ 11, 7, 21 },
		{ 11, 5, 22 },
		{ 12, 5, 23 },
		{ 13, 4, 24 },
		{ 14, 4, 25 },
		{ 15, 3, 26 },
		{ 15, 1, 27 },
		{ 16, 1, 28 },
		{ 17, 3, 29 },
		{ 17, 1, 30 },
		{ 18, 3, 31 },
		{ 18, 1, 32 },
		{ 19, 3, 33 },
		{ 19, 3, 34 },
		{ 19, 3, 35 },
		{ 19, 3, 36 },
		{ 19, 3, 37 },
		{ 19, 3, 38 },
		{ 19, 1, 39 },
		{ 20, 3, 40 },
		{ 20, 3, 41 },
		{ 20, 1, 42 },
		{ 21, 3, 43 },
		{ 21, 3, 44 },
		{ 21, 1, 45 },
		{ 22, 3, 46 },
		{ 22, 1, 47 },
		{ 22, 1, 48 },
		{ 22, 1, 49 },
		{ 22, 2, 50 }
	};
	yyreduction = reduction;

	yytokenaction_size = 70;

	static const yytokenaction_t YYNEARFAR YYBASED_CODE tokenaction[] = {
		{ 94, YYAT_SHIFT, 9 },
		{ 92, YYAT_SHIFT, 94 },
		{ 94, YYAT_SHIFT, 10 },
		{ 94, YYAT_SHIFT, 11 },
		{ 94, YYAT_SHIFT, 12 },
		{ 65, YYAT_SHIFT, 14 },
		{ 65, YYAT_SHIFT, 15 },
		{ 84, YYAT_SHIFT, 64 },
		{ 84, YYAT_SHIFT, 65 },
		{ 75, YYAT_SHIFT, 55 },
		{ 65, YYAT_SHIFT, 16 },
		{ 76, YYAT_SHIFT, 56 },
		{ 76, YYAT_SHIFT, 57 },
		{ 76, YYAT_SHIFT, 58 },
		{ 76, YYAT_SHIFT, 59 },
		{ 76, YYAT_SHIFT, 60 },
		{ 76, YYAT_SHIFT, 61 },
		{ 83, YYAT_SHIFT, 64 },
		{ 83, YYAT_SHIFT, 65 },
		{ 82, YYAT_SHIFT, 62 },
		{ 82, YYAT_SHIFT, 63 },
		{ 72, YYAT_SHIFT, 45 },
		{ 65, YYAT_SHIFT, 17 },
		{ 81, YYAT_SHIFT, 62 },
		{ 81, YYAT_SHIFT, 63 },
		{ 94, YYAT_SHIFT, 18 },
		{ 69, YYAT_SHIFT, 90 },
		{ 94, YYAT_SHIFT, 5 },
		{ 34, YYAT_SHIFT, 56 },
		{ 34, YYAT_SHIFT, 57 },
		{ 34, YYAT_SHIFT, 58 },
		{ 34, YYAT_SHIFT, 59 },
		{ 34, YYAT_SHIFT, 60 },
		{ 34, YYAT_SHIFT, 61 },
		{ 80, YYAT_SHIFT, 62 },
		{ 80, YYAT_SHIFT, 63 },
		{ 79, YYAT_SHIFT, 62 },
		{ 79, YYAT_SHIFT, 63 },
		{ 78, YYAT_SHIFT, 62 },
		{ 78, YYAT_SHIFT, 63 },
		{ 77, YYAT_SHIFT, 62 },
		{ 77, YYAT_SHIFT, 63 },
		{ 46, YYAT_SHIFT, 71 },
		{ 46, YYAT_SHIFT, 72 },
		{ 36, YYAT_SHIFT, 64 },
		{ 36, YYAT_SHIFT, 65 },
		{ 35, YYAT_SHIFT, 62 },
		{ 35, YYAT_SHIFT, 63 },
		{ 22, YYAT_SHIFT, 7 },
		{ 22, YYAT_SHIFT, 8 },
		{ 68, YYAT_SHIFT, 89 },
		{ 67, YYAT_SHIFT, 88 },
		{ 66, YYAT_SHIFT, 87 },
		{ 49, YYAT_SHIFT, 73 },
		{ 44, YYAT_SHIFT, 70 },
		{ 41, YYAT_SHIFT, 13 },
		{ 33, YYAT_SHIFT, 55 },
		{ 32, YYAT_SHIFT, 54 },
		{ 31, YYAT_SHIFT, 53 },
		{ 30, YYAT_SHIFT, 52 },
		{ 23, YYAT_SHIFT, 50 },
		{ 12, YYAT_SHIFT, 41 },
		{ 11, YYAT_SHIFT, 40 },
		{ 10, YYAT_SHIFT, 39 },
		{ 9, YYAT_SHIFT, 38 },
		{ 4, YYAT_SHIFT, 5 },
		{ 3, YYAT_SHIFT, 4 },
		{ 2, YYAT_ACCEPT, 0 },
		{ 1, YYAT_SHIFT, 3 },
		{ 0, YYAT_SHIFT, 1 }
	};
	yytokenaction = tokenaction;

	static const yystateaction_t YYNEARFAR YYBASED_CODE stateaction[] = {
		{ -198, 1, YYAT_ERROR, 0 },
		{ -214, 1, YYAT_ERROR, 0 },
		{ 67, 1, YYAT_ERROR, 0 },
		{ -217, 1, YYAT_ERROR, 0 },
		{ -221, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 22 },
		{ 0, 0, YYAT_REDUCE, 1 },
		{ 0, 0, YYAT_REDUCE, 5 },
		{ 0, 0, YYAT_REDUCE, 6 },
		{ -218, 1, YYAT_ERROR, 0 },
		{ -219, 1, YYAT_ERROR, 0 },
		{ -220, 1, YYAT_ERROR, 0 },
		{ -221, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 29 },
		{ 0, 0, YYAT_REDUCE, 49 },
		{ 0, 0, YYAT_REDUCE, 50 },
		{ 0, 0, YYAT_DEFAULT, 65 },
		{ 0, 0, YYAT_DEFAULT, 65 },
		{ 0, 0, YYAT_REDUCE, 21 },
		{ 0, 0, YYAT_REDUCE, 15 },
		{ 0, 0, YYAT_REDUCE, 11 },
		{ 0, 0, YYAT_DEFAULT, 72 },
		{ -209, 1, YYAT_DEFAULT, 94 },
		{ -227, 1, YYAT_DEFAULT, 94 },
		{ 0, 0, YYAT_REDUCE, 13 },
		{ 0, 0, YYAT_REDUCE, 14 },
		{ 0, 0, YYAT_REDUCE, 16 },
		{ 0, 0, YYAT_REDUCE, 17 },
		{ 0, 0, YYAT_REDUCE, 18 },
		{ 0, 0, YYAT_REDUCE, 19 },
		{ -225, 1, YYAT_ERROR, 0 },
		{ -213, 1, YYAT_REDUCE, 48 },
		{ -212, 1, YYAT_REDUCE, 28 },
		{ -212, 1, YYAT_REDUCE, 31 },
		{ -244, 1, YYAT_REDUCE, 33 },
		{ -232, 1, YYAT_REDUCE, 40 },
		{ -236, 1, YYAT_REDUCE, 43 },
		{ 0, 0, YYAT_REDUCE, 46 },
		{ 0, 0, YYAT_DEFAULT, 65 },
		{ 0, 0, YYAT_DEFAULT, 65 },
		{ 0, 0, YYAT_DEFAULT, 41 },
		{ -209, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 48 },
		{ 0, 0, YYAT_REDUCE, 51 },
		{ -229, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 7 },
		{ -242, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 4 },
		{ 0, 0, YYAT_REDUCE, 10 },
		{ -234, 1, YYAT_DEFAULT, 94 },
		{ 0, 0, YYAT_REDUCE, 9 },
		{ 0, 0, YYAT_REDUCE, 12 },
		{ 0, 0, YYAT_REDUCE, 20 },
		{ 0, 0, YYAT_DEFAULT, 65 },
		{ 0, 0, YYAT_DEFAULT, 65 },
		{ 0, 0, YYAT_DEFAULT, 65 },
		{ 0, 0, YYAT_DEFAULT, 65 },
		{ 0, 0, YYAT_DEFAULT, 65 },
		{ 0, 0, YYAT_DEFAULT, 65 },
		{ 0, 0, YYAT_DEFAULT, 65 },
		{ 0, 0, YYAT_DEFAULT, 65 },
		{ 0, 0, YYAT_DEFAULT, 65 },
		{ 0, 0, YYAT_DEFAULT, 65 },
		{ 0, 0, YYAT_DEFAULT, 65 },
		{ 0, 0, YYAT_DEFAULT, 65 },
		{ -260, 1, YYAT_DEFAULT, 41 },
		{ -231, 1, YYAT_ERROR, 0 },
		{ -232, 1, YYAT_ERROR, 0 },
		{ -233, 1, YYAT_ERROR, 0 },
		{ -257, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 47 },
		{ 0, 0, YYAT_REDUCE, 2 },
		{ -243, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 8 },
		{ 0, 0, YYAT_REDUCE, 27 },
		{ -259, 1, YYAT_REDUCE, 30 },
		{ -261, 1, YYAT_REDUCE, 32 },
		{ -238, 1, YYAT_REDUCE, 34 },
		{ -240, 1, YYAT_REDUCE, 35 },
		{ -242, 1, YYAT_REDUCE, 37 },
		{ -244, 1, YYAT_REDUCE, 36 },
		{ -255, 1, YYAT_REDUCE, 38 },
		{ -259, 1, YYAT_REDUCE, 39 },
		{ -263, 1, YYAT_REDUCE, 41 },
		{ -273, 1, YYAT_REDUCE, 42 },
		{ 0, 0, YYAT_REDUCE, 44 },
		{ 0, 0, YYAT_REDUCE, 45 },
		{ 0, 0, YYAT_DEFAULT, 94 },
		{ 0, 0, YYAT_DEFAULT, 94 },
		{ 0, 0, YYAT_REDUCE, 25 },
		{ 0, 0, YYAT_REDUCE, 26 },
		{ 0, 0, YYAT_REDUCE, 3 },
		{ -259, 1, YYAT_REDUCE, 23 },
		{ 0, 0, YYAT_REDUCE, 24 },
		{ -259, 1, YYAT_DEFAULT, 65 },
		{ 0, 0, YYAT_REDUCE, 22 }
	};
	yystateaction = stateaction;

	yynontermgoto_size = 50;

	static const yynontermgoto_t YYNEARFAR YYBASED_CODE nontermgoto[] = {
		{ 94, 19 },
		{ 63, 84 },
		{ 63, 37 },
		{ 94, 95 },
		{ 94, 25 },
		{ 94, 26 },
		{ 94, 27 },
		{ 94, 28 },
		{ 94, 29 },
		{ 94, 30 },
		{ 22, 48 },
		{ 21, 46 },
		{ 22, 21 },
		{ 21, 47 },
		{ 61, 82 },
		{ 61, 36 },
		{ 22, 49 },
		{ 22, 24 },
		{ 53, 74 },
		{ 53, 31 },
		{ 53, 32 },
		{ 53, 33 },
		{ 5, 20 },
		{ 65, 42 },
		{ 55, 76 },
		{ 55, 35 },
		{ 88, 93 },
		{ 5, 22 },
		{ 5, 23 },
		{ 65, 86 },
		{ 54, 75 },
		{ 54, 34 },
		{ 87, 92 },
		{ 72, 91 },
		{ 64, 85 },
		{ 62, 83 },
		{ 60, 81 },
		{ 59, 80 },
		{ 58, 79 },
		{ 57, 78 },
		{ 56, 77 },
		{ 49, 51 },
		{ 41, 69 },
		{ 40, 68 },
		{ 39, 67 },
		{ 38, 66 },
		{ 17, 44 },
		{ 16, 43 },
		{ 4, 6 },
		{ 0, 2 }
	};
	yynontermgoto = nontermgoto;

	static const yystategoto_t YYNEARFAR YYBASED_CODE stategoto[] = {
		{ 48, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 42, -1 },
		{ 20, 22 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 25, 65 },
		{ 31, 53 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 8, -1 },
		{ 8, 94 },
		{ 0, 49 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 30, 53 },
		{ 29, 53 },
		{ 27, -1 },
		{ 26, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 32, 94 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 3, 54 },
		{ 12, 55 },
		{ 5, 61 },
		{ 20, 61 },
		{ 19, 61 },
		{ 18, 61 },
		{ 17, 61 },
		{ 16, 61 },
		{ -6, 63 },
		{ 14, 63 },
		{ -20, 65 },
		{ 12, 65 },
		{ 7, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 28, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 23, 94 },
		{ 17, 94 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ -6, 53 },
		{ 0, -1 }
	};
	yystategoto = stategoto;

	yydestructorptr = NULL;

	yytokendestptr = NULL;
	yytokendest_size = 0;

	yytokendestbaseptr = NULL;
	yytokendestbase_size = 0;
}
#line 318 ".\\parser.y"


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

