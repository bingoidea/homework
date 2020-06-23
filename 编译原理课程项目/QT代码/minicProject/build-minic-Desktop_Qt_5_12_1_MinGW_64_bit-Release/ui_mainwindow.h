/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionopen_O;
    QAction *actionsave_S;
    QAction *actionsaveAs_A;
    QAction *actionexit_X;
    QAction *actionsyntaxTree;
    QAction *actionsymbolTab;
    QAction *actioncodeGen;
    QAction *actionabout;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile_F;
    QMenu *menuEdit_E;
    QMenu *menuHelp_H;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 300);
        actionopen_O = new QAction(MainWindow);
        actionopen_O->setObjectName(QString::fromUtf8("actionopen_O"));
        actionsave_S = new QAction(MainWindow);
        actionsave_S->setObjectName(QString::fromUtf8("actionsave_S"));
        actionsaveAs_A = new QAction(MainWindow);
        actionsaveAs_A->setObjectName(QString::fromUtf8("actionsaveAs_A"));
        actionexit_X = new QAction(MainWindow);
        actionexit_X->setObjectName(QString::fromUtf8("actionexit_X"));
        actionsyntaxTree = new QAction(MainWindow);
        actionsyntaxTree->setObjectName(QString::fromUtf8("actionsyntaxTree"));
        actionsymbolTab = new QAction(MainWindow);
        actionsymbolTab->setObjectName(QString::fromUtf8("actionsymbolTab"));
        actioncodeGen = new QAction(MainWindow);
        actioncodeGen->setObjectName(QString::fromUtf8("actioncodeGen"));
        actionabout = new QAction(MainWindow);
        actionabout->setObjectName(QString::fromUtf8("actionabout"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 23));
        menuFile_F = new QMenu(menuBar);
        menuFile_F->setObjectName(QString::fromUtf8("menuFile_F"));
        menuEdit_E = new QMenu(menuBar);
        menuEdit_E->setObjectName(QString::fromUtf8("menuEdit_E"));
        menuHelp_H = new QMenu(menuBar);
        menuHelp_H->setObjectName(QString::fromUtf8("menuHelp_H"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile_F->menuAction());
        menuBar->addAction(menuEdit_E->menuAction());
        menuBar->addAction(menuHelp_H->menuAction());
        menuFile_F->addAction(actionopen_O);
        menuFile_F->addAction(actionsave_S);
        menuFile_F->addAction(actionsaveAs_A);
        menuFile_F->addAction(actionexit_X);
        menuEdit_E->addAction(actionsyntaxTree);
        menuEdit_E->addAction(actionsymbolTab);
        menuEdit_E->addAction(actioncodeGen);
        menuHelp_H->addAction(actionabout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionopen_O->setText(QApplication::translate("MainWindow", "open(O)", nullptr));
        actionsave_S->setText(QApplication::translate("MainWindow", "save(S)", nullptr));
        actionsaveAs_A->setText(QApplication::translate("MainWindow", "saveAs(A)", nullptr));
        actionexit_X->setText(QApplication::translate("MainWindow", "exit(X)", nullptr));
        actionsyntaxTree->setText(QApplication::translate("MainWindow", "syntaxTree", nullptr));
        actionsymbolTab->setText(QApplication::translate("MainWindow", "symbolTab", nullptr));
        actioncodeGen->setText(QApplication::translate("MainWindow", "codeGen", nullptr));
        actionabout->setText(QApplication::translate("MainWindow", "about", nullptr));
        menuFile_F->setTitle(QApplication::translate("MainWindow", "File(F)", nullptr));
        menuEdit_E->setTitle(QApplication::translate("MainWindow", "Edit(E)", nullptr));
        menuHelp_H->setTitle(QApplication::translate("MainWindow", "Help(H)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
