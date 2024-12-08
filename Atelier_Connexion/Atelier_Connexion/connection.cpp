#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

Connection::Connection() {}

bool Connection::createconnection() {
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source2a26"); // Insérez le nom de la source de données
    db.setUserName("projetcpp2a26"); // Insérez le nom de l'utilisateur
    db.setPassword("mp2a26"); // Insérez le mot de passe de cet utilisateur

    if (db.open()) {
        test = true;
    } else {
        qDebug() << "Erreur de connexion :" << db.lastError().text(); // Pour le débogage
    }

    return test;
}
