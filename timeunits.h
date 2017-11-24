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
    QTimer* getTimer() const;
    QList<timeSplit*> getSplits() const;
    void clearSplits();
    void addSplit();

signals:
    void timerWasStarted(); // unused
    void msChanged();
    void sChanged();
    void mChanged();
    void hChanged();

public slots:
    void startTimer();
    void countupMs();

private:
    QTimer* timer;
    QList<timeSplit*> splits;
    bool timeIsRunning = false;
    int ms = 0;
    int s = 0;
    int m = 0;
    int h = 0;

};

#endif // TIMEUNITS_H
