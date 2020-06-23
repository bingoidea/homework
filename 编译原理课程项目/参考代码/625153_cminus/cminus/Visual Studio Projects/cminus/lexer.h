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
* lexer.h
* C++ header file generated from lexer.l.
* 
* Date: 12/10/03
* Time: 20:17:51
* 
* ALex Version: 2.06
****************************************************************************/

#ifndef _LEXER_H
#define _LEXER_H

#include <yyclex.h>

/////////////////////////////////////////////////////////////////////////////
// lexer

#ifndef YYEXPLEXER
#define YYEXPLEXER
#endif

class YYEXPLEXER YYFAR lexer : public _YL yyflexer {
public:
	lexer();
	virtual ~lexer();

	// backards compatibility with lex
#ifdef input
	virtual int yyinput();
#endif
#ifdef output
	virtual void yyoutput(int ch);
#endif
#ifdef unput
	virtual void yyunput(int ch);
#endif

protected:
	void yytables();
	virtual int yyaction(int action);

public:
#line 34 ".\\lexer.l"

	// place any extra class members here

#line 64 "lexer.h"
};

#ifndef YYLEXERNAME
#define YYLEXERNAME lexer
#endif

#ifndef INITIAL
#define INITIAL 0
#endif

#endif
