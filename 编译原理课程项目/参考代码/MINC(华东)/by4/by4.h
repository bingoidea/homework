// by4.h : main header file for the BY4 application
//

#if !defined(AFX_BY4_H__172636A1_211F_4012_AF00_27098B47D339__INCLUDED_)
#define AFX_BY4_H__172636A1_211F_4012_AF00_27098B47D339__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBy4App:
// See by4.cpp for the implementation of this class
//

class CBy4App : public CWinApp
{
public:
	CBy4App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBy4App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBy4App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BY4_H__172636A1_211F_4012_AF00_27098B47D339__INCLUDED_)
