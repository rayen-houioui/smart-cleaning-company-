#ifndef SERVICE_H
#define SERVICE_H
#include <QObject>
#include <QWidget>
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDate>

class Service
{
    QString nom, description;
    QDate date;
    int id,prix,id_employe,id_client;
public:
    Service();
    Service(int id,int prix,int id_client,int id_employe,QString nom,QString description,QDate date);

    QString getNom(){return nom;}
    QString getDescription(){return description;}
    int getID(){return id;}
    int getID_EMPLOYE(){return id_employe;}
    int getID_CLIENT(){return id_client;}
    int getPrix(){return prix;}
    QDate getDate(){return date;}

    void setNom(QString n){nom=n;}
    void setDescription(QString d){description=d;}
    void setID(int id){this->id=id;}
    void setID_EMPLOYE(int id_employe){this->id_employe=id_employe;}
    void setID_CLIENT(int id_client){this->id_client=id_client;}
    void setPrix(int prix){this->prix=prix;}
    void setDate(QDate date){this->date=date;}

    bool ajouter();

    QSqlQueryModel * afficher();
    bool supprimer(int id);
    bool modifier();
    bool idExists(int id);

};

#endif // SERVICE_H
