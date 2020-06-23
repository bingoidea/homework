// by4Doc.h : interface of the CBy4Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BY4DOC_H__510B53CC_6C70_4EE9_8D9D_C047559047CB__INCLUDED_)
#define AFX_BY4DOC_H__510B53CC_6C70_4EE9_8D9D_C047559047CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBy4Doc : public CDocument
{
protected: // create from serialization only
	CBy4Doc();
	DECLARE_DYNCREATE(CBy4Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBy4Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBy4Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBy4Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BY4DOC_H__510B53CC_6C70_4EE9_8D9D_C047559047CB__INCLUDED_)
