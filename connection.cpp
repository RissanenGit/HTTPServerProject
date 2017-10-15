#include "connection.h"

Connection::Connection(qintptr socketHandle, QObject *parent) : QThread(parent){
    this->socketHandle = socketHandle;
}

Connection::~Connection(){ //Clear memory
    delete buffer;
    delete headers;
    delete socket;

    socket = nullptr;
    buffer = nullptr;
    headers = nullptr;

    cout << "Destroyed connection " << endl;
}

void Connection::sendResponse(QByteArray response){ //Write response to socket
    socket->write(response);
}

void Connection::parseData(){ //Parse headers and send response accordingly
    QList<QByteArray> content = buffer->split('\n'); //Temporary list of raw headers
    for(int i = 0; i < content.length() - 2; i++){
        if(content[i].split(':').length() > 0){
            if(i == 0){
                headers->insert("Request",content[i].split(':')[0]); //Add request as key
            }
            else{
                headers->insert(content[i].split(':')[0],content[i].split(':')[1]); //Add headers and their values to a map
            }
        }

    }

    //TODO: Create responses
    if(headers->value("Request").contains("GET")){
        QString request = headers->value("Request");
        QString file = request.mid(4, request.length() - 14); //Requested file

        QByteArray fileContents;
        if(file != "/" && file != "/favico.ico"){
            fileContents = FileHandler::getFileContents(file);
        }
        else if(file == "/"){
            fileContents = FileHandler::getFileContents("/index.html");
        }
        sendResponse(HTTPResponse::Respond200(fileContents, headers));

    }
}

void Connection::readData(){ //Read data from socket
    *buffer = socket->readAll();
    parseData();

}

void Connection::closeConnection(){ //Close socket and exit from thread
    if(socket->isOpen()){
        socket->close();
    }
    exit(0);
}

void Connection::timeout(){ //If connection timeouts
    if(buffer->isEmpty()){
        cout << "Connection timeout" << endl;
        closeConnection();
    }
}

void Connection::run(){
    socket = new QTcpSocket();
    buffer = new QByteArray();
    headers = new QMap<QByteArray,QByteArray>();
    socket->setSocketDescriptor(socketHandle);

    connect(socket,SIGNAL(readyRead()),this,SLOT(readData()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(closeConnection()),Qt::DirectConnection);


    this->exec();
}
