; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "by4.h"
LastPage=0

ClassCount=8
Class1=CBy4App
Class2=CBy4Doc
Class3=CBy4View
Class4=CMainFrame

ResourceCount=5
Resource1=IDR_MENU_WORK
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Class6=MyEDIT
Resource3=IDD_DIALOG_DEIT
Class7=CEditListCtrl
Resource4=IDR_MAINFRAME
Class8=MyWork
Resource5=IDD_DIALOG_Work

[CLS:CBy4App]
Type=0
HeaderFile=by4.h
ImplementationFile=by4.cpp
Filter=N

[CLS:CBy4Doc]
Type=0
HeaderFile=by4Doc.h
ImplementationFile=by4Doc.cpp
Filter=N

[CLS:CBy4View]
Type=0
HeaderFile=by4View.h
ImplementationFile=by4View.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_FILE_SAVE_AS




[CLS:CAboutDlg]
Type=0
HeaderFile=by4.cpp
ImplementationFile=by4.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
Command9=ID_word
Command10=IDD_Lan
Command11=IDD_AL
Command12=ID_TEST
CommandCount=12

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DIALOG_DEIT]
Type=1
Class=MyEDIT
ControlCount=1
Control1=IDC_EDIT,edit,1353715844

[CLS:MyEDIT]
Type=0
HeaderFile=MyEDIT.h
ImplementationFile=MyEDIT.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT
VirtualFilter=dWC

[MNU:IDR_MENU_WORK]
Type=1
Class=?
Command1=ID_FILE_MyNEW
Command2=ID_FILE_MyOPEN
Command3=ID_FILE_MySAVE
Command4=ID_FILE_MyOPEN
Command5=ID_Window_stack
Command6=ID_Window_tile
Command7=ID_MENU_lexical
Command8=ID_MENU_grammer
Command9=ID_MENU_IDlist
Command10=ID_MENU_assembly
CommandCount=10

[CLS:CEditListCtrl]
Type=0
HeaderFile=EditListCtrl.h
ImplementationFile=EditListCtrl.cpp
BaseClass=CListCtrl
Filter=W
VirtualFilter=FWC
LastObject=CEditListCtrl

[DLG:IDD_DIALOG_Work]
Type=1
Class=MyWork
ControlCount=1
Control1=IDC_LIST,SysListView32,1350631937

[CLS:MyWork]
Type=0
HeaderFile=MyWork.h
ImplementationFile=MyWork.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LIST
VirtualFilter=dWC

