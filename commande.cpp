#include "commande.h"
#include<Qstring>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDateTime>
#include<QStandardItemModel>
#include<QPainter>
Commande::Commande()
{
    code="";
    id_client="";
    date_commande = QDate::currentDate();
    etat="";
    type="";
    prix_total=0;
}
Commande::Commande(QString num,QString type,QDate date_commande, float prix, QString etat,QString id_client){
    code=num;
    this->type=type;
    this->date_commande=date_commande;
    prix_total=prix;
    this->etat=etat;
    this->id_client=id_client;

}
bool Commande::ajouter()
{
    QSqlQuery query;

    query.prepare("insert into gs_commande (code, type,date_commande, prix_total, etat,id_client) "
                  "values (:code, :type, :date_commande, :prix_total, :etat, :id_client)");
    query.bindValue(":code",code);
    query.bindValue(":type",type);
    query.bindValue(":etat",etat);
    query.bindValue(":prix_total",prix_total);
    query.bindValue(":date_commande",date_commande);
    query.bindValue(":id_client",id_client);


    return query.exec();

}
bool Commande::supprimer(QString code)
{
    QSqlQuery query;
    query.prepare("delete from gs_commande where code= :code");
    query.bindValue(":code",code);
    return query.exec();

}

QStandardItemModel *Commande::afficher()
{
    QStandardItemModel *model = new QStandardItemModel();

    QSqlQuery query;
    query.prepare("SELECT gs_commande.code, "
                  "gs_client.nom || ' ' || gs_client.prenom AS client, "

                  "gs_commande.type, "
                  "gs_commande.date_commande, "
                  "gs_commande.prix_total, "
                  "gs_commande.etat "
                  "FROM gs_commande "
                  "INNER JOIN gs_client ON gs_commande.id_client = gs_client.id");

    query.exec();

    model->setHorizontalHeaderLabels({"Code", "Client", "Type", "Date Commande", "Prix Total", "État actuel"});

    while (query.next()) {
        QList<QStandardItem*> row;

        row.append(new QStandardItem(query.value(0).toString())); // Code
        row.append(new QStandardItem(query.value(1).toString())); // Client
        row.append(new QStandardItem(query.value(2).toString())); // Type


        QDate dateCommande = query.value(3).toDate();
        row.append(new QStandardItem(dateCommande.toString("dd/MM/yyyy")));

        row.append(new QStandardItem(query.value(4).toString())); // Prix total

        QString etat = query.value(5).toString();
        QStandardItem* etatItem = new QStandardItem(etat);


        QPixmap pixmap(20, 20);
        pixmap.fill(Qt::transparent);

        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(Qt::transparent);
        painter.setPen(Qt::NoPen);

        if (etat == "terminee") {
            painter.setBrush(QBrush(Qt::darkGreen));
        } else if (etat == "en cours") {
            painter.setBrush(QBrush(Qt::yellow));
        } else if (etat == "annulee") {
            painter.setBrush(QBrush(Qt::red));
        }


        painter.drawEllipse(0, 0, 12, 12);

        painter.end();
        QIcon icon(pixmap);
        etatItem->setIcon(icon);

        row.append(etatItem);

        model->appendRow(row);


    }

    return model;
}

QString Commande::recupererIdClient(const QString &idCommande) {
    QSqlQuery query;
    query.prepare("SELECT id_client FROM gs_commande WHERE code = :code");
    query.bindValue(":code", idCommande);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }

    return "";
}



