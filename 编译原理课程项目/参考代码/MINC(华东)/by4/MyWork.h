#if !defined(AFX_MYWORK_H__483B58B7_D6BF_4240_A038_2D7969383033__INCLUDED_)
#define AFX_MYWORK_H__483B58B7_D6BF_4240_A038_2D7969383033__INCLUDED_
#include "EditListCtrl.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyWork.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyWork dialog

class MyWork : public CDialog
{
// Construction
public:
	void move(int x,int y);
	CRect m_rect;
	int Linem;
	MyWork(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MyWork)
	enum { IDD = IDD_DIALOG_Work };
	CEditListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyWork)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MyWork)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy); //编辑框随对话框做相同大小变化的响应函数
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYWORK_H__483B58B7_D6BF_4240_A038_2D7969383033__INCLUDED_)
