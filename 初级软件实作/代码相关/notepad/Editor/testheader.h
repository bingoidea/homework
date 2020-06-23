#ifndef TESTHEADER_H
#define TESTHEADER_H

// 用于测试输出(qDebug()定义成qcout并且显示文件，行信息)
#include <QDebug>
#ifndef MYDEBUG
#define qcout qDebug()
#else
#define qcout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"
#endif


#endif // TESTHEADER_H
