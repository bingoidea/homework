// MyEDIT.cpp : implementation file
//

#include "stdafx.h"
#include "by4.h"
#include "MyEDIT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyEDIT dialog


MyEDIT::MyEDIT(CWnd* pParent /*=NULL*/)
	: CDialog(MyEDIT::IDD, pParent)
{
	//{{AFX_DATA_INIT(MyEDIT)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MyEDIT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MyEDIT)
	DDX_Control(pDX, IDC_EDIT, m_CEDIT);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MyEDIT, CDialog)
	//{{AFX_MSG_MAP(MyEDIT)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyEDIT message handlers

CString MyEDIT::resdline(int line)
{
  CString str;
  int    linenumber=0;
  int    x=0;
  for(int i=0;i<text.GetLength();i++)//根据\n的个数确定符号表的行数
	  if(text[i]=='\n')
	  linenumber+=1;
	  else continue;
  Linem=linenumber;
  for(int j=0;j<text.GetLength();j++)
	  if(x=line-1)
		  str+=text[j];
	  else continue;
  return str;
}

BOOL MyEDIT::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	HICON m_hIcon;
    m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);//修改对话框的图标
    SetIcon(m_hIcon,TRUE);

    GetClientRect(&m_rect);//获取对话框创建时的大小
	SetIcon(m_hIcon, TRUE);    // Set big icon
	SetIcon(m_hIcon, FALSE);   // Set small icon
	
	m_brush.CreateSolidBrush(RGB(255,0,0));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MyEDIT::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CWnd *pWnd;
    pWnd = GetDlgItem(IDC_EDIT);     //获取控件句柄
    if(nType==1) return;   //如果是窗体最小化则什么都不做
    if(pWnd)//判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建
    {
      CRect rect;   //获取控件变化前大小
      pWnd->GetWindowRect(&rect);
      ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标
      //　cx/m_rect.Width()为对话框在横向的变化比例
      rect.left=rect.left*cx/m_rect.Width();/////调整控件大小
      rect.right=rect.right*cx/m_rect.Width();
      rect.top=rect.top*cy/m_rect.Height();
      rect.bottom=rect.bottom*cy/m_rect.Height();
      pWnd->MoveWindow(rect);//设置控件大小
    }
    GetClientRect(&m_rect);//将变化后的对话框大小设为旧大小

	// TODO: Add your message handler code here
	
}






HBRUSH MyEDIT::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	//改变编辑框的属性
	if(nCtlColor==CTLCOLOR_EDIT &&
		pWnd->GetDlgCtrlID()==IDC_EDIT)//注意此处的（pWnd->），否则没效果
	{
		pDC->SetTextColor(RGB(0,255,0));
		pDC->SetBkColor(RGB(0,0,0));//设置文本背景色
		//pDC->SetBkMode(RGB(0,0,0));//设置背景透明
		hbr = (HBRUSH)m_brush;
	} 
	// TODO: Return a different brush if the default is not desired
	/*
	CTLCOLOR_BTN Button control
	CTLCOLOR_DLG Dialog box
	CTLCOLOR_EDIT Edit control
	CTLCOLOR_LISTBOX List-box control
	CTLCOLOR_MSGBOX Message box
	CTLCOLOR_SCROLLBAR Scroll-bar control
    CTLCOLOR_STATIC Static control
	*/
	return hbr;
}

void MyEDIT::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(MessageBox("                是否保存修改   ",NULL,MB_YESNO)==IDYES)
	{
		CFileDialog FileDlg(false,_T("txt"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,
			_T("文本文件(*.txt)*.txt||网页(*.html)*.html||"),NULL);
		if(FileDlg.DoModal()==IDOK)
		{
			CString strFile=FileDlg.GetPathName();
			CStdioFile file;
			
			if(true==file.Open(strFile,CFile::modeCreate|CFile::modeWrite|CFile::typeText))
			{
				CString str;
				m_CEDIT.GetWindowText(str);				
				file.WriteString((LPCTSTR)str);//把编辑框的东西写入文件
				file.Close();
			}
         }  	
	}

	CDialog::OnClose();
}
