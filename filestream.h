#ifndef FILESTREAM_H
#define FILESTREAM_H

#include <QObject>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include "timeunits.h"
#include "timesplit.h"
#include <QList>
#include <QTextStream>

class timeUnits;
class timeSplit;

class fileStream : public QObject
{
    Q_OBJECT
public:
    explicit fileStream(QObject *parent = nullptr);

signals:

public slots:
    void saveToFile(timeUnits*);

private:
    QString saveLocation;
    QString loadLocation;
    timeUnits* timeObject;
};

#endif // FILESTREAM_H
