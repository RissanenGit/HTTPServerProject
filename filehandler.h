#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QFile>
#include <QByteArray>
#include <QCoreApplication>

class FileHandler
{
public:
    FileHandler();
    static QByteArray getFileContents(QString filename);
};

#endif // FILEHANDLER_H
