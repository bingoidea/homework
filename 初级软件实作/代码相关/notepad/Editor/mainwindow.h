#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMimeData>
#include <QClipboard>
#include <QAction>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QTextEdit>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSettings>
#include <QStringList>
#include <QTextStream>
#include <QTabWidget>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QPrinter>
#include <QTabWidget>   // 分页窗口
// 增加打印功能支持
#include <QtPrintSupport/qtprintsupportglobal.h>
#include <QPrintDialog>
#include <QPrintPreviewDialog>

#include "texteditor.h"   // 编辑器类
#include "testheader.h"

// 不同系统的回车换行符
enum EndOfLine
{
    Default, Windows, Unix, Mac
};

namespace Ui {
class MainWindow;
}

// 显示窗口类
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool loadFile(const QString &fileName);   // 读取文件

protected:
    // 重载基类函数
    void closeEvent(QCloseEvent *event);            // 关闭事件
    void dragEnterEvent(QDragEnterEvent *event);    // 拖拽处理
    void dropEvent(QDropEvent *event);              // 拖拽释放处理

private:
    void createAction();                            // 创建动作
    void createMenus();                             // 创建菜单栏
    void createContextMenus();                      // 创建弹出菜单(在编辑区域内)
    void createToorBar();                           // 创建工具栏
    void createStatusBar();                         // 创建状态栏
    void readSettings();                            // 加载配置
    void writeSetting();                            // 写配置
    bool okToContinue();                            // 可以继续
    void setCurrentFile(const QString &fileName, int i = -1);   // 设置窗口标题显示当前正在操作的文件路径
    bool saveFile(const QString &fileName);         // 保存文件
    void updateRecentFileActions();                 // 更改曾经打开文件列表同时打开文件
    void updateEndOfLineModeLabel();                // 更新自动换行模式信息栏
    void updateActions();
    void LanguageMode(QString name);                // 读取文件后改变语言信息

// 槽函数
private slots:
    void newFile();   // 新文件
    void open();      // 打开文件
    bool save();      // 保存
    bool saveAs();    // 另存为
    void printFile(); // 打印文件
    void printFilePreview();       // 打印预览
    void printPreview(QPrinter *printer);
    void printFilePDF();           // 导出PDF
    void textEditorModified();     // 编辑器状态(是否有修改)
    void clipboardDataChanged();   // 剪贴板数据修改
    void openRecentFile();         // 打开已有文件
    void find();                   // 查找文本
    void setFullScreen();          // 设置全屏
    void changeAutoLine();         // 自动换行
    void changeLanguageMode();     // 改变输入框语言(暂时只有三种)
    void about();                  // 关于
    void slotCopyAvailable(bool enabled);   // 显示大小和总行数的状态栏
    void showSizeLines();          // 显示当前文档的字符总数以及总行数  NOTE: 注意这里的中文字符按一个字符来算
    void showCursorPosition(int line, int index);   // 显示光标所在的行列号
    void removeSubTab(int index);   // 关闭子页面

private:
    Ui::MainWindow *ui;
    // 当前文件名
    QString curFile;           // 带路径文件名
    QString shownName;         // 当curFile为空时，辅助shownName为new
    QStringList recentFiles;   // recentFiles文件名存储格式与curFile一致(保存已打开文件的路径)
    // 主编辑界面
    TextEditor *m_pTextEdit      = nullptr;   // 文本编辑器
    QTabWidget *m_pTabWidget     = nullptr;   // 可分页显示界面的窗口
    // 换行符(默认为Default)
    EndOfLine lineFormat = EndOfLine::Default;
    // 状态栏的五个显示标签
    QLabel* showLabel            = nullptr;   // 文件类型
    QLabel* sizeLinesLabel       = nullptr;   // 文件长度
    QLabel* rowColumnLabel       = nullptr;   // 行列位置
    QLabel* endOfLineModeLabel   = nullptr;   // 结束符模式
    QLabel* insertModeLabel      = nullptr;   // 插入方式显示
    // 自动换行判断(默认为true)
    bool isAutoLine = true;
    // 菜单项
    QMenu *fileMenu     = nullptr;   // 文件菜单
    QMenu *editMenu     = nullptr;   // 编辑菜单
    QMenu *searchMenu   = nullptr;   // 搜索菜单
    QMenu *viewMenu     = nullptr;   // 视图菜单
    QMenu *languageMenu = nullptr;   // 语言菜单
    QMenu *settingsMenu = nullptr;   // 设置菜单
    QMenu *toolsMenu    = nullptr;   // 工具菜单
    QMenu *md5Menu      = nullptr;   // MD5子菜单
    QMenu *helpMenu     = nullptr;   // 帮助菜单
    // 工具栏
    QToolBar *mainToolBar = nullptr;   // QToolBar出现的地方在菜单栏的下面
    // 各类菜单栏
    enum{ MaxRecentFiles = 5 };   // 最大能显示已有文件数
    QAction* recentFileActions[MaxRecentFiles];   // 文件菜单，最近打开文件
    QAction *newAction          = nullptr;   // 新建
    QAction *openAction         = nullptr;   // 打开
    QAction *saveAction         = nullptr;   // 保存
    QAction *saveAsAction       = nullptr;   // 另存为
    QAction *printAction        = nullptr;   // 打印
    QAction *printPreviewAction = nullptr;   // 打印预览
    QAction *exportToPDFAction  = nullptr;   // 导出PDF
    QAction *separatorAction    = nullptr;   // 用于最近打开文件菜单项的分隔
    QAction *exitAction         = nullptr;   // 关闭
    QAction *undoAction         = nullptr;   // 撤销
    QAction *redoAction         = nullptr;   // 恢复
    QAction *cutAction          = nullptr;   // 剪切
    QAction *copyAction         = nullptr;   // 复制
    QAction *pasteAction        = nullptr;   // 黏贴
    QAction *deleteAction       = nullptr;   // 删除
    QAction *selectAllAction    = nullptr;   // 全选
    QAction *findAction         = nullptr;   // 查找文本
    QAction *fullScreenAction   = nullptr;   // 切换全屏模式
    QAction *autoLineAction     = nullptr;   // 自动换行
    QAction *languageModeAction[4];          // 语言模式(暂时只有四种)
    QAction *optionAction       = nullptr;   // 首选项配置程序
    QAction *aboutAction        = nullptr;   // 显示应用相关信息

    // 用于新建
    TextEditor *NewTextEdit[10];             // 最多新建10个分页窗口
//    QAction *NewUndoAction[10];              // 每个新窗口对应的动作
//    QAction *NewRedoAction[10];
//    QAction *NewCutAction[10];
//    QAction *NewCopyAction[10];
//    QAction *NewPasteAction[10];
//    QAction *NewSelectAllAction[10];

};

#endif // MAINWINDOW_H
