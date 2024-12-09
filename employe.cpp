#include "employe.h"
#include "QSqlError"
#include <QApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QPdfWriter>
#include <QPainter>
#include <QBuffer>
#include <QByteArray>
#include <QFileDialog>
#include <QHeaderView>
#include<QMessageBox>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qscrollarea.h>
#include <qtextedit.h>
Employe::Employe() {}
Employe::Employe(int id2 ,int salaire , QString nom2, QString prenom2,QString poste){

    this->id2=id2;
    this->nom2=nom2;
    this->prenom2=prenom2;
    this->salaire=salaire;
    this->poste=poste;

}

bool Employe::ajouter2() {
    QSqlQuery query;
    QString res5 = QString::number(id2);
    QString sal = QString::number(salaire);
    query.prepare("INSERT INTO PROJETCPP2A26.GS_EMPLOYE (ID, NOM, PRENOM, SALAIRE, POSTE) VALUES (:id, :nom, :prenom, :salaire , :poste )");
    query.bindValue(":id", res5);
    query.bindValue(":nom", nom2);
    query.bindValue(":prenom", prenom2);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", sal);
    return query.exec();
}

bool Employe::supprimer2(int id2 ){
    QSqlQuery query ;
    QString res5 = QString::number(id2);
    query.prepare("delete from PROJETCPP2A26.GS_EMPLOYE where ID= :id ");
    query.bindValue(":id",res5);
    return query.exec();

}
QSqlQueryModel* Employe::afficher2()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("select * from PROJETCPP2A26.GS_EMPLOYE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("POSTE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));

    return model;
}

bool Employe::modifier2() {
    QSqlQuery query;
    QString res5 = QString::number(id2);
    QString sal = QString::number(salaire);

    query.prepare("UPDATE PROJETCPP2A26.GS_EMPLOYE SET SALAIRE = :salaire, NOM = :nom, PRENOM = :prenom, POSTE = :poste WHERE ID = :id");
    query.bindValue(":id", res5);
    query.bindValue(":nom", nom2);
    query.bindValue(":prenom", prenom2);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", sal);
    return query.exec();

}
bool Employe::idExists2(int id2) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM PROJETCPP2A26.GS_EMPLOYE WHERE ID = :id"); // Assuming your table is named 'employees' and the column is 'id'
    query.bindValue(":id", id2);

    if (query.exec()) {
        if (query.next()) {
            int count = query.value(0).toInt();
            return count > 0; // Return true if count is greater than 0
        }
    }

    return false; // Return false if query execution fails or no records found
}


Employe Employe::recupere(int id2) {
    // Initialize variables
    QString nom2 = "";
    QString prenom2 = "";
    double salaire = 0.0;
    QString poste = "";

    QSqlQuery query;
    query.prepare("SELECT * FROM PROJETCPP2A26.GS_EMPLOYE WHERE ID = :id"); // Modify the query as per your schema
    query.bindValue(":id", id2);

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return Employe(); // Returning an empty object if query execution fails
    }

    // Step 3: Retrieve the result
    if (query.next()) {
        // Assuming your table has columns like "name", "address", "phone"
        nom2 = query.value("NOM").toString();        // Correct for string
        prenom2 = query.value("PRENOM").toString();     // Correct for string
        salaire = query.value("SALAIRE").toDouble();   // Correct for double
        poste = query.value("POSTE").toString();     // Correct for string
    } else {
        qDebug() << "No record found with ID:" << id2;
    }

    // Return the populated employee object
    Employe E1(id2, salaire, nom2, prenom2, poste);
    return E1;
}
void calculatePostStatistics(QTableView *tableView) {
    // Get the model from the table view
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(tableView->model());
    if (!model) {
        qWarning() << "Invalid model";
        return;
    }

    // Create a map to store the count of each post
    QMap<QString, int> postCountMap;

    // Get the index of the "POST" column
    int postColumnIndex = 4; // Assuming the "POST" column is the 5th column (index 4)

    // Iterate through the rows of the model
    for (int row = 0; row < model->rowCount(); ++row) {
        // Get the data in the "POST" column
        QModelIndex index = model->index(row, postColumnIndex);
        QString post = model->data(index).toString();

        // Update the count in the map
        if (postCountMap.contains(post)) {
            postCountMap[post]++;
        } else {
            postCountMap[post] = 1;
        }
    }

    // Print the statistics
    QMapIterator<QString, int> i(postCountMap);
    while (i.hasNext()) {
        i.next();
        qDebug() << "Post:" << i.key() << ", Count:" << i.value();
    }
}


bool Employe::sendMessagePrivate(const QString& senderNom, const QString& senderPrenom, const QString& receiverNom, const QString& receiverPrenom, const QString& message) {
    QSqlQuery query;

    // Get the current date and time
    QDate today = QDate::currentDate();
    QTime currentTime = QTime::currentTime();

    // Format date and time as dd/MM/yyyy HH:mm:ss
    QString formattedDateTime = today.toString("dd/MM/yyyy") + " " + currentTime.toString("HH:mm:ss");

    // Format the private message for the sender
    QString formattedSenderMessage =  formattedDateTime + " [PRIVATE] [" + receiverNom + " " + receiverPrenom + "] " + message + "\n";

    // Update sender's sent messages with date, time, and private tag
    query.prepare("UPDATE PROJETCPP2A26.GS_EMPLOYE SET MESSAGES_ENVOYEES = NVL(MESSAGES_ENVOYEES, '') || :message WHERE NOM = :senderNom AND PRENOM = :senderPrenom");
    query.bindValue(":senderNom", senderNom);
    query.bindValue(":senderPrenom", senderPrenom);
    query.bindValue(":message", formattedSenderMessage);

    if (!query.exec()) {
        qDebug() << "Error updating sender's messages:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Error", "Error updating sender's messages: " + query.lastError().text());
        return false;
    }
    QMessageBox::information(nullptr, "Sender Update", "Sender's messages updated successfully."); // Debug message

    // Format the private message for the receiver
    QString formattedReceiverMessage = formattedDateTime + " [PRIVATE] " + message + "\n";

    // Update receiver's received messages with date, time, and private tag
    query.prepare("UPDATE PROJETCPP2A26.GS_EMPLOYE SET MESSAGES_RECUS = NVL(MESSAGES_RECUS, '') || :message WHERE NOM = :receiverNom AND PRENOM = :receiverPrenom");
    query.bindValue(":message", formattedReceiverMessage);
    query.bindValue(":receiverNom", receiverNom);
    query.bindValue(":receiverPrenom", receiverPrenom);

    if (!query.exec()) {
        qDebug() << "Error updating receiver's messages:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Error", "Error updating receiver's messages: " + query.lastError().text());
        return false;
    }
    QMessageBox::information(nullptr, "Receiver Update", "Receiver's messages updated successfully."); // Debug message

    return true;
}


bool Employe::sendMessageGeneral(const QString& senderNom, const QString& senderPrenom, const QString& message) {
    QSqlQuery query;

    // Get the current date and time
    QDate today = QDate::currentDate();
    QTime currentTime = QTime::currentTime();

    // Format date and time as dd/MM/yyyy HH:mm:ss
    QString formattedDateTime = today.toString("dd/MM/yyyy") + " " + currentTime.toString("HH:mm:ss");

    // Update sender's sent messages with date and time
    query.prepare("UPDATE PROJETCPP2A26.GS_EMPLOYE SET MESSAGES_ENVOYEES = NVL(MESSAGES_ENVOYEES, '') || :message WHERE NOM = :senderNom AND PRENOM = :senderPrenom");
    query.bindValue(":senderNom", senderNom);
    query.bindValue(":senderPrenom", senderPrenom);
    query.bindValue(":message", formattedDateTime + " [GENERAL] " + message + "\n");

    if (!query.exec()) {
        qDebug() << "Error updating sender's sent messages:" << query.lastError();
        return false;
    }

    // Update all other recipients' received messages with date and time
    query.prepare(
        "UPDATE PROJETCPP2A26.GS_EMPLOYESET MESSAGES_RECUS = NVL(MESSAGES_RECUS, '') || :message "
        "WHERE NOT (NOM = :senderNom AND PRENOM = :senderPrenom)"
        );
    query.bindValue(":message", formattedDateTime + " [GENERAL from " + senderNom + " " + senderPrenom + "] " + message + "\n");
    query.bindValue(":senderNom", senderNom);
    query.bindValue(":senderPrenom", senderPrenom);

    if (!query.exec()) {
        qDebug() << "Error updating recipients' messages:" << query.lastError();
        return false;
    }

    return true;
}


QString Employe::getMessagesPrivate(const QString& currentUserNom, const QString& currentUserPrenom) {
    QSqlQuery query;
    QString messages;

    // Fetch sent messages
    query.prepare("SELECT MESSAGES_ENVOYEES FROM PROJETCPP2A26.GS_EMPLOYE WHERE NOM = :currentUserNom AND PRENOM = :currentUserPrenom");
    query.bindValue(":currentUserNom", currentUserNom);
    query.bindValue(":currentUserPrenom", currentUserPrenom);

    if (!query.exec()) {
        qDebug() << "Error executing query for sent messages:" << query.lastError().text();
        return QString();
    }

    if (query.next()) {
        QString messagesEnvoyees = query.value(0).toString();

        if (!messagesEnvoyees.isEmpty()) {
            QStringList messageList = messagesEnvoyees.split("\n", Qt::SkipEmptyParts);
            for (const QString& message : messageList) {
                if (message.contains("[PRIVATE]")) {
                    messages += "[You] " + message.trimmed() + "\n";
                }
            }
        }
    }

    // Fetch received messages
    query.prepare("SELECT NOM, PRENOM, MESSAGES_RECUS FROM PROJETCPP2A26.GS_EMPLOYE");
    if (!query.exec()) {
        qDebug() << "Error executing query for received messages:" << query.lastError().text();
        return QString();
    }

    while (query.next()) {
        QString senderNom = query.value(0).toString();
        QString senderPrenom = query.value(1).toString();
        QString messagesRecus = query.value(2).toString();

        if (!messagesRecus.isEmpty()) {
            QStringList messageList = messagesRecus.split("\n", Qt::SkipEmptyParts);
            for (const QString& message : messageList) {
                if (message.contains("[PRIVATE]") && message.contains(currentUserNom + " " + currentUserPrenom)) {
                    QString formattedMessage = "[" + senderNom + " " + senderPrenom + "] " + message.trimmed();
                    messages += formattedMessage + "\n";
                }
            }
        }
    }

    qDebug() << "Private Messages Retrieved:" << messages;
    return messages.trimmed();
}


QString Employe::getMessagesPublic(const QString& currentUserNom, const QString& currentUserPrenom) {
    QSqlQuery query;
    query.prepare("SELECT NOM, PRENOM, MESSAGES_ENVOYEES FROM PROJETCPP2A26.GS_EMPLOYE");

    QString messages;

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return QString();
    }

    while (query.next()) {
        QString senderNom = query.value(0).toString();
        QString senderPrenom = query.value(1).toString();
        QString messagesEnvoyees = query.value(2).toString();

        // Check if the sender has any sent messages
        if (!messagesEnvoyees.isEmpty()) {
            // Split the messages into individual lines
            QStringList messageList = messagesEnvoyees.split("\n", Qt::SkipEmptyParts);

            // Only consider messages if there are more than one (i.e., they are properly separated)
            if (messageList.size() > 1) {
                for (const QString& message : messageList) {
                    // Format the message
                    QString formattedMessage;

                    if (senderNom == currentUserNom && senderPrenom == currentUserPrenom) {
                        // If the sender is the current user, format as "[You]"
                        formattedMessage = "[You] " + message.trimmed();
                    } else {
                        // Otherwise, include the sender's full name
                        formattedMessage = "[" + senderNom + " " + senderPrenom + "] " + message.trimmed();
                    }

                    messages += formattedMessage + "\n";
                }
            }
        }
    }

    qDebug() << "Public Messages Retrieved:" << messages;
    return messages.trimmed(); // Ensure no trailing new lines
}













void Employe::showMessages(QScrollArea* scrollArea, const QString& messages) {
    QWidget* container = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(container);

    for (const QString& message : messages.split("\n", Qt::SkipEmptyParts)) {
        QLabel* label = new QLabel(message);
        label->setWordWrap(true);
        layout->addWidget(label);
    }

    container->setLayout(layout);
    scrollArea->setWidget(container);
    scrollArea->setWidgetResizable(true);
}



