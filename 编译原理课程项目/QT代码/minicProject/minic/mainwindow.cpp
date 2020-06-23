#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"

extern "C" {
#include "util.h"
#include "scan.h"
#include "parse.h"
#include "analyze.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"
}

/* allocate global variables */
int lineno = 0;
int HighScope=0;
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = TRUE;
int TraceScan = TRUE;
int TraceParse = TRUE;
int TraceAnalyze = TRUE;
int TraceCode = TRUE;
int Error = FALSE;

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
    flag_isCgen = 0;              // 中间代码生成标志
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
                flag_isParse = 0;
                flag_isSymtab = 0;
                flag_isCgen = 0;
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
            flag_isParse = 0;
            flag_isSymtab = 0;
            flag_isCgen = 0;
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
                flag_isNew = 0;
                flag_isParse = 0;
                flag_isSymtab = 0;
                flag_isCgen = 0;
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
        flag_isParse = 0;
        flag_isSymtab = 0;
        flag_isCgen = 0;
        file.close();
    }
}

void MainWindow::on_actionexit_X_triggered()
{
    close();
}

void MainWindow::on_actionsyntaxTree_triggered()
{
    if(Last_FileContent == "")
    {
        statusBrowser->setTextColor(Qt::red);
        statusBrowser->setPlainText("=========================警告=========================\n"
                                    "还未打开任何文件,无法生成语法树！");
        return;
    }
    else
    {
        if(flag_isParse)
        {
            // 生成输出路径
            QStringList list = Last_FileName.split(".");
            QString pathName = list[0] + ".tree";
            QByteArray bb = pathName.toUtf8();
            char * saveTreeFileName = bb.data();

            // 读取已有文件
            QFile file(saveTreeFileName);
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                statusBrowser->setTextColor(Qt::red);
                statusBrowser->setPlainText("=========================警告=========================\n"
                                            "读入语法树文件失败,无法显示语法树！");
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
                        resultBrowser->setTextColor(Qt::blue);
                        resultBrowser->setPlainText(textStream.readAll());
                    }
                    resultBrowser->show();
                }
            }

            statusBrowser->setTextColor(Qt::red);
            statusBrowser->setPlainText("=========================提示=========================\n"
                                        "C文件名：\n"+Last_FileName+
                                        "\n\n语法树生成成功！"
                                        "\n\n语法树文件：\n"+pathName+
                                        "\n\n语法树载入成功！\n");
        }
        else
        {
            // 语法树指针初始化
            syntaxTree = nullptr;
            // 打开文件
            //source = fopen("D:/QTproject/minicProject/testFile/test1.cm","r");   // 读取文件
            QByteArray ba = Last_FileName.toUtf8();
            char * fileName = ba.data();
            source = fopen(fileName,"r");
            if(source == NULL)
            {
                statusBrowser->setTextColor(Qt::red);
                statusBrowser->setPlainText("=========================警告=========================\n"
                                            "读入文件失败,无法生成语法树！");
                return;
            }
            // 生成输出路径
            //listing = fopen("D:/QTproject/minicProject/testFile/test.tm", "w"); // 重定向输出
            QStringList list = Last_FileName.split(".");
            QString pathName = list[0] + ".tree";
            QByteArray bb = pathName.toUtf8();
            char * saveTreeFileName = bb.data();
            listing = fopen(saveTreeFileName, "w"); // 重定向输出
            qDebug() << listing;
            // 生成语法树
            fprintf(listing, "\nMINI-C COMPILATION: %s\n\n", saveTreeFileName);
            linepos = 0; /* current position in LineBuf */
            bufsize = 0; /* current size of buffer string */
            EOF_flag = FALSE; /* corrects ungetNextChar behavior on EOF */
            syntaxTree = parse(); // 生成
            fprintf(listing, "\n\nSyntax tree:\n\n");
            printTree(syntaxTree);
            fclose(source);
            fclose(listing);

            // 从语法树文件中读取显示
            QFile file(saveTreeFileName);
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                statusBrowser->setTextColor(Qt::red);
                statusBrowser->setPlainText("=========================警告=========================\n"
                                            "读入语法树文件失败,无法显示语法树！");
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
                                        "\n\n语法树文件：\n"+pathName+
                                        "\n\n语法树载入成功！\n");
        }
    }
}

void MainWindow::on_actionsymbolTab_triggered()
{
    if(Last_FileName == "")
    {
        statusBrowser->setTextColor(Qt::red);
        statusBrowser->setPlainText("=========================警告=========================\n"
                                    "还未打开任何文件,无法进行语义分析！\n");
        return;
    }
    else if(flag_isParse == 0 || syntaxTree == nullptr)
    {
        statusBrowser->setTextColor(Qt::red);
        statusBrowser->setPlainText("=========================警告=========================\n"
                                    "文件还未进行语法分析,无法进行语义分析！\n");
        return;
    }
    else
    {
        if(flag_isSymtab)
        {
            // 生成输出路径
            QStringList list = Last_FileName.split(".");
            QString pathName = list[0] + ".symbol";
            QByteArray bb = pathName.toUtf8();
            char * saveSymbolTabName = bb.data();

            // 读取已有文件
            QFile file(saveSymbolTabName);
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                statusBrowser->setTextColor(Qt::red);
                statusBrowser->setPlainText("=========================警告=========================\n"
                                            "读入符号表文件失败,无法显示符号表！");
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
                                        "\n\n符号表文件：\n"+pathName+
                                        "\n\n符号表载入成功！\n");
        }
        else
        {
            // 生成输出路径
            QStringList list = Last_FileName.split(".");
            QString pathName = list[0] + ".symbol";
            qDebug() << pathName;
            QByteArray bb = pathName.toUtf8();
            char * saveSymbolTabName = bb.data();
            listing = fopen(saveSymbolTabName, "w"); // 重定向输出
            qDebug() << listing;
            // 生成符号表
            scope_a=0;
            int i;
            for(i = 0; i < MAX_SCOPE; i++) location[i] = 0;
            No_change=0;
            fprintf(listing, "\nMINI-C SYMBOL TAB: %s\n\n", saveSymbolTabName);
            fprintf(listing,"\nBuilding Symbol Table...\n");
            buildSymtab(syntaxTree);
            fprintf(listing,"\nChecking Types...\n");
            typeCheck(syntaxTree);
            fprintf(listing,"\nType Checking Finished\n");
            fclose(listing);

            // 从符号表文件中读取显示
            QFile file(saveSymbolTabName);
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                statusBrowser->setTextColor(Qt::red);
                statusBrowser->setPlainText("=========================警告=========================\n"
                                            "读入符号表文件失败,无法显示符号表！");
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
                        resultBrowser->setTextColor(Qt::blue);
                        resultBrowser->setPlainText(textStream.readAll());
                    }
                    resultBrowser->show();
                }
            }

            flag_isSymtab = 1;

            statusBrowser->setTextColor(Qt::red);
            statusBrowser->setPlainText("=========================提示=========================\n"
                                        "C文件名：\n"+Last_FileName+
                                        "\n\n语义分析成功！"
                                        "\n\n符号表文件：\n"+pathName+
                                        "\n\n符号表载入成功！\n");
        }
    }
}

void MainWindow::on_actioncodeGen_triggered()
{
    if(Last_FileName == "")
    {
        statusBrowser->setTextColor(Qt::red);
        statusBrowser->setPlainText("=========================警告=========================\n"
                                    "还未打开任何文件,无法进行中间代码生成！\n");
        return;
    }
    else if(flag_isParse == 0 || syntaxTree == nullptr)
    {
        statusBrowser->setTextColor(Qt::red);
        statusBrowser->setPlainText("=========================警告=========================\n"
                                    "文件还未进行语法分析,无法进行中间代码生成！\n");
        return;
    }
    else if(flag_isSymtab == 0)
    {
        statusBrowser->setTextColor(Qt::red);
        statusBrowser->setPlainText("=========================警告=========================\n"
                                    "文件还未进行语义分析,无法进行中间代码生成！\n");
        return;
    }
    else
    {
        if(flag_isCgen)
        {
            // 生成输出路径
            QStringList list = Last_FileName.split(".");
            QString pathName = list[0] + ".tm";
            QByteArray bb = pathName.toUtf8();
            char * saveCodeName = bb.data();

            // 从中间代码文件中读取显示
            QFile file(saveCodeName);
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                statusBrowser->setTextColor(Qt::red);
                statusBrowser->setPlainText("=========================警告=========================\n"
                                            "读入文件失败,无法显示中间代码！");
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
                        resultBrowser->setTextColor(Qt::blue);
                        resultBrowser->setPlainText(textStream.readAll());
                    }
                    resultBrowser->show();
                }
            }

            statusBrowser->setTextColor(Qt::red);
            statusBrowser->setPlainText("=========================提示=========================\n"
                                        "C文件名：\n"+Last_FileName+
                                        "\n\n中间代码生成成功！"
                                        "\n\n中间代码文件：\n"+pathName+
                                        "\n\n中间代码载入成功！\n");
        }
        else
        {
            // 生成输出路径
            QStringList list = Last_FileName.split(".");
            QString pathName = list[0] + ".tm";
            qDebug() << pathName;
            QByteArray bb = pathName.toUtf8();
            char * saveCodeName = bb.data();
            code = fopen(saveCodeName,"w");
            qDebug() << code;
            // 生成中间代码
            if (code == NULL)
            {
                printf("Unable to open %s\n",saveCodeName);
                exit(1);
            }
            codeGen(syntaxTree,saveCodeName);
            fprintf(listing,"\nCode generated in file %s\n",saveCodeName);
            fclose(code);

            // 从中间代码文件中读取显示
            QFile file(saveCodeName);
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                statusBrowser->setTextColor(Qt::red);
                statusBrowser->setPlainText("=========================警告=========================\n"
                                            "读入文件失败,无法显示中间代码！");
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
                        resultBrowser->setTextColor(Qt::blue);
                        resultBrowser->setPlainText(textStream.readAll());
                    }
                    resultBrowser->show();
                }
            }

            flag_isCgen = 1;

            statusBrowser->setTextColor(Qt::red);
            statusBrowser->setPlainText("=========================提示=========================\n"
                                        "C文件名：\n"+Last_FileName+
                                        "\n\n中间代码生成成功！"
                                        "\n\n中间代码文件：\n"+pathName+
                                        "\n\n中间代码载入成功！\n");
        }
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
