#include "produit.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <QtNetwork>


Produit::Produit() {}
Produit::Produit( QString nom7,int id7,int prix_v ,int prix_a,int quantite)
{
    this->id7=id7;
    this->nom7=nom7;
    this->prix_v=prix_v;
    this->prix_a=prix_a;
    this->quantite=quantite;
}
bool Produit::ajouter7()
{
    QSqlQuery query;
    QString res12 = QString::number(id7);
    QString res13 = QString::number(prix_v);
    QString res14 = QString::number(prix_a);
    QString res15 = QString::number(quantite);
    // Conversion de id_client en QString
    query.prepare("INSERT INTO PROJETCPP2A26.GS_PRODUIT(ID_PRODUIT, NOM, PRIX_ACHAT, PRIX_VENTE, QUANTITE) values (:id, :nom, :prix_a,  :prix_v, :quantite  )");
    query.bindValue(":id",res12);
    query.bindValue(":prix_v",res13);
    query.bindValue(":prix_a",res14);
    query.bindValue(":nom",nom7);             // Utilisation de res2 qui est maintenant un QString
    query.bindValue(":quantite", res15);
    return query.exec();

}
QSqlQueryModel * Produit::afficher7()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select *from PROJETCPP2A26.GS_PRODUIT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_PRODUIT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRIX_ACHAT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRIX_VENTE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("QUANTITE"));
    return model;
}
bool Produit::supprimer7(int id7)
{

    QSqlQuery query;
    //  QString res=QString::number(id);
    query.prepare("DELETE FROM PROJETCPP2A26.GS_PRODUIT WHERE ID_PRODUIT = :id");

    // Lier le paramètre :id à la valeur de la variable 'id'
    query.bindValue(":id", id7); // 'id' est la variable qui contient la valeur à supprimer

    return query.exec();
}

//bool Service::modifier(int id, int nouveauPrix, int nouvelleDate, const QString &nouveauNom, const QString &nouvelleDescription) {
// Vérifiez si l'ID correspond à l'ID du service actuel
//if (this->id == id) {
// Mettez à jour les valeurs
//prix = nouveauPrix;
//date = nouvelleDate;
//nom = nouveauNom;
//description = nouvelleDescription;

// Si vous travaillez avec une base de données, effectuez ici les opérations de mise à jour
// par exemple : exécuter une requête SQL pour mettre à jour les données

//  return true; // Indique que la mise à jour a réussi
//}
// return false; // Indique que l'ID ne correspond pas
//}
bool Produit::modifier7() {
    QSqlQuery query;
    QString res12 = QString::number(id7);
    QString res13 = QString::number(prix_v);
    QString res14 = QString::number(prix_a);
    QString res15 = QString::number(quantite);
    // id_client est déjà un entier, conversion en QString
    query.prepare("UPDATE FROM PROJETCPP2A26.GS_PRODUIT SET NOM = :nom, PRIX_ACHAT = :prix_a, PRIX_VENTE = :prix_v, QUANTITE = :quantite,  WHERE ID_PRODUIT = :id");
    query.bindValue(":id",res12);
    query.bindValue(":prix_v",res13);
    query.bindValue(":prix_a",res14);
    query.bindValue(":nom",nom7);             // Utilisation de res2 qui est maintenant un QString
    query.bindValue(":quantite", res15);
    return query.exec();

}


bool Produit::idExists7(int id7) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM  PROJETCPP2A26.GS_PRODUIT  WHERE ID_PRODUIT = :id"); // Assuming your table is named 'services' and the column is 'id'
    query.bindValue(":id", id7);

    if (query.exec()) {
        if (query.next()) {
            int count = query.value(0).toInt();
            return count > 0; // Return true if count is greater than 0
        }
    }

    return false; // Return false if query execution fails or no records found
}


