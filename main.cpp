#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"
#include "connection.h"
#include <QSqlDatabase>
#include <qsqlerror.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    qDebug() << "Application started";
    qDebug() << "Available drivers:" << QSqlDatabase::drivers();

    Connection c;
    qDebug() << "Attempting to establish database connection";
    bool test = c.createConnection();

    if (test) {
        qDebug() << "Database connection successful";
    } else {
        qDebug() << "Database connection failed";
        qDebug() << "Detailed error message: " << QSqlDatabase::database().lastError().text();
    }

    qDebug() << "Creating MainWindow instance";
    MainWindow w;

    qDebug() << "Showing main window";
    w.show();

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Database is open"), QObject::tr("Connection successful.\nClick Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"), QObject::tr("Connection failed.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

    qDebug() << "Entering application event loop";
    return app.exec();
}
