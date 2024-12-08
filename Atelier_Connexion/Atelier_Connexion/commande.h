#ifndef COMMANDE_H
#define COMMANDE_H
#include <QObject>
#include <QWidget>
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDate>

class Commande
{
    QString type5,etat5;
    int num5,id_client5,prix5;
    QDate date5;
public:
    Commande();
    Commande(int num5,int prix5,int id_client5 ,QString type5,QString etat5,QDate date5);

    QString getType5(){return type5;}
    QString getEtat5(){return etat5;}
    int getNUM5(){return num5;}
    int getID_CLIENT5(){return id_client5;}
    int getPrix5(){return prix5;}
    QDate getDate5(){return date5;}

    void setType5(QString t){type5=t;}
    void setEtat5(QString e){etat5=e;}
    void setNUM5(int num5){this->num5=num5;}
    void setID_CLIENT5(int id_client5){this->id_client5=id_client5;}
    void setPrix5(int prix5){this->prix5=prix5;}
    void setDate5(QDate date5){this->date5=date5;}

    bool ajouter5();

    QSqlQueryModel * afficher5();
    bool supprimer5(int num5);
    bool modifier5();
    bool idExists5(int num5);


};
#endif // COMMANDE_H
