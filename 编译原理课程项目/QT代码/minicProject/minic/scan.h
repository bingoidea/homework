/****************************************************/
/* File: scan.h                                     */
/* The scanner interface for the TINY compiler      */
/* C-- Compiler Project				    */
/* ZEBRA 	                                    */
/****************************************************/


#ifndef _SCAN_H_
#define _SCAN_H_

/* MAXTOKENLEN is the maximum size of a token */
#define MAXTOKENLEN 40

/* tokenString array stores the lexeme of each token */
extern char tokenString[MAXTOKENLEN+1];

extern int linepos; /* current position in LineBuf */
extern int bufsize; /* current size of buffer string */
extern int EOF_flag; /* corrects ungetNextChar behavior on EOF */

/* function getToken returns the
 * next token in source file
 */
TokenType getToken(void);

#endif
