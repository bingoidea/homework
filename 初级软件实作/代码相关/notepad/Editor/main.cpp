#include "mainwindow.h"
#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    // 强制初始化图像引用资源images.qrc
    Q_INIT_RESOURCE(images);

    QApplication app(argc, argv);

    // 初始化组织名,应用名,软件代数
    QCoreApplication::setOrganizationName("South China Normal University");
    QCoreApplication::setApplicationName("NotePad--");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);   // QT库版本查询
    QCoreApplication::setApplicationVersion("1.0");

    // 增加命令行支持(QCommandLineParser是提供了一系列命令行参数的类)
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();      // 添加help选项(在窗口上有-h,--help and ?)
    parser.addVersionOption();   // 添加 -v/--version选项，这个用来显示应用程序的版本信息
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(app);

    MainWindow mainWindow;
    if(!parser.positionalArguments().isEmpty())
    {
        mainWindow.loadFile(parser.positionalArguments().first());
    }
    mainWindow.show();

    return app.exec();
}
