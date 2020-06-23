// by4Doc.cpp : implementation of the CBy4Doc class
//

#include "stdafx.h"
#include "by4.h"

#include "by4Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBy4Doc

IMPLEMENT_DYNCREATE(CBy4Doc, CDocument)

BEGIN_MESSAGE_MAP(CBy4Doc, CDocument)
	//{{AFX_MSG_MAP(CBy4Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBy4Doc construction/destruction

CBy4Doc::CBy4Doc()
{
	// TODO: add one-time construction code here

}

CBy4Doc::~CBy4Doc()
{
}

BOOL CBy4Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBy4Doc serialization

void CBy4Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBy4Doc diagnostics

#ifdef _DEBUG
void CBy4Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBy4Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBy4Doc commands
