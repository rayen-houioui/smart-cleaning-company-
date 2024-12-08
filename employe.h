#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QObject>
#include <QWidget>
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <qscrollarea.h>
#include <qsqlquerymodel.h>
#include<qtableview.h>
#include <qtextedit.h>
class Employe
{
    QString nom, prenom ,poste;
    int id;
    int  salaire ;

public:
    Employe();
    Employe(int,int,QString,QString,QString);
    //getters
    QString getnom(){return nom ;}
    QString getprenom(){return prenom ; }
    QString getpost(){return poste ;}
    int getid(){return id ;}
    double getsalair(){return salaire ;}
    //setters
    void setnom(QString n){nom=n ;}
    void setprenom(QString p ){prenom=p ;}
    void setid(int id ){this->id=id ; }
    //fonctions de base
    bool ajouter();
    bool salaireExists(int salaire);
    QSqlQueryModel * afficher();
    bool supprimer(int );
    bool modifier();
    bool idExists(int id);
    Employe recupere(int id );
    void exportTableViewToPDF();
    void calculatePostStatistics(QTableView *tableView);
    bool sendMessageGeneral(const QString& senderNom, const QString& senderPrenom, const QString& message);
    QString getMessagesPrivate(const QString& currentUserNom, const QString& currentUserPrenom);
    void getMessagesPrivate(const QString& receiverNom, const QString& receiverPrenom, QTextEdit* textEdit);
    void showMessages(QScrollArea* scrollArea, const QString& messages);
    QString getMessagesPublic(const QString& currentUserNom, const QString& currentUserPrenom);
    bool postExists(QString post );
    bool sendMessagePrivate(const QString& senderNom, const QString& senderPrenom, const QString& receiverNom, const QString& receiverPrenom, const QString& message);
};

#endif // EMPLOYE_H
