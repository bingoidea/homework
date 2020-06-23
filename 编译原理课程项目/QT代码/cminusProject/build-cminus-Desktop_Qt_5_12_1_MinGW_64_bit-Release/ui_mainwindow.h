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
    QAction *actionabout;
    QAction *actionclose;
    QAction *actionSyntaxAnalysis;
    QAction *actionsemanticAnalysis;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile_F;
    QMenu *menuEdit_E;
    QMenu *menuabout_H;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(483, 365);
        actionopen_O = new QAction(MainWindow);
        actionopen_O->setObjectName(QString::fromUtf8("actionopen_O"));
        actionsave_S = new QAction(MainWindow);
        actionsave_S->setObjectName(QString::fromUtf8("actionsave_S"));
        actionsaveAs_A = new QAction(MainWindow);
        actionsaveAs_A->setObjectName(QString::fromUtf8("actionsaveAs_A"));
        actionabout = new QAction(MainWindow);
        actionabout->setObjectName(QString::fromUtf8("actionabout"));
        actionclose = new QAction(MainWindow);
        actionclose->setObjectName(QString::fromUtf8("actionclose"));
        actionSyntaxAnalysis = new QAction(MainWindow);
        actionSyntaxAnalysis->setObjectName(QString::fromUtf8("actionSyntaxAnalysis"));
        actionsemanticAnalysis = new QAction(MainWindow);
        actionsemanticAnalysis->setObjectName(QString::fromUtf8("actionsemanticAnalysis"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 483, 23));
        menuFile_F = new QMenu(menuBar);
        menuFile_F->setObjectName(QString::fromUtf8("menuFile_F"));
        menuEdit_E = new QMenu(menuBar);
        menuEdit_E->setObjectName(QString::fromUtf8("menuEdit_E"));
        menuabout_H = new QMenu(menuBar);
        menuabout_H->setObjectName(QString::fromUtf8("menuabout_H"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile_F->menuAction());
        menuBar->addAction(menuEdit_E->menuAction());
        menuBar->addAction(menuabout_H->menuAction());
        menuFile_F->addAction(actionopen_O);
        menuFile_F->addAction(actionsave_S);
        menuFile_F->addAction(actionsaveAs_A);
        menuFile_F->addAction(actionclose);
        menuEdit_E->addAction(actionSyntaxAnalysis);
        menuEdit_E->addAction(actionsemanticAnalysis);
        menuabout_H->addAction(actionabout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionopen_O->setText(QApplication::translate("MainWindow", "open(O)", nullptr));
#ifndef QT_NO_SHORTCUT
        actionopen_O->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionsave_S->setText(QApplication::translate("MainWindow", "save(S)", nullptr));
#ifndef QT_NO_SHORTCUT
        actionsave_S->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionsaveAs_A->setText(QApplication::translate("MainWindow", "saveAs(A)", nullptr));
#ifndef QT_NO_SHORTCUT
        actionsaveAs_A->setShortcut(QApplication::translate("MainWindow", "Ctrl+Alt+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionabout->setText(QApplication::translate("MainWindow", "about", nullptr));
        actionclose->setText(QApplication::translate("MainWindow", "close(X)", nullptr));
#ifndef QT_NO_SHORTCUT
        actionclose->setShortcut(QApplication::translate("MainWindow", "Ctrl+W", nullptr));
#endif // QT_NO_SHORTCUT
        actionSyntaxAnalysis->setText(QApplication::translate("MainWindow", "syntaxAnalysis", nullptr));
        actionsemanticAnalysis->setText(QApplication::translate("MainWindow", "semanticAnalysis", nullptr));
        menuFile_F->setTitle(QApplication::translate("MainWindow", "File(F)", nullptr));
        menuEdit_E->setTitle(QApplication::translate("MainWindow", "Edit(E)", nullptr));
        menuabout_H->setTitle(QApplication::translate("MainWindow", "Help(H)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
