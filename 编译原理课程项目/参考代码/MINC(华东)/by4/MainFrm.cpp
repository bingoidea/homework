// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "by4.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_word, Onword)
	ON_COMMAND(IDD_Lan, OnLan)
	ON_COMMAND(IDD_AL, OnHB)
	ON_COMMAND(ID_TEST, OnTest)
	ON_WM_MOVE()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
     
	/////////////////////////////////
	//SetWindowText("");
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    
    cs.style&=~FWS_ADDTOTITLE;//设置更改标题
    
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnFileNew() 
{
	// TODO: Add your command handler code here
	 
    if(!m_editor.m_hWnd)
		m_editor.Create(IDD_DIALOG_DEIT);
	m_editor.SetWindowText("文件编辑");
	m_editor.ShowWindow(SW_SHOW);	
}

void CMainFrame::Onword() 
{
	// TODO: Add your command handler code here
	if(!m_editor.m_hWnd)
		MessageBox("Please create the file first");
	else{
        m_editor.m_CEDIT.GetWindowText(m_editor.text);//先把文本都存下来
		/*
		if(!m_wordA.m_hWnd)
			m_wordA.Create(IDD_DIALOG_DEIT);
		m_wordA.SetWindowText("词法分析");
		m_wordA.ShowWindow(SW_SHOW);
		*/
		if(!m_work.m_hWnd)
			m_work.Create(IDD_DIALOG_Work);
		m_work.SetWindowText("词法分析-符号表");
		CRect  rect;
		GetWindowRect(&rect);
	    m_work.ShowWindow(SW_SHOW);
        m_work.MoveWindow(rect.left+8,rect.bottom-rect.Height()/2-8,rect.Width()-16,rect.Height()/2);
		m_work.m_list.InsertColumn (0,"所在行", LVCFMT_LEFT,rect.Width()/3);
		m_work.m_list.InsertColumn (1,"关键词", LVCFMT_LEFT,rect.Width()/3);
	    m_work.m_list.InsertColumn (2,"属性", LVCFMT_LEFT,rect.Width()/3);
	    GetWord();
	}

}

void CMainFrame::GetWord()//词法分析
{
	CKeyword *temp=new CKeyword;
	CKeyword *remember;
	CKeyword *next;
	remember=temp;
	int nodenumber=1;  //记录结点个数
	int Line=1;        //记录行数
	temp->line.Format("%d",Line);
	for(int i=0;i<m_editor.text.GetLength();i++)
		if(m_editor.text[i]==' '||m_editor.text[i]=='\r'
			||m_editor.text[i]=='\n')
		{
			    if(m_editor.text[i]=='\n')
				Line++;
		        else continue;
		}
		else if(m_editor.text[i]=='('
			||m_editor.text[i]==')'
			||m_editor.text[i]=='{'
			||m_editor.text[i]=='}'
			||m_editor.text[i]=='+'
			||m_editor.text[i]=='='
			||m_editor.text[i]==';')
		{   
			nodenumber++;
			next=new CKeyword;
			temp->next=next;
			temp=temp->next;
			temp->word+=m_editor.text[i];
			temp->line.Format("%d",Line);
		}
		
		else if(m_editor.text[i]!=' '
			&&m_editor.text[i]!='('
			&&m_editor.text[i]!=')'
			&&m_editor.text[i]!='{'
			&&m_editor.text[i]!='}'
			&&m_editor.text[i]!='\r'
			&&m_editor.text[i]!='\n'
			&&m_editor.text[i]!=';'
			&&m_editor.text[i]!='+'
            &&m_editor.text[i]!='='
			&&i==0)
		{
			temp->word+=m_editor.text[i];
			temp->line.Format("%d",Line);
		}
		else if(i>0&&m_editor.text[i-1]==' '//当i=0时，i-1不符合语法，会报错
			||m_editor.text[i-1]=='('
			||m_editor.text[i-1]==')'
			||m_editor.text[i-1]=='{'
			||m_editor.text[i-1]=='}'
			||m_editor.text[i-1]=='\r'
			||m_editor.text[i-1]=='\n'
			||m_editor.text[i-1]==';'
			||m_editor.text[i-1]=='+'
            ||m_editor.text[i-1]=='='
			)
		{
			nodenumber++;
			next=new CKeyword;
			temp->next=next;
			temp=temp->next;
			temp->word+=m_editor.text[i];
			temp->line.Format("%d",Line);
		}
		else if(m_editor.text[i-1]!=' '
			&&m_editor.text[i-1]!='\n'&&m_editor.text[i-1]!=';')
		{
			temp->word+=m_editor.text[i]; 
		}
		else continue;
		
	     /*
		 temp=remember;
		 
		 for(int j=0;j<nodenumber;j++)	
		 {   
			 
			 m_wordA.text+="第"+temp->line+"行"+temp->word+"  OK"+"\r\n";
			 temp=temp->next;
		 }
		 */
		 temp=remember;
		 m_work.Linem=nodenumber;
		 for(int j=0;j<nodenumber;j++)	
		 {   
			 m_work.m_list.InsertItem (j,temp->line);
			 m_work.m_list.SetItemText (j,1,temp->word);
	         m_work.m_list.SetItemText (j,2,returncode(temp->word));
			 temp=temp->next;
		 }
		 //m_wordA.m_CEDIT.SetWindowText(m_wordA.text);
		
}

CString CMainFrame::returncode(CString str)
{   
	CString  tokencode="0";
	if(str=="void")       tokencode="1";
	else if(str=="int")   tokencode="2";
	else if(str=="main")  tokencode="3"; 
	else if(str=="char")  tokencode="4"; 
	else if(str=="+")     tokencode="5";
	else if(str=="=")     tokencode="6";
	else if(str==";")     tokencode="7"; 
	else if(str=="(")     tokencode="8"; 
	else if(str==")")     tokencode="9"; 
	else if(str=="{")     tokencode="10";
    else if(str=="return")tokencode="11";
	else if(str=="}")     tokencode="12";
	else if(str=="while") tokencode="13";
	else if(str=="if")    tokencode="14";
	else if(str=="else")  tokencode="15";
	else if(str=="for")   tokencode="16";
	else tokencode="20";
    return tokencode;
}

void CMainFrame::OnLan() 
{
	 // TODO: Add your command handler code here
	if(!m_work.m_hWnd)
		MessageBox("请先进行词法分析");
	else {
	    if(!m_Lan.m_hWnd)
		m_Lan.Create(IDD_DIALOG_DEIT);
	    m_Lan.SetWindowText("语法分析");
		m_Lan.ShowWindow(SW_SHOW);
		GetLan();
	}

}

void CMainFrame::GetLan()//语法分析
{
   CString  now;
   m_Lan.text="Function declaration:";
   for(int i=0;i<m_work.Linem;i++)
   {
	   now=m_work.m_list.GetItemText(i,2);
	   
	   if(now=="2"&&m_work.m_list.GetItemText(i+1,2)=="3")
	   {   
		   now=m_work.m_list.GetItemText(i,1);
           m_Lan.text+=now+" "; 
	   }
	   if(now=="3")
	   {   
		   now=m_work.m_list.GetItemText(i,1);
           m_Lan.text+=now+" "+"\r\n";
	   }
	   if(now=="5"||now=="6")
	   {   
		   now=m_work.m_list.GetItemText(i,1);
		   m_Lan.text+="OP:";
		   m_Lan.text+="\r\n";        //这样的换行符号只能置于赋值语句的最右端
		   m_Lan.text+="         ";
		   m_Lan.text+=now+"\r\n";
	   }
	   if(now=="20"&&m_work.m_list.GetItemText(i-1,2)!="11"
		   &&m_work.m_list.GetItemText(i-1,2)!="7")
	   {
          now=m_work.m_list.GetItemText(i,1);
		  m_Lan.text+="ID:";
		  m_Lan.text+="\r\n";
		  m_Lan.text+="         ";
		  m_Lan.text+=now+"\r\n";
	   }
	   if(now=="11")
	   {
		   now=m_work.m_list.GetItemText(i,1);
		   m_Lan.text+=now+"\r\n";
		   m_Lan.text+="         ";
           m_Lan.text+=m_work.m_list.GetItemText(i+1,1);
	   }
   }
   m_Lan.m_CEDIT.SetWindowText(m_Lan.text);
   //置编辑框中的光标于文字末尾
   m_Lan.m_CEDIT.SetSel(m_Lan.text.GetLength(),m_Lan.text.GetLength(),FALSE);
}

void CMainFrame::OnHB() 
{
	// TODO: Add your command handler code here
	if(!m_HB.m_hWnd)
		m_HB.Create(IDD_DIALOG_DEIT);
	m_HB.SetWindowText("汇编生成");
	m_HB.ShowWindow(SW_SHOW);
    CFile getstr;
	if(getstr.Open("test.asm",CFile::modeRead,NULL))
	{   //./use\\在打开文件中默认路径已经在use文件下了
		char *pBuf;
		DWORD dwFileLen;
		dwFileLen=getstr.GetLength();
		pBuf=new char[dwFileLen+1];
		pBuf[dwFileLen]=0;
		getstr.Read(pBuf,dwFileLen);
	
		CString putf;
		putf=pBuf;	
		m_HB.m_CEDIT.SetWindowText(putf);
		m_HB.m_CEDIT.SetSel(getstr.GetLength(),getstr.GetLength(),FALSE);
	    getstr.Close();
	}
	else
	{    /*
         getstr.Open("./use\\Hello.asm",CFile::modeRead,NULL);
			 char *pBuf;
		 DWORD dwFileLen;
		 dwFileLen=getstr.GetLength();
		 pBuf=new char[dwFileLen+1];
		 pBuf[dwFileLen]=0;
		 getstr.Read(pBuf,dwFileLen);
		 
		 CString putf;
		 putf=pBuf;	
		 m_HB.m_CEDIT.SetWindowText(putf);
		 m_HB.m_CEDIT.SetSel(getstr.GetLength(),getstr.GetLength(),FALSE);
	    getstr.Close();
		*/
	}
		
}

void CMainFrame::OnTest() 
{
	// TODO: Add your command handler code here
	WinExec("cmd.exe",SW_SHOW);//调用应用程序进行汇编代码的测试
}

void CMainFrame::OnMove(int x, int y) 
{
	CFrameWnd::OnMove(x, y);
	CRect  rect;
	GetWindowRect(&rect);
	if(!m_work.m_hWnd)
    m_work.move(x,y);            
	// TODO: Add your message handler code here
	
}

void CMainFrame::OnFileOpen() 
{
	// TODO: Add your command handler code here
	
	CFileDialog dlg(TRUE,".txt",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"文本文件(*.txt)|*.txt|所有文件 (*.*)|*.*||");		
	if(dlg.DoModal()==IDOK)  
	{
		CString m_FilePath = dlg.GetPathName();////////取出文件路径
		CString  m_path;
		m_path=m_FilePath;//将文件的路径放入m_path
		UpdateData(FALSE);
		if(!m_editor.m_hWnd)
			m_editor.Create(IDD_DIALOG_DEIT);
		m_editor.SetWindowText("文件编辑");	
		m_editor.ShowWindow(SW_SHOW);
		CFile getstr;
		if(getstr.Open(m_path,CFile::modeRead,NULL))
		{
			char *pBuf;
			DWORD dwFileLen;
			dwFileLen=getstr.GetLength();
			pBuf=new char[dwFileLen+1];
			pBuf[dwFileLen]=0;
			getstr.Read(pBuf,dwFileLen);
			
			CString putf;
			putf=pBuf;	
			m_editor.m_CEDIT.SetWindowText(putf);
			m_editor.m_CEDIT.SetSel(getstr.GetLength(),getstr.GetLength(),FALSE); 
			getstr.Close();
			
		}
		else
			MessageBox("faul");
		
    } 
}

void CMainFrame::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	
}
