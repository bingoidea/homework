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
  for(int i=0;i<text.GetLength();i++)//����\n�ĸ���ȷ�����ű������
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
    m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);//�޸ĶԻ����ͼ��
    SetIcon(m_hIcon,TRUE);

    GetClientRect(&m_rect);//��ȡ�Ի��򴴽�ʱ�Ĵ�С
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
    pWnd = GetDlgItem(IDC_EDIT);     //��ȡ�ؼ����
    if(nType==1) return;   //����Ǵ�����С����ʲô������
    if(pWnd)//�ж��Ƿ�Ϊ�գ���Ϊ�Ի��򴴽�ʱ����ô˺���������ʱ�ؼ���δ����
    {
      CRect rect;   //��ȡ�ؼ��仯ǰ��С
      pWnd->GetWindowRect(&rect);
      ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������
      //��cx/m_rect.Width()Ϊ�Ի����ں���ı仯����
      rect.left=rect.left*cx/m_rect.Width();/////�����ؼ���С
      rect.right=rect.right*cx/m_rect.Width();
      rect.top=rect.top*cy/m_rect.Height();
      rect.bottom=rect.bottom*cy/m_rect.Height();
      pWnd->MoveWindow(rect);//���ÿؼ���С
    }
    GetClientRect(&m_rect);//���仯��ĶԻ����С��Ϊ�ɴ�С

	// TODO: Add your message handler code here
	
}






HBRUSH MyEDIT::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	//�ı�༭�������
	if(nCtlColor==CTLCOLOR_EDIT &&
		pWnd->GetDlgCtrlID()==IDC_EDIT)//ע��˴��ģ�pWnd->��������ûЧ��
	{
		pDC->SetTextColor(RGB(0,255,0));
		pDC->SetBkColor(RGB(0,0,0));//�����ı�����ɫ
		//pDC->SetBkMode(RGB(0,0,0));//���ñ���͸��
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
	if(MessageBox("                �Ƿ񱣴��޸�   ",NULL,MB_YESNO)==IDYES)
	{
		CFileDialog FileDlg(false,_T("txt"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,
			_T("�ı��ļ�(*.txt)*.txt||��ҳ(*.html)*.html||"),NULL);
		if(FileDlg.DoModal()==IDOK)
		{
			CString strFile=FileDlg.GetPathName();
			CStdioFile file;
			
			if(true==file.Open(strFile,CFile::modeCreate|CFile::modeWrite|CFile::typeText))
			{
				CString str;
				m_CEDIT.GetWindowText(str);				
				file.WriteString((LPCTSTR)str);//�ѱ༭��Ķ���д���ļ�
				file.Close();
			}
         }  	
	}

	CDialog::OnClose();
}
