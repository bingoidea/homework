#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tinysyntaxtree.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = FALSE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;
int Error = FALSE;

// 生成树
bool MainWindow::tinySyntaxTree()
{
    if(Last_FileName == "")
    {
        return false;
    }
    else
    {
        TreeNode * syntaxTree;
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
        char * saveName = bb.data();
        source = fopen(filename,"r");
        if (source == NULL)
        {
            // todo 弹窗
            fprintf(stderr, "File %s not found\n", filename);
            return false;
            //exit(1);
        }
        listing = fopen(saveName, "w");
        fprintf(listing, "\nTINY COMPILATION: %s\n\n", saveName);
        // 进行重置
        linepos = 0; /* current position in LineBuf */
        bufsize = 0; /* current size of buffer string */
        EOF_flag = FALSE; /* corrects ungetNextChar behavior on EOF */
        syntaxTree = parse(); // 生成
        fprintf(listing, "Syntax tree:\n\n");
        printTree(syntaxTree);
        fseek(source,0L,0);
        fclose(source);
        fclose(listing);
        return true;
    }
}

// 加载生成树
bool MainWindow::loadtree()
{
    if(Last_FileName == "")
    {
        return false;
    }
    else
    {
        QString openFilePath = Last_FileName;   // 测试文件路径
        QStringList list = Last_FileName.split("/");
        qDebug() << "openFilePath-->"+openFilePath;
        QString openTreeName = openFilePath.insert(openFilePath.lastIndexOf('/')+1, "tree");
        qDebug() << "openTreeName-->"+openTreeName;
        QFile file(openTreeName);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"error","open file error!");
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
                    treeBrowser->setTextColor(Qt::red);
                    treeBrowser->setPlainText(textStream.readAll());
                }
                treeBrowser->show();
            }
        }
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
    mainLayout->addWidget(createCodeEditGroup());
    mainLayout->addWidget(createTreeEditGroup());

    mainWidget->setLayout(mainLayout);

    flag_isOpen = 0;             // 文件打开标志
    flag_isNew = 0;              // 文件新旧标志
    Last_FileName = "";           // 最后的文件名
    Last_FileContent = "";   // 最后的文件内容
}

MainWindow::~MainWindow()
{
    delete ui;
}

QGroupBox * MainWindow::createTopGroup()
{
    topGroup = new QGroupBox(tr("File Name"));
    fileNameBrowser = new QTextBrowser();
    fileNameBrowser->setText("D:/hhh/sss.txt");
    fileNameBrowser->setFixedHeight(1);
    QVBoxLayout * vbox = new QVBoxLayout;
    vbox->addWidget(fileNameBrowser);
    topGroup->setLayout(vbox);
    return topGroup;
}

QGroupBox * MainWindow::createCodeEditGroup()
{
    leftGroup = new QGroupBox(tr("Tiny Code Edit"));
    codeEdit = new QPlainTextEdit();
    QVBoxLayout * vbox = new QVBoxLayout;
    vbox->addWidget(codeEdit);
    leftGroup->setLayout(vbox);
    return leftGroup;
}

QGroupBox * MainWindow::createTreeEditGroup()
{
    rightGroup = new QGroupBox(tr("Tiny Syntax Tree"));
    treeBrowser = new QTextBrowser();
    QVBoxLayout * vbox = new QVBoxLayout;
    vbox->addWidget(treeBrowser);
    rightGroup->setLayout(vbox);
    return rightGroup;
}

void MainWindow::on_actionopen_O_triggered()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,"Open File","","Text File(*.*)");
    if(fileName == "")
    {
        return ;
    }
    else
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"error","open file error!");
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
                    treeBrowser->setPlainText("");
                    treeBrowser->show();
                }
                codeEdit->show();
                file.close();
                flag_isOpen = 1;
                Last_FileName = fileName;
                qDebug() << "Last_FileName--->"+Last_FileName;
                Last_FileContent = codeEdit->toPlainText();
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

void MainWindow::on_actionsave_as_A_triggered()
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
        file.close();
    }
}

void MainWindow::on_actionclose_C_triggered()
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

void MainWindow::on_actionTinySyntaxTree_triggered()
{
    QMessageBox::StandardButtons buttons = QMessageBox::Ok;
    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
    if(tinySyntaxTree())
    {
        QMessageBox::warning(this, "生成提示", "成功获取生成树", buttons, defaultButton);
    }
    else {
        QMessageBox::warning(this, "生成提示", "未能成功生成", buttons, defaultButton);
    }
}

void MainWindow::on_actionload_tree_triggered()
{
    if(loadtree())
    {
        QMessageBox::warning(this, "加载提示", "成功加载生成树", QMessageBox::Ok, QMessageBox::NoButton);
    }
    else {
        QMessageBox::warning(this, "加载提示", "未能加载生成树", QMessageBox::Ok, QMessageBox::NoButton);
    }
}

void MainWindow::on_actionabout_triggered()
{
    QMessageBox::about(this, tr("关于 Tiny"),
                       tr("<h2>Tiny v1.0</h2>"
                          "<p>Copyright &copy; 2019 SCNU."
                          "<p>"
                          "<p><b>此项目</b>是主要用来实现Tiny扩充语言的语法分析项目界面及功能."
                          "<p>本软件仅作为个人实验成品."));   // 获得软件版本
}
