
#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>
#include <QList>

class timeSplit;
class MainWindow;


class Stopwatch : public QObject
{
    Q_OBJECT

public:
    explicit Stopwatch(QObject *parent = nullptr);
    int getMs() const;
    int getS() const;   
    int getM() const;
    int getH() const;
    void setMs(int value);
    void setS(int value);
    void setM(int value);
    void setH(int value);
    bool getTimeIsRunning() const;
    void setTimeIsRunning(bool value);
    QTimer* getTimer() const;
    QList<Stopwatch*> getSplits() const;
    void clearSplits();
    void addSplit();
    void countTimeUnitUp(char);

signals:
    void timerWasStarted(); // unused
    void msChanged();
    void sChanged();
    void mChanged();
    void hChanged();

public slots:
    void startTimer();
    void countUpMs();

private:
    QTimer* timer;
    QList<Stopwatch*> splits;
    bool timeIsRunning = false;
    int ms = 0;
    int s = 0;
    int m = 0;
    int h = 0;

};

#endif // STOPWATCH_H
