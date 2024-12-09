#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("nouveau_source");
db.setUserName("projetcpp2a26");
db.setPassword("mp2a26");

if (db.open())
test=true;

    return  test;
}
void Connection::closeconnect()
{
    db.close();}
