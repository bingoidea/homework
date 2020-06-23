// EditListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "by4.h"
#include "EditListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditListCtrl

CEditListCtrl::CEditListCtrl()
{
	m_edit=NULL;
	m_isedit=NULL;
	m_item=-1;
	m_subitem=-1;
}

CEditListCtrl::~CEditListCtrl()
{
}


BEGIN_MESSAGE_MAP(CEditListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CEditListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_WM_HSCROLL()
	ON_NOTIFY_REFLECT(NM_SETFOCUS, OnSetfocus)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditListCtrl message handlers

void CEditListCtrl::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(!m_isedit) return;
	
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(!m_edit)
	{
		m_subitem=pNMListView->iSubItem;
		if(pNMListView->iItem!=m_item)
		{
			m_item=pNMListView->iItem;//标志被单击的项目
			return;
		}
	}
	if(!m_isedit[m_subitem])//若当前列不允许直接编辑,则返回 
		return;
	RECT m_itemrect,m_r;
	GetItemRect(m_item ,&m_itemrect,2);
	GetItemRect(0 ,&m_r,2);
	int m_height=m_itemrect.bottom -m_itemrect.top ;
	int x=m_r.left ,y=m_r.top,cx,cy;//(x,y,cx,cy)为编辑框显示的位置
	for(int i=0;i< m_item;i++)
		y+=m_height;
	cy=y+m_height;
	for(i=0;i<m_subitem;i++)
		x+=GetColumnWidth(i);
	cx=x+GetColumnWidth(i);
	if(m_edit)//若编辑框已存在。
	{
		CString s1;
		s1.Format ("%d %d %d %d",x,y,cx,cy);
		m_edit->MoveWindow(x,y,cx-x,cy-y);//移动到当前子项目的位置。
		Invalidate();//刷新屏幕。
		return;
	}
	//若编辑框不存在,则创建编辑框,并在当前子项目处显示编辑框。
	CRect rect(x,y,cx,cy);
	m_edit=new CEdit();
	m_edit->Create (WS_CHILD|WS_VISIBLE|WS_BORDER,rect,this,ID_LISTEDIT);
	CString str=GetItemText (pNMListView->iItem,pNMListView->iSubItem);
	m_edit->UpdateData(0);
	m_edit->SetWindowText(str); 
	DWORD  dwSel = m_edit->GetSel();   
	m_edit->SetSel(HIWORD(dwSel), -1);   
	m_edit->ShowWindow (SW_SHOW);//显示编辑框。
	m_edit->SetFocus ();
	*pResult = 0;
}

void CEditListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	//水平滚动时,移动已显示的编辑框。
	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
	LRESULT* pResult=new LRESULT;
	if(m_edit)  
	OnClick((NMHDR*)this,pResult) ;
}

void CEditListCtrl::OnSetfocus(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(m_edit)
	{//将编辑框中的数据写回对应的子项目中
		UpdateData( );
		CString str;
		m_edit->GetWindowText(str);
		SetItemText(m_item,m_subitem,str);
		delete m_edit;
		m_edit=NULL;
	}
	
	*pResult = 0;
}

void CEditListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	//垂直滚动时,移动已显示的编辑框。
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
	LRESULT* pResult=new LRESULT;
	if(m_edit)
	{
		RECT m_itemrect,m_headrect;
		GetItemRect(m_item ,&m_itemrect,2);
		GetHeaderCtrl()->GetWindowRect(&m_headrect);
		if(m_itemrect.top<m_headrect.bottom-m_headrect.top) 
		{
			RECT m_rect;
			m_edit->GetWindowRect(&m_rect);
			m_edit->MoveWindow(m_rect.left,-(m_rect.bottom-m_rect.top),m_rect.right,0);
		}
        else  
		{
			OnClick((NMHDR*)this,pResult) ;
		}
	}
}

BOOL CEditListCtrl::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete [] m_isedit;
	return CListCtrl::DestroyWindow();
}

void CEditListCtrl::SetEditColomn(int col, BOOL edit)
{
	//设置允许直接进行编辑的列
	if(!m_isedit)
	{
		int len=GetHeaderCtrl()->GetItemCount();
		m_isedit=new BOOL[len];
		for(int i=0;i<len;i++)//初始化m_isedit。
			m_isedit[i]=FALSE;
	}
	m_isedit[col]=edit;
}
