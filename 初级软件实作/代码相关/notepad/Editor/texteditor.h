#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QTextEdit>
#include <QPalette>

#include <Qsci/qsciscintilla.h>   // 引用qsciscintilla
#include <Qsci/qscilexercpp.h>    // c++词法分析器
#include <Qsci/qscilexerjava.h>   // Java词法分析器
#include <Qsci/qscilexerpython.h> // python词法分析其
#include <Qsci/qsciapis.h>        // 代码提示功能
#include <Qsci/qscidocument.h>    // 文件操作

// 不同系统的结束换行符(每个编辑框都不一样)
enum EndOfLineText
{
    Default1, Windows1, Unix1, Mac1
};

// 编辑器类继承于QsciScintilla
class TextEditor : public QsciScintilla
{
    Q_OBJECT

signals:
    void overwriteModeChanged();              // 写入模式变换(不覆盖INS，覆盖OVR)
    void modificationChanged(bool changed);   // 修改变化

public:
    TextEditor(QWidget *parent = nullptr);     // 构造一个编辑器
    bool readFile(const QString &fileName);    // 读文件函数
    bool writeFile(const QString &fileName);   // 写文件函数
    EndOfLineText getLineFormat();             // 获得行尾换行格式

protected:
    void keyPressEvent(QKeyEvent *ev);         // 键盘输入

public slots:
    // Qt::CaseSensitivity cs则是指输入的大小写要敏感
    void findNext(const QString &str, Qt::CaseSensitivity cs);       // 找下一个
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);   // 找上一个

private slots:
    void signalTextModification(bool changed);

private:
    // 默认编辑器换行符为Default1
    EndOfLineText lineFormat = EndOfLineText::Default1;
};

#endif // TEXTEDITOR_H
