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
    m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);//�޸ĶԻ����ͼ��
    SetIcon(m_hIcon,TRUE);

	// TODO: Add extra initialization here
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	m_list.SetEditColomn (0,TRUE);//�����0�п�ֱ�ӱ༭
	m_list.SetEditColomn (1,TRUE); //�����1�п�ֱ�ӱ༭
	m_list.SetEditColomn (2,TRUE); //�����2�п�ֱ�ӱ༭
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	
}

void MyWork::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CWnd *pWnd;
    pWnd = GetDlgItem(IDC_LIST);     //��ȡ�ؼ����
    if(nType==1) return;             //����Ǵ�����С����ʲô������
    if(pWnd)                         //�ж��Ƿ�Ϊ�գ���Ϊ�Ի��򴴽�ʱ����ô˺���������ʱ�ؼ���δ����
    {
      CRect rect;                    //��ȡ�ؼ��仯ǰ��С
      pWnd->GetWindowRect(&rect);
      ScreenToClient(&rect);         //���ؼ���Сת��Ϊ�ڶԻ����е���������
      //��cx/m_rect.Width()Ϊ�Ի����ں���ı仯����
      rect.left=rect.left*cx/m_rect.Width();/////�����ؼ���С
      rect.right=rect.right*cx/m_rect.Width();
      rect.top=rect.top*cy/m_rect.Height();
      rect.bottom=rect.bottom*cy/m_rect.Height();
      pWnd->MoveWindow(rect);        //���ÿؼ���С
    }
    GetClientRect(&m_rect);          //���仯��ĶԻ����С��Ϊ�ɴ�С
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
