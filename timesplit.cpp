#include "timesplit.h"

timeSplit::timeSplit(QObject *parent) : QObject(parent)
{
}

int timeSplit::getMs() const
{
    return ms;
}

void timeSplit::setMs(int value)
{
    ms = value;
}

int timeSplit::getS() const
{
    return s;
}

void timeSplit::setS(int value)
{
    s = value;
}

int timeSplit::getM() const
{
    return m;
}

void timeSplit::setM(int value)
{
    m = value;
}

int timeSplit::getH() const
{
    return h;
}

void timeSplit::setH(int value)
{
    h = value;
}


