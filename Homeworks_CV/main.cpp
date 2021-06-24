#include "mainframe.h"
#include <QApplication>

#ifndef _DEBUG
#define _DEBUG
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainFrame w;
    w.show();

    return a.exec();
}
