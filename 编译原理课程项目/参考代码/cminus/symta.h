#ifndef _SYMTAB_H_ 
#define _SYMTAB_H_ 
 
void st_insert( char * name, int lineno, int loc );   /*插入函数*/ 
int st_lookup ( char * name );             /*查找函数*/ 
void printSymTab(FILE * listing);               /*用来打印哈稀表内容*/ 
#endif 
