/****************************************************/
/* File: analyze.h                                  */
/* Semantic analyzer interface for C-   compiler    */
/* C- Compiler Project				    */
/* ZEBRA 	                                    */
/****************************************************/
#ifndef _ANALYZE_H_
#define _ANALYZE_H_

#include "symtab.h"

extern int scope_a;
/* counter for variable memory locations */
extern int location[MAX_SCOPE];

extern int No_change;

/* Function buildSymtab constructs the symbol
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode *);

/* Procedure typeCheck performs type checking
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode *);

#endif
