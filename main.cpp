#include "mainwindow.h"
#include <QApplication>
#include <QtGlobal>
#include "stopwatch.h"

typedef int qint32;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Stopwatch stopwatchObj;
    MainWindow w(&stopwatchObj);
    w.show();

    return a.exec();
}
