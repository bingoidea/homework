#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QString>
#include<QFile>


static const int RETCODE_RESTART = 100;
#define REG_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //槽
private slots:

    void Open_file();
    void New_file();
    void Save_as();
    void Source_display();
    void Cifafenxi();//词法记号
    void Cifa_char();
    void Yuyi_sy();
    void Huibiandaima();
    void Aboutus();
    void Reboot();
    void paintEvent(QPaintEvent *event);
    void All_start();
    void Sweep();
    void Central_code();
private:
    Ui::MainWindow *ui;
    QString fileName="test.c";
    QString myString;
    QProcess myprocess1;
    QProcess myprocess2;
    QProcess myprocess3;
    QProcess myprocess4;
    QProcess myprocess5;

};

#endif // MAINWINDOW_H
