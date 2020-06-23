// Keyword.h: interface for the CKeyword class.
//
//////////////////////////////////////////////////////////////////////
#include<string>
using namespace std;
#if !defined(AFX_KEYWORD_H__58A99464_293E_4510_8A5B_59B6068A7CB5__INCLUDED_)
#define AFX_KEYWORD_H__58A99464_293E_4510_8A5B_59B6068A7CB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//结点类，把每一个关键词存放在这个类的对象里
class CKeyword  
{
public:
	CString  word;     //关键词
	CString  line;     //这个词在编辑框中的行数
	bool     Int;      //布尔型
	bool     Char;     //字符类型
	bool     Add;      //+
	bool     Equle;    //=（赋值）
	bool     Semic;    //;
	bool     Void;     //空
	bool     par_L;    //(
	bool     par_R;    //)
	bool     pab_L;    //{
	bool     pab_R;    //}
	CKeyword *before;  //双向链表的前结点
	CKeyword *next;    //双向链表的后结点
public:
	CKeyword();
	virtual ~CKeyword();

};

#endif // !defined(AFX_KEYWORD_H__58A99464_293E_4510_8A5B_59B6068A7CB5__INCLUDED_)
