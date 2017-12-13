#ifndef TRIGGEREDALARMWINDOW_H
#define TRIGGEREDALARMWINDOW_H

#include <QWidget>
#include <QCoreApplication>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include "Alarm.h"
#include "alarmcontroller.h"

class TriggeredAlarmWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TriggeredAlarmWindow(Alarm*, AlarmController*, QWidget *parent = 0);

protected:
    void  closeEvent(QCloseEvent*);

signals:

public slots:
    void destroyThis();

private:
    Alarm* alarmObj;
    AlarmController* AlarmControllerObject;

};

#endif // TRIGGEREDALARMWINDOW_H
