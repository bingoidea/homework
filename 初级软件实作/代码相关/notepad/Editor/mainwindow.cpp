#include "mainwindow.h"
#include "ui_mainwindow.h"

// _MSC_VER 定义编译器的版本
// 在程序中加入_MSC_VER宏可以根据编译器版本让不同版本的编译器选择性地编译一段程序
#ifdef _MSC_VER
#if _MSC_VER >= 1600   // MS VC++10.0 以上
#pragma execution_character_set("utf-8")   // 解决QT中显示中文字乱码
#endif
#endif

// 公有函数
// 构造软件窗口
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 编辑界面
    m_pTabWidget = new QTabWidget(this);      // 分页窗口
    m_pTextEdit = new TextEditor(this);       // 每个分页的编辑器
    m_pTextEdit->setUtf8(true);
    for(int i = 0; i < 10 ;i++)
    {
        // 初始化新文本框数组
        NewTextEdit[i] = nullptr;
    }

    // 分页窗口为中心窗口
    this->setCentralWidget(m_pTabWidget);

    // 设置分页窗口可关闭
    m_pTabWidget->setTabsClosable(true);
    // 把文本编辑区放入分页窗口
    m_pTabWidget->addTab(m_pTextEdit, tr("new"));

    // 获得当前焦点事件的窗口(即多窗口中选中一个来编辑)
    m_pTextEdit->setFocus();
    m_pTextEdit->setAcceptDrops(false);  // 不可拖拽分页窗口
    setAcceptDrops(true);                // 主窗口可以拖拽

    // 用QsciScintilla中的函数来设置行号
    m_pTextEdit->setMarginType(0, QsciScintilla::NumberMargin);   // //设置编号为0的页边显示行号
    m_pTextEdit->setMarginLineNumbers(0, true);   //对该页边启用行号
    m_pTextEdit->setMarginWidth(0, 35);   // 设置页边宽度
    m_pTextEdit->setCaretLineVisible(true);   //显示选中的行号
    m_pTextEdit->setCaretLineBackgroundColor(Qt::lightGray);   //显示选中行号的背景色

    // 创建主界面
    createAction();
    createMenus();
    createContextMenus();
    createToorBar();
    createStatusBar();

    // 设置应用程序图标
    setWindowIcon(QIcon(":/Myimages/images/fileIcon.png"));
    this->setCurrentFile("");   // 设置初始化的文件标题
    this->resize(1024, 768);    // 改变窗口初始大小
    setUnifiedTitleAndToolBarOnMac(true);   // 在Mac显示statusbar区域

    // 读取配置(打开软件时读取上次保存的配置)
    readSettings();

    // 更新actions();
    updateActions();

    // 链接信号和槽
    connect(m_pTabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(removeSubTab(int)));   // 手动定义一个接受int类型的槽函数，然后把参数再传递给关闭函数removeTab()
    connect(m_pTextEdit, SIGNAL(textChanged()), this, SLOT(textEditorModified()));   //textChanged()信号在编辑框中文本有变化时激发,检测文本变化
    connect(m_pTextEdit, SIGNAL(cursorPositionChanged(int, int)), this, SLOT(showCursorPosition(int, int)));   // 信号会在光标位置变化时激发,检测光标位置并显示
    connect(m_pTextEdit, &TextEditor::overwriteModeChanged, [=](){   // 用TextEditor类的overwriteModeChanged信号检测输入模式是否变化
        if(m_pTextEdit->overwriteMode())
        {
            // overwriteMode()变为可覆盖
            insertModeLabel->setText(("OVR"));
        }
        else
        {
            insertModeLabel->setText("INS");
        }
    });   // lambda表达式，[=]表示值传递方式捕捉所有父作用域的变量
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 加载文件
bool MainWindow::loadFile(const QString &fileName)
{
    QFileInfo fileInfo(fileName);   // 获取文件信息
    // 不打开大于200MB的文件
    if(fileInfo.size() > 200 *1024 *1024)
    {
        QMessageBox::warning(this, tr("File size problem"),
                             tr("<p>The current open file is too large</p>"
                                "<p>Can't not open in QEditor</p>"));
        return false;
    }

    QFile file(fileName);
    // 如果不是只读模式打开
    if(!file.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream in(&file);    // 文件读入流
    QApplication::setOverrideCursor(Qt::WaitCursor);   // 设置应用程序强制光标为Waitcursor

    // 读入显示文件(显示在新的分页)
    int i = 0;
    while(i < 10 && NewTextEdit[i] != nullptr)
    {
        i++;
    }
    if(i >= 10)
    {
        QMessageBox::warning(this, tr("注意!"), tr("不可再增加新的分页"));
        QApplication::restoreOverrideCursor();   // 恢复光标
        return false;
    }
    newFile();   // 新建一个文本框
    NewTextEdit[i]->setText(in.readAll());

    QApplication::restoreOverrideCursor();   // 读完后恢复光标

    // 在窗口标题显示文件路径
    setCurrentFile(fileName, i+1);
    statusBar()->showMessage(tr("File loaded"), 2000);   // 临时信息显示2000ms
    saveAction->setEnabled(false);   // 没有编辑时保存功能设置为false

    return true;
}

// 保护函数(重载基类函数)
// 关闭动作(在用户尝试退出时警告用户关于未保存的修改信息)(在关闭动作发生时调用)
void MainWindow::closeEvent(QCloseEvent *event)
{
    // 可以继续
    if(okToContinue())
    {
        writeSetting();
        event->accept();   // accept()的作用是：将当前的窗口隐藏（这样就做到子窗口功能消失这个功能）
    }
    else
    {
        event->ignore();   // 不关闭
    }
}

// 拖拽处理
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    // 让一个widget接受URL拖拽
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

// 拖拽释放处理
void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.empty())
    {
        return;
    }

    QString filePath = urls.first().toLocalFile();
    if(filePath.isEmpty())
    {
        return;
    }

    if(okToContinue())
    {
        loadFile(filePath);
    }
}

// 私有函数
// 创建若干动作信号
void MainWindow::createAction()
{
    // 工具栏--新建
    newAction = new QAction(tr("新建(&N)"), this);
    newAction->setIcon(QIcon(":/Myimages/images/new.png"));
    newAction->setShortcut(QKeySequence::New);   // 设置快捷键，QKeySequence::New在windows一般默认为ctrl+N，后面类似代码相同
    newAction->setToolTip(tr("新建一个文件"));     // 设置提示框,鼠标放到控件上,浮动出一个小黄框
    newAction->setStatusTip(tr("新建一个文件"));   // 添加状态栏的提示语句,状态栏提示
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);   // triggered表示action被触发，可以是各种形式

    // 工具栏--打开
    openAction = new QAction(tr("打开(&O)"), this);
    openAction->setIcon(QIcon(":/Myimages/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);   // ctrl+O
    openAction->setToolTip(tr("打开一个文件"));
    openAction->setStatusTip(tr("打开一个文件"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    // 工具栏--保存
    saveAction = new QAction(tr("保存(&S)"), this);
    saveAction->setIcon(QIcon(":/Myimages/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);   // ctrl+S
    saveAction->setToolTip("保存文件");
    saveAction->setStatusTip("保存文件");
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);
    saveAction->setEnabled(false);   // 保存后就不能再点击保存键

    // 工具栏--另存为
    saveAsAction = new QAction(tr("另存为(&A)..."), this);
    saveAsAction->setShortcut(tr("Ctrl+Alt+S"));   // QKeySequence中saveAs没有定义快捷键
    saveAsAction->setToolTip(tr("将文件另存为..."));
    saveAsAction->setStatusTip(tr("将文件另存为..."));
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAs);

    // 工具栏--打印
    printAction = new QAction(tr("打印...(&P)"), this);
    printAction->setIcon(QIcon(":/Myimages/images/print.png"));
    printAction->setShortcut(QKeySequence::Print);   // ctrl+P
    printAction->setToolTip(tr("打印文档"));
    printAction->setStatusTip(tr("打印文档"));
    connect(printAction, &QAction::triggered, this, &MainWindow::printFile);

    // 打印预览
    printPreviewAction = new QAction(tr("打印预览..."), this);
    printPreviewAction->setToolTip(tr("打印预览"));
    printPreviewAction->setStatusTip(tr("打印预览"));
    connect(printPreviewAction, &QAction::triggered, this, &MainWindow::printFilePreview);

    // 导出至PDF
    exportToPDFAction = new QAction(tr("导出至PDF..."), this);
    exportToPDFAction->setIcon(QIcon(":/Myimages/images/exportpdf.png"));
    exportToPDFAction->setToolTip(tr("导出至PDF"));
    exportToPDFAction->setStatusTip(tr("导出至PDF"));
    connect(exportToPDFAction, &QAction::triggered, this, &MainWindow::printFilePDF);

    // 文件菜单--最近打开文件(每一个元素都是一个Action)
    for(int i = 0; i < MaxRecentFiles; i++)
    {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);   // setVisible(bool)设置“动作”显示与否
        connect(recentFileActions[i], &QAction::triggered, this, &MainWindow::openRecentFile);   // 点击链接打开文件
    }

    // 工具栏--关闭
    exitAction = new QAction(tr("关闭(&Q)"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));   // ctrl+Q
    exitAction->setToolTip(tr("退出程序"));
    exitAction->setStatusTip(tr("退出程序"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);   // QWidget自带close()

    // 工具栏--撤销
    undoAction = new QAction(tr("撤销(&U)"), this);
    undoAction->setIcon(QIcon(":/Myimages/images/undo.png"));
    undoAction->setShortcut(QKeySequence::Undo);   // Ctrl+Z, Alt+Backspace
    undoAction->setToolTip(tr("撤销"));
    undoAction->setStatusTip(tr("撤销"));
    connect(undoAction, &QAction::triggered, m_pTextEdit, &TextEditor::undo);   // QsciScintilla自带undo，撤销仅对每个分页作用

    // 工具栏--恢复
    redoAction = new QAction(tr("恢复(&R)"), this);
    redoAction->setIcon(QIcon(":/Myimages/images/redo.png"));
    redoAction->setShortcut(QKeySequence::Redo);   // Ctrl+Y, Shift+Ctrl+Z, Alt+Shift+Backspace
    redoAction->setToolTip(tr("恢复"));
    redoAction->setStatusTip(tr("恢复"));
    connect(redoAction, &QAction::triggered, m_pTextEdit, &TextEditor::redo);   // QsciScintilla自带redo，恢复仅对每个分页作用

    // 工具栏--剪切
    cutAction = new QAction(tr("剪切(&T)"), this);
    cutAction->setIcon(QIcon(":/Myimages/images/cut.png"));
    cutAction->setShortcut(QKeySequence::Cut);   // Ctrl+X, Shift+Del
    cutAction->setToolTip(tr("剪切文本"));
    cutAction->setStatusTip(tr("剪切文本"));
    cutAction->setEnabled(false);
    connect(cutAction, &QAction::triggered, m_pTextEdit, &TextEditor::cut);   // QsciScintilla自带cut，剪切仅对每个分页作用

    // 工具栏--复制
    copyAction = new QAction(tr("复制(&C)"), this);
    copyAction->setIcon(QIcon(":/Myimages/images/copy.png"));
    copyAction->setShortcut(QKeySequence::Copy);   // Ctrl+C, Ctrl+Ins
    copyAction->setToolTip(tr("复制文本"));
    copyAction->setStatusTip(tr("复制文本"));
    copyAction->setEnabled(false);
    connect(copyAction, &QAction::triggered, m_pTextEdit, &TextEditor::copy);   // QsciScintilla自带copy，复制仅对每个分页作用
    connect(m_pTextEdit, SIGNAL(copyAvailable(bool)), this, SLOT(slotCopyAvailable(bool)));   // 当选择文字时，用copyAvailable(bool)信号激活了复制按钮

    // 工具栏--黏贴
    pasteAction = new QAction(tr("粘贴(&P)"), this);
    pasteAction->setIcon(QIcon(":/Myimages/images/paste.png"));
    pasteAction->setShortcut(QKeySequence::Paste);   // Ctrl+V, Shift+Ins
    pasteAction->setToolTip(tr("粘贴文本"));
    pasteAction->setStatusTip(tr("粘贴文本"));
    connect(pasteAction, &QAction::triggered, m_pTextEdit, &TextEditor::paste);   // QsciScintilla自带paste，黏贴仅对每个分页作用
    // 绑定全局剪贴板
    connect(QApplication::clipboard(), &QClipboard::dataChanged, this, &MainWindow::clipboardDataChanged);   // *QApplication::clipboard()返回一个只向全局粘贴板的指针,dataChanged() 信号,以便监听剪贴板数据变化
    // 初始化
    if(const QMimeData *md = QApplication::clipboard()->mimeData())
    {
        // QMimeData为数据提供一个容器，用来记录关于MIME类型数据的信息,常用来描述保存在剪切板里信息
        pasteAction->setEnabled(md->hasText());
    }

    // 工具栏--删除
    deleteAction = new QAction(tr("删除(&D)"), this);
    deleteAction->setShortcut(QKeySequence::Delete);   // Del
    deleteAction->setToolTip(tr("删除所选文本"));
    deleteAction->setStatusTip(tr("删除所选文本"));
    connect(deleteAction, &QAction::triggered,
            [=]()
            {
                QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier);
                QCoreApplication::postEvent(m_pTextEdit, event);
            });

    // 工具栏--全选
    selectAllAction = new QAction(tr("全选(&L)"), this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);   // Ctrl+A
    selectAllAction->setToolTip(tr("全选文本"));
    selectAllAction->setStatusTip(tr("全选文本"));
    connect(selectAllAction, &QAction::triggered, m_pTextEdit, &TextEditor::selectAll);   // QsciScintilla自带selectAll，全选仅对每个分页作用

    // 工具栏--查找
    findAction = new QAction(tr("查找(&F)"), this);
    findAction->setIcon(QIcon(":/Myimages/images/find.png"));
    findAction->setShortcut(QKeySequence::Find);   // Ctrl+F
    findAction->setToolTip(tr("查找文本"));
    findAction->setStatusTip(tr("查找文本"));
    connect(findAction, &QAction::triggered, this, &MainWindow::find);   // 对整个应用进行查找

    // 切换全屏
    fullScreenAction = new QAction(tr("切换全屏模式"), this);
    fullScreenAction->setShortcut(QKeySequence::FullScreen);   // 全屏
    fullScreenAction->setCheckable(true);         // 打开可选开关，表示可以选中
    fullScreenAction->setChecked(isFullScreen()); // 表示是否已经选中
    fullScreenAction->setToolTip(tr("全屏显示"));
    fullScreenAction->setStatusTip(tr("全屏显示"));
    connect(fullScreenAction, &QAction::triggered, this, &MainWindow::setFullScreen);

    // 自动换行
    autoLineAction = new QAction(tr("自动换行"), this);
    autoLineAction->setCheckable(true);     // 打开可选开关，表示可以选中
    autoLineAction->setChecked(isAutoLine); // 表示是否已经选中
    connect(autoLineAction, &QAction::triggered, this, &MainWindow::changeAutoLine);

    /**/
    // 语言选择(待完善)
    languageModeAction[0] = new QAction(tr("Normal"), this);
    languageModeAction[1] = new QAction(tr("c++"), this);
    languageModeAction[2] = new QAction(tr("Java"), this);
    languageModeAction[3] = new QAction(tr("python"), this);
    for(int i = 0; i < 4; i++)
    {
        connect(languageModeAction[i], &QAction::triggered, this, &MainWindow::changeLanguageMode);
    }
    /**/

    // 首选项
    optionAction = new QAction(tr("首选项..."), this);
    optionAction->setToolTip(tr("配置程序"));
    optionAction->setStatusTip(tr("配置程序"));

    // 关于应用程序
    aboutAction = new QAction(tr("关于 TextEditor..."), this);
    aboutAction->setToolTip(tr("显示应用的相关信息"));
    aboutAction->setStatusTip(tr("显示应用的相关信息"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

    // 初始化还未用到的动作
//    for(int i = 0; i < 10; i++)
//    {
//        NewUndoAction[i] = nullptr;
//        NewRedoAction[i] = nullptr;
//        NewCutAction[i] = nullptr;
//        NewCopyAction[i] = nullptr;
//        NewPasteAction[i] = nullptr;
//        NewSelectAllAction[i] = nullptr;
//    }
}

// 创建菜单栏
void MainWindow::createMenus()
{
    // 文件菜单
    fileMenu = menuBar()->addMenu(tr("文件(&F)"));   // menuBar()返回窗口的菜单栏，没有则新建; addMenu()在菜单栏中加入菜单选项
    fileMenu->addAction(newAction);    // 添加新建动作
    fileMenu->addAction(openAction);   // 添加打开动作
    fileMenu->addAction(saveAction);   // 添加保存动作
    fileMenu->addAction(saveAsAction); // 添加另存为动作
    fileMenu->addSeparator();          // 添加分隔符
    fileMenu->addAction(printAction);  // 添加打印文件动作
    fileMenu->addAction(printPreviewAction);   // 添加打印预览动作
    fileMenu->addAction(exportToPDFAction);    // 添加导出为PDF
    separatorAction = fileMenu->addSeparator();// 添加分割线
    for(int i = 0; i < MaxRecentFiles; i++)
    {
        // 每个文件路径都是一个动作
        fileMenu->addAction(recentFileActions[i]);
    }
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // 编辑菜单
    editMenu = menuBar()->addMenu(tr("编辑(&E)"));
    editMenu->addAction(undoAction);      // 撤销
    editMenu->addAction(redoAction);      // 恢复
    editMenu->addSeparator();
    editMenu->addAction(cutAction);       // 剪切
    editMenu->addAction(copyAction);      // 复制
    editMenu->addAction(pasteAction);     // 黏贴
    editMenu->addAction(deleteAction);    // 删除
    editMenu->addAction(selectAllAction); // 全选

    // 搜索菜单
    searchMenu = menuBar()->addMenu(tr("搜索(&S)"));
    searchMenu->addAction(findAction);    // 查找

    // 视图菜单(有bug)
    viewMenu = menuBar()->addMenu(tr("视图(&V)"));
    viewMenu->addAction(fullScreenAction);// 切换全屏
    viewMenu->addSeparator();
    viewMenu->addAction(autoLineAction);  // 自动换行

    /**/
    // 语言菜单(需完善)
    languageMenu = menuBar()->addMenu(tr("语言(&L)"));
    for(int i = 0; i < 4; i++)
    {
        // 每个选项都是一个动作
        languageMenu->addAction(languageModeAction[i]);
    }
    /**/

    // 设置菜单
    settingsMenu = menuBar()->addMenu(tr("设置(&T)"));
    settingsMenu->addAction(optionAction);// 首选项

    // 工具菜单(暂无)
    toolsMenu = menuBar()->addMenu(tr("工具(&O)"));
    md5Menu = new QMenu(tr("MD5"));              // MD5子菜单
    toolsMenu->addMenu(md5Menu);                 // 往工具菜单添加MD5子菜单

    // 帮助菜单
    helpMenu = menuBar()->addMenu(tr("帮助(&H)"));
    helpMenu->addAction(aboutAction);    // 关于app
}

// 创建弹出菜单(在编辑区域内)
void MainWindow::createContextMenus()
{
    m_pTextEdit->addAction(copyAction);        // 复制
    m_pTextEdit->addAction(cutAction);         // 剪切
    m_pTextEdit->addAction(pasteAction);       // 黏贴
    m_pTextEdit->addAction(deleteAction);      // 删除
    m_pTextEdit->addAction(selectAllAction);   // 全选
    m_pTextEdit->setContextMenuPolicy(Qt::ActionsContextMenu);   // 由Action定义弹出菜单,部件将自动按顺序显示菜单
}

// 创建工具栏
void MainWindow::createToorBar()
{
    mainToolBar = addToolBar(tr("main"));
    mainToolBar->addAction(newAction);     // 新建
    mainToolBar->addAction(openAction);    // 打开
    mainToolBar->addAction(saveAction);    // 保存
    mainToolBar->addAction(printAction);   // 打印
    mainToolBar->addSeparator();
    mainToolBar->addAction(cutAction);     // 剪切
    mainToolBar->addAction(copyAction);    // 复制
    mainToolBar->addAction(pasteAction);   // 黏贴
    mainToolBar->addSeparator();
    mainToolBar->addAction(undoAction);    // 撤销
    mainToolBar->addAction(redoAction);    // 恢复
    mainToolBar->addSeparator();
    mainToolBar->addAction(findAction);    // 查找
}

// 创建底部状态栏(需改进)
void MainWindow::createStatusBar()
{
    // 文件信息
    showLabel = new QLabel(tr("Normal text file"));   // 新建的文件均为普通文件
    showLabel->setAlignment(Qt::AlignLeft);           // 右对齐
    showLabel->setMinimumSize(showLabel->sizeHint()); // 设置显示窗口大小，sizeHint()返回一个合适的大小值
    //showLabel->setIndent(50);   // 设定间距

    // 文件大小(长度,行数)
    sizeLinesLabel = new QLabel(tr("length : %1 lines : %2"));
    sizeLinesLabel->setAlignment(Qt::AlignLeft);   // 左对齐
    sizeLinesLabel->setMinimumSize(sizeLinesLabel->sizeHint());

    // 行列号
    rowColumnLabel = new QLabel(tr("Ln : 1   Col : 1"));
    rowColumnLabel->setAlignment(Qt::AlignLeft);
    rowColumnLabel->setMinimumSize(rowColumnLabel->sizeHint());

    // 结束符种类
    EndOfLineText endLineFormat = m_pTextEdit->getLineFormat();
    if(endLineFormat == EndOfLineText::Windows1)
    {
        lineFormat = EndOfLine::Windows;
        endOfLineModeLabel = new QLabel(tr("Windows (CR LF)"));
    }
    else if(endLineFormat == EndOfLineText::Unix1)
    {
        lineFormat = EndOfLine::Unix;
        endOfLineModeLabel = new QLabel(tr("Unix (LF)"));
    }
    else if(endLineFormat == EndOfLineText::Mac1)
    {
        lineFormat = EndOfLine::Mac;
        endOfLineModeLabel = new QLabel(tr("Macintosh (CR)"));
    }
    else
    {
        lineFormat = EndOfLine::Default;
        endOfLineModeLabel = new QLabel(tr("Unix (LF)"));
    }
    endOfLineModeLabel->setAlignment(Qt::AlignLeft);
    endOfLineModeLabel->setMinimumSize(endOfLineModeLabel->sizeHint());

    // 输入模式
    insertModeLabel = new QLabel(tr("INS"));   // 默认为INS
    insertModeLabel->setAlignment(Qt::AlignLeft);
    insertModeLabel->setMinimumSize(insertModeLabel->sizeHint());

    // 显示一般信息
    statusBar()->addWidget(showLabel);
    // 显示永久信息
    statusBar()->addPermanentWidget(sizeLinesLabel);
    statusBar()->addPermanentWidget(rowColumnLabel);
    statusBar()->addPermanentWidget(endOfLineModeLabel);
    statusBar()->addPermanentWidget(insertModeLabel);
}

// 加载配置
void MainWindow::readSettings()
{
    // 获取配置
    QSettings settings(QCoreApplication::organizationName(),
                       QCoreApplication::applicationName());   // 组织名，产品名

    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();   // 软件窗口大小记录
    // 如果没打开过软件
    if(geometry.isEmpty())
    {
        // 获取可用系统屏幕大小
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
    else
    {
        // 恢复窗口的上一次打开的大小
        restoreGeometry(geometry);
    }
    // 获取上次打开的文件名列表
    recentFiles = settings.value("recentFiles").toStringList();
    // 获取是否设置自动换行
    isAutoLine = settings.value("autoLineSwitch").toInt() == 1 ? true : false;
    // 更新曾经打开文件列表
    updateRecentFileActions();
}

// 写配置
void MainWindow::writeSetting()
{
    // 获取配置
    QSettings settings(QCoreApplication::organizationName(),
                       QCoreApplication::applicationName());
    // 保存窗口大小
    settings.setValue("geometry", saveGeometry());
    // 保存已打开的文件名列表
    settings.setValue("recentFiles", recentFiles);
    // 保存是否设置自动换行
    settings.setValue("autoLineSwitch", autoLineAction->isChecked() ? 1 : 0);
}

// 可以继续
bool MainWindow::okToContinue()
{
    // 判断编辑框是否有变化
    if(isWindowModified())
    {
        // 有更改的话会有弹窗提示是否保存
        QMessageBox box(QMessageBox::Question, tr("保存"),
                        tr("是否保存文件\"%1\"?").arg(curFile.isEmpty() ? shownName : curFile));
        box.setWindowIcon(QIcon(":/myimages/images/fileIcon.png"));
        box.setStandardButtons(QMessageBox::Ok | QMessageBox::No | QMessageBox::Cancel);
        box.setButtonText(QMessageBox::Ok, tr("是(&Y)"));
        box.setButtonText(QMessageBox::No, tr("否(&N)"));
        box.setButtonText(QMessageBox::Cancel, tr("取消"));

        int res = box.exec();
        // 保存
        if(res == QMessageBox::Ok)
        {
            return save();
        }
        // 取消
        else if(res == QMessageBox::Cancel)
        {
            return false;   // 不继续
        }
    }
    return true;   // 保存后继续
}

// 设置窗口标题显示当前正在操作的文件路径(软件窗口标题显示当前选择的分页窗口的文件的路径)
void MainWindow::setCurrentFile(const QString &fileName, int i)
{
    // 保存带路径文件名
    curFile = fileName;
    // 如果文件名不存在(即刚打开软件或者刚新建了一个文件)
    if(fileName.isEmpty())
    {
        curFile.append("new");   // 新文件名初始化为new
    }
    m_pTextEdit->setModified(false);   // 设置文档修改状态为false
    setWindowModified(false);          // 窗口不显示有修改标志
    shownName = tr("new");             // 展示的路径名为new
    // 如果文件名存在
    if(!curFile.isEmpty())
    {
        curFile.replace('/', '\\');   // 把路径中的"/"替换成"\\"
        shownName = curFile;
        recentFiles.removeAll(curFile);   // 把现操作文件名先从列表中去除
        recentFiles.prepend(curFile);     // 再把现操作中的文件路径插入stringList(recentFiles)的头部
        updateRecentFileActions();        // 更新曾经打开文件列表
    }
    // 在窗口的标题显示现在正在操作的文件路径
    // 更简单的方法改变默认星号的位置 [*]可以解析 [#或者其他字符]无法解析
    setWindowTitle(tr("[*]%1 - %2").arg(shownName).arg(tr("notepad--")));
    // 改变标签栏的名字
    if(i == -1)
    {
        m_pTabWidget->setTabText(m_pTabWidget->currentIndex(), shownName.section('\\', -1));   // 保存完后改变标签名字(取保存路径的最后一个)
    }
    else
    {
        m_pTabWidget->setTabText(i, shownName.section('\\', -1));   // 保存完后改变标签名字(取保存路径的最后一个)
    }
}

// 保存文件(有bug)
bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly))
    {
        QMessageBox::warning(this, tr("Application"),
                            tr("Cannot write file %1:\n%2.")
                            .arg(fileName)
                            .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    // Qt设置鼠标等待状态与恢复
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << m_pTextEdit->text();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    saveAction->setEnabled(false);

    return true;
}

// 更新曾经打开文件列表
void MainWindow::updateRecentFileActions()
{
    //适用于QStringList的java风格迭代器
    QMutableStringListIterator i(recentFiles);
    while(i.hasNext())
    {
        // 判断文件是否存在
        if(!QFile::exists(i.next()))
        {
            i.remove();
        }
    }

    for(int j = 0; j < MaxRecentFiles; j++)
    {
        if(j < recentFiles.count())
        {
            // 按序号显示曾经打开过的文件(最多显示最近五条)
            QString text = tr("%1: %2").arg(j + 1).arg(recentFiles[j]);
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        }
        else
        {
            // 大于5条不做文字提示
            recentFileActions[j]->setVisible(false);
        }
    }
    // 如果显示曾经打开文件列表不为空，划分出一个区域显示列表
    separatorAction->setVisible(!recentFiles.isEmpty());
}

// 更新自动换行模式信息栏
void MainWindow::updateEndOfLineModeLabel()
{
    EndOfLineText endLineFormat = m_pTextEdit->getLineFormat();
    if(endLineFormat == EndOfLineText::Windows1)
    {
        lineFormat = EndOfLine::Windows;
        endOfLineModeLabel->setText(tr("Windows (CR LF)"));
    }
    else if(endLineFormat == EndOfLineText::Unix1)
    {
        lineFormat = EndOfLine::Unix;
        endOfLineModeLabel->setText(tr("Unix (LF)"));
    }
    else if(endLineFormat == EndOfLineText::Mac1)
    {
        lineFormat = EndOfLine::Mac;
        endOfLineModeLabel->setText(tr("Macintosh (CR)"));
    }
    else
    {
        lineFormat = EndOfLine::Default;
        endOfLineModeLabel->setText(tr("Unix (LF)"));
    }
}

// 更新动作
void MainWindow::updateActions()
{
    // 更新是否自动换行
    autoLineAction->setChecked(isAutoLine);
}

// 读取文件后改变语言信息
void MainWindow::LanguageMode(QString name)
{
    int i = 0;
    if(name == "cpp" || name == "cxx" || name == "cc" || name == "h" || name == "hpp" || name == "hxx")
    {
        // 改变状态栏
        showLabel->setText(tr("c++"));
        // 语法高亮
        QsciLexerCPP *textLexer = new QsciLexerCPP; // 创建c++词法分析器
        while(i < 10 && NewTextEdit[i] != nullptr)
        {
            i++;
        }
        if(i >= 10) return;
        NewTextEdit[i-1]->setLexer(textLexer);   // 给QsciScintilla设置词法分析器
        // 自动补全
        QsciAPIs *apis = new QsciAPIs(textLexer);   // 引用自动补全函数
        if(!apis->load(":/Mykeywords/keywords/c++keywords.txt"))
            QMessageBox::warning(this,QString("提示"),QString("读取文件失败"));
        else
            apis->prepare();
    }
    else if(name == "java")
    {
        // 改变状态栏
        showLabel->setText(tr("Java"));
        // 语法高亮
        QsciLexerJava *textLexer = new QsciLexerJava; // 创建Java词法分析器
        while(i < 10 && NewTextEdit[i] != nullptr)
        {
            i++;
        }
        if(i >= 10) return;
        NewTextEdit[i-1]->setLexer(textLexer);   // 给QsciScintilla设置词法分析器
        // 自动补全
        QsciAPIs *apis = new QsciAPIs(textLexer);     // 引用自动补全函数
        if(!apis->load(":/Mykeywords/keywords/Javakeywords.txt"))
            QMessageBox::warning(this,QString("提示"),QString("读取文件失败"));
        else
            apis->prepare();
    }
    else if(name == "py" || name == "pyw")
    {
        // 改变状态栏
        showLabel->setText(tr("python"));
        // 语法高亮
        QsciLexerPython *textLexer = new QsciLexerPython; // 创建python词法分析器
        while(i < 10 && NewTextEdit[i] != nullptr)
        {
            i++;
        }
        if(i >= 10) return;
        NewTextEdit[i-1]->setLexer(textLexer);   // 给QsciScintilla设置词法分析器
        // 自动补全
        QsciAPIs *apis = new QsciAPIs(textLexer);     // 引用自动补全函数
        if(!apis->load(":/Mykeywords/keywords/Pythonkeywords.txt"))
            QMessageBox::warning(this,QString("提示"),QString("读取文件失败"));
        else
            apis->prepare();
    }
    else if(name == "txt")
    {
        // 改变状态栏
        showLabel->setText(tr("Normal text file"));
        return;
    }
    NewTextEdit[i-1]->setAutoCompletionSource(QsciScintilla::AcsAll);   //设置源
    NewTextEdit[i-1]->setAutoCompletionCaseSensitivity(true);   //设置自动补全大小写敏感
    NewTextEdit[i-1]->setAutoCompletionThreshold(1);    //设置每输入一个字符就会出现自动补全的提示
    NewTextEdit[i-1]->setFont(QFont("Consolas"));  // 设置等宽字体
    NewTextEdit[i-1]->setAutoIndent(true);   // 自动缩进
    NewTextEdit[i-1]->setIndentationGuides(QsciScintilla::SC_IV_LOOKBOTH);   // 设置缩进的显示方式
    NewTextEdit[i-1]->setBraceMatching(QsciScintilla::SloppyBraceMatch);   // 设置括号匹配
}

// 私有槽函数
// 新文件(有bug)
void MainWindow::newFile()
{
    if(okToContinue())
    {
        // 新建一个编辑器
        int i = 0;
        while(i < 10 && NewTextEdit[i] != nullptr) i++;
        if(i >= 10)
        {
            QMessageBox::warning(this,QString("注意!"),QString("最多只能新建10个分页"));
            return;
        }
        NewTextEdit[i] = new TextEditor(this);   // 新建一个文本框
        NewTextEdit[i]->setUtf8(true);

        // 设置分页窗口可关闭
        m_pTabWidget->setTabsClosable(true);
        m_pTabWidget->addTab(NewTextEdit[i], tr("new"));   // 把文本编辑区放入分页窗口

        // 获得当前焦点事件的窗口(即多窗口中选中一个来编辑)
        NewTextEdit[i]->setFocus();
        NewTextEdit[i]->setAcceptDrops(false);  // 不可拖拽分页窗口
        setAcceptDrops(true);   // 主窗口可以拖拽

        // 用QsciScintilla来设置行号
        NewTextEdit[i]->setMarginType(0, QsciScintilla::NumberMargin);   // //设置编号为0的页边显示行号
        NewTextEdit[i]->setMarginLineNumbers(0, true);   //对该页边启用行号
        NewTextEdit[i]->setMarginWidth(0, 35);   // 设置页边宽度
        NewTextEdit[i]->setCaretLineVisible(true);   //显示选中的行号
        NewTextEdit[i]->setCaretLineBackgroundColor(Qt::lightGray);   //显示选中行号的背景色
        NewTextEdit[i]->clear();

        connect(NewTextEdit[i], SIGNAL(textChanged()), this, SLOT(textEditorModified()));   //textChanged()信号在编辑框中文本有变化时激发,检测文本变化
        connect(NewTextEdit[i], SIGNAL(cursorPositionChanged(int, int)), this, SLOT(showCursorPosition(int, int)));   // 信号会在光标位置变化时激发,检测光标位置并显示
        connect(NewTextEdit[i], &TextEditor::overwriteModeChanged, [=](){   // 用TextEditor类的overwriteModeChanged信号检测输入模式是否变化
            if(NewTextEdit[i]->overwriteMode())
            {
                // overwriteMode()变为可覆盖
                insertModeLabel->setText(("OVR"));
            }
            else
            {
                insertModeLabel->setText("INS");
            }
        });   // lambda表达式，[=]表示值传递方式捕捉所有父作用域的变量

//        NewUndoAction[i] = new QAction(this);
//        NewRedoAction[i] = new QAction(this);
//        NewCutAction[i] = new QAction(this);
//        NewCopyAction[i] = new QAction(this);
//        NewPasteAction[i] = new QAction(this);
//        NewSelectAllAction[i] = new QAction(this);

//        NewUndoAction[i]->setShortcut(QKeySequence::Undo); // Ctrl+Z, Alt+Backspace
//        NewRedoAction[i]->setShortcut(QKeySequence::Redo); // Ctrl+Y, Shift+Ctrl+Z, Alt+Shift+Backspace
//        NewCutAction[i]->setShortcut(QKeySequence::Cut); // Ctrl+X, Shift+Del
//        NewCopyAction[i]->setShortcut(QKeySequence::Copy); // Ctrl+C, Ctrl+Ins
//        NewPasteAction[i]->setShortcut(QKeySequence::Paste); // Ctrl+V, Shift+Ins
//        NewSelectAllAction[i]->setShortcut(QKeySequence::SelectAll); // Ctrl+A

//        connect(NewUndoAction[i], &QAction::triggered, NewTextEdit[i], &TextEditor::undo);   // QsciScintilla自带undo，撤销仅对每个分页作用
//        connect(NewRedoAction[i], &QAction::triggered, NewTextEdit[i], &TextEditor::redo);   // QsciScintilla自带redo，恢复仅对每个分页作用
//        connect(NewCutAction[i], &QAction::triggered, NewTextEdit[i], &TextEditor::cut);   // QsciScintilla自带cut，剪切仅对每个分页作用
//        connect(NewCopyAction[i], &QAction::triggered, NewTextEdit[i], &TextEditor::copy);   // QsciScintilla自带copy，复制仅对每个分页作用
//        connect(NewPasteAction[i], &QAction::triggered, NewTextEdit[i], &TextEditor::paste);   // QsciScintilla自带paste，黏贴仅对每个分页作用
//        connect(NewSelectAllAction[i], &QAction::triggered, NewTextEdit[i], &TextEditor::selectAll);   // QsciScintilla自带selectAll，全选仅对每个分页作用

        setCurrentFile("", i+1);
    }
}

// 打开
void MainWindow::open()
{
    if(okToContinue())
    {
        // getOpenFileName 获取本地文件; 四个参数为指定父类、标题、默认打开后显示的目录、右下角的文件过滤器
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".",
                                                        tr("All types(*.*);;"
                                                           "Normal text file (*.txt);;"
                                                           "C++ source file (*.h;*.hpp;*.hxx;*.cpp;*.cxx;*.cc);;"
                                                           "Java source file (*.java);;"
                                                           "Python file (*.py;*.pyw)"));
        if(!fileName.isEmpty())
        { 
            loadFile(fileName);
            LanguageMode(fileName.section('.', -1));   // 根据打开的文件的后缀改变文本编辑框的语言
        }
    }
    updateEndOfLineModeLabel();
}

// 保存(有bug)
bool MainWindow::save()
{
    if(curFile == "new")
    {
        // 如果还没存在这个文件
        return saveAs();
    }
    else
    {
        return saveFile(curFile);
    }
}

// 另存为(有bug)
bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save TextEditor"), ".",
                                                    tr("Normal text file (*.txt);;"
                                                       "C++ source file (*.cpp);;"
                                                       "Java sourcce file (*.java);;"
                                                       "python file (*.py)"));
    if(fileName.isEmpty())
    {
        return false;
    }
    return saveFile(fileName);
}

// 打印文件
void MainWindow::printFile()
{
    // TODO
}

// 打印预览
void MainWindow::printFilePreview()
{
    // TODO
}

// 打印记录
void MainWindow::printPreview(QPrinter *printer)
{
    //  TODO
}

// 打印为PDF
void MainWindow::printFilePDF()
{
    // TODO
}

// 编辑器状态(是否有修改)
void MainWindow::textEditorModified()
{
    saveAction->setEnabled(true);
    // 如果文档修改过，则设置标记
    if(m_pTabWidget->currentIndex() == 0)
    {
        setWindowModified(m_pTextEdit->isModified());
    }
    else
    {
        setWindowModified(NewTextEdit[m_pTabWidget->currentIndex()-1]->isModified());
    }
}

// 剪贴板数据修改(获取剪贴板内容)
void MainWindow::clipboardDataChanged()
{
    // 获取剪切版内容
    // QMimeData为数据提供一个容器，用来记录关于MIME类型数据的信息,常用来描述保存在剪切板里信息，或者拖拽原理
    if(const QMimeData *md = QApplication::clipboard()->mimeData())
    {
        // 简单的文本格式
        pasteAction->setEnabled(md->hasText());
    }
}

// 打开已有文件
void MainWindow::openRecentFile()
{
    if(okToContinue())
    {
        // QObject *QObject::sender() const
        // QObject::Sender()返回发送信号的对象的指针,返回类型为QObject *
        QAction *action = qobject_cast<QAction *>(sender());
        if(action)
        {   
            loadFile(action->data().toString());
            LanguageMode(action->iconText().section('.', -1));   // 根据打开的文件的后缀改变文本编辑框的语言
        }
    }
    updateEndOfLineModeLabel();
}

// 查找文本
void MainWindow::find()
{
    // TODO
}

// 全屏(最大化代码可套用)
void MainWindow::setFullScreen()
{
    // 判断是否为全屏isFullScreen()(判断是否为最大化isMaximized())
    if(isFullScreen())
    {
        // 已经是全屏，则还原窗口
        this->showNormal();
    }
    else
    {
        // 不是全屏，则设置为全屏
        this->setWindowState(Qt::WindowFullScreen);   // 全屏Qt::WindowFullScreen(Qt::WindowMaximized是最大化，有边框)
    }
}

// 改变换行模式
void MainWindow::changeAutoLine()
{
    isAutoLine = autoLineAction->isChecked();

    // 注册表读写操作
    QSettings settings(QCoreApplication::organizationName(),
                       QCoreApplication::applicationName());   // 设置组织名、产品名
    settings.setValue("autoLineSwitch", QVariant(isAutoLine ? "1" : "0"));   // 使用QSettings对注冊表进行操作
}

// 改变语言模式(有bug)
void MainWindow::changeLanguageMode()
{
    QAction *act=qobject_cast<QAction*>(sender());//使用Qt的类型转换，将获得的信号指针恢复为QAction类型
    // 用act->iconText()来获取信号名
    if(act->iconText() == "c++")
    {
        // 改变显示的文件名后缀和状态栏(m_pTabWidget->currentIndex()获得当前活动的分页)
        m_pTabWidget->setTabText(m_pTabWidget->currentIndex(), "new.cpp");
        showLabel->setText(tr("c++"));
        // 语法高亮
        QsciLexerCPP *textLexer = new QsciLexerCPP; // 创建c++词法分析器
        // 根据分页给QsciScintilla设置词法分析器
        if(m_pTabWidget->currentIndex() == 0)
        {
            m_pTextEdit->setLexer(textLexer);
        }
        else
        {
            NewTextEdit[m_pTabWidget->currentIndex()-1]->setLexer(textLexer);
        }
        // 自动补全
        QsciAPIs *apis = new QsciAPIs(textLexer);   // 引用自动补全函数
        if(!apis->load(":/Mykeywords/keywords/c++keywords.txt"))
            QMessageBox::warning(this,QString("提示"),QString("读取文件失败"));
        else
            apis->prepare();
    }
    else if(act->iconText() == "Java")
    {
        // 改变显示的文件名后缀和状态栏
        m_pTabWidget->setTabText(m_pTabWidget->currentIndex(), "new.java");
        showLabel->setText(tr("Java"));
        // 语法高亮
        QsciLexerJava *textLexer = new QsciLexerJava; // 创建Java词法分析器
        // 根据分页给QsciScintilla设置词法分析器
        if(m_pTabWidget->currentIndex() == 0)
        {
            m_pTextEdit->setLexer(textLexer);
        }
        else
        {
            NewTextEdit[m_pTabWidget->currentIndex()-1]->setLexer(textLexer);
        }
        // 自动补全
        QsciAPIs *apis = new QsciAPIs(textLexer);     // 引用自动补全函数
        if(!apis->load(":/Mykeywords/keywords/Javakeywords.txt"))
            QMessageBox::warning(this,QString("提示"),QString("读取文件失败"));
        else
            apis->prepare();
    }
    else if(act->iconText() == "python")
    {
        // 改变显示的文件名后缀和状态栏
        m_pTabWidget->setTabText(m_pTabWidget->currentIndex(), "new.py");
        showLabel->setText(tr("python"));
        // 语法高亮
        QsciLexerPython *textLexer = new QsciLexerPython; // 创建python词法分析器
        // 根据分页给QsciScintilla设置词法分析器
        if(m_pTabWidget->currentIndex() == 0)
        {
            m_pTextEdit->setLexer(textLexer);
        }
        else
        {
            NewTextEdit[m_pTabWidget->currentIndex()-1]->setLexer(textLexer);
        }
        // 自动补全
        QsciAPIs *apis = new QsciAPIs(textLexer);     // 引用自动补全函数
        if(!apis->load(":/Mykeywords/keywords/Pythonkeywords.txt"))
            QMessageBox::warning(this,QString("提示"),QString("读取文件失败"));
        else
            apis->prepare();
    }
    else if(act->iconText() == "Normal")
    {
        // 改变显示的文件名后缀和状态栏
        m_pTabWidget->setTabText(m_pTabWidget->currentIndex(), "new.txt");
        showLabel->setText(tr("Normal text file"));
        // 根据分页给QsciScintilla设置词法分析器
        if(m_pTabWidget->currentIndex() == 0)
        {
            m_pTextEdit->setLexer(0);
            m_pTextEdit->setAutoCompletionSource(QsciScintilla::AcsNone);   // 文本文件不需要自动补全
        }
        else
        {
            NewTextEdit[m_pTabWidget->currentIndex()-1]->setLexer(0);
            NewTextEdit[m_pTabWidget->currentIndex()-1]->setAutoCompletionSource(QsciScintilla::AcsNone);   // 文本文件不需要自动补全
        }

        return;
    }
    if(m_pTabWidget->currentIndex() == 0)
    {
        m_pTextEdit->setAutoCompletionSource(QsciScintilla::AcsAll);   //设置源
        m_pTextEdit->setAutoCompletionCaseSensitivity(true);   //设置自动补全大小写敏感
        m_pTextEdit->setAutoCompletionThreshold(1);    //设置每输入一个字符就会出现自动补全的提示
        m_pTextEdit->setFont(QFont("Consolas"));  // 设置等宽字体
        m_pTextEdit->setAutoIndent(true);   // 自动缩进
        m_pTextEdit->setIndentationGuides(QsciScintilla::SC_IV_LOOKBOTH);   // 设置缩进的显示方式
        m_pTextEdit->setBraceMatching(QsciScintilla::SloppyBraceMatch);   // 设置括号匹配
    }
    else
    {
        NewTextEdit[m_pTabWidget->currentIndex()-1]->setAutoCompletionSource(QsciScintilla::AcsAll);   //设置源
        NewTextEdit[m_pTabWidget->currentIndex()-1]->setAutoCompletionCaseSensitivity(true);   //设置自动补全大小写敏感
        NewTextEdit[m_pTabWidget->currentIndex()-1]->setAutoCompletionThreshold(1);    //设置每输入一个字符就会出现自动补全的提示
        NewTextEdit[m_pTabWidget->currentIndex()-1]->setFont(QFont("Consolas"));  // 设置等宽字体
        NewTextEdit[m_pTabWidget->currentIndex()-1]->setAutoIndent(true);   // 自动缩进
        NewTextEdit[m_pTabWidget->currentIndex()-1]->setIndentationGuides(QsciScintilla::SC_IV_LOOKBOTH);   // 设置缩进的显示方式
        NewTextEdit[m_pTabWidget->currentIndex()-1]->setBraceMatching(QsciScintilla::SloppyBraceMatch);   // 设置括号匹配
    }
}

// 关于
void MainWindow::about()
{
    QMessageBox::about(this, tr("关于 NotePad--"),
                       tr("<h2>NotePad-- v%1</h2>"
                          "<p>Copyright &copy; 2019 SCNU 曾德明.</p>"
                          "<p>"
                          "<p><b>NotePad--</b> 是主要用来展示QAction, QMainWindow, QMenuBar, "
                          "QStatusBar, QTableWidget, QToolBar以及其他Qt类的常用用法的测试性软件.</p>"
                          "<p>本软件仅作为个人软件实作成品.   _(:з」∠)_</p>").arg(QCoreApplication::applicationVersion()));   // 获得软件版本
}

// 是否允许复制
void MainWindow::slotCopyAvailable(bool enabled)
{
    cutAction->setEnabled(enabled);
    copyAction->setEnabled(enabled);
    deleteAction->setEnabled(enabled);
}

// 显示当前文档的字符总数以及总行数  NOTE: 注意这里的中文字符按一个字符来算
void MainWindow::showSizeLines()
{
//    sizeLinesLabel->setText(tr("length : %1  lines : %2")
//                            .arg(m_pTextEdit->document()->characterCount() - 1)
//                            .arg(m_pTextEdit->document()->lineCount()));
}

// 显示当前光标所在的行列号
void MainWindow::showCursorPosition(int line, int index)
{
    rowColumnLabel->setText(tr("Ln : %1   Col : %2").arg(line + 1).arg(index));
}

// 关闭子页面
void MainWindow::removeSubTab(int index)
{
    int i;
    if(okToContinue())
    {
        // index是槽函数获取的页面编号，最开始那个不关闭
        if(index != 0)
        {
            // removeTab()函数是公有函数，不是槽函数，所以不能直接用于信号和槽的链接
            for(i = index; i < 10; i++)
            {
                // 后面的分页往前移，覆盖被删除的分页的位置
                NewTextEdit[i-1] = NewTextEdit[i];
            }
            NewTextEdit[9] = nullptr;
            m_pTabWidget->removeTab(index);
        }
    }
}
