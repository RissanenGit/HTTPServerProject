#include "httpresponse.h"

#include <QDebug>

HTTPResponse::HTTPResponse(){}
QByteArray HTTPResponse::Respond404(){
    return "HTTP/1.1 404 Not Found\r\nConnection: close\r\n\r\n";
}

QByteArray HTTPResponse::Respond200(QByteArray data, QMap<QByteArray,QByteArray> *headers){
    //qDebug() << *headers;
    QString response = QString("HTTP/1.1 200 OK\r\nContent-Length:%1\r\nContent-type:" + headers->value("Accept") + "\r\nConnection:keep-alive\r\n\r\n" + data + "\r\n\r\n").arg(strlen(data));
    return response.toUtf8();
}
