/*
 *2012-1-11 paintEvent 产生的原因是因为部件内容被改动或则update函数，所以在这里，固定是30fps
 *荣超群
 */



#include <QtGui/QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
