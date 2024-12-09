#include "produit.h"
#include <QsqlQuery>
#include <QtDebug>
#include <QObject>
#include <QtSql>
#include <QDate>
#include <QMessageBox>
#include <QApplication>  // Ajoutez cette ligne
//#include "mainwindow.h"


produit::produit()
{
    id=0;
    nom="";
    prixdachat=0;
    prixdevente=0;
    quantite= 0;

}

void  produit::setid(int i){id=i;}
void produit:: setnom(QString n){nom=n;}
void produit ::setprixdevente(float pv){prixdevente=pv;}
void produit::setprixdachat(float pa){ prixdachat=pa;}
void produit::setquantite(int q){ quantite = q;}




int produit::getid(){return id;}
QString produit::getnom(){return nom;}
float produit::getprixdachat(){return prixdachat;}
float produit ::getprixdevente(){return prixdevente; }
int produit ::getquantite(){return quantite; }





produit::produit( QString nom,int id,int quantite,float prixdachat,float prixdevente)
{
    this->id=id;
    this->nom=nom;
    this->quantite=quantite;
    this->prixdachat=prixdachat;
    this->prixdevente=prixdevente;

}
bool produit::Ajouter()
{
    if (id <= 0) {
        qDebug() << "ID invalide.";
        return false;
    }
    if (prixdachat < 0 || prixdevente < 0) {
        qDebug() << "Les prix doivent être positifs.";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO GS_PRODUIT (id, nom, prixdachat, prixdevente, quantite) "
                  "VALUES (:id, :nom, :prixdachat, :prixdevente, :quantite)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prixdachat", prixdachat);
    query.bindValue(":prixdevente", prixdevente);
    query.bindValue(":quantite", quantite);

    if (query.exec()) {
        qDebug() << "Produit ajouté avec succès";
        addToHistory_recherch("Produit ajouté :", id);  // Ajout dans l'historique après l'ajout
        return true;
    } else {
        qDebug() << "Erreur lors de l'ajout du produit :" << query.lastError().text();
        return false;
    }
}

QSqlQueryModel* produit::Afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    // Requête pour afficher tous les produits
    model->setQuery("SELECT * FROM GS_PRODUIT");

    // Configuration des en-têtes pour chaque colonne
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prixdachat"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("prixdevente"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("quantite "));

    return model;
}


bool produit::Supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM GS_PRODUIT WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        qDebug() << "Produit supprimé avec succès";
        addToHistory_recherch("Produit supprimé :", id);  // Ajout dans l'historique après la suppression
        return true;
    } else {
        qDebug() << "Erreur lors de la suppression du produit :" << query.lastError().text();
        return false;
    }
}



bool produit::Modifier()
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");  // Obtenez la connexion à la base de données

    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "Erreur : Connexion invalide ou non ouverte.";
        // Gérez l'erreur de connexion à la base de données ici si nécessaire.
        return false;
    }

    // Vous devez construire la requête SQL pour la mise à jour des données.
    QSqlQuery query(db);
    query.prepare("UPDATE GS_PRODUIT SET nom = :nom, prixdachat = :prixdachat, quantite = :quantite, prixdevente = :prixdevente WHERE id = :id");




    query.bindValue(":id", id);
    query.bindValue(":NOM",nom);
    query.bindValue(":quantite",quantite);
    query.bindValue(":prixdachat", prixdachat);
    query.bindValue(":prixdevente",prixdevente);

    if (query.exec()) {
        qDebug() << "Modification réussie pour ID : " << id;

        if (query.exec()) {
            addToHistory_recherch("Produit modifier :", id);  // Ajout dans l'historique après l'ajout
            return true;
        }
        return true;  // La mise à jour a réussi.
    } else {
        qDebug() << "Erreur lors de la modification pour l ID " << id << " : " << query.lastError().text();
        // Gérez l'erreur de mise à jour ici si nécessaire.
        return false;
        addToHistory("Modification du Produit ", id);

    }
}
bool produit::rechercherParId(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM GS_PRODUIT WHERE id = :id");
    query.bindValue(":id", id);
    if (query.exec()) {
        qDebug() << "Produit trouvee avec succès";
        addToHistory_recherch("Produit trouve :", id);  // Ajout dans l'historique après l'ajout
        return true;
    } else {
        qDebug() << "Erreur lors de la recherche du produit :" << query.lastError().text();
        return false;
    }
}

bool produit::rechercheQuantite(int quantite){

    QSqlQuery query;
    query.prepare("SELECT * FROM GS_PRODUIT WHERE quantite = :quantite");
    query.bindValue(":quantite", quantite);
    if (query.exec() && query.next()) {
addToHistory_recherch("Produit trouvé :", quantite);
        return true;  // Produit trouvé
    }
    return false;  // Produit non trouvé


}
bool produit::rechercherParNom(const QString &nom) {
    QSqlQuery query;

    // Vérification de la connexion à la base de données
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Erreur : Connexion à la base de données non ouverte.";
        return false;
    }

    query.prepare("SELECT * FROM GS_PRODUIT WHERE nom = :nom");
    query.bindValue(":nom", nom);

    if (query.exec() && query.next()) {
        // Appel à la fonction addToHistory_nom avec l'action et le nom
        addToHistory_nom("Produit trouvé :", nom);
        return true;  // Produit trouvé
    }

    // Ajouter une entrée dans l'historique pour un produit non trouvé
    addToHistory_nom("Produit non trouvé :", nom);

    qDebug() << "Aucun produit trouvé pour le nom : " << nom;
    return false;  // Produit non trouvé
}


void produit::addToHistory_recherch(const QString &action, int id)
{
    // Générer l'historique
    QString historiqueText = "Action effectuée : " + action;
    if (id != 0) {
        historiqueText += " avec ID : " + QString::number(id);
    }

    // Accéder à la fenêtre principale et mettre à jour l'historique
    //MainWindow* mainWindow = qobject_cast<MainWindow*>(QApplication::activeWindow());
    /*if (mainWindow) {
        mainWindow->appendHistorique(historiqueText);  // Passer le texte d'historique à la méthode
    }*/
}





void produit::addToHistory_nom(const QString &action, const QString &nom)
{
    // Spécifier le chemin complet du fichier historique
    QString cheminFichier = "C:/Users/ranim/Downloads/nouv/Atelier_Connexion/historique_produittxt.txt";

    // Ouvrir le fichier en écriture
    QFile file(cheminFichier);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier historique.";
        return;
    }

    // Créer un flux texte pour écrire dans le fichier
    QTextStream out(&file);

    // Obtenir la date et l'heure actuelles
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Écrire l'action dans le fichier historique avec la date, l'heure et le nom
    out << currentDateTime.toString("yyyy-MM-dd hh:mm:ss") << " - " << action;
    if (!nom.isEmpty()) { // Vérifie si la chaîne de caractères n'est pas vide
        out << " Nom : " << nom;
    }
    out << "\n";

    // Fermer le fichier
    file.close();
}
