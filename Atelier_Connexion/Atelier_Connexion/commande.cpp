#include "commande.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <QtNetwork>

Commande::Commande() {}

Commande::Commande(int num5,int prix5,int id_client5,QString type5,QString etat5,QDate date5)
{
    this->num5 = num5;
    this->id_client5 = id_client5;
    this->type5 = type5;
    this->etat5 = etat5;
    this->prix5 = prix5;
    this->date5 = date5;
}

bool Commande::ajouter5()
{

    QSqlQuery query;
    QString res7 = QString::number(num5);
    QString res8 = QString::number(prix5);
    QString res9 = QString::number(id_client5);
    query.prepare("INSERT INTO PROJETCPP2A26.GS_COMMANDE(NUM_COMMANDE, TYPE ,DATE_COMMANDE, PRIX_TOTALE, ETAT,ID_CLIENT ) values (:num_commande, :type, :date_commande, :prix_totale ,  :etat , :id_client )");
    query.bindValue(":num_commande",res7);
    query.bindValue(":etat",etat5);
    query.bindValue(":type",type5);
    query.bindValue(":prix",res8);
    query.bindValue(":id_client5",res9);
    query.bindValue(":date_commande", date5);


    return query.exec();
}

QSqlQueryModel * Commande::afficher5()
{
    QSqlQueryModel * model = new QSqlQueryModel();

    // Exécution de la requête pour récupérer tous les services
    model->setQuery("SELECT * FROM PROJETCPP2A26.GS_COMMANDE");

    // Vérification de l'erreur SQL
    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors de la récupération des données : " << model->lastError().text();
        return nullptr;  // Retourner nullptr si une erreur se produit
    }

    // Définir les en-têtes du modèle
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM_COMMANDE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE_COMMANDE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX_TOTALE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID_CLIENT"));

    return model;
}



bool Commande::supprimer5(int num5)
{
    QSqlQuery query;

    query.prepare("DELETE FROM PROJETCPP2A26.GS_COMMANDE WHERE NUM_COMMANDE = :num_commande");
    query.bindValue(":num_commande", num5);

    // Vérifier si la suppression a réussi
    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression du service : " << query.lastError().text();
        return false;
    }

    return true;
}

bool Commande::modifier5()
{
    QSqlQuery query;

    // Préparation des variables pour la requête
    query.prepare("UPDATE PROJETCPP2A26.GS_COMMANDE SET TYPE = :type, DATE_COMMANDE = :date_commande ,PRIX_totale = :prix_totale , ETAT = :etat , ID_CLIENT = :id_client WHERE NUM_COMMANDE = :num_commande");

    query.bindValue(":num_commande", num5);  // Lier l'entier id
    query.bindValue(":id_client", id_client5);  // Lier l'entier id_client
    query.bindValue(":prix_totale", prix5);  // Lier le prix directement
    query.bindValue(":date_commande", date5);  // Le pilote SQL gère la conversion de QDate en type SQL
    query.bindValue(":etat", etat5);
    query.bindValue(":type", type5);

    // Vérifier l'exécution de la requête
    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour du service : " << query.lastError().text();
        return false;
    }

    return true;
}

bool Commande::idExists5(int num5)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM PROJETCPP2A26.GS_COMMANDE WHERE NUM_COMMANDE = :num_commande");
    query.bindValue(":num_commande", num5);

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
