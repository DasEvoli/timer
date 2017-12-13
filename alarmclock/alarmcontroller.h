#ifndef ALARMCONTROLLER_H
#define ALARMCONTROLLER_H

#include <QObject>
#include "alarm.h"
#include <QVector>
#include <QSound>
#include <QFileDialog>
#include <QDateTime>
#include <QTimer>
#include <QSignalMapper>

class AlarmController : public QObject
{
    Q_OBJECT
public:
    explicit AlarmController(QObject *parent = nullptr);
    bool getTimerRunning() const;
    QList<Alarm*> getObjects() const;
    Alarm* getTriggeredObj() const;
    void setTriggeredObj(Alarm*);
    void setSoundObj(QSound*);
    void addAlarm(Alarm* obj);
    void deleteAlarm(Alarm* = nullptr, int = 0);
    void stopAlarmTimer();

signals:
    void openWindow(Alarm*);

public slots:
    void startAlarmTimer();
    void shouldAlarmTrigger();
    void triggerAlarm();
    void addSnooth();
    void startSound();
    void stopSound();

private:
    QList<Alarm*> alarmObjects;
    bool timerRunning = false;
    QSound* soundObj;
    Alarm* lastTriggeredObj;
    QTimer* alarmTimer;
};

#endif // ALARMCONTROLLER_H
