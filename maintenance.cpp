#include "maintenance.h"
#include<QString>
#include<QDate>
#include<QSqlQuery>
#include<QSqlQueryModel>
Maintenance::Maintenance()
{
    id=0;
    date = QDate::currentDate();
    etat="";
    nom="";
    description="";
    duree=0;

}
Maintenance::Maintenance(int num,QString nom,QString description,QDate date, int duree, QString etat){
    id=num;
    this->nom=nom;
    this->description=description;
    this->date=date;
    this->duree=duree;
    this->etat=etat;

}
bool Maintenance::ajouter()
{
    QSqlQuery query;

    query.prepare("insert into gs_maintenance (id, nom,description,datee, duree, etat) "
                  "values (:id, :nom, :description, :date, :duree, :etat)");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":description",description);
    query.bindValue(":duree",duree);
    query.bindValue(":etat",etat);
    query.bindValue(":date",date.toString("yyyy-MM-dd"));

    return query.exec();

}
bool Maintenance::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("delete from gs_maintenance WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();

}
QSqlQueryModel * Maintenance ::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from gs_maintenance");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("description"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("duree"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("etat"));

    return model;

}
