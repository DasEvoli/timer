#include "alarm.h"

Alarm::Alarm(QObject *parent) : QObject(parent)
{
    soundFileName = "C:\\Users\\Laura\\Music\\pirate.wav";
}

QVector<Alarm::weekdays> Alarm::getEnabledDays()
{
    return enabledDays;
}

int Alarm::getH() const
{
    return h;
}

void Alarm::setH(int value)
{
    h = value;
}

int Alarm::getM() const
{
    return m;
}

void Alarm::setM(int value)
{
    m = value;
}

void Alarm::setAlarmSound(QString file)
{
    soundFileName = file;
}

void Alarm::addWeekday(Alarm::weekdays enumWeekday)
{
    enabledDays.append(enumWeekday);
}

void Alarm::removeWeekday(Alarm::weekdays enumWeekday)
{
    enabledDays.remove(enabledDays.indexOf(enumWeekday));
}

QString Alarm::getSoundFileName() const
{
    return soundFileName;
}

bool Alarm::getIsSnooth() const
{
    return isSnooth;
}

void Alarm::setIsSnooth(bool b)
{
    isSnooth = b;
}
