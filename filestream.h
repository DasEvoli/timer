#ifndef FILESTREAM_H
#define FILESTREAM_H

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include "timeunits.h"

class fileStream : public QObject
{
    Q_OBJECT

public:
    explicit fileStream(QObject *parent = nullptr);
    void saveToFile(timeUnits*);

signals:

public slots:

private:
    QString saveLocation;
    QString loadLocation;

};

#endif // FILESTREAM_H
