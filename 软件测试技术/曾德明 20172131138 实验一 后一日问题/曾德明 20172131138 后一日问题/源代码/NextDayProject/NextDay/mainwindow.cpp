#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 计算
void MainWindow::on_pushButton_3_clicked()
{
    int year, month, day;
    QString ans = "";
    year = ui->lineEdit->text().toInt();
    month = ui->lineEdit_2->text().toInt();
    day = ui->lineEdit_3->text().toInt();

    if(isLegel(year, month, day)) {
        ans = calc(year, month, day);
        ui->lineEdit_4->clear();
        ui->lineEdit_4->setText("Tomorrow's date is:"+ans+".");
    }
    else {
        //ui->lineEdit->clear();
        //ui->lineEdit_2->clear();
        //ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        QMessageBox::warning(this, "warning", "输入无效", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}

// 清除
void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}

// 确定
void MainWindow::on_pushButton_clicked()
{
    close();
}

// 取消
void MainWindow::on_pushButton_2_clicked()
{
    close();
}

// 判断闰年
bool MainWindow::isLeapYear(int year)
{
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

// 判断合法
bool MainWindow::isLegel(int year, int month, int day)
{
    if(year >= 1800 && year <= 2050) {
        // 如果月份不是2月
        if (month != 2) {
            // 月份不是2月且是小月
            if ( month == 4 || month == 6 || month == 9 || month == 11 ) {
                if ( 0 < day && day <= 30) return true;
                return false;
            }
            // 月份不是2月且是大月
            else {
                if ( 0 < day && day <= 31 && 0 < month && month <= 12 ) return true;
                return false;
            }
        }
        // 月份是2月且是闰年
        else if (isLeapYear(year)) {
            if ( 0 < day && day <= 29) return true;
            return false;
        }
        // 月份是2月且不是闰年
        else {
            if ( 0 < day && day <= 28) return true;
            return false;
        }
    }
    else {
        return false;
    }
}

// 计算
QString MainWindow::calc(int year, int month, int day)
{
    QString ans = "";

    //非2月情况
    if (month != 2) {
        //小月只有30天
        if ( month == 4 || month == 6 || month == 9 || month == 11 ) {
            if (day == 30){
                day = 1;
                month++;
            }
            else day = day + 1;
        }
        //非12月的大月，有31天
        else if(month != 12){
            if (day == 31){
                day = 1;
                month++;
            }
            else day = day + 1;
        }
        //12月，涉及跨年
        else {
            if (day == 31){
                day = 1;
                month = 1;
                year++;
            }
            else day = day + 1;
        }
    }
    //2月，分平年、闰年
    else if (isLeapYear(year)) {
        if (day == 29){
            day = 1;
            month++;
        }
        else day = day + 1;
    }
    //平年2月只有28天
    else {
        if (day == 28){
            day = 1;
            month++;
        }
        else day = day + 1;
    }

    QString newYear = QString::number(year);
    QString newMonth = QString::number(month);
    QString newDay = QString::number(day);
    ans = newYear+"-"+newMonth+"-"+newDay;

    return ans;
}
