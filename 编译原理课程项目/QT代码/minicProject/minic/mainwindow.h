#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPlainTextEdit>
#include <QTextBrowser>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include "globals.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QGroupBox * createCodeEditGroup();
    QGroupBox * createStatusGroup();
    QGroupBox * createResultGroup();

    QString getFileName() { return Last_FileName; }

private slots:
    void closeEvent(QCloseEvent *event);  // 重写

    void on_actionopen_O_triggered();

    void on_actionsave_S_triggered();

    void on_actionsaveAs_A_triggered();

    void on_actionexit_X_triggered();

    void on_actionsyntaxTree_triggered();

    void on_actionsymbolTab_triggered();

    void on_actioncodeGen_triggered();

    void on_actionabout_triggered();

private:
    Ui::MainWindow *ui;

    QWidget * mainWidget = nullptr;

    QHBoxLayout * mainLayout = nullptr;
    QVBoxLayout * leftLayout = nullptr;
    QVBoxLayout * rightLayout = nullptr;

    QGroupBox * leftGroup1 = nullptr;
    QGroupBox * leftGroup2 = nullptr;
    QGroupBox * rightGroup = nullptr;

    QPlainTextEdit * codeEdit = nullptr;
    QTextBrowser * statusBrowser = nullptr;
    QTextBrowser * resultBrowser = nullptr;

    int flag_isOpen;
    int flag_isNew;
    int flag_isParse;
    int flag_isSymtab;
    int flag_isCgen;
    QString Last_FileName;
    QString Last_FileContent;

    TreeNode * syntaxTree;
};

#endif // MAINWINDOW_H
