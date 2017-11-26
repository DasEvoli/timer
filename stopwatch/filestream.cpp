#include "stopwatch\filestream.h"

FileStream::FileStream(QObject *parent) : QObject(parent)
{
}

void FileStream::saveToFile(Stopwatch* list)
{
    QList<Stopwatch*>splitList = list->getSplits();
    QString saveLocation = QFileDialog::getSaveFileName(nullptr, "Speicher Splits", "C:\\Users\\Laura\\Documents\\stopwatch_splits", "Text (*.txt)");
    if(saveLocation.isEmpty()){
        return;
    }
    else{
        QFile file(saveLocation);
        if(!file.open(QIODevice::WriteOnly)){   // QIODevice is abstract
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
