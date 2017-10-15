#include <QCoreApplication>
#include <server.h>
#include <QDir>

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);
    Server *server = new Server;
    int event = a.exec();

    delete server;
    server = nullptr;

    return event;
}
