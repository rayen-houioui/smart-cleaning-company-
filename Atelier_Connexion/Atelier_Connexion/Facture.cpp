#include "facture.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Facture::Facture() {}

Facture::Facture(int id_facture, int id_client, double montant, QDate date_emise)
    : id_facture(id_facture), id_client(id_client), montant(montant), date_emise(date_emise) {}

bool Facture::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO GS_FACTURE (ID_FACTURE, ID_CLIENT, MONTANT, DATE_EMISE) "
                  "VALUES (:id_facture, :id_client, :montant, :date_emise)");

    query.bindValue(":id_facture", id_facture);
    query.bindValue(":id_client", id_client);
    query.bindValue(":montant", montant);
    query.bindValue(":date_emise", date_emise);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur lors de l'ajout de la facture : " << query.lastError().text();
        return false;
    }
}

QSqlQueryModel* Facture::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM GS_FACTURE");

    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors de la récupération des factures : " << model->lastError().text();
        return nullptr;
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FACTURE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_CLIENT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("MONTANT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_EMISE"));
    return model;
}

bool Facture::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM GS_FACTURE WHERE ID_FACTURE = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression de la facture : " << query.lastError().text();
        return false;
    }

    return true;
}

bool Facture::modifier() {
    QSqlQuery query;
    query.prepare("UPDATE GS_FACTURE SET ID_CLIENT = :id_client, MONTANT = :montant, DATE_EMISE = :date_emise "
                  "WHERE ID_FACTURE = :id_facture");

    query.bindValue(":id_facture", id_facture);
    query.bindValue(":id_client", id_client);
    query.bindValue(":montant", montant);
    query.bindValue(":date_emise", date_emise);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour de la facture : " << query.lastError().text();
        return false;
    }

    return true;
}

bool Facture::idExists(int id) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM GS_FACTURE WHERE ID_FACTURE = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.next()) {
            return query.value(0).toInt() > 0;
        }
    }

    return false;
}
