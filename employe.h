#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QObject>
#include <QWidget>
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <qscrollarea.h>
#include<qtableview.h>
#include <qtextedit.h>
class Employe
{
    QString nom2, prenom2 ,poste;
    int id2;
    int  salaire ;

public:
    Employe();
    Employe(int,int,QString,QString,QString);
    //getters
    QString getnom2(){return nom2 ;}
    QString getprenom2(){return prenom2 ; }
    QString getpost(){return poste ;}
    int getid2(){return id2 ;}
    double getsalair(){return salaire ;}
    //setters
    void setnom2(QString n2){nom2=n2 ;}
    void setprenom2(QString p2 ){prenom2=p2 ;}
    void setid2(int id2 ){this->id2=id2 ; }
    //fonctions de base
    bool ajouter2();
    bool salaireExists(int salaire);
    QSqlQueryModel * afficher2();
    bool supprimer2(int );
    bool modifier2();
    bool idExists2(int id2);
    Employe recupere(int id2);
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
