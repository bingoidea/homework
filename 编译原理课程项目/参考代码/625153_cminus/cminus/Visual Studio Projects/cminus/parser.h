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
* parser.h
* C++ header file generated from parser.y.
* 
* Date: 12/10/03
* Time: 20:17:51
* 
* AYACC Version: 2.06
****************************************************************************/

#ifndef _PARSER_H
#define _PARSER_H

#include <yycpars.h>

/////////////////////////////////////////////////////////////////////////////
// parser

#ifndef YYEXPPARSER
#define YYEXPPARSER
#endif

class YYEXPPARSER YYFAR parser : public _YL yyfparser {
public:
	parser();
	virtual ~parser();

protected:
	void yytables();
	virtual void yyaction(int action);
#ifdef YYDEBUG
	void YYFAR* yyattribute1(int index) const;
	void yyinitdebug(void YYFAR** p, int count) const;
#endif

	// attribute functions
	virtual void yystacktoval(int index);
	virtual void yyvaltostack(int index);
	virtual void yylvaltoval();
	virtual void yyvaltolval();
	virtual void yylvaltostack(int index);

	virtual void YYFAR* yynewattribute(int count);
	virtual void yydeleteattribute(void YYFAR* attribute);
	virtual void yycopyattribute(void YYFAR* dest, const void YYFAR* src, int count);

public:
#line 31 ".\\parser.y"

	// place any extra class members here

#line 68 "parser.h"
};

#ifndef YYPARSERNAME
#define YYPARSERNAME parser
#endif

#line 46 ".\\parser.y"

#ifndef YYSTYPE
#define YYSTYPE Node *
#endif

#line 81 "parser.h"
#define INT 257
#define CHAR 258
#define IF 259
#define ELSE 260
#define WHILE 261
#define INPUT 262
#define PRINT 263
#define ID 264
#define NUM 265
#define CONSTCHAR 266
#define MAIN 267
#define AND 268
#define OR 269
#define NOT 270
#define ASSIGN 271
#define EQ 272
#define LT 273
#define LE 274
#define GT 275
#define GE 276
#define NE 277
#define PLUS 278
#define MINUS 279
#define TIMES 280
#define OVER 281
#define LPAREN 282
#define RPAREN 283
#define SEMICOLON 284
#define COMMA 285
#define LBRACE 286
#define RBRACE 287
#define ERROR 288
#define ENDFILE 289
#endif
