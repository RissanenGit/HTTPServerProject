#ifndef SERVER_H
#define SERVER_H


#include <QTcpServer>

#include <iostream>
#include <connection.h>

using namespace std;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent = 0);
protected:
    void incomingConnection(qintptr handle);
};

#endif // SERVER_H
