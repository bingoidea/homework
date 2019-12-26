/****************************************************/
/* File: scan.h                                     */
/* The scanner interface for the TINY compiler      */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef SCAN_H_INCLUDED
#define SCAN_H_INCLUDED

/* MAXTOKENLEN is the maximum size of a token */
#define MAXTOKENLEN 40

/* tokenString array stores the lexeme of each token */
extern char tokenString[MAXTOKENLEN+1];
// 把scan.c中的变量移进来
extern int linepos; /* current position in LineBuf */
extern int bufsize; /* current size of buffer string */
extern int EOF_flag; /* corrects ungetNextChar behavior on EOF */

/* function getToken returns the
 * next token in source file
 */
TokenType getToken(void);

#endif // SCAN_H_INCLUDED
