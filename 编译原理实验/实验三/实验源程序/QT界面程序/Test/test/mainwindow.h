#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QGroupBox>
#include <QTextBrowser>
#include <QPlainTextEdit>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QGroupBox * createTopGroup();
    QGroupBox * createCodeEditGroup();
    QGroupBox * createTreeEditGroup();

    QString getFileName() { return Last_FileName; }
    bool tinySyntaxTree();
    bool loadtree();

private slots:
    // ui界面右键转到槽，实际上就是一种隐式的connect
    void on_actionopen_O_triggered();

    void on_actionsave_S_triggered();

    void on_actionsave_as_A_triggered();

    void on_actionclose_C_triggered();

    void closeEvent(QCloseEvent *event);  // 重写

    void on_actionTinySyntaxTree_triggered();

    void on_actionload_tree_triggered();

    void on_actionabout_triggered();

private:
    Ui::MainWindow *ui;

    int flag_isOpen = 0;             // 文件打开标志
    int flag_isNew = 0;              // 文件新旧标志
    QString Last_FileName = "";           // 最后的文件名
    QString Last_FileContent = "";   // 最后的文件内容

    QWidget * mainWidget = nullptr;
    // 布局
    QHBoxLayout * mainLayout = nullptr;
    // 菜单
    QMenuBar * mainMenuBar = nullptr;
    QMenu * fileMenu = nullptr;
    QMenu * editMenu = nullptr;
    QMenu * helpMenu = nullptr;
    // Toobar
    QToolBar * mainToolBar = nullptr;
    // 主窗口控件
    QGroupBox *topGroup = nullptr;
    QGroupBox * leftGroup = nullptr;
    QGroupBox * rightGroup = nullptr;
    QTextBrowser * fileNameBrowser = nullptr;
    QPlainTextEdit * codeEdit = nullptr;
    QTextBrowser * treeBrowser = nullptr;
    // 动作
    QAction * openAction = nullptr;           // 打开
    QAction * saveAction = nullptr;           // 保存
    QAction * saveAsAction = nullptr;         // 另存为
    QAction * closeAction = nullptr;          // 关闭
    QAction * undoAction = nullptr;           // 撤销
    QAction * redoAction = nullptr;           // 还原
    QAction * cutAction = nullptr;            // 剪切
    QAction * copyAction = nullptr;           // 复制
    QAction * pasteAction = nullptr;          // 黏贴
    QAction * selectAllAction = nullptr;      // 全选
    QAction * tinySyntaxTreeAction = nullptr; // 生成语法树
    QAction * loadTreeAction = nullptr;       // 加载语法树
    QAction * aboutAction = nullptr;          // 关于
};

#endif // MAINWINDOW_H
