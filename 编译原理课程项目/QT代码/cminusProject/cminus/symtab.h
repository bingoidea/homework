#ifndef _SYMTAB_H_
#define _SYMTAB_H_


#include "globals.h"
/*
#include <iostream>
#include <vector>
using namespace std;*/

/* 生成符号表 */
void createSYMTAB(TreeNode* tree);

/* 打印符号表 */
void printSYMTAB(void);

/* 检查 */
void checkNode(TreeNode* tree);

#endif
