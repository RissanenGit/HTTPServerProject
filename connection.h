#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QThread>
#include <QHostAddress>
#include <QMap>

#include <httpresponse.h>
#include <filehandler.h>

#include <iostream>


using namespace std;

class Connection : public QThread
{
    Q_OBJECT
public:
    Connection(qintptr socketHandle,QObject *parent = 0);
    ~Connection();
    void sendResponse(QByteArray response);
    void parseData();

private:
    qintptr socketHandle;
    QTcpSocket *socket;
    QByteArray *buffer;
    QMap<QByteArray,QByteArray> *headers;

protected:
   virtual void run() override;
public slots:
   void readData();
   void closeConnection();
   void timeout();

};

#endif // CONNECTION_H
