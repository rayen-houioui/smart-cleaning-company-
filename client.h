#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QWidget>
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDate>

class Client
{
    QString nom1, prenom,adresse,e_mail;
    int id1,telephone;
public:
    Client();
    Client(int id1,int telephone,QString nom1,QString prenom,QString adresse,QString e_mail);

    QString getNom1(){return nom1;}
    QString getPRENOM(){return prenom;}
    int getID1(){return id1;}
    int getTELEPHONE(){return telephone;}
    QString getADRESSE(){return adresse;}
    QString getE_mail(){return e_mail;}

    void setNom1(QString n1){nom1=n1;}
    void setPRENOM(QString p){prenom=p;}
    void setID1(int id1){this->id1=id1;}
    void setTELEPHONE(int telephone){this->telephone=telephone;}
    void setADRESSE(QString a){this->adresse=a;}
    void setE_MAIL(QString e){this->e_mail=e;}

    bool ajouter1();

    QSqlQueryModel * afficher1();
    bool supprimere(int id1);
    bool modifier(QString &errorMsg);
    bool idExist(int id1);
    QSqlQueryModel* getMostUsedClient();

    QSqlQueryModel * trier_nom();
    QSqlQueryModel * trier_id();
    QSqlQueryModel * trier_adresse();

    QSqlQueryModel *trier_Denom();
    QSqlQueryModel *trier_Deid();
    QSqlQueryModel *trier_Deadresse();
};

#endif // CLIENT_H
