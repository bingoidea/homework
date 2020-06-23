#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QPainter>
#include <QTextEdit>
#include <QKeyEvent>
#include <QSettings>
int Flag_IsNew = 0;        //标记：如果新建了文件就为1，初始值为0
QString Last_FileName;     //最后一次保存的文件的名字
QString Last_FileContent;  //最后一次保存文件的内容


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_open, SIGNAL(triggered(bool)), this, SLOT(Open_file()));
    //connect(ui->open, SIGNAL(clicked(bool)), this, SLOT(Open_file()));
    connect(ui->action_save, SIGNAL(triggered(bool)), this, SLOT(Save_as()));
    connect(ui->action_write, SIGNAL(triggered(bool)), this, SLOT(New_file()));
    connect(ui->action_cifafenxi, SIGNAL(triggered(bool)), this, SLOT(Cifafenxi()));
    connect(ui->action_char, SIGNAL(triggered(bool)), this, SLOT(Cifa_char()));
    connect(ui->action_source, SIGNAL(triggered(bool)), this, SLOT(Source_display()));
    connect(ui->action_yuyi, SIGNAL(triggered(bool)), this, SLOT(Yuyi_sy()));
    connect(ui->action_huibiandaima, SIGNAL(triggered(bool)), this, SLOT(Huibiandaima()));//汇编代码
    connect(ui->action_centralcode, SIGNAL(triggered(bool)), this, SLOT(Central_code()));//中间代码
    connect(ui->action_all, SIGNAL(triggered(bool)), this, SLOT(All_start()));
    connect(ui->action_BY_4, SIGNAL(triggered(bool)), this, SLOT(Aboutus()));
    connect(ui->action_reboot, SIGNAL(triggered(bool)), this, SLOT(Reboot()));
    connect(ui->action_sweep, SIGNAL(triggered(bool)), this, SLOT(Sweep()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
//打开文件的按钮
void MainWindow :: Open_file()
{
    QString fileNameTemp=fileName;
        fileName=QFileDialog::getOpenFileName(this, tr("select file"), ".", tr(".c文件(*c)"));
        if(fileName=="")
        {
            fileName=fileNameTemp;
            return;
        }
        else
        {
            ui->Error_display->clear();
            //ui->source->setEnabled(true);
        }
        //提示框
        QMessageBox msgBox;
        msgBox.setText("文件打开成功\n"+fileName);
        QApplication::beep();//报警声
        msgBox.exec();
             //在Write显示打开文件
             QFile f(fileName);
             if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
             {
                 return ;
             }

             QTextStream txtInput(&f);
             QString lineStr;
             ui->Write->clear();
             while(!txtInput.atEnd())
             {
                 lineStr = txtInput.readLine();
                 ui->Write->append(lineStr);
             }

             f.close();


             myprocess1.start("./minic.exe "+fileName);

             myprocess1.waitForStarted();
             myprocess1.waitForFinished();
              //ui->token->setDisabled(true);
             ui->Error_display->append("初次编译完成!\n");
             QString strTemp=QString::fromLocal8Bit(myprocess1.readAllStandardOutput());
             ui->Error_display->append(strTemp);
             ui->Error_display->moveCursor(QTextCursor::End);
}

//写入文件
void MainWindow::New_file()
{
        QFile new_file("test.c");
        myString=ui->Write->toPlainText();
        if (!new_file.open( QFile::WriteOnly | QFile::Text  ))
        {
            QMessageBox::information(this, "Error Message", "Please Select a Text File!");
                    return;

        }
          QTextStream out(&new_file);                 //分行写入文件
       out << ui->Write->toPlainText();
       new_file.close();
}

//另存为

void MainWindow::Save_as()
{
    QFileDialog fileDialog;
    QString save_asfileName = fileDialog.getSaveFileName(this,tr("Open file"),".",tr("Text File(*.txt)"));
    if(save_asfileName == "")
       {
           return;
       }
    QFile file(save_asfileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
       {
           QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
            //QApplication::beep();//报警声
           return;
       }
    else
       {
           QTextStream textStream(&file);
           QString str = ui->Write->toPlainText();
           textStream<<str;
           QMessageBox::warning(this,tr("提示"),tr("保存文件成功"));
            //QApplication::beep();//报警声
           Last_FileContent = str;
           Last_FileName = save_asfileName;
           Flag_IsNew = 0;
           file.close();
       }
}

//显示源文件
void MainWindow::Source_display()
{
    QFile f(fileName);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return ;
    }

    QTextStream txtInput(&f);
    QString lineStr;
    //ui->Other_display->clear();
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        ui->Other_display->append(lineStr);
        ui->Other_display->moveCursor(QTextCursor::End);
    }

    f.close();
     //QApplication::beep();//报警声
}

 //词法分析
void MainWindow::Cifafenxi()
{
    myprocess2.start("./minic.exe "+fileName+" -to");

    myprocess2.waitForStarted();
    myprocess2.waitForFinished();
     //ui->token->setDisabled(true);
    ui->Error_display->append("词法分析完成!\n");
    QString strTemp=QString::fromLocal8Bit(myprocess2.readAllStandardOutput());
    ui->Other_display->append(strTemp);
    ui->Other_display->moveCursor(QTextCursor::End);
     //QApplication::beep();//报警声
}
//词法——字符信息
void MainWindow::Cifa_char()
{
    myprocess5.start("./minic.exe "+fileName+" -ch");
    myprocess5.waitForStarted();
    myprocess5.waitForFinished();
     //ui->token->setDisabled(true);
    ui->Error_display->append("词法---字符信息完成!\n");
    QString strTemp=QString::fromLocal8Bit(myprocess5.readAllStandardOutput());
    ui->Other_display->append(strTemp);
    ui->Other_display->moveCursor(QTextCursor::End);
     //QApplication::beep();//报警声
}
void MainWindow::Yuyi_sy()
{
    myprocess3.start("./minic.exe "+fileName+" -sy");
    myprocess3.waitForStarted();
    myprocess3.waitForFinished();
    //ui->token->setDisabled(true);
    ui->Error_display->append("语义分析完成!\n");
    QString strTemp=QString::fromLocal8Bit(myprocess3.readAllStandardOutput());
    ui->Other_display->append(strTemp);
    ui->Other_display->moveCursor(QTextCursor::End);
    //QApplication::beep();//报警声
}
//汇编代码
void MainWindow::Huibiandaima()
{
    ui->Other_display->append("\n\n*******BY_4******汇编代码*******\n");
    QFile f(fileName.left(fileName.length()-2)+".s");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox m;
        m.setText("打开成功");
         m.exec();
        return ;
    }

    QTextStream txtInput(&f);
    QString lineStr;
   // ui->Other_display->clear();
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        ui->Other_display->append(lineStr);
        ui->Other_display->moveCursor(QTextCursor::End);
    }
    f.close();
     //QApplication::beep();//报警声
}
//中间代码
void MainWindow::Central_code()
{
     ui->Other_display->append("\n\n*******BY_4******中间代码*******\n");
    myprocess3.start("./minic.exe "+fileName+" -mc");
    myprocess3.waitForStarted();
    myprocess3.waitForFinished();
    //ui->token->setDisabled(true);
    ui->Error_display->append("中间代码执行成功!\n");
    QString strTemp=QString::fromLocal8Bit(myprocess3.readAllStandardOutput());
    ui->Other_display->append(strTemp);
    ui->Other_display->moveCursor(QTextCursor::End);
    //QApplication::beep();//报警声
}

//关于我们
void MainWindow::Aboutus()
{
         QMessageBox msgBox;
         msgBox.setText("小组成员：\n组长：程志超\n组员：吴和伟\n         周红梅\n         罗焯丹\n         魏薇\n***************************\n");
         //QApplication::beep();//报警声
         msgBox.exec();

}

//重启程序
void MainWindow::Reboot()
{
     QApplication::beep();//报警声
     qApp->exit(RETCODE_RESTART);
}

//重写paintEvent();
void MainWindow::paintEvent(QPaintEvent *event)
{
    /*QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap("./background.jpg"));*/
}

//一步
void MainWindow::All_start()
{

    QFile new_file_all("test.c");
    myString=ui->Write->toPlainText();
    if (!new_file_all.open( QFile::WriteOnly | QFile::Text  ))
    {
        QMessageBox::information(this, "Error Message", "Please Select a Text File!");
                return;

    }
      QTextStream out(&new_file_all);                 //分行写入文件
     out << ui->Write->toPlainText();
      new_file_all.close();
     fileName="test.c";
     myprocess1.start("./minic.exe "+fileName);
     myprocess1.waitForStarted();
     myprocess1.waitForFinished();
      //ui->token->setDisabled(true);
     ui->Error_display->append("初次编译完成!\n");
     QString strTemp=QString::fromLocal8Bit(myprocess1.readAllStandardOutput());
     ui->Error_display->append(strTemp);
     ui->Error_display->moveCursor(QTextCursor::End);
     Cifafenxi();//词法记号
     Cifa_char();
     Yuyi_sy(); 
     Central_code();
     Huibiandaima();
}

//清屏
void MainWindow::Sweep()
{
    ui->Write->clear();
    ui->Error_display->clear();
    ui->Other_display->clear();
    QApplication::beep();
}
