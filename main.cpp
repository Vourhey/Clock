/*
 * Clock by Vourhey v0.1
 */

#include <QtGui/QApplication>
//#include "mainwindow.h"
#include "clockwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClockWidget cl;
    cl.show();
    
    return a.exec();
}
