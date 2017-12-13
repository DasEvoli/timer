#include "alarmcontroller.h"

AlarmController::AlarmController(QObject *parent) : QObject(parent)
{
}

void AlarmController::addAlarm(Alarm *obj)
{
    alarmObjects.append(obj);
}

QList<Alarm *> AlarmController::getObjects() const
{
    return alarmObjects;
}

void AlarmController::deleteAlarm(Alarm* alarmObj, int index)
{
    //Deletes alarmObj by its pointer or by its index in alarmObjects
    if(alarmObj != nullptr){
        int i = alarmObjects.indexOf(alarmObj);
        alarmObjects.removeAt(i);
        delete alarmObj;
    }
    else{
        Alarm* obj = alarmObjects[index];
        alarmObjects.removeAt(index);
        delete obj;
    }
}

void AlarmController::shouldAlarmTrigger()
{
    //checks choosed weekday and time of obj with current date/time
    if(alarmObjects.count() > 0){
        QDate* dateobj = new QDate(QDate::currentDate());
        QTime* currentTime = new QTime(QTime::currentTime());
        int currentDay = dateobj->dayOfWeek() - 1;          //dayOfWeek starts at 1 (monday)
        for(int i = 0; i < alarmObjects.count(); i++) {
            if(alarmObjects[i]->getEnabledDays().count() > 0){
                for(int d = 0; d < alarmObjects[i]->getEnabledDays().count(); d++){
                    if(alarmObjects[i]->getEnabledDays().at(d) == currentDay){
                        QTime* timeObj = new QTime(alarmObjects[i]->getH(),alarmObjects[i]->getM(),0,0);
                        int remainingTime = currentTime->secsTo(*timeObj);
                        if(remainingTime == 0){
                            lastTriggeredObj = alarmObjects[i];
                            lastTriggeredObj->setIsSnooth(false);
                            triggerAlarm();
                        };
                    }
                }
            }
        }
    }
}

void AlarmController::startAlarmTimer()
{
    alarmTimer = new QTimer();
    connect(alarmTimer, SIGNAL(timeout()), this, SLOT(shouldAlarmTrigger()));
    alarmTimer->start(1000);
    timerRunning = true;
}

bool AlarmController::getTimerRunning() const
{
    return timerRunning;
}

void AlarmController::triggerAlarm()
{
    // mainwindow function to open a window to show the alarm
    emit openWindow(lastTriggeredObj);
}

void AlarmController::addSnooth()
{
    lastTriggeredObj->setIsSnooth(true);
    QTimer::singleShot(300000, this, SLOT(triggerAlarm()));   // After 5 minutes snooth will trigger
}

void AlarmController::startSound()
{
    soundObj->play();
}

void AlarmController::stopSound()
{
    soundObj->stop();
}

Alarm *AlarmController::getTriggeredObj() const
{
    return lastTriggeredObj;
}

void AlarmController::setTriggeredObj(Alarm *obj)
{
    lastTriggeredObj = obj;
}

void AlarmController::setSoundObj(QSound* obj)
{
    soundObj = obj;
}

void AlarmController::stopAlarmTimer()
{
    alarmTimer->stop();
    timerRunning = false;
}


