#include "server.h"

class ServerData : public QSharedData
{
public:
};

Server::Server()
    : data(new ServerData)
{}

Server::Server(const Server &rhs)
    : data{rhs.data}
{}

Server &Server::operator=(const Server &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

Server::~Server() {}
