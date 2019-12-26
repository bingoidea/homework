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
    QAction *actionsave_as_A;
    QAction *actionclose_C;
    QAction *actionabout;
    QAction *actionundo;
    QAction *actionredo_R;
    QAction *actioncut_X;
    QAction *actioncopy_C;
    QAction *actionpaste_V;
    QAction *actionselect_all_A;
    QAction *actionTinySyntaxTree;
    QAction *actionload_tree;
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
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/myicons/icons/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionopen_O->setIcon(icon);
        actionsave_S = new QAction(MainWindow);
        actionsave_S->setObjectName(QString::fromUtf8("actionsave_S"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/myicons/icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionsave_S->setIcon(icon1);
        actionsave_as_A = new QAction(MainWindow);
        actionsave_as_A->setObjectName(QString::fromUtf8("actionsave_as_A"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/myicons/icons/saveas.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionsave_as_A->setIcon(icon2);
        actionclose_C = new QAction(MainWindow);
        actionclose_C->setObjectName(QString::fromUtf8("actionclose_C"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/myicons/icons/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionclose_C->setIcon(icon3);
        actionabout = new QAction(MainWindow);
        actionabout->setObjectName(QString::fromUtf8("actionabout"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/myicons/icons/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionabout->setIcon(icon4);
        actionundo = new QAction(MainWindow);
        actionundo->setObjectName(QString::fromUtf8("actionundo"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/myicons/icons/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionundo->setIcon(icon5);
        actionredo_R = new QAction(MainWindow);
        actionredo_R->setObjectName(QString::fromUtf8("actionredo_R"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/myicons/icons/redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionredo_R->setIcon(icon6);
        actioncut_X = new QAction(MainWindow);
        actioncut_X->setObjectName(QString::fromUtf8("actioncut_X"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/myicons/icons/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actioncut_X->setIcon(icon7);
        actioncopy_C = new QAction(MainWindow);
        actioncopy_C->setObjectName(QString::fromUtf8("actioncopy_C"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/myicons/icons/copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actioncopy_C->setIcon(icon8);
        actionpaste_V = new QAction(MainWindow);
        actionpaste_V->setObjectName(QString::fromUtf8("actionpaste_V"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/myicons/icons/paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionpaste_V->setIcon(icon9);
        actionselect_all_A = new QAction(MainWindow);
        actionselect_all_A->setObjectName(QString::fromUtf8("actionselect_all_A"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/myicons/icons/selectall.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionselect_all_A->setIcon(icon10);
        actionTinySyntaxTree = new QAction(MainWindow);
        actionTinySyntaxTree->setObjectName(QString::fromUtf8("actionTinySyntaxTree"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/myicons/icons/tree.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTinySyntaxTree->setIcon(icon11);
        actionload_tree = new QAction(MainWindow);
        actionload_tree->setObjectName(QString::fromUtf8("actionload_tree"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/myicons/icons/load.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionload_tree->setIcon(icon12);
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
        menuFile_F->addAction(actionsave_as_A);
        menuFile_F->addAction(actionclose_C);
        menuEdit_E->addAction(actionTinySyntaxTree);
        menuEdit_E->addAction(actionload_tree);
        menuHelp_H->addAction(actionabout);
        mainToolBar->addAction(actionopen_O);
        mainToolBar->addAction(actionsave_S);
        mainToolBar->addAction(actionsave_as_A);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionTinySyntaxTree);
        mainToolBar->addAction(actionload_tree);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionopen_O->setText(QApplication::translate("MainWindow", "open (O)", nullptr));
#ifndef QT_NO_SHORTCUT
        actionopen_O->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionsave_S->setText(QApplication::translate("MainWindow", "save (S)", nullptr));
#ifndef QT_NO_SHORTCUT
        actionsave_S->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionsave_as_A->setText(QApplication::translate("MainWindow", "save as (A)", nullptr));
#ifndef QT_NO_SHORTCUT
        actionsave_as_A->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionclose_C->setText(QApplication::translate("MainWindow", "close (C)", nullptr));
#ifndef QT_NO_SHORTCUT
        actionclose_C->setShortcut(QApplication::translate("MainWindow", "Ctrl+W", nullptr));
#endif // QT_NO_SHORTCUT
        actionabout->setText(QApplication::translate("MainWindow", "about...", nullptr));
        actionundo->setText(QApplication::translate("MainWindow", "undo (U)", nullptr));
#ifndef QT_NO_SHORTCUT
        actionundo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_NO_SHORTCUT
        actionredo_R->setText(QApplication::translate("MainWindow", "redo (R)", nullptr));
#ifndef QT_NO_SHORTCUT
        actionredo_R->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Z", nullptr));
#endif // QT_NO_SHORTCUT
        actioncut_X->setText(QApplication::translate("MainWindow", "cut (X)", nullptr));
#ifndef QT_NO_SHORTCUT
        actioncut_X->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_NO_SHORTCUT
        actioncopy_C->setText(QApplication::translate("MainWindow", "copy (C)", nullptr));
#ifndef QT_NO_SHORTCUT
        actioncopy_C->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_NO_SHORTCUT
        actionpaste_V->setText(QApplication::translate("MainWindow", "paste (V)", nullptr));
#ifndef QT_NO_SHORTCUT
        actionpaste_V->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_NO_SHORTCUT
        actionselect_all_A->setText(QApplication::translate("MainWindow", "select all (A)", nullptr));
#ifndef QT_NO_SHORTCUT
        actionselect_all_A->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_NO_SHORTCUT
        actionTinySyntaxTree->setText(QApplication::translate("MainWindow", "TinySyntaxTree", nullptr));
#ifndef QT_NO_SHORTCUT
        actionTinySyntaxTree->setShortcut(QApplication::translate("MainWindow", "Ctrl+F5", nullptr));
#endif // QT_NO_SHORTCUT
        actionload_tree->setText(QApplication::translate("MainWindow", "load tree", nullptr));
#ifndef QT_NO_SHORTCUT
        actionload_tree->setShortcut(QApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_NO_SHORTCUT
        menuFile_F->setTitle(QApplication::translate("MainWindow", "File (F)", nullptr));
        menuEdit_E->setTitle(QApplication::translate("MainWindow", "Edit (E)", nullptr));
        menuHelp_H->setTitle(QApplication::translate("MainWindow", "Help (H)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
