#ifndef ALARM_H
#define ALARM_H

#include <QObject>
#include <QApplication>
#include <QVector>

class Alarm : public QObject
{
    Q_OBJECT
public:
    explicit Alarm(QObject *parent = nullptr);
    enum weekdays{MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY};
    QVector<weekdays> getEnabledDays();
    int getH() const;
    int getM() const;
    void setH(int value);
    void setM(int value);
    bool getIsSnooth() const;
    void setIsSnooth(bool);
    void addWeekday(weekdays);
    void removeWeekday(weekdays);
    void setAlarmSound(QString);
    QString getSoundFileName() const;

signals:

public slots:

private:
    int h = 0;
    int m = 0;
    int remainingTime;  // Not used, but could be
    bool isSnooth = false;
    QString soundFileName;
    QVector<weekdays> enabledDays;
};

#endif // ALARM_H
