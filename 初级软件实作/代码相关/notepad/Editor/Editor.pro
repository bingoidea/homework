#-------------------------------------------------
#
# Project created by QtCreator 2019-06-15T11:07:49
#
#-------------------------------------------------

QT       += core gui
QT += printsupport   #use Qprinter

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Editor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    texteditor.cpp

HEADERS  += mainwindow.h \
    testheader.h \
    texteditor.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../QScintilla_gpl-2.11.1/build-qscintilla-Desktop_Qt_5_8_0_MinGW_32bit-Release/release/ -lqscintilla2_qt5
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../QScintilla_gpl-2.11.1/build-qscintilla-Desktop_Qt_5_8_0_MinGW_32bit-Release/debug/ -lqscintilla2_qt5
else:unix: LIBS += -L$$PWD/../QScintilla_gpl-2.11.1/build-qscintilla-Desktop_Qt_5_8_0_MinGW_32bit-Release/ -lqscintilla2_qt5

INCLUDEPATH += $$PWD/../QScintilla_gpl-2.11.1/build-qscintilla-Desktop_Qt_5_8_0_MinGW_32bit-Release/release
DEPENDPATH += $$PWD/../QScintilla_gpl-2.11.1/build-qscintilla-Desktop_Qt_5_8_0_MinGW_32bit-Release/release

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../QScintilla_gpl-2.11.1/build-qscintilla-Desktop_Qt_5_8_0_MinGW_32bit-Release/release/libqscintilla2_qt5.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../QScintilla_gpl-2.11.1/build-qscintilla-Desktop_Qt_5_8_0_MinGW_32bit-Release/debug/libqscintilla2_qt5.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../QScintilla_gpl-2.11.1/build-qscintilla-Desktop_Qt_5_8_0_MinGW_32bit-Release/release/qscintilla2_qt5.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../QScintilla_gpl-2.11.1/build-qscintilla-Desktop_Qt_5_8_0_MinGW_32bit-Release/debug/qscintilla2_qt5.lib
else:unix: PRE_TARGETDEPS += $$PWD/../QScintilla_gpl-2.11.1/build-qscintilla-Desktop_Qt_5_8_0_MinGW_32bit-Release/libqscintilla2_qt5.a

RESOURCES += \
    images.qrc \
    keywords.qrc
