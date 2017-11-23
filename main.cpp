typedef int qint32;

#include "mainwindow.h"
#include <QApplication>
#include "timeunits.h"
#include "filestream.h"
#include <QtGlobal>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    timeUnits timeObject;
    MainWindow w(&timeObject);
    w.show();

    return a.exec();
}
