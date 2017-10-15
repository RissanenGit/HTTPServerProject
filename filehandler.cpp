#include "filehandler.h"
#include <QDebug>

FileHandler::FileHandler(){}

QByteArray FileHandler::getFileContents(QString filename){
    QString fullPath = QCoreApplication::applicationDirPath() + filename;
    QFile file (fullPath);

    if(!filename.contains(".jpg") && file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << "Text file";
        return file.readAll();
    }
    else if(file.open(QIODevice::ReadOnly)){
        qDebug() << "Image file";
        return file.readAll();
    }
    else{
        return nullptr;
    }

}


