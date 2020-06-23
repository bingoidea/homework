#include <QApplication>
#include <QMessageBox>
#include <QFile>        // QT的文件操作
#include <QTextStream>
#include <QKeyEvent>
#include <QTextCodec>   // 文本互相转换
#include <QTime>        // 时间类
#include <QMimeData>
#include <QDebug>

#include "texteditor.h"
#include "testheader.h"

// 构造函数(构造一个继承于QsciScintilla的类)
TextEditor::TextEditor(QWidget* parent)
    :QsciScintilla(parent)
{
    clear();
}

// 读文件函数
bool TextEditor::readFile(const QString &fileName)
{
    // 创建文件
    QFile file(fileName);
    // QIODevice::Text 会改变原来文件的换行方式，不推荐这种打开方式,对于读'\n',对于写'\r\n'
    if(!file.open(QIODevice::ReadOnly))
    {
        // 如果不是只读模式，弹出警告
        QMessageBox::warning(this, tr("TextEditor"), tr("Cannot read file %1.\n%2.").arg(file.fileName()).arg(file.errorString()));
        return false;
    }

    clear();

    // QTextStream inFile(&file);
    // 设置应用程序强制光标为cursor,应用程序强制光标是为了显示应用程序是在特定状态下,比如等待文件读入
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);   // wait光标
#endif

    QTime t1, t2, t3, t4;        // 记录时间
    t1 = QTime::currentTime();   // 开始打开文件时间

    // QByteArray可用于存储原始字节（包括“\ 0” ）和传统的8位 “\ 0” 端接字符串
    const QByteArray data = file.readAll();

    // 判断读入文件的换行方式，contains()用于判断是否有匹配字符串
    if(data.contains(QByteArray("\r\n")))
    {
        // windows系统换行符
        lineFormat = EndOfLineText::Windows1;
    }
    else if(data.contains('\r'))
    {
        // mac换行符
        lineFormat = EndOfLineText::Mac1;
    }
    else if(data.contains('\n'))
    {
        // unix换行符
        lineFormat = EndOfLineText::Unix1;
    }
    else
    {
        // 默认
        lineFormat = EndOfLineText::Default1;
    }

    t2 = QTime::currentTime();
    qcout << t1.msecsTo(t2);   // 文件打开时间为t2-t1

    QTextCodec::ConverterState state;   // 文本代码转换
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");   // 代码格式为UTF-8
    const QString text = codec->toUnicode(data.constData(), data.size(), &state);   // 转为unicode编码

    t3 = QTime::currentTime();
    qcout << t2.msecsTo(t3);   // 文本转换时间

    if(state.invalidChars > 0)
    {
        // 转换出现无效字符则认为不是UTF-8编码格式文件，用回系统自带的
        QTextCodec * codec1 = QTextCodec::codecForLocale();
        qcout << codec1->name();
        if (!codec1)
            return false;
        qcout << "invalidChars > 0";
    }
    else
    {
        qcout << "invalidChars = 0";
    }

    t4 = QTime::currentTime();
    qcout << t3.msecsTo(t4);

    // 读完全部文件，光标恢复正常
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    return true;
}

// 写文件函数
bool TextEditor::writeFile(const QString &fileName)
{
    QFile file(fileName);
    // 如果非只写或Text,弹出警告
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("TextEditor"),
                             tr("Cannot write file %1.\n%2")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }
    // 写入文件流
    QTextStream out(&file);
    out.setCodec("UTF-8");

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    return true;
}

// 获得行尾换行格式
EndOfLineText TextEditor::getLineFormat()
{
    return lineFormat;
}

// 保护函数
// 判断键盘输入
void TextEditor::keyPressEvent(QKeyEvent *ev)
{
    // 如果按下Insert键
    if(Qt::Key_Insert == ev->key())
    {
        // 置反当前写入模式(即是否覆盖输入)
        setOverwriteMode(!overwriteMode());
        emit overwriteModeChanged();   // 发射overwriteModeChanged信号
        return;
    }
    QsciScintilla::keyPressEvent(ev);
}

//公有槽函数
// 找下一个
void TextEditor::findNext(const QString &str, Qt::CaseSensitivity cs)
{
    // TODO
}

// 找前一个
void TextEditor::findPrevious(const QString &str, Qt::CaseSensitivity cs)
{
    // TODO
}

// 私有槽函数
void TextEditor::signalTextModification(bool changed)
{
    emit modificationChanged(changed);   // 发出modificationChanged信号
}
