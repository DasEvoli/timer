#ifndef FILESTREAM_H
#define FILESTREAM_H

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include "stopwatch\stopwatch.h"

class FileStream : public QObject
{
    Q_OBJECT

public:
    explicit FileStream(QObject *parent = nullptr);
    void saveToFile(Stopwatch*);

signals:

public slots:

private:

};

#endif // FILESTREAM_H
