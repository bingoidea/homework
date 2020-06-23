// by4View.h : interface of the CBy4View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BY4VIEW_H__0B43CA5E_F179_4CDC_B9E7_02CAB8056E1E__INCLUDED_)
#define AFX_BY4VIEW_H__0B43CA5E_F179_4CDC_B9E7_02CAB8056E1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBy4View : public CView
{
protected: // create from serialization only
	CBy4View();
	DECLARE_DYNCREATE(CBy4View)

// Attributes
public:
	CBy4Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBy4View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBy4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBy4View)
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in by4View.cpp
inline CBy4Doc* CBy4View::GetDocument()
   { return (CBy4Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BY4VIEW_H__0B43CA5E_F179_4CDC_B9E7_02CAB8056E1E__INCLUDED_)
