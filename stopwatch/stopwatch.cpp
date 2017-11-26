#include "stopwatch\stopwatch.h"

Stopwatch::Stopwatch(QObject *parent) : QObject(parent)
{
}

void Stopwatch::startTimer()
{
   timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(countUpMs()));
   setTimeIsRunning(true);
   timer->start(10);
}

void Stopwatch::countUpMs()
{
    if(ms <= 980){
        ms += 10;
        emit msChanged();
    }
    else {
        ms = 0;
        emit msChanged();
        countTimeUnitUp('s');
    }
}

QTimer *Stopwatch::getTimer() const
{
    return timer;
}

bool Stopwatch::getTimeIsRunning() const
{
    return timeIsRunning;
}

void Stopwatch::setTimeIsRunning(bool value)
{
    timeIsRunning = value;
}

int Stopwatch::getH() const
{
    return h;
}

void Stopwatch::setH(int value)
{
    h = value;
    emit hChanged();
}

int Stopwatch::getM() const
{
    return m;
}

void Stopwatch::setM(int value)
{
    m = value;
    emit mChanged();
}

int Stopwatch::getS() const
{
    return s;
}

void Stopwatch::setS(int value)
{
    s = value;
    emit sChanged();
}

int Stopwatch::getMs() const
{
    return ms;
}

void Stopwatch::setMs(int value)
{
    ms = value;
    emit msChanged();
}

void Stopwatch::countTimeUnitUp(char unit)
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
            countTimeUnitUp('m');
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
            countTimeUnitUp('h');
        }
        break;
    case 'h':
            h++;
            emit hChanged();
        break;
    }
}

QList<Stopwatch*> Stopwatch::getSplits() const
{
    return splits;
}

void Stopwatch::clearSplits()
{
    splits.clear();
}

void Stopwatch::addSplit()
{
    auto obj = new Stopwatch();
    obj->setMs(ms);
    obj->setS(s);
    obj->setM(m);
    obj->setH(h);
    splits.append(obj);
}

