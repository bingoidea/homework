#############################################################################
#                         A C A D E M I C   C O P Y
# 
# This file was produced by an ACADEMIC COPY of Parser Generator. It is for
# use in non-commercial software only. An ACADEMIC COPY of Parser Generator
# can only be used by a student, or a member of an academic community. If
# however you want to use Parser Generator for commercial purposes then you
# will need to purchase a license. For more information see the online help or
# go to the Bumble-Bee Software homepage at:
# 
# http://www.bumblebeesoftware.com
# 
# This notice must remain present in the file. It cannot be removed.
#############################################################################

#############################################################################
# parser.v
# YACC verbose file generated from parser.y.
# 
# Date: 12/10/03
# Time: 20:17:51
# 
# AYACC Version: 2.06
#############################################################################


##############################################################################
# Rules
##############################################################################

    0  $accept : program $end

    1  program : MAIN LPAREN RPAREN compound_stmt

    2  var_declaration : type_specifier idlist SEMICOLON

    3  idlist : idlist COMMA id
    4         | id

    5  type_specifier : INT
    6                 | CHAR

    7  id : ID

    8  compound_stmt : LBRACE local_declarations statement_list RBRACE
    9                | LBRACE statement_list RBRACE

   10  local_declarations : local_declarations var_declaration
   11                     | var_declaration

   12  statement_list : statement_list statement
   13                 | statement

   14  statement : expression_stmt
   15            | compound_stmt
   16            | selection_stmt
   17            | while_stmt
   18            | input_stmt
   19            | print_stmt

   20  expression_stmt : expression SEMICOLON
   21                  | SEMICOLON

   22  selection_stmt : IF LPAREN expression RPAREN statement ELSE statement
   23                 | IF LPAREN expression RPAREN statement

   24  while_stmt : WHILE LPAREN expression RPAREN statement

   25  input_stmt : INPUT LPAREN var RPAREN

   26  print_stmt : PRINT LPAREN var RPAREN

   27  expression : var ASSIGN expression
   28             | or_expression

   29  var : ID

   30  or_expression : or_expression OR and_expression
   31                | and_expression

   32  and_expression : and_expression AND additive_expression
   33                 | additive_expression

   34  additive_expression : additive_expression EQ rel_expression
   35                      | additive_expression LT rel_expression
   36                      | additive_expression GT rel_expression
   37                      | additive_expression LE rel_expression
   38                      | additive_expression GE rel_expression
   39                      | additive_expression NE rel_expression
   40                      | rel_expression

   41  rel_expression : rel_expression PLUS term
   42                 | rel_expression MINUS term
   43                 | term

   44  term : term TIMES factor
   45       | term OVER factor
   46       | factor

   47  factor : LPAREN expression RPAREN
   48         | var
   49         | NUM
   50         | CONSTCHAR
   51         | NOT factor


##############################################################################
# States
##############################################################################

state 0
	$accept : . program $end

	MAIN  shift 1

	program  goto 2


state 1
	program : MAIN . LPAREN RPAREN compound_stmt

	LPAREN  shift 3


state 2
	$accept : program . $end  (0)

	$end  accept


state 3
	program : MAIN LPAREN . RPAREN compound_stmt

	RPAREN  shift 4


state 4
	program : MAIN LPAREN RPAREN . compound_stmt

	LBRACE  shift 5

	compound_stmt  goto 6


state 5
	compound_stmt : LBRACE . local_declarations statement_list RBRACE
	compound_stmt : LBRACE . statement_list RBRACE

	INT  shift 7
	CHAR  shift 8
	IF  shift 9
	WHILE  shift 10
	INPUT  shift 11
	PRINT  shift 12
	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17
	SEMICOLON  shift 18
	LBRACE  shift 5

	compound_stmt  goto 19
	var_declaration  goto 20
	type_specifier  goto 21
	local_declarations  goto 22
	statement_list  goto 23
	statement  goto 24
	expression_stmt  goto 25
	selection_stmt  goto 26
	while_stmt  goto 27
	input_stmt  goto 28
	print_stmt  goto 29
	expression  goto 30
	var  goto 31
	or_expression  goto 32
	and_expression  goto 33
	additive_expression  goto 34
	rel_expression  goto 35
	term  goto 36
	factor  goto 37


state 6
	program : MAIN LPAREN RPAREN compound_stmt .  (1)

	.  reduce 1


state 7
	type_specifier : INT .  (5)

	.  reduce 5


state 8
	type_specifier : CHAR .  (6)

	.  reduce 6


state 9
	selection_stmt : IF . LPAREN expression RPAREN statement ELSE statement
	selection_stmt : IF . LPAREN expression RPAREN statement

	LPAREN  shift 38


state 10
	while_stmt : WHILE . LPAREN expression RPAREN statement

	LPAREN  shift 39


state 11
	input_stmt : INPUT . LPAREN var RPAREN

	LPAREN  shift 40


state 12
	print_stmt : PRINT . LPAREN var RPAREN

	LPAREN  shift 41


state 13
	var : ID .  (29)

	.  reduce 29


state 14
	factor : NUM .  (49)

	.  reduce 49


state 15
	factor : CONSTCHAR .  (50)

	.  reduce 50


state 16
	factor : NOT . factor

	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17

	var  goto 42
	factor  goto 43


state 17
	factor : LPAREN . expression RPAREN

	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17

	expression  goto 44
	var  goto 31
	or_expression  goto 32
	and_expression  goto 33
	additive_expression  goto 34
	rel_expression  goto 35
	term  goto 36
	factor  goto 37


state 18
	expression_stmt : SEMICOLON .  (21)

	.  reduce 21


state 19
	statement : compound_stmt .  (15)

	.  reduce 15


state 20
	local_declarations : var_declaration .  (11)

	.  reduce 11


state 21
	var_declaration : type_specifier . idlist SEMICOLON

	ID  shift 45

	idlist  goto 46
	id  goto 47


state 22
	compound_stmt : LBRACE local_declarations . statement_list RBRACE
	local_declarations : local_declarations . var_declaration

	INT  shift 7
	CHAR  shift 8
	IF  shift 9
	WHILE  shift 10
	INPUT  shift 11
	PRINT  shift 12
	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17
	SEMICOLON  shift 18
	LBRACE  shift 5

	compound_stmt  goto 19
	var_declaration  goto 48
	type_specifier  goto 21
	statement_list  goto 49
	statement  goto 24
	expression_stmt  goto 25
	selection_stmt  goto 26
	while_stmt  goto 27
	input_stmt  goto 28
	print_stmt  goto 29
	expression  goto 30
	var  goto 31
	or_expression  goto 32
	and_expression  goto 33
	additive_expression  goto 34
	rel_expression  goto 35
	term  goto 36
	factor  goto 37


state 23
	compound_stmt : LBRACE statement_list . RBRACE
	statement_list : statement_list . statement

	IF  shift 9
	WHILE  shift 10
	INPUT  shift 11
	PRINT  shift 12
	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17
	SEMICOLON  shift 18
	LBRACE  shift 5
	RBRACE  shift 50

	compound_stmt  goto 19
	statement  goto 51
	expression_stmt  goto 25
	selection_stmt  goto 26
	while_stmt  goto 27
	input_stmt  goto 28
	print_stmt  goto 29
	expression  goto 30
	var  goto 31
	or_expression  goto 32
	and_expression  goto 33
	additive_expression  goto 34
	rel_expression  goto 35
	term  goto 36
	factor  goto 37


state 24
	statement_list : statement .  (13)

	.  reduce 13


state 25
	statement : expression_stmt .  (14)

	.  reduce 14


state 26
	statement : selection_stmt .  (16)

	.  reduce 16


state 27
	statement : while_stmt .  (17)

	.  reduce 17


state 28
	statement : input_stmt .  (18)

	.  reduce 18


state 29
	statement : print_stmt .  (19)

	.  reduce 19


state 30
	expression_stmt : expression . SEMICOLON

	SEMICOLON  shift 52


state 31
	expression : var . ASSIGN expression
	factor : var .  (48)

	ASSIGN  shift 53
	.  reduce 48


state 32
	expression : or_expression .  (28)
	or_expression : or_expression . OR and_expression

	OR  shift 54
	.  reduce 28


state 33
	or_expression : and_expression .  (31)
	and_expression : and_expression . AND additive_expression

	AND  shift 55
	.  reduce 31


state 34
	and_expression : additive_expression .  (33)
	additive_expression : additive_expression . EQ rel_expression
	additive_expression : additive_expression . LT rel_expression
	additive_expression : additive_expression . GT rel_expression
	additive_expression : additive_expression . LE rel_expression
	additive_expression : additive_expression . GE rel_expression
	additive_expression : additive_expression . NE rel_expression

	EQ  shift 56
	LT  shift 57
	LE  shift 58
	GT  shift 59
	GE  shift 60
	NE  shift 61
	.  reduce 33


state 35
	additive_expression : rel_expression .  (40)
	rel_expression : rel_expression . PLUS term
	rel_expression : rel_expression . MINUS term

	PLUS  shift 62
	MINUS  shift 63
	.  reduce 40


state 36
	rel_expression : term .  (43)
	term : term . TIMES factor
	term : term . OVER factor

	TIMES  shift 64
	OVER  shift 65
	.  reduce 43


state 37
	term : factor .  (46)

	.  reduce 46


state 38
	selection_stmt : IF LPAREN . expression RPAREN statement ELSE statement
	selection_stmt : IF LPAREN . expression RPAREN statement

	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17

	expression  goto 66
	var  goto 31
	or_expression  goto 32
	and_expression  goto 33
	additive_expression  goto 34
	rel_expression  goto 35
	term  goto 36
	factor  goto 37


state 39
	while_stmt : WHILE LPAREN . expression RPAREN statement

	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17

	expression  goto 67
	var  goto 31
	or_expression  goto 32
	and_expression  goto 33
	additive_expression  goto 34
	rel_expression  goto 35
	term  goto 36
	factor  goto 37


state 40
	input_stmt : INPUT LPAREN . var RPAREN

	ID  shift 13

	var  goto 68


state 41
	print_stmt : PRINT LPAREN . var RPAREN

	ID  shift 13

	var  goto 69


state 42
	factor : var .  (48)

	.  reduce 48


state 43
	factor : NOT factor .  (51)

	.  reduce 51


state 44
	factor : LPAREN expression . RPAREN

	RPAREN  shift 70


state 45
	id : ID .  (7)

	.  reduce 7


state 46
	var_declaration : type_specifier idlist . SEMICOLON
	idlist : idlist . COMMA id

	SEMICOLON  shift 71
	COMMA  shift 72


state 47
	idlist : id .  (4)

	.  reduce 4


state 48
	local_declarations : local_declarations var_declaration .  (10)

	.  reduce 10


state 49
	compound_stmt : LBRACE local_declarations statement_list . RBRACE
	statement_list : statement_list . statement

	IF  shift 9
	WHILE  shift 10
	INPUT  shift 11
	PRINT  shift 12
	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17
	SEMICOLON  shift 18
	LBRACE  shift 5
	RBRACE  shift 73

	compound_stmt  goto 19
	statement  goto 51
	expression_stmt  goto 25
	selection_stmt  goto 26
	while_stmt  goto 27
	input_stmt  goto 28
	print_stmt  goto 29
	expression  goto 30
	var  goto 31
	or_expression  goto 32
	and_expression  goto 33
	additive_expression  goto 34
	rel_expression  goto 35
	term  goto 36
	factor  goto 37


state 50
	compound_stmt : LBRACE statement_list RBRACE .  (9)

	.  reduce 9


state 51
	statement_list : statement_list statement .  (12)

	.  reduce 12


state 52
	expression_stmt : expression SEMICOLON .  (20)

	.  reduce 20


state 53
	expression : var ASSIGN . expression

	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17

	expression  goto 74
	var  goto 31
	or_expression  goto 32
	and_expression  goto 33
	additive_expression  goto 34
	rel_expression  goto 35
	term  goto 36
	factor  goto 37


state 54
	or_expression : or_expression OR . and_expression

	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17

	var  goto 42
	and_expression  goto 75
	additive_expression  goto 34
	rel_expression  goto 35
	term  goto 36
	factor  goto 37


state 55
	and_expression : and_expression AND . additive_expression

	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17

	var  goto 42
	additive_expression  goto 76
	rel_expression  goto 35
	term  goto 36
	factor  goto 37


state 56
	additive_expression : additive_expression EQ . rel_expression

	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17

	var  goto 42
	rel_expression  goto 77
	term  goto 36
	factor  goto 37


state 57
	additive_expression : additive_expression LT . rel_expression

	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17

	var  goto 42
	rel_expression  goto 78
	term  goto 36
	factor  goto 37


state 58
	additive_expression : additive_expression LE . rel_expression

	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17

	var  goto 42
	rel_expression  goto 79
	term  goto 36
	factor  goto 37


state 59
	additive_expression : additive_expression GT . rel_expression

	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17

	var  goto 42
	rel_expression  goto 80
	term  goto 36
	factor  goto 37


state 60
	additive_expression : additive_expression GE . rel_expression

	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17

	var  goto 42
	rel_expression  goto 81
	term  goto 36
	factor  goto 37


state 61
	additive_expression : additive_expression NE . rel_expression

	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17

	var  goto 42
	rel_expression  goto 82
	term  goto 36
	factor  goto 37


state 62
	rel_expression : rel_expression PLUS . term

	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17

	var  goto 42
	term  goto 83
	factor  goto 37


state 63
	rel_expression : rel_expression MINUS . term

	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17

	var  goto 42
	term  goto 84
	factor  goto 37


state 64
	term : term TIMES . factor

	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17

	var  goto 42
	factor  goto 85


state 65
	term : term OVER . factor

	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17

	var  goto 42
	factor  goto 86


state 66
	selection_stmt : IF LPAREN expression . RPAREN statement ELSE statement
	selection_stmt : IF LPAREN expression . RPAREN statement

	RPAREN  shift 87


state 67
	while_stmt : WHILE LPAREN expression . RPAREN statement

	RPAREN  shift 88


state 68
	input_stmt : INPUT LPAREN var . RPAREN

	RPAREN  shift 89


state 69
	print_stmt : PRINT LPAREN var . RPAREN

	RPAREN  shift 90


state 70
	factor : LPAREN expression RPAREN .  (47)

	.  reduce 47


state 71
	var_declaration : type_specifier idlist SEMICOLON .  (2)

	.  reduce 2


state 72
	idlist : idlist COMMA . id

	ID  shift 45

	id  goto 91


state 73
	compound_stmt : LBRACE local_declarations statement_list RBRACE .  (8)

	.  reduce 8


state 74
	expression : var ASSIGN expression .  (27)

	.  reduce 27


state 75
	or_expression : or_expression OR and_expression .  (30)
	and_expression : and_expression . AND additive_expression

	AND  shift 55
	.  reduce 30


state 76
	and_expression : and_expression AND additive_expression .  (32)
	additive_expression : additive_expression . EQ rel_expression
	additive_expression : additive_expression . LT rel_expression
	additive_expression : additive_expression . GT rel_expression
	additive_expression : additive_expression . LE rel_expression
	additive_expression : additive_expression . GE rel_expression
	additive_expression : additive_expression . NE rel_expression

	EQ  shift 56
	LT  shift 57
	LE  shift 58
	GT  shift 59
	GE  shift 60
	NE  shift 61
	.  reduce 32


state 77
	additive_expression : additive_expression EQ rel_expression .  (34)
	rel_expression : rel_expression . PLUS term
	rel_expression : rel_expression . MINUS term

	PLUS  shift 62
	MINUS  shift 63
	.  reduce 34


state 78
	additive_expression : additive_expression LT rel_expression .  (35)
	rel_expression : rel_expression . PLUS term
	rel_expression : rel_expression . MINUS term

	PLUS  shift 62
	MINUS  shift 63
	.  reduce 35


state 79
	additive_expression : additive_expression LE rel_expression .  (37)
	rel_expression : rel_expression . PLUS term
	rel_expression : rel_expression . MINUS term

	PLUS  shift 62
	MINUS  shift 63
	.  reduce 37


state 80
	additive_expression : additive_expression GT rel_expression .  (36)
	rel_expression : rel_expression . PLUS term
	rel_expression : rel_expression . MINUS term

	PLUS  shift 62
	MINUS  shift 63
	.  reduce 36


state 81
	additive_expression : additive_expression GE rel_expression .  (38)
	rel_expression : rel_expression . PLUS term
	rel_expression : rel_expression . MINUS term

	PLUS  shift 62
	MINUS  shift 63
	.  reduce 38


state 82
	additive_expression : additive_expression NE rel_expression .  (39)
	rel_expression : rel_expression . PLUS term
	rel_expression : rel_expression . MINUS term

	PLUS  shift 62
	MINUS  shift 63
	.  reduce 39


state 83
	rel_expression : rel_expression PLUS term .  (41)
	term : term . TIMES factor
	term : term . OVER factor

	TIMES  shift 64
	OVER  shift 65
	.  reduce 41


state 84
	rel_expression : rel_expression MINUS term .  (42)
	term : term . TIMES factor
	term : term . OVER factor

	TIMES  shift 64
	OVER  shift 65
	.  reduce 42


state 85
	term : term TIMES factor .  (44)

	.  reduce 44


state 86
	term : term OVER factor .  (45)

	.  reduce 45


state 87
	selection_stmt : IF LPAREN expression RPAREN . statement ELSE statement
	selection_stmt : IF LPAREN expression RPAREN . statement

	IF  shift 9
	WHILE  shift 10
	INPUT  shift 11
	PRINT  shift 12
	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17
	SEMICOLON  shift 18
	LBRACE  shift 5

	compound_stmt  goto 19
	statement  goto 92
	expression_stmt  goto 25
	selection_stmt  goto 26
	while_stmt  goto 27
	input_stmt  goto 28
	print_stmt  goto 29
	expression  goto 30
	var  goto 31
	or_expression  goto 32
	and_expression  goto 33
	additive_expression  goto 34
	rel_expression  goto 35
	term  goto 36
	factor  goto 37


state 88
	while_stmt : WHILE LPAREN expression RPAREN . statement

	IF  shift 9
	WHILE  shift 10
	INPUT  shift 11
	PRINT  shift 12
	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17
	SEMICOLON  shift 18
	LBRACE  shift 5

	compound_stmt  goto 19
	statement  goto 93
	expression_stmt  goto 25
	selection_stmt  goto 26
	while_stmt  goto 27
	input_stmt  goto 28
	print_stmt  goto 29
	expression  goto 30
	var  goto 31
	or_expression  goto 32
	and_expression  goto 33
	additive_expression  goto 34
	rel_expression  goto 35
	term  goto 36
	factor  goto 37


state 89
	input_stmt : INPUT LPAREN var RPAREN .  (25)

	.  reduce 25


state 90
	print_stmt : PRINT LPAREN var RPAREN .  (26)

	.  reduce 26


state 91
	idlist : idlist COMMA id .  (3)

	.  reduce 3


92: shift-reduce conflict (shift 94, reduce 23) on ELSE
state 92
	selection_stmt : IF LPAREN expression RPAREN statement . ELSE statement
	selection_stmt : IF LPAREN expression RPAREN statement .  (23)

	ELSE  shift 94
	.  reduce 23


state 93
	while_stmt : WHILE LPAREN expression RPAREN statement .  (24)

	.  reduce 24


state 94
	selection_stmt : IF LPAREN expression RPAREN statement ELSE . statement

	IF  shift 9
	WHILE  shift 10
	INPUT  shift 11
	PRINT  shift 12
	ID  shift 13
	NUM  shift 14
	CONSTCHAR  shift 15
	NOT  shift 16
	LPAREN  shift 17
	SEMICOLON  shift 18
	LBRACE  shift 5

	compound_stmt  goto 19
	statement  goto 95
	expression_stmt  goto 25
	selection_stmt  goto 26
	while_stmt  goto 27
	input_stmt  goto 28
	print_stmt  goto 29
	expression  goto 30
	var  goto 31
	or_expression  goto 32
	and_expression  goto 33
	additive_expression  goto 34
	rel_expression  goto 35
	term  goto 36
	factor  goto 37


state 95
	selection_stmt : IF LPAREN expression RPAREN statement ELSE statement .  (22)

	.  reduce 22


##############################################################################
# Summary
##############################################################################

State 92 contains 1 shift-reduce conflict(s)


33 token(s), 23 nonterminal(s)
52 grammar rule(s), 96 state(s)


##############################################################################
# End of File
##############################################################################
