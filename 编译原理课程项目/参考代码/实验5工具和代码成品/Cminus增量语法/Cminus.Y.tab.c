
/*  A Bison parser, made from Cminus.Y
 by  GNU Bison version 1.25
  */

#define YYBISON 1  /* Identify Bison output.  */

#define alloca

#define	CONSTANT	258
#define	INT	259
#define	VOID	260
#define	IDENTIFIER	261
#define	STRING_LITERAL	262
#define	SIZEOF	263
#define	PTR_OP	264
#define	INC_OP	265
#define	DEC_OP	266
#define	LEFT_OP	267
#define	RIGHT_OP	268
#define	LE_OP	269
#define	GE_OP	270
#define	EQ_OP	271
#define	NE_OP	272
#define	AND_OP	273
#define	OR_OP	274
#define	MUL_ASSIGN	275
#define	DIV_ASSIGN	276
#define	MOD_ASSIGN	277
#define	ADD_ASSIGN	278
#define	SUB_ASSIGN	279
#define	LEFT_ASSIGN	280
#define	RIGHT_ASSIGN	281
#define	AND_ASSIGN	282
#define	XOR_ASSIGN	283
#define	OR_ASSIGN	284
#define	TYPE_NAME	285
#define	TYPEDEF	286
#define	EXTERN	287
#define	STATIC	288
#define	AUTO	289
#define	REGISTER	290
#define	INLINE	291
#define	RESTRICT	292
#define	CHAR	293
#define	SHORT	294
#define	LONG	295
#define	SIGNED	296
#define	UNSIGNED	297
#define	FLOAT	298
#define	DOUBLE	299
#define	CONST	300
#define	VOLATILE	301
#define	BOOL	302
#define	COMPLEX	303
#define	IMAGINARY	304
#define	STRUCT	305
#define	UNION	306
#define	ENUM	307
#define	ELLIPSIS	308
#define	CASE	309
#define	DEFAULT	310
#define	IF	311
#define	ELSE	312
#define	SWITCH	313
#define	WHILE	314
#define	DO	315
#define	FOR	316
#define	GOTO	317
#define	CONTINUE	318
#define	BREAK	319
#define	RETURN	320
#define	PARAM	321
#define	FUNC	322
#define	VAR	323
#define	CALL	324
#define	GLOBAL_VAR	325
#define	LOWER_THAN_ELSE	326

#line 1 "Cminus.Y"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "node.h"
#include "hash.h"
#include "var.h"
#include "command.h"
Node *tmp;
/* 属性操作类型 */
Node *opr(int name, int num, ...);
Node *set_index(int value);
Node *set_content(int value);
void freeNode(Node *p);
int exeNode(Node *p, int signal);
int yylexeNode(void);
void yyerror(char *s);
/*int var[26]; [> 变量数组 <]*/

#line 21 "Cminus.Y"
typedef union {
    int iValue;
    int sIndex;
    Node *nPtr;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		102
#define	YYFLAG		32768
#define	YYNTBASE	87

#define YYTRANSLATE(x) ((unsigned)(x) <= 326 ? yytranslate[x] : 116)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    75,
    76,    85,    83,    77,    84,     2,    86,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    72,    81,
    80,    82,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    73,     2,    74,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    78,     2,    79,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     5,     7,     9,    11,    15,    22,    24,    26,
    32,    34,    36,    38,    42,    44,    47,    52,    57,    60,
    61,    64,    65,    67,    69,    71,    73,    75,    78,    80,
    86,    94,   100,   103,   107,   111,   113,   115,   120,   124,
   126,   128,   130,   132,   134,   136,   138,   142,   144,   146,
   148,   152,   154,   156,   158,   162,   164,   166,   168,   173,
   175,   176,   180
};

static const short yyrhs[] = {    88,
     0,    88,    89,     0,    89,     0,    90,     0,    92,     0,
    91,     6,    72,     0,    91,     6,    73,     3,    74,    72,
     0,     4,     0,     5,     0,    91,     6,    75,    93,    76,
     0,    96,     0,    94,     0,     5,     0,    94,    77,    95,
     0,    95,     0,    91,     6,     0,    91,     6,    73,    74,
     0,    78,    97,    98,    79,     0,    97,    90,     0,     0,
    98,    99,     0,     0,   100,     0,    96,     0,   101,     0,
   102,     0,   103,     0,   104,    72,     0,    72,     0,    56,
    75,   104,    76,    99,     0,    56,    75,   104,    76,    99,
    57,    99,     0,    59,    75,   104,    76,    99,     0,    65,
    72,     0,    65,   104,    72,     0,   105,    80,   104,     0,
   106,     0,     6,     0,     6,    73,   104,    74,     0,   108,
   107,   108,     0,   108,     0,    14,     0,    81,     0,    82,
     0,    15,     0,    16,     0,    17,     0,   108,   109,   110,
     0,   110,     0,    83,     0,    84,     0,   110,   111,   112,
     0,   112,     0,    85,     0,    86,     0,    75,   104,    76,
     0,   105,     0,   113,     0,     3,     0,     6,    75,   114,
    76,     0,   115,     0,     0,   115,    77,   104,     0,   104,
     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    60,    64,    65,    69,    73,    77,    84,    94,    95,    99,
   106,   111,   112,   116,   117,   121,   128,   138,   143,   144,
   148,   149,   153,   154,   155,   156,   157,   161,   162,   166,
   167,   172,   176,   177,   181,   185,   189,   190,   199,   203,
   207,   208,   209,   210,   211,   212,   216,   220,   227,   228,
   232,   236,   240,   241,   245,   246,   247,   248,   252,   261,
   262,   266,   267
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","CONSTANT",
"INT","VOID","IDENTIFIER","STRING_LITERAL","SIZEOF","PTR_OP","INC_OP","DEC_OP",
"LEFT_OP","RIGHT_OP","LE_OP","GE_OP","EQ_OP","NE_OP","AND_OP","OR_OP","MUL_ASSIGN",
"DIV_ASSIGN","MOD_ASSIGN","ADD_ASSIGN","SUB_ASSIGN","LEFT_ASSIGN","RIGHT_ASSIGN",
"AND_ASSIGN","XOR_ASSIGN","OR_ASSIGN","TYPE_NAME","TYPEDEF","EXTERN","STATIC",
"AUTO","REGISTER","INLINE","RESTRICT","CHAR","SHORT","LONG","SIGNED","UNSIGNED",
"FLOAT","DOUBLE","CONST","VOLATILE","BOOL","COMPLEX","IMAGINARY","STRUCT","UNION",
"ENUM","ELLIPSIS","CASE","DEFAULT","IF","ELSE","SWITCH","WHILE","DO","FOR","GOTO",
"CONTINUE","BREAK","RETURN","PARAM","FUNC","VAR","CALL","GLOBAL_VAR","LOWER_THAN_ELSE",
"';'","'['","']'","'('","')'","','","'{'","'}'","'='","'<'","'>'","'+'","'-'",
"'*'","'/'","program","declaration_list","declaration","var_declaration","type_specifier",
"fun_declaration","params","params_list","param","compound_stmt","local_declarations",
"statement_list","statement","expression_stmt","selection_stmt","iteration_stmt",
"return_stmt","expression","var","simple_expression","relop","additive_expression",
"addop","term","mulop","factor","call","args","arg_list", NULL
};
#endif

static const short yyr1[] = {     0,
    87,    88,    88,    89,    89,    90,    90,    91,    91,    92,
    92,    93,    93,    94,    94,    95,    95,    96,    97,    97,
    98,    98,    99,    99,    99,    99,    99,   100,   100,   101,
   101,   102,   103,   103,   104,   104,   105,   105,   106,   106,
   107,   107,   107,   107,   107,   107,   108,   108,   109,   109,
   110,   110,   111,   111,   112,   112,   112,   112,   113,   114,
   114,   115,   115
};

static const short yyr2[] = {     0,
     1,     2,     1,     1,     1,     3,     6,     1,     1,     5,
     1,     1,     1,     3,     1,     2,     4,     4,     2,     0,
     2,     0,     1,     1,     1,     1,     1,     2,     1,     5,
     7,     5,     2,     3,     3,     1,     1,     4,     3,     1,
     1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
     3,     1,     1,     1,     3,     1,     1,     1,     4,     1,
     0,     3,     1
};

static const short yydefact[] = {     0,
     8,     9,    20,     1,     3,     4,     0,     5,    11,    22,
     2,     0,    19,     0,     0,     6,     0,     0,     0,    58,
    37,     0,     0,     0,    29,     0,    18,    24,    21,    23,
    25,    26,    27,     0,    56,    36,    40,    48,    52,    57,
     0,     9,     0,     0,    12,    15,     0,    61,     0,     0,
    33,     0,     0,    28,     0,    41,    44,    45,    46,    42,
    43,    49,    50,     0,     0,    53,    54,     0,     0,    16,
    10,     0,     0,    63,     0,    60,     0,     0,    34,    55,
    35,    56,    39,    47,    51,     7,     0,    14,    38,    59,
     0,     0,     0,    17,    62,    30,    32,     0,    31,     0,
     0,     0
};

static const short yydefgoto[] = {   100,
     4,     5,     6,     7,     8,    44,    45,    46,    28,    10,
    15,    29,    30,    31,    32,    33,    34,    35,    36,    64,
    37,    65,    38,    68,    39,    40,    75,    76
};

static const short yypact[] = {     2,
-32768,-32768,-32768,     2,-32768,-32768,    15,-32768,-32768,    34,
-32768,   -45,-32768,    27,    -3,-32768,     5,    36,   -29,-32768,
   -44,   -26,   -25,    -2,-32768,     6,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,   -21,   -28,-32768,     1,   -40,-32768,-32768,
   -20,   -19,    53,   -16,   -14,-32768,     6,     6,     6,     6,
-32768,   -11,   -10,-32768,     6,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,     6,     6,-32768,-32768,     6,    -7,    -6,
-32768,    34,    13,-32768,    -8,    11,     3,    16,-32768,-32768,
-32768,-32768,   -36,   -40,-32768,-32768,    17,-32768,-32768,-32768,
     6,    -1,    -1,-32768,-32768,    32,-32768,    -1,-32768,    90,
    93,-32768
};

static const short yypgoto[] = {-32768,
-32768,    91,    84,    14,-32768,-32768,-32768,    24,    10,-32768,
-32768,   -73,-32768,-32768,-32768,-32768,   -13,   -42,-32768,-32768,
    33,-32768,    35,-32768,    30,-32768,-32768,-32768
};


#define	YYLAST		100


static const short yytable[] = {    20,
    20,    20,    21,    21,    21,     1,     2,    41,    20,     9,
    52,    21,    53,     9,    56,    57,    58,    59,    96,    97,
    12,    82,    82,    14,    99,    82,    16,    17,    47,    18,
    48,    43,    19,    73,    74,    77,    78,     1,     2,     1,
    42,    81,    16,    17,    66,    67,    62,    63,    49,    50,
    54,    55,    22,    69,    22,    23,   -13,    23,    70,    71,
    79,    24,    72,    24,    86,    80,    87,    90,    25,    51,
    25,    26,    26,    26,     3,    27,     3,    95,    92,     3,
    26,    60,    61,    62,    63,    43,    89,    91,    98,   101,
    94,    93,   102,    13,    11,    88,    83,    85,     0,    84
};

static const short yycheck[] = {     3,
     3,     3,     6,     6,     6,     4,     5,     3,     3,     0,
    24,     6,    26,     4,    14,    15,    16,    17,    92,    93,
     6,    64,    65,    10,    98,    68,    72,    73,    73,    75,
    75,    18,     6,    47,    48,    49,    50,     4,     5,     4,
     5,    55,    72,    73,    85,    86,    83,    84,    75,    75,
    72,    80,    56,    74,    56,    59,    76,    59,     6,    76,
    72,    65,    77,    65,    72,    76,    73,    76,    72,    72,
    72,    75,    75,    75,    78,    79,    78,    91,    76,    78,
    75,    81,    82,    83,    84,    72,    74,    77,    57,     0,
    74,    76,     0,    10,     4,    72,    64,    68,    -1,    65
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 60 "Cminus.Y"
{ exeNode(yyvsp[0].nPtr, 0); freeNode(yyvsp[0].nPtr); ;
    break;}
case 2:
#line 64 "Cminus.Y"
{ yyval.nPtr = opr(';', 2, yyvsp[-1].nPtr, yyvsp[0].nPtr); ;
    break;}
case 3:
#line 65 "Cminus.Y"
{ yyval.nPtr = yyvsp[0].nPtr; ;
    break;}
case 4:
#line 70 "Cminus.Y"
{ 
            yyval.nPtr  = opr(GLOBAL_VAR, 1, yyvsp[0].nPtr);
        ;
    break;}
case 5:
#line 73 "Cminus.Y"
{ yyval.nPtr = yyvsp[0].nPtr; ;
    break;}
case 6:
#line 78 "Cminus.Y"
{
            Node *tmp1;
            /* here to insert new var declaration */
            tmp1 = set_index(yyvsp[-1].sIndex);
            yyval.nPtr = opr(VAR, 2, yyvsp[-2].nPtr, tmp1);
        ;
    break;}
case 7:
#line 85 "Cminus.Y"
{
            Node *tmp1, *tmp2;
            tmp1 = set_index(yyvsp[-4].sIndex);
            tmp2 = set_content(yyvsp[-2].iValue);
            yyval.nPtr = opr(VAR, 3, yyvsp[-5].nPtr, tmp1, tmp2);
        ;
    break;}
case 8:
#line 94 "Cminus.Y"
{ yyval.nPtr = set_content(INT); ;
    break;}
case 9:
#line 95 "Cminus.Y"
{ yyval.nPtr = set_content(VOID); ;
    break;}
case 10:
#line 100 "Cminus.Y"
{
            Node *tmp1;
            tmp1 = set_index(yyvsp[-3].sIndex);
            yyval.nPtr = opr(FUNC, 3, yyvsp[-4].nPtr, tmp1, yyvsp[-1].nPtr);
        ;
    break;}
case 11:
#line 107 "Cminus.Y"
{ yyval.nPtr = opr(FUNC, 1, yyvsp[0].nPtr); ;
    break;}
case 12:
#line 111 "Cminus.Y"
{ yyval.nPtr = yyvsp[0].nPtr; ;
    break;}
case 13:
#line 112 "Cminus.Y"
{ yyval.nPtr = NULL; ;
    break;}
case 14:
#line 116 "Cminus.Y"
{ yyval.nPtr = opr(',', 2, yyvsp[-2].nPtr, yyvsp[0].nPtr); ;
    break;}
case 15:
#line 117 "Cminus.Y"
{ yyval.nPtr = yyvsp[0].nPtr; ;
    break;}
case 16:
#line 122 "Cminus.Y"
{
            Node *tmp1;
            /* here to insert new var declaration */
            tmp1 = set_index(yyvsp[0].sIndex);
            yyval.nPtr = opr(PARAM, 2, yyvsp[-1].nPtr, tmp1);
        ;
    break;}
case 17:
#line 129 "Cminus.Y"
{
            Node *tmp1;
            /* here to insert new var declaration */
            tmp1 = set_index(yyvsp[-2].sIndex);
            yyval.nPtr = opr(PARAM, 3, yyvsp[-3].nPtr, tmp1, NULL);
        ;
    break;}
case 18:
#line 139 "Cminus.Y"
{ yyval.nPtr = opr('{', 2, yyvsp[-2].nPtr, yyvsp[-1].nPtr); ;
    break;}
case 19:
#line 143 "Cminus.Y"
{ yyval.nPtr = opr(';', 2, yyvsp[-1].nPtr, yyvsp[0].nPtr); ;
    break;}
case 20:
#line 144 "Cminus.Y"
{ yyval.nPtr = NULL; ;
    break;}
case 21:
#line 148 "Cminus.Y"
{ yyval.nPtr = opr(';', 2, yyvsp[-1].nPtr, yyvsp[0].nPtr); ;
    break;}
case 22:
#line 149 "Cminus.Y"
{ yyval.nPtr = NULL; ;
    break;}
case 23:
#line 153 "Cminus.Y"
{ yyval.nPtr = yyvsp[0].nPtr; ;
    break;}
case 24:
#line 154 "Cminus.Y"
{ yyval.nPtr = yyvsp[0].nPtr; ;
    break;}
case 25:
#line 155 "Cminus.Y"
{ yyval.nPtr = yyvsp[0].nPtr; ;
    break;}
case 26:
#line 156 "Cminus.Y"
{ yyval.nPtr = yyvsp[0].nPtr; ;
    break;}
case 27:
#line 157 "Cminus.Y"
{ yyval.nPtr = yyvsp[0].nPtr; ;
    break;}
case 28:
#line 161 "Cminus.Y"
{ yyval.nPtr = yyvsp[-1].nPtr; ;
    break;}
case 29:
#line 162 "Cminus.Y"
{ yyval.nPtr = NULL; ;
    break;}
case 30:
#line 166 "Cminus.Y"
{ yyval.nPtr = opr(IF, 2, yyvsp[-2].nPtr, yyvsp[0].nPtr); ;
    break;}
case 31:
#line 168 "Cminus.Y"
{ yyval.nPtr = opr(IF, 3, yyvsp[-4].nPtr, yyvsp[-2].nPtr, yyvsp[0].nPtr); ;
    break;}
case 32:
#line 172 "Cminus.Y"
{ yyval.nPtr = opr(WHILE, 2, yyvsp[-2].nPtr, yyvsp[0].nPtr); ;
    break;}
case 33:
#line 176 "Cminus.Y"
{ yyval.nPtr = opr(RETURN, 0); ;
    break;}
case 34:
#line 177 "Cminus.Y"
{ yyval.nPtr = opr(RETURN, 1, yyvsp[-1].nPtr); ;
    break;}
case 35:
#line 182 "Cminus.Y"
{
            yyval.nPtr = opr('=', 2, yyvsp[-2].nPtr, yyvsp[0].nPtr);
        ;
    break;}
case 36:
#line 185 "Cminus.Y"
{ yyval.nPtr = yyvsp[0].nPtr; ;
    break;}
case 37:
#line 189 "Cminus.Y"
{ yyval.nPtr = set_index(yyvsp[0].sIndex); ;
    break;}
case 38:
#line 191 "Cminus.Y"
{
            Node *tmp1;
            tmp1 = set_index(yyvsp[-3].sIndex);
            yyval.nPtr = opr('[', 2, tmp1, yyvsp[-1].nPtr); 
        ;
    break;}
case 39:
#line 200 "Cminus.Y"
{
            yyval.nPtr = opr(yyvsp[-1].iValue, 2, yyvsp[-2].nPtr, yyvsp[0].nPtr); 
        ;
    break;}
case 40:
#line 203 "Cminus.Y"
{ yyval.nPtr = yyvsp[0].nPtr; ;
    break;}
case 41:
#line 207 "Cminus.Y"
{ yyval.iValue = LE_OP; ;
    break;}
case 42:
#line 208 "Cminus.Y"
{ yyval.iValue = '<'; ;
    break;}
case 43:
#line 209 "Cminus.Y"
{ yyval.iValue = '>'; ;
    break;}
case 44:
#line 210 "Cminus.Y"
{ yyval.iValue = GE_OP; ;
    break;}
case 45:
#line 211 "Cminus.Y"
{ yyval.iValue = EQ_OP; ;
    break;}
case 46:
#line 212 "Cminus.Y"
{ yyval.iValue = NE_OP; ;
    break;}
case 47:
#line 217 "Cminus.Y"
{
            yyval.nPtr = opr(yyvsp[-1].iValue, 2, yyvsp[-2].nPtr, yyvsp[0].nPtr);
        ;
    break;}
case 48:
#line 221 "Cminus.Y"
{ 
            yyval.nPtr = yyvsp[0].nPtr;
        ;
    break;}
case 49:
#line 227 "Cminus.Y"
{ yyval.iValue = '+'; ;
    break;}
case 50:
#line 228 "Cminus.Y"
{ yyval.iValue = '-'; ;
    break;}
case 51:
#line 233 "Cminus.Y"
{
            yyval.nPtr = opr(yyvsp[-1].iValue, 2, yyvsp[-2].nPtr, yyvsp[0].nPtr);
        ;
    break;}
case 52:
#line 236 "Cminus.Y"
{ yyval.nPtr = yyvsp[0].nPtr; ;
    break;}
case 53:
#line 240 "Cminus.Y"
{ yyval.iValue = '*'; ;
    break;}
case 54:
#line 241 "Cminus.Y"
{ yyval.iValue = '/'; ;
    break;}
case 55:
#line 245 "Cminus.Y"
{ yyval.nPtr = yyvsp[-1].nPtr; ;
    break;}
case 56:
#line 246 "Cminus.Y"
{ yyval.nPtr = yyvsp[0].nPtr; ;
    break;}
case 57:
#line 247 "Cminus.Y"
{ yyval.nPtr = yyvsp[0].nPtr; ;
    break;}
case 58:
#line 248 "Cminus.Y"
{ yyval.nPtr = set_content(yyvsp[0].iValue); ;
    break;}
case 59:
#line 253 "Cminus.Y"
{ 
            Node *tmp1;
            tmp1 = set_index(yyvsp[-3].sIndex);
            yyval.nPtr = opr(CALL, 2, tmp1, yyvsp[-1].nPtr);
        ;
    break;}
case 60:
#line 261 "Cminus.Y"
{ yyval.nPtr = yyvsp[0].nPtr; ;
    break;}
case 61:
#line 262 "Cminus.Y"
{ yyval.nPtr = NULL; ;
    break;}
case 62:
#line 266 "Cminus.Y"
{ yyval.nPtr = opr(',', 2, yyvsp[-2].nPtr, yyvsp[0].nPtr); ;
    break;}
case 63:
#line 267 "Cminus.Y"
{ yyval.nPtr = yyvsp[0].nPtr; ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 270 "Cminus.Y"

#define SIZE_OF_NODE ((char *)&p->content - (char *)p)

Node *set_content(int value) 
{
	Node *p;
	size_t sizeNode;
	/* 分配结点空间 */
	sizeNode = SIZE_OF_NODE + sizeof(int);
	
	if ((p = malloc(sizeNode)) == NULL)
		yyerror("out of memory");
		
	/* 复制内容 */
	p->type = TYPE_CONTENT;
	p->content = value;

	return p;
}

Node *set_index(int value) 
{
	Node *p;
	size_t sizeNode;
	/* 分配结点空间 */
	sizeNode = SIZE_OF_NODE + sizeof(int);
	if ((p = malloc(sizeNode)) == NULL)
		yyerror("out of memory"); 
	
	/* 复制内容 */
	p->type = TYPE_INDEX;
	p->index = value;  
	return p;
}

Node *opr(int name, int num, ...) 
{
	va_list valist;
	Node *p;
	size_t sizeNode;
	int i;
	/* 分配结点空间 */
	sizeNode = SIZE_OF_NODE + sizeof(OpNode) + (num - 1) * sizeof(Node*);
 
	if ((p = malloc(sizeNode)) == NULL)
		yyerror("out of memory"); 
		
	/* 复制内容 */
	p->type = TYPE_OP;
	p->op.name = name;
	p->op.num = num;
	va_start(valist, num);
 
	for (i = 0; i < num; i++)
		p->op.node[i] = va_arg(valist, Node*);
		
	va_end(valist);
	return p;
}

void freeNode(Node *p) 
{
	int i;
	if (!p) return;
	if (p->type == TYPE_OP) {
		for (i = 0; i < p->op.num; i++)
            freeNode(p->op.node[i]);
	}
	free (p);
}

void yyerror(char *s) 
{
   printf("%s\n", s);
}

int main() 
{

    hash_init(var_local, HASHSIZE);
    hash_init(var_local_SorA, HASHSIZE);
    hash_init(var_local_GorP, HASHSIZE);

    yyparse();

    return 0;
}