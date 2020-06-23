// by4View.cpp : implementation of the CBy4View class
//

#include "stdafx.h"
#include "by4.h"

#include "by4Doc.h"
#include "by4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBy4View

IMPLEMENT_DYNCREATE(CBy4View, CView)

BEGIN_MESSAGE_MAP(CBy4View, CView)
	//{{AFX_MSG_MAP(CBy4View)
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBy4View construction/destruction

CBy4View::CBy4View()
{
	// TODO: add construction code here

}

CBy4View::~CBy4View()
{
}

BOOL CBy4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBy4View drawing

void CBy4View::OnDraw(CDC* pDC)
{
	CBy4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//¸Ä±ä±³¾°ÑÕÉ«
	CRect rect;          
	GetClientRect(rect);
    pDC->FillSolidRect(rect,RGB(128,128,128));
}

/////////////////////////////////////////////////////////////////////////////
// CBy4View printing

BOOL CBy4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBy4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBy4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBy4View diagnostics

#ifdef _DEBUG
void CBy4View::AssertValid() const
{
	CView::AssertValid();
}

void CBy4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBy4Doc* CBy4View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBy4Doc)));
	return (CBy4Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBy4View message handlers

void CBy4View::OnMove(int x, int y) 
{
	CView::OnMove(x, y); 
	// TODO: Add your message handler code here
	
}
