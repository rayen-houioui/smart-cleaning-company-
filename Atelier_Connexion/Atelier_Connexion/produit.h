#ifndef PRODUIT_H
#define PRODUIT_H
#include <QObject>
#include <QWidget>
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QDate>

class Produit
{
    QString nom7;
    int id7,prix_v,prix_a,quantite;
public:
    Produit();
    Produit( QString nom7,int id7,int prix_v ,int prix_a,int quantite);

    QString getNom7(){return nom7;}
    int getID7(){return id7;}
    int getPrix_v(){return prix_v;}
    int getPrix_a(){return prix_a;}
    int getQuantite(){return quantite;}
    void setNom7(QString n7){nom7=n7;}
    void setID7(int id7){this->id7=id7;}
    void setPrix_v(int prix_v){this->prix_v=prix_v;}
    void setPrix_a(int prix_a){this->prix_a=prix_a;}
    void setQuantite(int quantite){this->quantite=quantite;}

    bool ajouter7();

    QSqlQueryModel * afficher7();
    bool supprimer7(int id7);
    bool modifier7();
    bool idExists7(int id7);

};
#endif // PRODUIT_H
