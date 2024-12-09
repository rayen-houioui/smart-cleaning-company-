#ifndef PRODUIT_H_INCLUDED
#define PRODUIT_H_INCLUDED
#include<QString>
#include<QsqlQuery>
#include<QsqlQueryModel>
class produit

{
private:


    QString nom;
    int id,quantite;
    float prixdachat,prixdevente;

public:
    produit();
    produit(QString,int,int,float,float);
    void setid(int i);
    void setnom(QString n);
    void setprixdevente(float pv);
    void setprixdachat(float pa);
    void setquantite(int q);



    int getid();
    QString getnom();
    int  getquantite();
    float getprixdachat();
    float getprixdevente();



    bool Ajouter();
    QSqlQueryModel* Afficher();
    bool Supprimer(int id);
    bool Modifier();
    bool rechercherParId(int id);
    bool rechercherParNom(const QString &nom);
    bool rechercheQuantite(int quantite);
    void addToHistory(const QString &action,int id);
    void addToHistory_nom(const QString &action, const QString &nom);
    void addToHistory_recherch(const QString &action,int id);
    void logNotification(const QString &title, const QString &message);  // Enregistrer une notification
    QSqlQueryModel* getNotifications();



};


#endif // PRODUIT_H_INCLUDED
