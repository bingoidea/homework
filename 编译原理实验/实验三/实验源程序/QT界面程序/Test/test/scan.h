#ifndef SCAN_H
#define SCAN_H

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

#endif // SCAN_H
