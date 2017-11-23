#ifndef TIMEUNITS_H
#define TIMEUNITS_H

#include <QObject>
#include <QTimer>
#include <QList>
#include "timesplit.h"

class timeSplit;
class MainWindow;


class timeUnits : public QObject
{
    Q_OBJECT
public:
    explicit timeUnits(QObject *parent = nullptr);

    int getMs() const;
    void setMs(int value);

    int getS() const;
    void setS(int value);

    int getM() const;
    void setM(int value);

    int getH() const;
    void setH(int value);

    void count_time_unit_up(char);

    bool getTimeIsRunning() const;
    void setTimeIsRunning(bool value);

    QTimer *getTimer() const;
    QList<timeSplit*> getSplits() const;
    void clearSplits();

    void addSplit();

signals:
    void timer_was_started();
    void ms_changed();
    void s_changed();
    void m_changed();
    void h_changed();
public slots:
    void start_timer();
    void countup_ms();
private:

    QTimer *timer;
    QList<timeSplit*> splits;
    bool timeIsRunning = false;
    int ms = 0;
    int s = 0;
    int m = 0;
    int h = 0;



};

#endif // TIMEUNITS_H
