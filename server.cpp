#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent){
    if(this->listen(QHostAddress::Any,80)){
        cout << "Started Server" << endl;
    }
    else{
        cout << "Could not start server" << endl;
    }
}

void Server::incomingConnection(qintptr handle){ //New connection
    cout << "New Connection from: " << handle << endl;
    Connection *clientConnection = new Connection(handle,this);
    connect(clientConnection,SIGNAL(finished()),clientConnection,SLOT(deleteLater()));
    clientConnection->start();
}



