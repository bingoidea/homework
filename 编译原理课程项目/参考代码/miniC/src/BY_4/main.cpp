#include "mainwindow.h"
#include <QApplication>
#include <QProcess>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    w.setWindowTitle("BY_4-编译器");
   // return a.exec();
    int e = a.exec();
         if(e == RETCODE_RESTART)
       {
           // 传入 qApp->applicationFilePath()，启动自己
          QProcess::startDetached(qApp->applicationFilePath(), QStringList());
           return 0;
       }
     return e;
}
