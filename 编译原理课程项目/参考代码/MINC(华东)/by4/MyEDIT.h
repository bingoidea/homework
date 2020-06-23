#if !defined(AFX_MYEDIT_H__51173ECA_4CFC_4659_A44B_D51EF51B462F__INCLUDED_)
#define AFX_MYEDIT_H__51173ECA_4CFC_4659_A44B_D51EF51B462F__INCLUDED_

#include"resource.h" //在resource.h文件中定义了ID就需要把这个ID让要用它的类知道
#include<string>
using namespace std;
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyEDIT.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyEDIT dialog

class MyEDIT : public CDialog
{
// Construction
public:
	CString  text;  //当前编辑框的内容
    CBrush m_brush; //改变编辑框颜色的画刷
public:
	CRect m_rect;
	int Linem;                      //行数
	CString resdline(int line);      
	MyEDIT(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MyEDIT)
	enum { IDD = IDD_DIALOG_DEIT };
	CEdit	m_CEDIT;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyEDIT)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MyEDIT)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYEDIT_H__51173ECA_4CFC_4659_A44B_D51EF51B462F__INCLUDED_)
