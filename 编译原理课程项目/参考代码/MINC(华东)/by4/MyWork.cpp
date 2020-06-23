// MyWork.cpp : implementation file
//

#include "stdafx.h"
#include "by4.h"
#include "MyWork.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyWork dialog


MyWork::MyWork(CWnd* pParent /*=NULL*/)
	: CDialog(MyWork::IDD, pParent)
{
	//{{AFX_DATA_INIT(MyWork)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MyWork::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MyWork)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MyWork, CDialog)
	//{{AFX_MSG_MAP(MyWork)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyWork message handlers

BOOL MyWork::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetClientRect(&m_rect);

	HICON m_hIcon;
    m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);//修改对话框的图标
    SetIcon(m_hIcon,TRUE);

	// TODO: Add extra initialization here
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	m_list.SetEditColomn (0,TRUE);//允许第0列可直接编辑
	m_list.SetEditColomn (1,TRUE); //允许第1列可直接编辑
	m_list.SetEditColomn (2,TRUE); //允许第2列可直接编辑
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	
}

void MyWork::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CWnd *pWnd;
    pWnd = GetDlgItem(IDC_LIST);     //获取控件句柄
    if(nType==1) return;             //如果是窗体最小化则什么都不做
    if(pWnd)                         //判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建
    {
      CRect rect;                    //获取控件变化前大小
      pWnd->GetWindowRect(&rect);
      ScreenToClient(&rect);         //将控件大小转换为在对话框中的区域坐标
      //　cx/m_rect.Width()为对话框在横向的变化比例
      rect.left=rect.left*cx/m_rect.Width();/////调整控件大小
      rect.right=rect.right*cx/m_rect.Width();
      rect.top=rect.top*cy/m_rect.Height();
      rect.bottom=rect.bottom*cy/m_rect.Height();
      pWnd->MoveWindow(rect);        //设置控件大小
    }
    GetClientRect(&m_rect);          //将变化后的对话框大小设为旧大小
	// TODO: Add your message handler code here
	
}



HBRUSH MyWork::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void MyWork::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	// TODO: Add your message handler code here
	
}

void MyWork::move(int x, int y)
{
    CDialog::OnMove(x, y);
}
