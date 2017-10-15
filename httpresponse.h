#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QByteArray>
#include <QString>

class HTTPResponse
{
public:
    HTTPResponse();
    static QByteArray Respond404();
    static QByteArray Respond200(QByteArray data, QMap<QByteArray,QByteArray> *headers);
};

#endif // HTTPRESPONSE_H
