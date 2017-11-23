#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "timeunits.h"
#include <QTableWidget>
#include <QCoreApplication>
#include <QHeaderView>
#include <QMessageBox>
#include <QTime>
#include "filestream.h"

namespace Ui {
class MainWindow;
}
class timeUnits;
class fileStream;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(timeUnits* timeObject, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void start_timer();
    void stop_timer();
    void split_timer();
    void clear_splits();
    void update_ms();
    void update_s();
    void update_m();
    void update_h();
    void saveToFile();


signals:


private:
    Ui::MainWindow *ui;
    timeUnits* timeObject;
    void setup_connections();
    QTableWidget* m_pTableWidget;
    fileStream* fileObject;

};

#endif // MAINWINDOW_H
