/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_open;
    QAction *action_write;
    QAction *action_save;
    QAction *action_BY_4;
    QAction *action_cifafenxi;
    QAction *action_source;
    QAction *action_yufafenxi;
    QAction *action_tree;
    QAction *action_yuyi;
    QAction *action_huibiandaima;
    QAction *action_reboot;
    QAction *action_all;
    QAction *action_sweep;
    QAction *action_autorun;
    QAction *action_centralcode;
    QAction *action_yhh_centralcode;
    QAction *action_char;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QTextEdit *Write;
    QTextBrowser *Error_display;
    QTextBrowser *Other_display;
    QMenuBar *menuBar;
    QMenu *menu_N;
    QMenu *menu;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QMenu *menu_6;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(644, 436);
        MainWindow->setStyleSheet(QString::fromUtf8("color:rgb(170, 0, 0);\n"
"font: 87 9pt \"Arial Black\";\n"
"font: 10pt \"Arial\";\n"
"font: 9pt \"\345\256\213\344\275\223\";\n"
"font: 87 9pt \"Arial Black\";\n"
"background-color: rgb(224, 255, 237);\n"
""));
        action_open = new QAction(MainWindow);
        action_open->setObjectName(QStringLiteral("action_open"));
        action_write = new QAction(MainWindow);
        action_write->setObjectName(QStringLiteral("action_write"));
        action_save = new QAction(MainWindow);
        action_save->setObjectName(QStringLiteral("action_save"));
        action_BY_4 = new QAction(MainWindow);
        action_BY_4->setObjectName(QStringLiteral("action_BY_4"));
        action_cifafenxi = new QAction(MainWindow);
        action_cifafenxi->setObjectName(QStringLiteral("action_cifafenxi"));
        action_source = new QAction(MainWindow);
        action_source->setObjectName(QStringLiteral("action_source"));
        action_yufafenxi = new QAction(MainWindow);
        action_yufafenxi->setObjectName(QStringLiteral("action_yufafenxi"));
        action_tree = new QAction(MainWindow);
        action_tree->setObjectName(QStringLiteral("action_tree"));
        action_yuyi = new QAction(MainWindow);
        action_yuyi->setObjectName(QStringLiteral("action_yuyi"));
        action_huibiandaima = new QAction(MainWindow);
        action_huibiandaima->setObjectName(QStringLiteral("action_huibiandaima"));
        action_reboot = new QAction(MainWindow);
        action_reboot->setObjectName(QStringLiteral("action_reboot"));
        action_all = new QAction(MainWindow);
        action_all->setObjectName(QStringLiteral("action_all"));
        action_sweep = new QAction(MainWindow);
        action_sweep->setObjectName(QStringLiteral("action_sweep"));
        action_autorun = new QAction(MainWindow);
        action_autorun->setObjectName(QStringLiteral("action_autorun"));
        action_centralcode = new QAction(MainWindow);
        action_centralcode->setObjectName(QStringLiteral("action_centralcode"));
        action_yhh_centralcode = new QAction(MainWindow);
        action_yhh_centralcode->setObjectName(QStringLiteral("action_yhh_centralcode"));
        action_char = new QAction(MainWindow);
        action_char->setObjectName(QStringLiteral("action_char"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter_2 = new QSplitter(centralWidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        Write = new QTextEdit(splitter);
        Write->setObjectName(QStringLiteral("Write"));
        Write->setStyleSheet(QLatin1String("color:rgb(0, 0, 0);\n"
"font: 9pt \"Tahoma\";\n"
"background-color: rgb(255, 236, 224);"));
        splitter->addWidget(Write);
        Error_display = new QTextBrowser(splitter);
        Error_display->setObjectName(QStringLiteral("Error_display"));
        Error_display->setStyleSheet(QLatin1String("background-color: rgb(253, 255, 202);\n"
"color: rgb(0, 93, 23);\n"
"\n"
"font: 25 9pt \"Bahnschrift Light\";\n"
""));
        splitter->addWidget(Error_display);
        splitter_2->addWidget(splitter);
        Other_display = new QTextBrowser(splitter_2);
        Other_display->setObjectName(QStringLiteral("Other_display"));
        Other_display->setStyleSheet(QLatin1String("background-color: rgb(195, 255, 181);\n"
"color:rgb(0, 0, 0);\n"
"font: 25 9pt \"Bahnschrift Light\";"));
        splitter_2->addWidget(Other_display);

        gridLayout->addWidget(splitter_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 644, 23));
        menu_N = new QMenu(menuBar);
        menu_N->setObjectName(QStringLiteral("menu_N"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        menu_5 = new QMenu(menuBar);
        menu_5->setObjectName(QStringLiteral("menu_5"));
        menu_6 = new QMenu(menuBar);
        menu_6->setObjectName(QStringLiteral("menu_6"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu_N->menuAction());
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menu_5->menuAction());
        menuBar->addAction(menu_6->menuAction());
        menu_N->addAction(action_open);
        menu_N->addAction(action_write);
        menu_N->addAction(action_save);
        menu->addAction(action_source);
        menu->addAction(action_cifafenxi);
        menu->addAction(action_char);
        menu_3->addAction(action_yuyi);
        menu_4->addAction(action_centralcode);
        menu_4->addAction(action_huibiandaima);
        menu_4->addAction(action_all);
        menu_5->addAction(action_BY_4);
        menu_6->addAction(action_sweep);
        menu_6->addAction(action_reboot);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        action_open->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        action_write->setText(QApplication::translate("MainWindow", "\345\206\231\345\205\245", nullptr));
        action_save->setText(QApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272", nullptr));
        action_BY_4->setText(QApplication::translate("MainWindow", "BY_4", nullptr));
        action_cifafenxi->setText(QApplication::translate("MainWindow", "\350\257\215\346\263\225\350\256\260\345\217\267", nullptr));
        action_source->setText(QApplication::translate("MainWindow", "\346\272\220\346\226\207\344\273\266", nullptr));
        action_yufafenxi->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214", nullptr));
        action_tree->setText(QApplication::translate("MainWindow", "\350\257\255\346\263\225\345\210\206\346\236\220\346\240\221", nullptr));
        action_yuyi->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214", nullptr));
        action_huibiandaima->setText(QApplication::translate("MainWindow", "\346\261\207\347\274\226\344\273\243\347\240\201", nullptr));
        action_reboot->setText(QApplication::translate("MainWindow", "\351\207\215\345\220\257\347\250\213\345\272\217", nullptr));
        action_all->setText(QApplication::translate("MainWindow", "\344\270\200\346\255\245\345\210\260\345\272\225", nullptr));
        action_sweep->setText(QApplication::translate("MainWindow", "\346\270\205\345\261\217", nullptr));
        action_autorun->setText(QApplication::translate("MainWindow", "\350\207\252\345\220\257\345\212\250", nullptr));
        action_centralcode->setText(QApplication::translate("MainWindow", "\344\270\255\351\227\264\344\273\243\347\240\201", nullptr));
        action_yhh_centralcode->setText(QApplication::translate("MainWindow", "\344\274\230\345\214\226\345\220\216\347\232\204\344\270\255\351\227\264\344\273\243\347\240\201", nullptr));
        action_char->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\345\255\227\347\254\246", nullptr));
        menu_N->setTitle(QApplication::translate("MainWindow", "\346\226\260\345\273\272(&N)", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\350\257\215\346\263\225\345\210\206\346\236\220(&C)", nullptr));
        menu_3->setTitle(QApplication::translate("MainWindow", "\350\257\255\344\271\211\345\210\206\346\236\220(&Y)", nullptr));
        menu_4->setTitle(QApplication::translate("MainWindow", "\346\261\207\347\274\226\344\273\243\347\240\201(H)", nullptr));
        menu_5->setTitle(QApplication::translate("MainWindow", "\345\205\263\344\272\216\346\210\221\344\273\254(&A)", nullptr));
        menu_6->setTitle(QApplication::translate("MainWindow", "\345\205\266\344\273\226(&R)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
