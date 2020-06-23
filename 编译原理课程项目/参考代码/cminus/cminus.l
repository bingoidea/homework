%{ 
#include "globals.h" 
#include "util.h"
#include "scan.h " 
#define MAXTOKENLEN 40 
char tokenString[40];
int lineno = 0; 
%}
digit   [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+ 
%% /*以下为关键字定义:*/ 
"if"       {return IF;} 
"else"     {return ELSE;} 
"int"      {return INT;} 
"void"     {return VOID;} 
"return"   {return RETURN;} 
"while"    {return WHILE;}
/*以下为运算符号定义:*/ 
"="         {return ASSIGN;} 
"<="         {return LTEQ;} 
">="         {return GTEQ;} 
"<"          {return LT;} 
">"          {return GT;} 
"=="         {return EQ;} 
"!="         {return NOTEQ;} 
"+"          {return PLUS;} 
"-"          {return MINUS;} 
"*"          {return TIMES;} 
"/"          {return OVER;}
"("             {return LPAREN;} 
")"             {return RPAREN;} 
"["             {return LBRACK;} 
"]"             {return RBRACK;} 
"{"             {return LCURL;} 
"}"             {return RCURL;} 
";"             {return SEMI;} 
","             {return COMMA;}
/*终结符及注释符号*/ 
{number}        {return NUM;} 
{identifier}    {return ID;} 
{newline}       {lineno++;} 
{whitespace}    {/* skip whitespace */} 
"/*"      { char c;char d; c = input();if (c != EOF)do            {                 d = c;  c = input(); if (c == EOF)break;if (c == '\n') lineno++;} while (!(d == '*' && c=='/'));  } } 
.               {return ERROR;} 
%%定义getToken()函数体:
TokenType getToken(void) { static int firstTime = TRUE;   
TokenType currentToken;   
if (firstTime)   { firstTime = FALSE;     lineno++;     yyin = source;     yyout = listing;   }   currentToken = yylex();   strncpy(tokenString,yytext,MAXTOKENLEN);   if (TraceScan) {     fprintf(listing,"\t%d: ",lineno);     printToken(currentToken,tokenString);   }   return currentToken; }
