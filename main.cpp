#include "mainwindow.h"
#include <QApplication>
#include <QtGlobal>
#include "timeunits.h"

typedef int qint32;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    timeUnits timeUnitsObj;
    MainWindow w(&timeUnitsObj);
    w.show();

    return a.exec();
}
