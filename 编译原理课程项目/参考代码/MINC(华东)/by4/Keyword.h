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
//����࣬��ÿһ���ؼ��ʴ���������Ķ�����
class CKeyword  
{
public:
	CString  word;     //�ؼ���
	CString  line;     //������ڱ༭���е�����
	bool     Int;      //������
	bool     Char;     //�ַ�����
	bool     Add;      //+
	bool     Equle;    //=����ֵ��
	bool     Semic;    //;
	bool     Void;     //��
	bool     par_L;    //(
	bool     par_R;    //)
	bool     pab_L;    //{
	bool     pab_R;    //}
	CKeyword *before;  //˫�������ǰ���
	CKeyword *next;    //˫������ĺ���
public:
	CKeyword();
	virtual ~CKeyword();

};

#endif // !defined(AFX_KEYWORD_H__58A99464_293E_4510_8A5B_59B6068A7CB5__INCLUDED_)
