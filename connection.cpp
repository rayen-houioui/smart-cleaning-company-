#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlField>

Connection::Connection() {
    // List available drivers
    qDebug() << "Available drivers before creating connection:" << QSqlDatabase::drivers();

    // Attempt to establish the database connection
    qDebug() << "Attempting to establish database connection...";

    // Use QODBC driver (ensure you have this configured correctly)
    db = QSqlDatabase::addDatabase("QODBC");

    // Set the database name (DSN) and credentials
    db.setDatabaseName("source2a26");  // Replace with your DSN
    db.setUserName("projetcpp2a26");   // Replace with your username
    db.setPassword("mp2a26");          // Replace with your password

    qDebug() << "Database Name (DSN):" << db.databaseName();
    qDebug() << "User Name:" << db.userName();

    // Try to open the database
    if (db.open()) {
        qDebug() << "Database connection established successfully.";
    } else {
        qDebug() << "Error: Unable to open the database.";
        qDebug() << "Error message: " << db.lastError().text();  // Print detailed error message
    }
}

bool Connection::createConnection() {
    // Double-check the available drivers again
    qDebug() << "Checking available drivers again:" << QSqlDatabase::drivers();

    if (!db.isOpen()) {
        qDebug() << "Database is not open. Trying to reconnect...";
        if (!db.open()) {
            qDebug() << "Reconnection failed.";
            qDebug() << "Error message: " << db.lastError().text();
            return false;
        }
    }

    // Try to execute a simple query to verify connection
    qDebug() << "Executing test query to verify connection.";
    QSqlQuery query("SELECT 1");  // Simple query to check the connection
    if (!query.exec()) {
        qDebug() << "Error executing test query:" << query.lastError().text();
        return false;
    }

    qDebug() << "Database connection is valid.";
    return true;
}

Connection::~Connection() {
    // Close the database connection when the object is destroyed
    if (db.isOpen()) {
        db.close();
        qDebug() << "Database connection closed.";
    }
}
