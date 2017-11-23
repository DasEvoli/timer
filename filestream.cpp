#include "filestream.h"

fileStream::fileStream(QObject *parent) : QObject(parent)
{

}

void fileStream::saveToFile(timeUnits* list)
{
    QList<timeSplit*>splitList = list->getSplits();
    QString fileName = QFileDialog::getSaveFileName(0, "Speicher Splits", "C:\\Users\\Laura\\Documents\\stopwatch_splits", "Text (*.txt)");

    if(fileName.isEmpty()){
        return;
    }
    else{
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly)){   // QIODevice ist abstrakt
            QMessageBox::information(0, "Datei kann nicht beschrieben werden", file.errorString());
            return;
        }
        else {
            QTextStream out(&file);

            for(int i = 0; i < splitList.count(); i++)
            {
                out << splitList[i]->getH() << ':'
                    << splitList[i]->getM() << ':'
                    << splitList[i]->getS() << '.'
                    << splitList[i]->getMs() << "\r\n";
            }
            file.close();
        }
    }

}
