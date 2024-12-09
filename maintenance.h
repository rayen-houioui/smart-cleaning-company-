#ifndef MAINTENANCE_H
#define MAINTENANCE_H
#include"QDate"
#include<QSqlQuery>
#include<QSqlQueryModel>
#include"QString"



class Maintenance
{
private:
    int id,duree;
    QDate date;
    QString etat,nom,description;
public:
    //constructeurs
    Maintenance();
    Maintenance(int num, QString nom, QString description, QDate date, int duree, QString etat);

    //getters
    QString getEtat(){return etat;}
    QString getNom(){return nom;}
    QString getDescription(){return description;}
    int getid(){return id;}
    int getduree(){return duree;}
    QDate getDate(){return date;}
    //setters
    void setEtat(QString eta){etat=eta;}
    void setNom(QString nomm){nom=nomm;}
    void setDescription(QString descri){description=descri;}
    void setid(int num){id=num;}
    void setduree(int dure){duree=dure;}
    void setDate(QDate dte){date=dte;}
    //functions
    bool ajouter();
    bool supprimer(int id);
    QSqlQueryModel *afficher();
};

#endif // MAINTENANCE_H
