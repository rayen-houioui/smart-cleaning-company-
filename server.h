#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>

class ServerData;

class Server
{
    Q_OBJECT
    QML_ELEMENT
public:
    Server();
    Server(const Server &);
    Server &operator=(const Server &);
    ~Server();

private:
    QSharedDataPointer<ServerData> data;
};

#endif // SERVER_H
