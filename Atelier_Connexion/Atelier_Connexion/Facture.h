#ifndef FACTURE_H
#define FACTURE_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class Facture {
public:
    int id_facture;
    int id_client;
    double montant;
    QDate date_emise;

    Facture();
    Facture(int id_facture, int id_client, double montant, QDate date_emise);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool modifier();
    static bool idExists(int id);
};

#endif // FACTURE_H
