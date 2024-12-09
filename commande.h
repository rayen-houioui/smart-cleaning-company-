#ifndef COMMANDE_H
#define COMMANDE_H
#include<Qstring>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include"QDate"
#include<QStandardItemModel>
class Commande
{
private:
    QString code;
    QDate date_commande;
    float prix_total;
    QString etat,type,id_client;

public:
    QString nomClient;
    QString message;
    //constructeurs
    Commande();
    Commande(QString code,QString type,QDate date_commande, float prix, QString etat,QString id_client);

    //getters
    QString getEtat(){return etat;}
    QString getType(){return type;}
    float getPrixtotal(){return prix_total;}
    QString getcode(){return code;}
    QString getid_client(){return id_client;}
    QDate getDate(){return date_commande;}
    //setters
    void setEtat(QString eta){etat=eta;}
    void setType(QString typ){type=typ;}
    void setPrixtotal(float pri){prix_total=pri;}
    void setcode(QString num){code=num;}
    void setid_client(QString num){id_client=num;}
    void setDate(QDate dte){date_commande=dte;}
    //functions
    bool ajouter();
    bool supprimer(QString id);
    //QSqlQueryModel *afficher();
    QStandardItemModel *afficher();
     static QString recupererIdClient(const QString &idCommande);




};

#endif // COMMANDE_H
