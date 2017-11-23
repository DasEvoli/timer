#include "timeunits.h"

timeUnits::timeUnits(QObject *parent) : QObject(parent)
{
}

void timeUnits::start_timer()
{
   timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(countup_ms()));
   setTimeIsRunning(true);
   timer->start(10);
}

void timeUnits::countup_ms()
{
    if(ms <= 980){
        ms += 10;
        emit ms_changed();
    }
    else {
        ms = 0;
        emit ms_changed();
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
    h =+ value;
    emit h_changed();
}

int timeUnits::getM() const
{
    return m;
}

void timeUnits::setM(int value)
{
    m =+ value;
    emit m_changed();
}

int timeUnits::getS() const
{
    return s;
}

void timeUnits::setS(int value)
{
    s =+ value;
    emit s_changed();
}

int timeUnits::getMs() const
{
    return ms;
}

void timeUnits::setMs(int value)
{
    ms =+ value;
    emit ms_changed();
}

void timeUnits::count_time_unit_up(char unit)
{
    switch(unit)
    {
    case 's':
        if(s <=58){
            s++;
            emit s_changed();
        }
        else {
            setS(0);
            emit s_changed();
            count_time_unit_up('m');
        }
        break;
    case 'm':
        if(m <= 58){
            m++;
            emit m_changed();
        }
        else{
            setM(0);
            emit m_changed();
            count_time_unit_up('h');
        }
        break;
    case 'h':
            h++;
            emit h_changed();
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

