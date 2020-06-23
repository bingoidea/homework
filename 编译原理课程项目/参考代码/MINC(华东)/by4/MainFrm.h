// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#include "MyWork.h"
#include<windows.h>
#include<winbase.h>
#if !defined(AFX_MAINFRM_H__4F08BF0A_AD58_4642_85EA_55E770927EC1__INCLUDED_)
#define AFX_MAINFRM_H__4F08BF0A_AD58_4642_85EA_55E770927EC1__INCLUDED_

#include "MyEDIT.h"	// Added by ClassView
#include <string>
using namespace std;
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void GetLan();                   //语法分析函数
	CString returncode(CString str); //辨识关键字函数
	void GetWord();                  //分词函数
	MyEDIT m_editor;                 //编辑窗口对应的非模态窗口
	MyEDIT m_wordA;                  //显示分词结果的非模态窗口
	MyEDIT m_Lan;                    //分析语法功能的非模态窗口
	MyEDIT m_HB;                     //显示生成的汇编代码窗口
	MyWork m_work;                   //符号表窗口
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileNew();
	afx_msg void Onword();
	afx_msg void OnLan();
	afx_msg void OnHB();
	afx_msg void OnTest();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveAs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__4F08BF0A_AD58_4642_85EA_55E770927EC1__INCLUDED_)
