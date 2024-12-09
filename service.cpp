#include "service.h"
#include "email.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <QtNetwork>

Service::Service() {}

Service::Service(int id, int prix, QString id_client, int id_employe, QString nom, QString description, QDate date)
{
    this->id = id;
    this->id_client = id_client;
    this->id_employe = id_employe;
    this->nom = nom;
    this->description = description;
    this->prix = prix;
    this->date = date;
}

bool Service::ajouter()
{
    QString queryStr = "INSERT INTO GS_SERVICE (ID_SERVICE, NOM, DESCRIPTION, PRIX, DATE_ESTIME, ID_CLIENT, ID_EMPLOYE) "
                       "VALUES (:id, :nom, :description, :prix, :date, :id_client, :id_employe)";
    QSqlQuery query;
    query.prepare(queryStr);

    // Remplacer les paramètres par des valeurs réelles avant d'exécuter
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":description", description);
    query.bindValue(":prix", prix);
    query.bindValue(":date", date);
    query.bindValue(":id_client", id_client);
    query.bindValue(":id_employe", id_employe);

    if (query.exec()) {
        // Si l'ajout du service est réussi, envoyer un email
        QString destinataire = "destinataire@gmail.com";  // Remplacez par l'email réel du destinataire
        QString sujet = "Service ajouté avec succès";
        QString message = QString("Le service \"%1\" a été ajouté avec succès. Détails:\n"
                                  "Nom: %2\n"
                                  "Description: %3\n"
                                  "Prix: %4\n"
                                  "Date: %5")
                              .arg(nom)
                              .arg(nom)
                              .arg(description)
                              .arg(prix)
                              .arg(date.toString("yyyy-MM-dd"));

        if (Email::envoyerEmail(destinataire, sujet, message)) {
            // Afficher un message de confirmation dans l'interface utilisateur
            QWidget *mainWindow = QApplication::activeWindow();
            QMessageBox::information(mainWindow, "Succès", "Le service a été ajouté avec succès et un email a été envoyé.");
        }

        return true;
    } else {
        // Afficher un message d'erreur si l'ajout échoue
        QWidget *mainWindow = QApplication::activeWindow();
        QMessageBox::critical(mainWindow, "Erreur", "Erreur lors de l'ajout du service : " + query.lastError().text());
        return false;
    }
}


QSqlQueryModel * Service::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();

    // Exécution de la requête pour récupérer tous les services
    model->setQuery("SELECT * FROM GS_SERVICE");

    // Vérification de l'erreur SQL
    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors de la récupération des données : " << model->lastError().text();
        return nullptr;  // Retourner nullptr si une erreur se produit
    }

    // Définir les en-têtes du modèle
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID_CLIENT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ID_EMPLOYE"));

    return model;
}



bool Service::supprimer(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM GS_SERVICE WHERE ID_SERVICE = :id");
    query.bindValue(":id", id);

    // Vérifier si la suppression a réussi
    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression du service : " << query.lastError().text();
        return false;
    }

    return true;
}

bool Service::modifier()
{
    QSqlQuery query;

    // Préparation des variables pour la requête
    query.prepare("UPDATE GS_SERVICE SET PRIX = :prix, NOM = :nom, DESCRIPTION = :description, DATE_ESTIME = :date , ID_CLIENT = :id_client, ID_EMPLOYE = :id_employe WHERE ID_SERVICE = :id");

    query.bindValue(":id", id);  // Lier l'entier id
    query.bindValue(":id_employe", id_employe);  // Lier l'entier id_employe
    query.bindValue(":id_client", id_client);  // Lier l'entier id_client
    query.bindValue(":prix", prix);  // Lier le prix directement
    query.bindValue(":date", date);  // Le pilote SQL gère la conversion de QDate en type SQL
    query.bindValue(":nom", nom);
    query.bindValue(":description", description);

    // Vérifier l'exécution de la requête
    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour du service : " << query.lastError().text();
        return false;
    }

    return true;
}

bool Service::idExists(int id)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM GS_SERVICE WHERE ID_SERVICE = :id");
    query.bindValue(":id", id);

    // Exécuter la requête et vérifier si elle a réussi
    if (query.exec()) {
        if (query.next()) {
            int count = query.value(0).toInt();
            return count > 0;  // Retourner true si l'ID existe
        }
    } else {
        qDebug() << "Erreur lors de la vérification de l'existence de l'ID : " << query.lastError().text();
    }

    return false;  // Retourner false si aucune correspondance trouvée ou en cas d'erreur
}
