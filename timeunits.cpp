#include "timeunits.h"

timeUnits::timeUnits(QObject *parent) : QObject(parent)
{
}

void timeUnits::startTimer()
{
   timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(countupMs()));
   setTimeIsRunning(true);
   timer->start(10);
}

void timeUnits::countupMs()
{
    if(ms <= 980){
        ms += 10;
        emit msChanged();
    }
    else {
        ms = 0;
        emit msChanged();
        count_time_unit_up('s');
    }
}


QTimer *timeUnits::getTimer() const
{
    return timer;
}

bool timeUnits::getTimeIsRunning() const
{
    return timeIsRunning;
}

void timeUnits::setTimeIsRunning(bool value)
{
    timeIsRunning = value;
}

int timeUnits::getH() const
{
    return h;
}

void timeUnits::setH(int value)
{
    h = value;
    emit hChanged();
}

int timeUnits::getM() const
{
    return m;
}

void timeUnits::setM(int value)
{
    m = value;
    emit mChanged();
}

int timeUnits::getS() const
{
    return s;
}

void timeUnits::setS(int value)
{
    s = value;
    emit sChanged();
}

int timeUnits::getMs() const
{
    return ms;
}

void timeUnits::setMs(int value)
{
    ms = value;
    emit msChanged();
}

void timeUnits::count_time_unit_up(char unit)
{
    switch(unit)
    {
    case 's':
        if(s <=58){
            s++;
            emit sChanged();
        }
        else {
            setS(0);
            emit sChanged();
            count_time_unit_up('m');
        }
        break;
    case 'm':
        if(m <= 58){
            m++;
            emit mChanged();
        }
        else{
            setM(0);
            emit mChanged();
            count_time_unit_up('h');
        }
        break;
    case 'h':
            h++;
            emit hChanged();
        break;
    }
}


QList<timeSplit*>timeUnits::getSplits() const
{
    return splits;
}

void timeUnits::clearSplits()
{
    splits.clear();
}

void timeUnits::addSplit()
{
    auto obj = new timeSplit();
    obj->setMs(ms);
    obj->setS(s);
    obj->setM(m);
    obj->setH(h);
    splits.append(obj);
}

