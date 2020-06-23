#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"

/* set NO_PARSE to TRUE to get a scanner-only compiler */
#define NO_PARSE FALSE
/* set NO_ANALYZE to TRUE to get a parser-only compiler */
#define NO_ANALYZE FALSE

extern "C" {
#include "util.h"
#if NO_PARSE
#include "scan.h"
#else
#include "parse.h"
#endif
}

#include "symtab.h"
/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = TRUE;
int TraceScan = TRUE;
int TraceParse = TRUE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;
int Error = FALSE;

// 生成语法树
bool MainWindow::createSyntaxTree()
{
    if(Last_FileName == "")
    {
        statusBrowser->setTextColor(Qt::red);
        statusBrowser->setPlainText("=========================警告=========================\n"
                                    "还未打开任何文件,无法生成语法树！");
        return false;
    }
    else
    {
        syntaxTree = NULL;
        // 获取当前文件路径
        QByteArray ba = Last_FileName.toUtf8();
        char * filename = ba.data();   // 把文件名转化为char *
        qDebug() << filename;
        QStringList list = Last_FileName.split("/"); // 把文件路径分割以获取最后的文件名
        // 需要一个转化文件名的过程(用于解决存储)
        QString openFilePath = Last_FileName;   // 测试文件路径
        qDebug() << "openFilePath-->"+openFilePath;
        QString treeName = openFilePath.insert(openFilePath.lastIndexOf('/')+1, "tree");   // 生成的树文件直接存储在测试用例文件的同级中， 并重命名为tree xxx.tiny
        qDebug() << "treeName-->"+treeName;
        QByteArray bb = treeName.toUtf8();
        char * saveName = bb.data();    // 保存用的文件名
        source = fopen(filename,"r");   // 读取文件
        if (source == NULL)
        {
            // todo 弹窗
            fprintf(stderr, "File %s not found\n", filename);
            return false;
            //exit(1);
        }
        // 重定向把生成树先输出保存到文件中
        listing = fopen(saveName, "w"); // 重定向输出
        fprintf(listing, "\nC-MINUS COMPILATION: %s\n\n", saveName);
        syntaxTree = parse(); // 生成
        fprintf(listing, "Syntax tree:\n\n");
        printTree(syntaxTree);
        fseek(source,0L,0);
        fclose(source);
        fclose(listing);

        // 从生成树文件中读取生成树显示
        QFile file(treeName);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"error","open syntaxTreefile error!");
            return false;
        }
        else
        {
            if(!file.isReadable())
                QMessageBox::warning(this,"error","this file is not readable!");
            else
            {
                QTextStream textStream(&file);
                while(!textStream.atEnd())
                {
                    resultBrowser->setTextColor(Qt::blue);
                    resultBrowser->setPlainText(textStream.readAll());
                }
                resultBrowser->show();
            }
        }

        flag_isParse = 1;

        statusBrowser->setTextColor(Qt::red);
        statusBrowser->setPlainText("=========================提示=========================\n"
                                    "C文件名：\n"+Last_FileName+
                                    "\n\n语法树生成成功！"
                                    "\n\n语法树文件：\n"+saveName+
                                    "\n\n语法树载入成功！\n");

        return true;
    }
}

bool MainWindow::semanticAnalysis()
{
    if(Last_FileName == "")
    {
        statusBrowser->setTextColor(Qt::red);
        statusBrowser->setPlainText("=========================警告=========================\n"
                                    "还未打开任何文件,无法进行语义分析！\n");
        return false;
    }
    else if(flag_isParse == 0)
    {
        statusBrowser->setTextColor(Qt::red);
        statusBrowser->setPlainText("=========================警告=========================\n"
                                    "文件还未进行语法分析,无法进行语义分析！\n");
        return false;
    }
    else
    {
        // 获取当前文件路径
        QByteArray ba = Last_FileName.toUtf8();
        char * filename = ba.data();   // 把文件名转化为char *
        qDebug() << filename;
        QStringList list = Last_FileName.split("/"); // 把文件路径分割以获取最后的文件名
        // 需要一个转化文件名的过程(用于解决存储)
        QString openFilePath = Last_FileName;   // 测试文件路径
        qDebug() << "openFilePath-->"+openFilePath;
        QString semanticName = openFilePath.insert(openFilePath.lastIndexOf('/')+1, "semantic");   // 生成的树文件直接存储在测试用例文件的同级中， 并重命名为tree xxx.tiny
        qDebug() << "semanticName-->"+semanticName;
        QByteArray bb = semanticName.toUtf8();
        char * saveName = bb.data();    // 保存用的文件名

        // 重定向把生成树先输出保存到文件中
        listing = fopen(saveName, "w"); // 重定向输出
        fprintf(listing, "\nC-MINUS SYMTAB: %s\n\n", saveName);
        createSYMTAB(syntaxTree);
        printSYMTAB();
        checkNode(syntaxTree);
        fclose(listing);

        // 从符号表文件中读取生成树显示
        QFile file(semanticName);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"error","open syntaxTreefile error!");
            return false;
        }
        else
        {
            if(!file.isReadable())
                QMessageBox::warning(this,"error","this file is not readable!");
            else
            {
                QTextStream textStream(&file);
                while(!textStream.atEnd())
                {
                    resultBrowser->setTextColor(Qt::blue);
                    resultBrowser->setPlainText(textStream.readAll());
                }
                resultBrowser->show();
            }
        }

        statusBrowser->setTextColor(Qt::red);
        statusBrowser->setPlainText("=========================提示=========================\n"
                                    "C文件名：\n"+Last_FileName+
                                    "\n\n语义分析成功！"
                                    "\n\n符号表文件：\n"+saveName+
                                    "\n\n符号表载入成功！\n");

        return true;
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化窗口标题和大小
    this->resize(QSize(800, 600));
    setWindowTitle("编译原理实验");

    // 由于QMainWindow是默认有layout的，所以再次设置layout会失效，要先在里面放一个widget
    mainWidget = new QWidget();
    this->setCentralWidget(mainWidget);

    mainLayout = new QHBoxLayout();
    leftLayout = new QVBoxLayout();
    rightLayout = new QVBoxLayout();

    leftLayout->addWidget(createCodeEditGroup());
    leftLayout->addWidget(createStatusGroup());
    rightLayout->addWidget(createResultGroup());
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    mainWidget->setLayout(mainLayout);

    flag_isOpen = 0;              // 文件打开标志
    flag_isNew = 0;               // 文件新旧标志
    flag_isParse = 0;             // 语法分析标志
    flag_isSymtab = 0;            // 语义分析标志
    Last_FileName = "";           // 最后的文件名
    Last_FileContent = "";        // 最后的文件内容
}

MainWindow::~MainWindow()
{
    delete ui;
}

QGroupBox * MainWindow::createCodeEditGroup()
{
    leftGroup1 = new QGroupBox(tr("C-minus Code Edit"));
    codeEdit = new QPlainTextEdit();
    QVBoxLayout * vbox = new QVBoxLayout;
    vbox->addWidget(codeEdit);
    leftGroup1->setLayout(vbox);
    return leftGroup1;
}

QGroupBox * MainWindow::createStatusGroup()
{
    leftGroup2 = new QGroupBox(tr("compile status"));
    statusBrowser = new QTextBrowser();
    QVBoxLayout * vbox = new QVBoxLayout;
    vbox->addWidget(statusBrowser);
    leftGroup2->setLayout(vbox);
    return leftGroup2;
}

QGroupBox * MainWindow::createResultGroup()
{
    rightGroup = new QGroupBox(tr("compile result"));
    resultBrowser = new QTextBrowser();
    QVBoxLayout * vbox = new QVBoxLayout;
    vbox->addWidget(resultBrowser);
    rightGroup->setLayout(vbox);
    return rightGroup;
}

void MainWindow::on_actionopen_O_triggered()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,"Open File","","Text File(*.*)");
    if(fileName == "")
    {
        statusBrowser->setTextColor(Qt::red);
        statusBrowser->setPlainText("=========================警告=========================\n"
                                    "文件打开失败!");
        return ;
    }
    else
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            statusBrowser->setTextColor(Qt::red);
            statusBrowser->setPlainText("=========================提示=========================\n"
                                        "文件打开失败!");
            return;
        }
        else
        {
            if(!file.isReadable())
                QMessageBox::warning(this,"error","this file is not readable!");
            else
            {
                QTextStream textStream(&file);
                while(!textStream.atEnd())
                {
                    codeEdit->setPlainText(textStream.readAll());
                }
                // 如果在打开之前已经打开过别的文件，而且生成树显示区有文字，则清空生成树显示区
                if(Last_FileContent != "")
                {
                    resultBrowser->setPlainText("");
                    resultBrowser->show();
                }
                codeEdit->show();
                file.close();
                flag_isOpen = 1;
                flag_isParse = 0;             // 语法分析标志
                flag_isSymtab = 0;            // 语义分析标志
                Last_FileName = fileName;
                qDebug() << "Last_FileName--->"+Last_FileName;
                Last_FileContent = codeEdit->toPlainText();
                statusBrowser->setTextColor(Qt::red);
                statusBrowser->setPlainText("=========================提示=========================\n"
                                            "文件载入成功！"
                                            "\n\n文件名：\n"+Last_FileName);
            }
        }
    }
}

void MainWindow::on_actionsave_S_triggered()
{
    if(flag_isNew)
    {
        if(codeEdit->toPlainText()=="")
        {
            QMessageBox::warning(this,"error","content can not be none!",QMessageBox::Ok);
        }
        else
        {
            QFileDialog fileDialog;
            QString str = fileDialog.getSaveFileName(this,"Open File","","Text File(*.txt)");
            if(str == "")
            {
                return;
            }
            QFile filename(str);
            if(!filename.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::warning(this,"error","Open File Error!");
                return;
            }
            else
            {
                QTextStream textStream(&filename);
                QString str = codeEdit->toPlainText();
                textStream << str;
                Last_FileContent =str;
            }
            QMessageBox::information(this,"Ssve File","Save File Success",QMessageBox::Ok);
            filename.close();
            flag_isNew = 0;
            flag_isParse = 0;             // 语法分析标志
            flag_isSymtab = 0;            // 语义分析标志
            Last_FileName = str;
        }
    }
    else
    {
        if(flag_isOpen)
        {
            QFile file(Last_FileName);
            if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::warning(this,"error","Open File Faile");
                return;
            }
            else
            {
                QTextStream textString(&file);
                QString str = codeEdit->toPlainText();
                textString << str;
                QMessageBox::warning(this,"tip","Save File Success!");
                flag_isParse = 0;             // 语法分析标志
                flag_isSymtab = 0;            // 语义分析标志
                Last_FileContent = str;
                file.close();
            }
        }
        else
        {
            QMessageBox::warning(this,"Warning","Please new or open a file");
            return;
        }
    }
}

void MainWindow::on_actionsaveAs_A_triggered()
{
    QFileDialog fileDialog;
    QString fileName = fileDialog.getSaveFileName(this,"Save File As","","Text File(*.txt)");
    if(fileName == "")
    {
        return;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"error","open file failure!");
        return;
    }
    else
    {
        QTextStream textStream(&file);
        QString str = codeEdit->toPlainText();
        textStream<<str;
        QMessageBox::warning(this,"tip","Save File Success!");
        Last_FileContent = str;
        Last_FileName = fileName;

        flag_isNew = 0;
        flag_isParse = 0;             // 语法分析标志
        flag_isSymtab = 0;            // 语义分析标志
        file.close();
    }
}

void MainWindow::on_actionclose_triggered()
{
    close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(codeEdit->toPlainText() == Last_FileContent)
            event->accept();
    else
    {
        if(QMessageBox::warning(this,"Warning","the file have not save,ensure exit?",QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
        {
            event->accept();
        }
        else
            event->ignore();
    }
}

void MainWindow::on_actionSyntaxAnalysis_triggered()
{
    QMessageBox::StandardButtons buttons = QMessageBox::Ok;
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
    if(createSyntaxTree())
    {
        QMessageBox::warning(this, "生成提示", "成功构建生成树", buttons, defaultButton);
    }
    else {
        QMessageBox::warning(this, "生成提示", "未能成功构建生成树", buttons, defaultButton);
    }
}

void MainWindow::on_actionsemanticAnalysis_triggered()
{
    if(semanticAnalysis())
    {
        QMessageBox::warning(this, "分析提示", "语义分析成功", QMessageBox::Ok, QMessageBox::NoButton);
    }
    else {
        QMessageBox::warning(this, "分析提示", "语义分析失败", QMessageBox::Ok, QMessageBox::NoButton);
    }
}

void MainWindow::on_actionabout_triggered()
{
    QMessageBox::about(this, tr("关于 Tiny"),
                       tr("<h2>miniC v1.0</h2>"
                          "<p>Copyright &copy; 2020 SCNU."
                          "<p>作者：李嘉荣，曾德明."
                          "<p>"
                          "<p><b>此项目</b>是主要用来实现minic扩充语言的语法分析项目界面及功能."
                          "<p>本软件仅作为个人实验成品."));   // 获得软件版本
}
