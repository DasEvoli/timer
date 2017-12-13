#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QCoreApplication>
#include <QTime>
#include <QGroupBox>
#include <QLabel>
#include <QSignalMapper>
#include <QFileDialog>
#include "stopwatch\stopwatch.h"
#include "stopwatch\filestream.h"
#include "alarmclock\alarm.h"
#include "alarmclock\alarmcontroller.h"
#include "alarmclock\triggeredalarmwindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Stopwatch* stopwatchObj, QWidget *parent = 0);
    ~MainWindow();
    void setupConnections();
    void updateEditedAlarmInWindow();

protected:
    void  closeEvent(QCloseEvent*);

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
    void addAlarmWidget();
    void editAlarm(QWidget*);
    void alarmHUp();
    void alarmMUp();
    void alarmHDown();
    void alarmMDown();
    void saveAlarm();
    void cancelAlarmEdit();
    void openTriggeredAlarmWindow(Alarm*);
    void toggleWeekday(QWidget*);
    void deleteAlarm(QWidget*);
    void loadSound();

signals:


private:
    Ui::MainWindow* ui;
    Stopwatch* stopwatchObj;
    QTableWidget* m_pTableWidget;
    QStringList m_TableHeader;
    FileStream* fileStreamObject;
    QPushButton* b_addAlarm;
    QWidget* lastEditedWidget;
    Alarm* currentAlarmObj;
    AlarmController* AlarmControllerObject;
    TriggeredAlarmWindow* trAlWin = nullptr;

};

#endif // MAINWINDOW_H
