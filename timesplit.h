#ifndef TIMESPLIT_H
#define TIMESPLIT_H

#include <QObject>
#include "timeunits.h"

class timeUnits;
class timeSplit : public QObject
{
    Q_OBJECT
public:
    explicit timeSplit(QObject *parent = nullptr);
    int getMs() const;
    void setMs(int value);
    int getS() const;
    void setS(int value);
    int getM() const;
    void setM(int value);
    int getH() const;
    void setH(int value);

signals:



public slots:



private:
    int ms = 0;
    int s = 0;
    int m = 0;
    int h = 0;
};

#endif // TIMESPLIT_H
