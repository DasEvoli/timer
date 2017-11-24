#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QCoreApplication>
#include <QTime>
#include "timeunits.h"
#include "filestream.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(timeUnits* timeUnitsObj, QWidget *parent = 0);
    ~MainWindow();
    void setupConnections();

public slots:
    void startTimer();
    void stopTimer();
    void splitTimer();
    void clearSplits();
    void updateMs();
    void updateS();
    void updateM();
    void updateH();
    void saveToFile();

signals:


private:
    Ui::MainWindow* ui;
    timeUnits* timeUnitsObj;
    QTableWidget* m_pTableWidget;
    QStringList m_TableHeader;
    fileStream* fileStreamObject;

};

#endif // MAINWINDOW_H
