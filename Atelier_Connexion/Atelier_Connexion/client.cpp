#include "client.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>

using namespace std;

Client::Client() {}
Client::Client(int id1,int telephone,QString nom1,QString prenom,QString adresse,QString e_mail)
{
    this->id1=id1;
    this->nom1=nom1;
    this->prenom=prenom;
    this->adresse=adresse;
    this->telephone=telephone;
    this->e_mail=e_mail;
}

bool Client::ajouter1()
{
    QSqlQuery query;
    QString res3 = QString::number(id1);
    QString res4 = QString::number(telephone);
    query.prepare("INSERT INTO PROJETCPP2A26.GS_CLIENT(ID, NOM, PRENOM, ADRESSE,TELEPHONE,E_MAIL ) values (:id, :nom, :prenom,  :adresse, :telephone, :e_mail )");
    query.bindValue(":id",res3);
    query.bindValue(":nom",nom1);
    query.bindValue(":prenom",prenom);
    query.bindValue(":adresse",adresse);
    query.bindValue(":telephone",res4);
    query.bindValue(":e_mail",e_mail);


    return query.exec();

}
QSqlQueryModel * Client::afficher1()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select *from PROJETCPP2A26.GS_CLIENT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("TELEPHONE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("E_MAIL"));

    return model;
}
bool Client::supprimere(int id1)
{

    QSqlQuery query;
    //  QString res=QString::number(id);
    query.prepare("DELETE FROM PROJETCPP2A26.GS_CLIENT WHERE ID = :id");

    // Lier le paramètre :id à la valeur de la variable 'id'
    query.bindValue(":id", id1); // 'id' est la variable qui contient la valeur à supprimer

    return query.exec();
}

bool Client::modifier(QString &errorMsg) {
    QSqlQuery query;
    QString res3 = QString::number(id1);  // Convertir l'ID en chaîne
    QString res4 = QString::number(telephone);  // Convertir le téléphone en chaîne

    query.prepare("UPDATE PROJETCPP2A26.GS_CLIENT SET nom1 = :NOM, prenom = :PRENOM, adresse = :ADRESSE, "
                  "telephone = :TELEPHONE, e_mail = :E_MAIL WHERE id1 = :ID");  // Ajout du WHERE

    query.bindValue(":ID", res3);  // Lier l'ID
    query.bindValue(":NOM", nom1);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":ADRESSE", adresse);
    query.bindValue(":TELEPHONE", res4);
    query.bindValue(":E_MAIL", e_mail);

    if (!query.exec()) {
        errorMsg = query.lastError().text();  // Enregistrer l'erreur SQL dans le message
        return false;
    }

    return true;
}


QSqlQueryModel *Client::trier_nom()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PROJETCPP2A26.GS_CLIENT ORDER BY LOWER(NOM) asc;");

    if (model->lastError().isValid()) {
        qDebug() << "Erreur SQL : " << model->lastError().text();
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("e_mail"));

    return model;
}
QSqlQueryModel *Client::trier_id()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PROJETCPP2A26.GS_CLIENT ORDER BY ID ASC;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("e_mail"));

    return model;
}

QSqlQueryModel *Client::trier_adresse()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PROJETCPP2A26.GS_CLIENT ORDER BY LOWER(ADRESSE) asc;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("e_mail"));

    return model;
}

QSqlQueryModel* Client::trier_Denom()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PROJETCPP2A26.GS_CLIENT ORDER BY LOWER(NOM) desc;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("e_mail"));

    return model;
}
QSqlQueryModel* Client::trier_Deid()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PROJETCPP2A26.GS_CLIENT ORDER BY ID DESC;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("e_mail"));

    return model;
}

QSqlQueryModel *Client::trier_Deadresse()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PROJETCPP2A26.GS_CLIENT ORDER BY LOWER(ADRESSE) desc;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("e_mail"));


    return model;
}



bool Client::idExist(int id1)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM  PROJETCPP2A26.GS_CLIENT WHERE ID= :id1"); // Assuming your table is named 'services' and the column is 'id'
    query.bindValue(":id1", id1);

    if (query.exec()) {
        if (query.next()) {
            int count = query.value(0).toInt();
            return count > 0; // Return true if count is greater than 0
        }
    }

    return false; // Return false if query execution fails or no records found
}

QSqlQueryModel* Client::getMostUsedClient()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM  PROJETCPP2A26.GS_CLIENT WHERE used_count > 0 ORDER BY used_count DESC"); // Exemple de requête
    if (query.exec()) {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(query);
        qDebug() << "Requête réussie, nombre de lignes récupérées: " << model->rowCount();
        return model;
    } else {
        qDebug() << "Erreur de requête : " << query.lastError().text();
        return nullptr;  // Retourne nullptr si la requête échoue
    }
}
