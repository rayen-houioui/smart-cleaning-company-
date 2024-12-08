#include "mainwindow.h"
#include "service.h"
#include <QMessageBox>
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QRegularExpression>
#include <QDate>
#include <QSqlError>
#include <QFileDialog>  // Ajouter l'inclusion manquante
#include <QPdfWriter>   // Ajouter l'inclusion manquante
#include <QPageSize>    // Ajouter l'inclusion manquante
#include <QPainter>     // Ajouter l'inclusion manquante
#include <QTableView>
#include <QTextDocument>
#include <QPrinter>
#include "facture.h"

#include <QtSql/QSqlQueryModel>       // Pour utiliser QSqlQueryModel pour les requêtes SQL
#include <QtCharts/QChart>            // Pour la création du graphique
#include <QtCharts/QChartView>        // Pour afficher le graphique
#include <QtCharts/QPieSeries>        // Pour la série de graphique en camembert (pie chart)
#include <QtCharts/QPieSlice>        // Pour les morceaux individuels du graphique en camembert
#include <QMediaPlayer>               // Pour lire un son lors du clic
#include <QPen>

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSqlQueryModel>
#include <QPieSeries>
#include <QChart>
#include <QChartView>

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSqlQueryModel>
#include <QPieSeries>
#include <QChart>
#include <QChartView>
#include <QVBoxLayout>
#include "email.h"
#include "client.h"
#include "historique.h"

#include "employe.h"
#include <QTimer>
#include <QtCharts/QLineSeries>
#include <QSortFilterProxyModel>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QMap>
#include "commande.h"
#include "produit.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->ComboBox_trier, SIGNAL(currentIndexChanged(int)), this, SLOT(on_ComboBox_trier_clicked(int)));

    tableView = new QTableView(this);
    ui->verticalLayout->addWidget(tableView);


    updateTableView();
    // Initialiser l'affichage de la table
    ui->tableView_3->setModel(Etmp.afficher());
    ui->tableView_10->setModel(Etmp1.afficher1());
    ui->tableView_2->setModel(Emp2.afficher2());
    ui->tableView_11->setModel(Etmp5.afficher5());
    ui->tableView_4->setModel(Etmp7.afficher7());
    // Cacher les champs de modification au départ
    ui->Nommodifier_2->setVisible(false);
    ui->Desmodifier_2->setVisible(false);
    ui->Prixmodifier_2->setVisible(false);
    ui->Datemodifier_2->setVisible(false);
    ui->EMPLOYEmodifier->setVisible(false);
    ui->CLIENTmodifier->setVisible(false);
    ui->PrixHT_20->setVisible(false);
    ui->PrixHT_19->setVisible(false);
    ui->PrixHT_21->setVisible(false);
    ui->PrixHT_22->setVisible(false);
    ui->PrixHT_23->setVisible(false);
    ui->PrixHT_24->setVisible(false);
    ui->Enregistrer_2->setVisible(false);
    ui->Annulermodif_2->setVisible(false);

    ui->Nommodifier_3->setVisible(false);
    ui->PRENOMOD_3->setVisible(false);
    ui->ADRESSEMOD_3->setVisible(false);
    ui->TELEPHONEMOD_3->setVisible(false);
    ui->E_MAILMOD_3->setVisible(false);
    ui->PrixHT_24->setVisible(false);
    ui->PrixHT_23->setVisible(false);
    ui->PrixHT_25->setVisible(false);
    ui->PrixHT_26->setVisible(false);
    ui->Enregistrer_3->setVisible(false);
    ui->Annulermodif_3->setVisible(false);

    ui->nommodifier->setVisible(false);
    ui->prenommodifier->setVisible(false);
    ui->postemodifier->setVisible(false);
    ui->salairemodifier->setVisible(false);
    ui->label_19->setVisible(false);
    ui->label_81->setVisible(false);
    ui->label_82->setVisible(false);
    ui->label_83->setVisible(false);
    ui->enregistrer->setVisible(false);
    ui->annulermodif->setVisible(false);
    ui->tabWidget_2->setVisible(false);
    ui->nomconnecte->setVisible(false);
    ui->nomid->setVisible(false );
    temperatureCheckTimer = new QTimer(this);

    temperatureCheckTimer->start(10000); // Chec


    ui->PRENOMOD_4->setVisible(false);
    ui->ADRESSEMOD_4->setVisible(false);
    ui->TELEPHONEMOD_4->setVisible(false);
    ui->E_MAILMOD_4->setVisible(false);
    ui->PrixHT_50->setVisible(false);
    ui->PrixHT_51->setVisible(false);
    ui->PrixHT_52->setVisible(false);
    ui->PrixHT_53->setVisible(false);
    ui->Enregistrer_40->setVisible(false);
    ui->Annulermodif_40->setVisible(false);


    ui->Nommodifier_7->setVisible(false);
    ui->Prixmodifier_7->setVisible(false);
    ui->EMPLOYEmodifier_8->setVisible(false);
    ui->EMPLOYEmodifier_7->setVisible(false);
    ui->PrixHT_70->setVisible(false);
    ui->PrixHT_71->setVisible(false);
    ui->PrixHT_72->setVisible(false);
    ui->PrixHT_73->setVisible(false);
    ui->PrixHT_19->setVisible(false);
    ui->Enregistrer_7->setVisible(false);
    ui->Annulermodif_7->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_refresh_clicked()
{
    // Prepare the query to fetch all employees
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PROJETCPP2A26.GS_EMPLOYE");  // Assuming you want to show all employees

    // Set the headers
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("POSTE"));

    // Set the model to the table view to refresh the data
    ui->tableView_2->setModel(model);  // Assuming your table view is named tableView

    // Optionally, reset any filters or selections here if necessary
    ui->tableView_2->reset();  // Resets the table view to its initial state
}


bool recherche  (int id2 )
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM PROJETCPP2A26.GS_EMPLOYE WHERE ID = :id"); // Assuming your table is named 'employees' and the column is 'id'
    query.bindValue(":id", id2);

    if (query.exec()) {
        if (query.next()) {
            int count = query.value(0).toInt();
            return count > 0; // Return true if count is greater than 0
        }
    }

    return false; // Return false if query execution fails or no records found
}

void MainWindow::on_pushButton_8_clicked()
{
    bool ok; // Variable pour vérifier si la conversion est réussie

    // Récupérer l'ID du service depuis le QLineEdit
    int id = ui->lineEdit_ID_2->text().toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::critical(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    // Récupérer le prix depuis le QLineEdit
    int prix = ui->lineEdit_PRIX_2->text().toInt(&ok);
    if (!ok || prix <= 0) {
        QMessageBox::critical(this, "Erreur", "Veuillez entrer un prix valide.");
        return;
    }

    // Récupérer l'ID client depuis le QLineEdit
    int id_client = ui->lineEdit_CLIENT->text().toInt(&ok);
    if (!ok || id_client <= 0) {
        QMessageBox::critical(this, "Erreur", "Veuillez entrer un ID client valide.");
        return;
    }

    // Récupérer l'ID employé depuis le QLineEdit
    int id_employe = ui->lineEdit_EMPLOYE->text().toInt(&ok);
    if (!ok || id_employe <= 0) {
        QMessageBox::critical(this, "Erreur", "Veuillez entrer un ID employé valide.");
        return;
    }

    // Récupérer le nom du service depuis le QLineEdit
    QString nom = ui->lineEdit_nom_2->text();
    if (nom.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Veuillez entrer un nom pour le service.");
        return;
    }

    // Récupérer la description depuis un QLineEdit
    QString description = ui->lineEdit_description_2->text();
    if (description.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Veuillez entrer une description.");
        return;
    }

    // Récupérer la date estimée depuis un QDateEdit
    QDate date = ui->lineEdit_DATE_2->date();
    if (!date.isValid()) {
        QMessageBox::critical(this, "Erreur", "Veuillez entrer une date valide.");
        return;
    }

    // Création du service avec les informations récupérées
    Service service(id, prix, id_client, id_employe, nom, description, date);

    // Ajout du service dans la base de données
    if (service.ajouter()) {
        // Si l'ajout réussit, afficher les services dans le QTableView
        QSqlQueryModel *model = service.afficher();  // Utilisation de la méthode afficher()

        // Vérification si le modèle est valide
        if (model) {
            // Lier le modèle au QTableView pour afficher les services
            ui->tableView_3->setModel(model);
            ui->tableView_3->resizeColumnsToContents();  // Redimensionner les colonnes automatiquement

            // Afficher un message de succès
            QMessageBox::information(this, "Succès", "Service ajouté avec succès.");
        } else {
            QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de la récupération des services.");
        }

        // Optionnel : Envoi d'un email après l'ajout
        QString destinataire = "destinataire@example.com";  // Remplacez par l'email réel
        QString sujet = "Service ajouté avec succès";
        QString message = QString("Le service \"%1\" a été ajouté avec succès. Détails :\n"
                                  "Nom : %2\n"
                                  "Description : %3\n"
                                  "Prix : %4\n"
                                  "Date : %5")
                              .arg(nom)
                              .arg(nom)
                              .arg(description)
                              .arg(prix)
                              .arg(date.toString("yyyy-MM-dd"));

        // Appel de la fonction pour envoyer l'email (assurez-vous que la méthode Email::envoyerEmail existe et fonctionne)
        if (Email::envoyerEmail(destinataire, sujet, message)) {
            QMessageBox::information(this, "Succès", "Service ajouté et email envoyé.");
        } else {
            QMessageBox::critical(this, "Erreur", "Le service a été ajouté, mais l'envoi de l'email a échoué.");
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de l'ajout du service.");
    }
}

void MainWindow::on_pushButton_90_clicked()
{
    int id1 = ui->lineEdit_ID_5->text().toInt();
    int telephone = ui->lineEdit_TELEPHONE->text().toInt();
    QString nom1 = ui->lineEdit_nomc_3->text();
    QString prenom = ui->lineEdit_PRENOM_3->text();
    QString adresse = ui->lineEdit_ADRESSE->text();
    QString e_mail = ui->lineEdit_E_MAIL->text();

    Client c(id1,telephone,nom1,prenom,adresse,e_mail);
    bool test1 = c.ajouter1();

    if (test1) {
        ui->tableView_10->setModel(Etmp1.afficher1());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

    historique h;
    QString textajouter = "L'ajout d'un client dans la base de donnees dont la id est = " + QString::number(id1) + " a ete effectuee avec succees";
    h.write(textajouter);
    QMessageBox::information(this, "Ajout réussi", "L'ajout a été effectué avec succès.");
}

void MainWindow::on_ajoutemploye_clicked()
{
    QString idStr2 = ui->cinE->text();
    QString nom2 = ui->nomE->text();
    QString prenom2 = ui->prenomE->text();
    QString poste = ui->listWidget->currentItem()->text() ;
    QString salaireStr = ui->salaireE->text();

    // Define static regular expressions
    static const QRegularExpression reInt("^[0-9]+$"); // Pattern for integers
    static const QRegularExpression reStr("^[a-zA-Z]+$"); // Pattern for alphabetic strings

    // Check if ID is an integer and has a length of 8
    if (!reInt.match(idStr2).hasMatch() || idStr2.length() != 8) {
        QString errorMessage;
        if (idStr2.length() != 8) {
            errorMessage += QObject::tr("L'ID doit avoir une longueur de 8 caractères.\n");
        }
        if (!reInt.match(idStr2).hasMatch()) {
            errorMessage += QObject::tr("L'ID doit être un nombre entier valide.\n");
        }
        errorMessage += QObject::tr("Click Cancel to exit.");

        QMessageBox::critical(nullptr, QObject::tr("Invalid Input"), errorMessage, QMessageBox::Cancel);
        return;

    }
    int id2 = idStr2.toInt();
    if (recherche(id2 )){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr(" Cette id deja existe .\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        return ;
    }

    // Check if name contains only letters
    if (!reStr.match(nom2).hasMatch()) {
        QMessageBox::critical(nullptr, QObject::tr("Invalid Input"),
                              QObject::tr("nom doit etre seulement des caractéres.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }
    // Check if surname contains only letters
    if (!reStr.match(prenom2).hasMatch()) {
        QMessageBox::critical(nullptr, QObject::tr("Invalid Input"),
                              QObject::tr("prenom doit etre seulement des caractéres.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }
    // Check if salary is an integer
    if (!reInt.match(salaireStr).hasMatch()) {
        QMessageBox::critical(nullptr, QObject::tr("Invalid Input"),
                              QObject::tr("Salaire doit etre un nombre.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }





    int salaire = salaireStr.toInt();

    Employe E(id2, salaire, nom2, prenom2, poste);
    if (E.idExists2(id2)) {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr(" ID.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        bool test = E.ajouter2();
        if (test) // If query executed => QMessageBox::information
        {
            ui->tableView_2->setModel(Emp2.afficher2());
            ui->cinE->clear();
            ui->nomE->clear();
            ui->prenomE->clear();
            ui->salaireE->clear();
            ui->salaireE->clear();

            QMessageBox::information(nullptr, QObject::tr("OK"),
                                     QObject::tr("Addition successful.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
        } else // If query not executed => QMessageBox::critical
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Addition not successful.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }
}




void MainWindow::on_pushButton_6_clicked()
{
    int id = ui->lineEdit_247->text().toInt();
    bool test = Etmp.supprimer(id);

    if (test) {
        ui->tableView_3->setModel(Etmp.afficher());
        QMessageBox::information(this, "Succès", "Suppression effectuée.");
    } else {
        QMessageBox::critical(this, "Erreur", "Suppression non effectuée.");
    }
}


void MainWindow::on_pushButton_67_clicked()
{
    int id1 = ui->lineEdit_249->text().toInt();
    bool test1=Etmp1.supprimere(id1);

    if (test1) {
        ui->tableView_10->setModel(Etmp1.afficher1());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("suppression effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("suppression non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_7_clicked() //supression
{

    int id2 = ui->lineEdit_15->text().toInt();
    if (Emp2.idExists2(id2)) {
        bool test2 = Emp2.supprimer2(id2);  // Call the supprimer() method via the Etmp attribute

        if (test2)
        {
            ui->tableView_2->setModel(Emp2.afficher2());
            QMessageBox::information(nullptr, QObject::tr("OK"),
                                     QObject::tr("Suppression effectuée.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Suppression non effectuée.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr(" Cette CIN n'existe pas vous devez saisir une CIN valide.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);




    }
}

void MainWindow::on_pushButton_5_clicked()
{
    QString idStr = ui->lineEdit_247->text();
    bool isNumber;
    int id = idStr.toInt(&isNumber);

    if (!isNumber) {
        QMessageBox::critical(this, "Erreur", "L'ID doit être un nombre entier valide.");
        return;
    }

    if (Etmp.idExists(id)) {
        // Afficher les champs de modification si l'ID existe
        ui->Nommodifier_2->setVisible(true);
        ui->Desmodifier_2->setVisible(true);
        ui->Prixmodifier_2->setVisible(true);
        ui->Datemodifier_2->setVisible(true);
        ui->EMPLOYEmodifier->setVisible(true);
        ui->CLIENTmodifier->setVisible(true);
        ui->PrixHT_20->setVisible(true);
        ui->PrixHT_19->setVisible(true);
        ui->PrixHT_21->setVisible(true);
        ui->PrixHT_22->setVisible(true);
        ui->PrixHT_23->setVisible(true);
        ui->PrixHT_24->setVisible(true);
        ui->Enregistrer_2->setVisible(true);
        ui->Annulermodif_2->setVisible(true);
    } else {
        QMessageBox::information(this, "Erreur", "L'ID n'existe pas. Veuillez entrer un ID valide.");
    }
}


void MainWindow::on_pushButton_10_clicked()
{
    QString idStr1 = ui->lineEdit_249->text(); // Get the text from the line edit
    bool isNumber1;

    // Convert the input string to an integer
    int id1 = idStr1.toInt(&isNumber1);

    // Check if the input is not a valid number
    if (!isNumber1) {
        QMessageBox::critical(nullptr, QObject::tr("Invalid Input"),
                              QObject::tr("L'ID doit être un nombre entier valide.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }

    // Proceed to check if the ID exists
    if (Etmp1.idExist(id1)) {
        // Show the fields for modification
        ui->Nommodifier_3->setVisible(true);
        ui->PRENOMOD_3->setVisible(true);
        ui->ADRESSEMOD_3->setVisible(true);
        ui->TELEPHONEMOD_3->setVisible(true);
        ui->E_MAILMOD_3->setVisible(true);
        ui->PrixHT_24->setVisible(true);
        ui->PrixHT_23->setVisible(true);
        ui->PrixHT_25->setVisible(true);
        ui->PrixHT_26->setVisible(true);
        ui->Enregistrer_3->setVisible(true);
        ui->Annulermodif_3->setVisible(true);

        historique h;
        QString textModification = "La modification d'un client de la base de données dont l'ID est = " + QString::number(id1) + " a été effectuée avec succès";
        h.write(textModification);
        QMessageBox::information(this, "Modification réussie", "La modification a été effectuée avec succès.");
    } else {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Cette ID n'existe pas. Vous devez saisir une CIN valide.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_modifier_clicked()
{
    QString idStr2 = ui->lineEdit_15->text(); // Get the text from the line edit
    bool isNumber2; // Variable to check if the conversion is successful

    // Convert the input string to an integer
    int id2 = idStr2.toInt(&isNumber2); // Convert to int and set isNumber based on success

    // Check if the input is not a valid number
    if (!isNumber2) {
        QMessageBox::critical(nullptr, QObject::tr("Invalid Input"),
                              QObject::tr("L'ID doit être un nombre entier valide.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return; // Exit the function if the input is invalid
    }

    // Proceed to check if the ID exists
    if (Emp2.idExists2(id2)) {
        Employe E;
        E=E.recupere(id2);
        QString employeeName = E.getnom2();
        QString employeeprenom=E.getprenom2();
        double employeesalair=E.getsalair();
        QString str2 = QString::number(employeesalair);
        QString employeepost=E.getpost();
        qDebug() << "Employee Name: " << employeeName;  // Ensure this prints the correct name
        ui->nommodifier->setText(employeeName);
        ui->nommodifier->repaint();
        ui->prenommodifier->setText(employeeprenom);
        ui->nommodifier->repaint();
        ui->salairemodifier->setText(str2);
        ui->salairemodifier->repaint();
        ui->postemodifier->setText(employeepost);
        ui->postemodifier->repaint();

        // Show the fields for modification
        ui->nommodifier->setVisible(true);
        ui->prenommodifier->setVisible(true);
        ui->postemodifier->setVisible(true);
        ui->salairemodifier->setVisible(true);
        ui->label_19->setVisible(true);
        ui->label_81->setVisible(true);
        ui->label_82->setVisible(true);
        ui->label_83->setVisible(true);
        ui->enregistrer->setVisible(true);
        ui->annulermodif->setVisible(true);




    } else {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Cette CIN n'existe pas. Vous devez saisir une CIN valide.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
}




void MainWindow::on_Enregistrer_2_clicked()
{
    int id = ui->lineEdit_247->text().toInt();
    QString nom = ui->Nommodifier_2->text();
    QString description = ui->Desmodifier_2->text();
    int prix = ui->Prixmodifier_2->text().toInt();
    int id_employe = ui->EMPLOYEmodifier->text().toInt();
    int id_client = ui->CLIENTmodifier->text().toInt();

    // Vérifier que les champs sont valides
    if (nom.isEmpty() || description.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Le nom et la description doivent être remplis.");
        return;
    }

    // Corriger la conversion de la date
    QDate date = QDate::fromString(ui->Datemodifier_2->text(), "dd-MM-yyyy");
    if (!date.isValid()) {
        QMessageBox::critical(this, "Erreur", "Date invalide. Veuillez entrer une date correcte.");
        return;
    }

    Service S(id, prix, id_client, id_employe, nom, description, date);
    bool test = S.modifier();

    if (test) {
        ui->tableView_3->setModel(Etmp.afficher());
        // Masquer les champs après la modification
        ui->Nommodifier_2->setVisible(false);
        ui->Desmodifier_2->setVisible(false);
        ui->Prixmodifier_2->setVisible(false);
        ui->Datemodifier_2->setVisible(false);
        ui->EMPLOYEmodifier->setVisible(false);
        ui->CLIENTmodifier->setVisible(false);
        ui->PrixHT_20->setVisible(false);
        ui->PrixHT_19->setVisible(false);
        ui->PrixHT_21->setVisible(false);
        ui->PrixHT_22->setVisible(false);
        ui->PrixHT_23->setVisible(false);
        ui->PrixHT_24->setVisible(false);
        ui->Enregistrer_2->setVisible(false);
        ui->Annulermodif_2->setVisible(false);

        // Réinitialiser les champs
        ui->Nommodifier_2->clear();
        ui->Desmodifier_2->clear();
        ui->Prixmodifier_2->clear();
        ui->Datemodifier_2->clear();
        ui->EMPLOYEmodifier->clear();
        ui->CLIENTmodifier->clear();

        QMessageBox::information(this, "Succès", "Modification effectuée.");
    } else {
        QMessageBox::critical(this, "Erreur", "Modification non effectuée.");
    }
}


void MainWindow::on_Enregistrer_3_clicked()
{
    int id1 = ui->lineEdit_249->text().toInt();  // Convertir l'ID en entier
    QString nom1 = ui->Nommodifier_3->text();
    QString prenom = ui->PRENOMOD_3->text();
    QString adresse = ui->ADRESSEMOD_3->text();
    int telephone = ui->TELEPHONEMOD_3->text().toInt();
    QString e_mail = ui->E_MAILMOD_3->text();

    // Vérification que les champs ne sont pas vides
    if (nom1.isEmpty() || prenom.isEmpty() || adresse.isEmpty() || telephone == 0 || e_mail.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Tous les champs doivent être remplis !"), QMessageBox::Cancel);
        return;
    }

    Client c(id1, telephone, nom1, prenom, adresse, e_mail);
    QString errorMsg;
    bool test1 = c.modifier(errorMsg);  // Appeler la méthode de modification avec un message d'erreur

    if (test1) {
        ui->tableView_10->setModel(Etmp1.afficher1());
        ui->Nommodifier_3->setVisible(false);
        ui->PRENOMOD_3->setVisible(false);
        ui->ADRESSEMOD_3->setVisible(false);
        ui->TELEPHONEMOD_3->setVisible(false);
        ui->E_MAILMOD_3->setVisible(false);
        ui->PrixHT_24->setVisible(false);
        ui->PrixHT_23->setVisible(false);
        ui->PrixHT_25->setVisible(false);
        ui->PrixHT_26->setVisible(false);
        ui->Enregistrer_3->setVisible(false);
        ui->Nommodifier_3->clear();
        ui->PRENOMOD_3->clear();
        ui->ADRESSEMOD_3->clear();
        ui->TELEPHONEMOD_3->clear();
        ui->E_MAILMOD_3->clear();
        ui->tableView_10->setModel(Etmp1.afficher1());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        // Afficher l'erreur SQL
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Modification non effectuée. Erreur SQL :\n%1")
                                  .arg(errorMsg), QMessageBox::Cancel);
    }
}


void MainWindow::on_enregistrer_clicked()
{
    int id2 = ui->lineEdit_15->text().toInt();  // Convert the entered string to an integer because the id attribute is of type int

    QString nom2=ui->nommodifier->text();
    QString prenom2=ui->prenommodifier->text();
    QString poste=ui->postemodifier->text();
    int salaire=ui->salairemodifier->text().toInt();
    Employe E(id2,salaire,nom2,prenom2,poste);
    bool test2=E.modifier2();
    if(test2) // Si requête exécutée => QMessageBox::information
    {
        ui->tableView->setModel(Emp2.afficher2());
        ui->nommodifier->setVisible(false);
        ui->prenommodifier->setVisible(false);
        ui->postemodifier->setVisible(false);
        ui->salairemodifier->setVisible(false);
        ui->label_19->setVisible(false);
        ui->label_81->setVisible(false);
        ui->label_82->setVisible(false);
        ui->label_83->setVisible(false);
        ui->enregistrer->setVisible(false);
        ui->nommodifier->clear();
        ui->prenommodifier->clear();
        ui->postemodifier->clear();
        ui->salairemodifier->clear();


        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("modification effectué.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else // Si requête non exécutée => QMessageBox::critical
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("modification non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

}


void MainWindow::on_Annulermodif_2_clicked()
{
    // Masquer les champs de modification si l'utilisateur annule
    ui->Nommodifier_2->setVisible(false);
    ui->Desmodifier_2->setVisible(false);
    ui->Prixmodifier_2->setVisible(false);
    ui->Datemodifier_2->setVisible(false);
    ui->EMPLOYEmodifier->setVisible(false);
    ui->CLIENTmodifier->setVisible(false);
    ui->PrixHT_20->setVisible(false);
    ui->PrixHT_19->setVisible(false);
    ui->PrixHT_21->setVisible(false);
    ui->PrixHT_22->setVisible(false);
    ui->PrixHT_23->setVisible(false);
    ui->PrixHT_24->setVisible(false);
    ui->Enregistrer_2->setVisible(false);
    ui->Annulermodif_2->setVisible(false);

    // Réinitialiser les champs
    ui->Nommodifier_2->clear();
    ui->Desmodifier_2->clear();
    ui->Prixmodifier_2->clear();
    ui->Datemodifier_2->clear();
    ui->EMPLOYEmodifier->clear();
    ui->CLIENTmodifier->clear();
}

void MainWindow::on_Annulermodif_3_clicked()
{


    ui->Nommodifier_3->setVisible(false);
    ui->PRENOMOD_3->setVisible(false);
    ui->ADRESSEMOD_3->setVisible(false);
    ui->TELEPHONEMOD_3->setVisible(false);
    ui->E_MAILMOD_3->setVisible(false);
    ui->PrixHT_24->setVisible(false);
    ui->PrixHT_23->setVisible(false);
    ui->PrixHT_25->setVisible(false);
    ui->PrixHT_26->setVisible(false);
    ui->Enregistrer_3->setVisible(false);
    ui->Nommodifier_3->clear();
    ui->PRENOMOD_3->clear();
    ui->ADRESSEMOD_3->clear();
    ui->TELEPHONEMOD_3->clear();
    ui->E_MAILMOD_3->clear();
}


void MainWindow::on_annulermodif_clicked()
{
    ui->nommodifier->setVisible(false);
    ui->prenommodifier->setVisible(false);
    ui->postemodifier->setVisible(false);
    ui->salairemodifier->setVisible(false);
    ui->label_19->setVisible(false);
    ui->label_81->setVisible(false);
    ui->label_82->setVisible(false);
    ui->label_83->setVisible(false);
    ui->enregistrer->setVisible(false);
    ui->nommodifier->clear();
    ui->prenommodifier->clear();
    ui->postemodifier->clear();
    ui->salairemodifier->clear();
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    // Retrieve the text of the selected item
    QString selectedItemText = item->text();

    // Use the text directly here, for example, display it in a message box
    QMessageBox::information(this, "Item Selected", "You selected: " + selectedItemText);

    // If you need to store the text for later use, you can store it in a member variable
    lastSelectedItemText = selectedItemText;
}


void MainWindow::on_ComboBox_trier_clicked(int index)
{
    // Créer une requête pour trier les services
    QSqlQuery query;
    QString queryString;

    // Vérifier le choix de l'utilisateur dans le QComboBox
    if (index == 0) {  // Si l'utilisateur choisit "ID"
        queryString = "SELECT * FROM PROJETCPP2A26.GS_SERVICE ORDER BY ID_SERVICE";
    } else if (index == 1) {  // Si l'utilisateur choisit "Nom"
        queryString = "SELECT * FROM PROJETCPP2A26.GS_SERVICE ORDER BY NOM";
    } else if (index == 2) {  // Si l'utilisateur choisit "DATE_ESTIME"
        queryString = "SELECT * FROM PROJETCPP2A26.GS_SERVICE ORDER BY DATE_ESTIME";
    }

    // Afficher la requête SQL dans le débogage
    qDebug() << "Requête SQL générée : " << queryString;

    // Exécuter la requête SQL
    query.prepare(queryString);
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête de tri : " << query.lastError().text();
        return;
    }

    // Créer un modèle de requêtes pour afficher les données dans le QTableView
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Afficher les résultats dans le QTableView
    ui->tableView_3->setModel(model);
}


void MainWindow::on_pushButton_exporter_clicked()
{
    // Ouvrir une boîte de dialogue pour sélectionner l'emplacement de sauvegarde
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exporter en PDF"), "", "*.pdf");

    if (fileName.isEmpty()) {
        return; // Si aucun fichier n'est sélectionné
    }

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(200); // Résolution de 200 DPI

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    // Définir la police pour le titre
    QFont titleFont;
    titleFont.setPointSize(20); // Taille plus grande pour le titre
    titleFont.setBold(true);
    painter.setFont(titleFont);

    // Positionner et dessiner le titre
    QString title = "Liste des Services";
    int yPosition = 50; // Position verticale pour le titre
    painter.drawText(100, yPosition, pdfWriter.width() - 200, 50, Qt::AlignCenter, title);

    // Ajuster yPosition pour laisser de l'espace après le titre
    yPosition += 70; // Ajustez cette valeur pour contrôler l'espace après le titre

    // Ajouter de l'espace supplémentaire entre le titre et le tableau
    yPosition += 50; // Espace supplémentaire avant le tableau, ajustez cette valeur selon votre besoin

    // Redéfinir la police pour le reste du contenu
    QFont font;
    font.setPointSize(14); // Taille de police pour une meilleure lisibilité
    painter.setFont(font);

    QFontMetrics fontMetrics(font);
    int cellHeight = fontMetrics.height() + 60; // Hauteur ajustée pour espacer les lignes
    int rowCount = ui->tableView_3->model()->rowCount(); // Correction de la syntaxe
    int columnCount = ui->tableView_3->model()->columnCount() + 1; // +1 pour la colonne de numérotation

    // Calcul de la largeur des cellules pour remplir la page A4, incluant la colonne de numérotation
    int cellWidth = pdfWriter.width() / columnCount;

    // Dessiner l'en-tête des colonnes avec fond vert
    painter.setBrush(QColor(144, 238, 144)); // Vert clair pour l'en-tête
    painter.drawRect(100, yPosition, cellWidth, cellHeight); // Cadre pour la colonne de numérotation
    painter.drawText(100, yPosition, cellWidth, cellHeight, Qt::AlignCenter, ""); // En-tête de la colonne de numérotation

    for (int col = 0; col < columnCount - 1; ++col) { // Boucle pour les autres colonnes d'en-tête
        QString headerData = ui->tableView_3->model()->headerData(col, Qt::Horizontal).toString();
        painter.drawRect(100 + (col + 1) * cellWidth, yPosition, cellWidth, cellHeight); // Cadre de la cellule d'en-tête
        painter.drawText(100 + (col + 1) * cellWidth, yPosition, cellWidth, cellHeight, Qt::AlignCenter, headerData);
    }

    painter.setBrush(Qt::NoBrush); // Enlever le pinceau après avoir dessiné l'en-tête
    yPosition += cellHeight; // Déplacer la position verticale après l'en-tête

    // Boucle pour chaque ligne et colonne pour dessiner les données sous forme de tableau
    for (int row = 0; row < rowCount; ++row) {
        int xPosition = 100; // Position horizontale de départ pour chaque ligne

        // Colonne de numérotation avec fond bleu ciel
        painter.setBrush(QColor(173, 216, 230)); // Bleu ciel pour la colonne de numérotation
        QString rowNumber = QString::number(row + 1);
        painter.drawRect(xPosition, yPosition, cellWidth, cellHeight); // Cadre de la cellule de numérotation
        painter.drawText(xPosition, yPosition, cellWidth, cellHeight, Qt::AlignCenter, rowNumber);
        xPosition += cellWidth; // Déplacer horizontalement pour la prochaine cellule

        painter.setBrush(Qt::NoBrush); // Enlever le pinceau après avoir dessiné la cellule de numérotation

        // Autres colonnes de données
        for (int col = 0; col < columnCount - 1; ++col) {
            QString cellData;

            if (col == 0) { // Si c'est la colonne où l'ID employé est stocké
                // Récupérer l'ID de l'employé
                int id_employe = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, col)).toInt();

                // Utiliser la fonction getNomEmploye pour obtenir le nom de l'employé
                QString nomEmploye = getNomEmploye(id_employe);

                cellData = nomEmploye; // Mettre le nom dans la cellule
            } else {
                // Pour les autres colonnes, afficher les données normalement
                cellData = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, col)).toString();
            }

            painter.drawRect(xPosition, yPosition, cellWidth, cellHeight); // Cadre de la cellule
            painter.drawText(xPosition, yPosition, cellWidth, cellHeight, Qt::AlignCenter, cellData);
            xPosition += cellWidth; // Déplacer horizontalement pour la prochaine cellule
        }

        yPosition += cellHeight; // Déplacer verticalement pour la prochaine ligne
    }

    painter.end(); // Fin de la peinture du PDF

    // Message de confirmation
    QMessageBox::information(this, "Exportation réussie", "L'affichage a été exporté en PDF avec succès.");
}



void MainWindow::on_pushButton_exporter_3_clicked()
{


    // Ouvrir une boîte de dialogue pour choisir le fichier PDF
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer en PDF", "", "PDF Files (*.pdf);;All Files (*)");
    if (filePath.isEmpty()) {
        return; // Annuler si aucun fichier n'est sélectionné
    }

    // Ajouter l'extension .pdf si elle est manquante
    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
        filePath += ".pdf";
    }

    // Configurer le QPdfWriter pour créer un fichier PDF
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4)); // Format A4
    pdfWriter.setResolution(300); // Résolution en DPI

    QPainter painter(&pdfWriter);
    if (!painter.isActive()) {
        QMessageBox::warning(this, "Erreur", "Impossible de créer le fichier PDF.");
        return;
    }

    // Récupérer le modèle de données du QTableView
    QAbstractItemModel *model = ui->tableView_10->model();
    if (!model) {
        QMessageBox::warning(this, "Erreur", "Aucun modèle trouvé dans le tableau.");
        return;
    }

    // Initialisation des variables pour dessiner le tableau
    int rows = model->rowCount();
    int cols = model->columnCount();

    int startX = 50;     // Position de départ en X
    int startY = 50;     // Position de départ en Y
    int cellWidth = 120; // Largeur des cellules
    int cellHeight = 30; // Hauteur des cellules

    int currentY = startY;

    // Dessiner les en-têtes de colonnes
    for (int col = 0; col < cols; ++col) {
        QRect rect(startX + col * cellWidth, currentY, cellWidth, cellHeight);
        painter.drawRect(rect);
        painter.drawText(rect, Qt::AlignCenter, model->headerData(col, Qt::Horizontal).toString());
    }

    currentY += cellHeight;

    // Dessiner les lignes de données
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            QRect rect(startX + col * cellWidth, currentY, cellWidth, cellHeight);
            painter.drawRect(rect);
            painter.drawText(rect, Qt::AlignCenter, model->data(model->index(row, col)).toString());
        }
        currentY += cellHeight;

        // Passer à une nouvelle page si nécessaire
        if (currentY + cellHeight > pdfWriter.height()) {
            pdfWriter.newPage();
            currentY = startY + cellHeight; // Réinitialiser la position en Y
        }
    }

    painter.end();

    QMessageBox::information(this, "Succès", "Le tableau a été exporté avec succès en PDF !");
}

void MainWindow::on_pushButton_4_clicked() // Export to PDF
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF"), QString(), "*.pdf");
    if (fileName.isEmpty()) {
        return;
    }
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    if (!printer.isValid()) {
        QMessageBox::warning(this, tr("Export Failed"), tr("Failed to create the PDF file."));
        return;
    }

    QPainter painter(&printer);

    // Create a model with custom columns (Date Entree and Date Sortie)
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID FROM PROJETCPP2A26.GS_EMPLOYE");  // Only select the ID column from the EMPLOYE table

    // Add custom Date Entree and Date Sortie columns
    model->insertColumn(1);  // Insert a new column for Date Entree
    model->insertColumn(2);  // Insert a new column for Date Sortie

    // Populate the new columns with custom values
    for (int row = 0; row < model->rowCount(); ++row) {
        model->setData(model->index(row, 1), "01/01/2024");  // Example static value for Date Entree
        model->setData(model->index(row, 2), "01/01/2025");  // Example static value for Date Sortie
    }

    // Set the headers for the columns
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Entree"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Sortie"));

    // Set the model to the table view for rendering (for PDF rendering)
    ui->tableView_2->setModel(model);

    // Render the table view to the printer
    ui->tableView_2->render(&painter);

    painter.end();

    QMessageBox::information(this, tr("Export Completed"), tr("PDF export completed successfully."));
}

void MainWindow::on_tabWidget_26_currentChanged()
{
    {
        QSqlQuery query;

        // Récupérer le nombre total de services dans la base de données
        query.prepare("SELECT COUNT(*) FROM PROJETCPP2A26.GS_CLIENT");
        if (!query.exec()) {
            qDebug() << "Erreur lors de la récupération du nombre total de clients : " << query.lastError().text();
            return;
        }

        query.next();
        int totalClients = query.value(0).toInt();
        qDebug() << "Total Client: " << totalClients;

        if (totalClients == 0) {
            QMessageBox::warning(this, "Aucun client", "Aucun client trouvé dans la base de données.");
            return;
        }

        // Création de la série de données pour le graphique circulaire (camembert)
        QPieSeries *series = new QPieSeries();

        // Récupérer le nombre de services par nom (type de service)
        query.prepare("SELECT ADRESSE, COUNT(*) FROM PROJETCPP2A26.GS_CLIENT GROUP BY ADRESSE");
        if (!query.exec()) {
            qDebug() << "Erreur lors de la récupération des clients par adresse : " << query.lastError().text();
            return;
        }

        // Ajouter les services à la série
        while (query.next()) {
            QString clientadresse = query.value(0).toString();  // NOM de service
            int clientCount = query.value(1).toInt();  // Compter le nombre de services

            double percentage = (static_cast<double>(clientCount) / totalClients) * 100;
            qDebug() << "Service: " << clientadresse << ", Nombre: " << clientCount << ", Pourcentage: " << percentage;

            // Ajouter la donnée à la série avec le nom et le nombre
            QPieSlice *slice = series->append(clientadresse + ": " + QString::number(percentage, 'f', 2) + "%", clientCount);

            // Rendre l'étiquette visible
            slice->setLabelVisible(true);

            // Ajouter une couleur pour rendre les labels visibles sur un fond blanc (optionnel)
            slice->setLabelColor(Qt::black);  // Changez la couleur si nécessaire
            slice->setLabelFont(QFont("Arial", 10));  // Police et taille du texte des labels
        }

        if (series->count() == 0) {
            qDebug() << "Aucune donnée à afficher dans la série";
            return;
        }

        // Création du graphique
        QChart *chart = new QChart();
        chart->setBackgroundBrush(QBrush(Qt::white));  // Fond blanc pour le graphique
        chart->setTitle("Répartition des clients par adresse");
        chart->addSeries(series);
        chart->legend()->hide();  // Masquer la légende

        // Création de la vue du graphique
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);  // Activer l'anticrénelage pour améliorer l'affichage
        chartView->setMinimumSize(400, 300);  // Définir une taille minimale pour s'assurer qu'il est visible

        // Vérification de la taille du widget parent
        qDebug() << "Taille de label_type: " << ui->label_type1->size();
        ui->label_type1->setMinimumSize(400, 300);  // Définir une taille minimale pour label_type

        // Suppression du layout précédent (s'il y en a un) et ajout du nouveau graphique dans label_type
        if (ui->label_type1->layout() != nullptr) {
            delete ui->label_type1->layout();
        }

        QVBoxLayout *layout = new QVBoxLayout(ui->label_type1);
        layout->addWidget(chartView);
        ui->label_type1->setLayout(layout);

        // Forcer le redessin du widget parent
        ui->label_type1->repaint();

        // Configuration du son
        QMediaPlayer *player = new QMediaPlayer;
        QAudioOutput *audioOutput = new QAudioOutput;
        player->setAudioOutput(audioOutput);
        audioOutput->setVolume(1.0);  // Volume entre 0.0 et 1.0
        player->setSource(QUrl::fromLocalFile("C:/Users/HP/Downloads/intg/button.wav"));
        player->play();
    }
}


QString MainWindow::getNomEmploye(int id_employe)
{
    QSqlQuery query;
    query.prepare("SELECT NOM FROM PROJETCPP2A26.GS_EMPLOYE WHERE ID = :id_employe");
    query.bindValue(":id_employe", id_employe);

    if (query.exec() && query.next()) {
        return query.value(0).toString();  // Retourner le nom de l'employé
    }
    return "Nom inconnu";  // Retourner un message par défaut si aucun nom trouvé
}






void MainWindow::on_tabWidget_22_currentChanged()
{
    QSqlQuery query;

    // Récupérer le nombre total de services dans la base de données
    query.prepare("SELECT COUNT(*) FROM PROJETCPP2A26.GS_SERVICE");
    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération du nombre total de services : " << query.lastError().text();
        return;
    }

    query.next();
    int totalServices = query.value(0).toInt();
    qDebug() << "Total Services: " << totalServices;

    if (totalServices == 0) {
        QMessageBox::warning(this, "Aucun service", "Aucun service trouvé dans la base de données.");
        return;
    }

    // Création de la série de données pour le graphique circulaire (camembert)
    QPieSeries *series = new QPieSeries();

    // Récupérer le nombre de services par nom (type de service)
    query.prepare("SELECT NOM, COUNT(*) FROM PROJETCPP2A26.GS_SERVICE GROUP BY NOM");
    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des services par nom : " << query.lastError().text();
        return;
    }

    // Ajouter les services à la série
    while (query.next()) {
        QString serviceName = query.value(0).toString();  // NOM de service
        int serviceCount = query.value(1).toInt();  // Compter le nombre de services

        double percentage = (static_cast<double>(serviceCount) / totalServices) * 100;
        qDebug() << "Service: " << serviceName << ", Nombre: " << serviceCount << ", Pourcentage: " << percentage;

        // Ajouter la donnée à la série avec le nom et le nombre
        QPieSlice *slice = series->append(serviceName + ": " + QString::number(percentage, 'f', 2) + "%", serviceCount);

        // Rendre l'étiquette visible
        slice->setLabelVisible(true);

        // Ajouter une couleur pour rendre les labels visibles sur un fond blanc (optionnel)
        slice->setLabelColor(Qt::black);  // Changez la couleur si nécessaire
        slice->setLabelFont(QFont("Arial", 10));  // Police et taille du texte des labels
    }

    if (series->count() == 0) {
        qDebug() << "Aucune donnée à afficher dans la série";
        return;
    }

    // Création du graphique
    QChart *chart = new QChart();
    chart->setBackgroundBrush(QBrush(Qt::white));  // Fond blanc pour le graphique
    chart->setTitle("Répartition des services par nom");
    chart->addSeries(series);
    chart->legend()->hide();  // Masquer la légende

    // Création de la vue du graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  // Activer l'anticrénelage pour améliorer l'affichage
    chartView->setMinimumSize(400, 300);  // Définir une taille minimale pour s'assurer qu'il est visible

    // Vérification de la taille du widget parent
    qDebug() << "Taille de label_type: " << ui->label_type->size();
    ui->label_type->setMinimumSize(400, 300);  // Définir une taille minimale pour label_type

    // Suppression du layout précédent (s'il y en a un) et ajout du nouveau graphique dans label_type
    if (ui->label_type->layout() != nullptr) {
        delete ui->label_type->layout();
    }

    QVBoxLayout *layout = new QVBoxLayout(ui->label_type);
    layout->addWidget(chartView);
    ui->label_type->setLayout(layout);

    // Forcer le redessin du widget parent
    ui->label_type->repaint();

    // Configuration du son
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(1.0);  // Volume entre 0.0 et 1.0
    player->setSource(QUrl::fromLocalFile("C:/Users/HP/Downloads/intg/button.wav"));
    player->play();
}

void MainWindow::on_ajouterFactureButton_clicked() {
    int id_facture = ui->idFactureLineEdit->text().toInt();
    int id_client = ui->idClientLineEdit->text().toInt();
    double montant = ui->montantLineEdit->text().toDouble();
    QDate date_emise = ui->dateEmiseDateEdit->date();

    Facture facture(id_facture, id_client, montant, date_emise);
    if (facture.ajouter()) {
        QMessageBox::information(this, "Succès", "La facture a été ajoutée.");
        updateTableView();
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout de la facture.");
    }
}

void MainWindow::on_exporterFactureButton_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter la facture", "", "Text Files (*.txt);;All Files (*)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        // Exporter les données de la facture
        QSqlQuery query("SELECT * FROM GS_FACTURE");
        while (query.next()) {
            out << "ID_FACTURE: " << query.value(0).toString() << "\n";
            out << "ID_CLIENT: " << query.value(1).toString() << "\n";
            out << "MONTANT: " << query.value(2).toString() << "\n";
            out << "DATE_EMISE: " << query.value(3).toString() << "\n\n";
        }

        file.close();
        QMessageBox::information(this, "Exportation", "Les factures ont été exportées avec succès.");
    }
}


void MainWindow::on_pushButton_rechercher12_clicked()
{
    // Récupérer le texte de la ligne de recherche
    QString recherche = ui->lineEdit_249->text().trimmed();

    // Créer une requête pour la recherche
    QSqlQuery query;
    QString queryString;

    // Vérifier si l'utilisateur a saisi quelque chose dans le champ de recherche
    if (recherche.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un critère de recherche.");
        return;
    }

    // Vérifier si l'entrée est un entier (pour rechercher par ID_SERVICE)
    bool ok;
    int id1 = recherche.toInt(&ok);
    if (ok) {
        // Recherche par ID_SERVICE
        queryString = QString("SELECT * FROM PROJETCPP2A26.GS_CLIENT WHERE ID= %1").arg(id1);
    } else {
        // Si ce n'est pas un ID, chercher par NOM ou DESCRIPTION
        queryString = QString("SELECT * FROM PROJETCPP2A26.GS_CLIENT WHERE NOM LIKE '%%1%' OR ADRESSE LIKE '%%1%'").arg(recherche);
    }

    // Afficher la requête SQL générée dans le débogage
    qDebug() << "Requête SQL générée : " << queryString;

    // Exécuter la requête SQL
    query.prepare(queryString);
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête de recherche : " << query.lastError().text();
        QMessageBox::critical(this, "Erreur", "Recherche échouée.");
        return;
    }

    // Créer un modèle pour afficher les résultats dans le QTableView
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Vérifier si des résultats ont été trouvés
    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Aucun résultat", "Aucun service trouvé pour ce critère.");
    }

    // Afficher les résultats dans le QTableView
    ui->tableView_10->setModel(model);
}

void MainWindow::updateTableView() {
    Facture f;
    tableView->setModel(f.afficher());
}

void MainWindow::on_pushButton_rechercher_clicked()
{
    // Récupérer le texte de la ligne de recherche
    QString recherche = ui->lineEdit_247->text().trimmed();

    // Créer une requête pour la recherche
    QSqlQuery query;
    QString queryString;

    // Vérifier si l'utilisateur a saisi quelque chose dans le champ de recherche
    if (recherche.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un critère de recherche.");
        return;
    }

    // Vérifier si l'entrée est un entier (pour rechercher par ID_SERVICE)
    bool ok;
    int id = recherche.toInt(&ok);
    if (ok) {
        // Recherche par ID_SERVICE
        queryString = QString("SELECT * FROM PROJETCPP2A26.GS_SERVICE WHERE ID_SERVICE = %1").arg(id);
    } else {
        // Si ce n'est pas un ID, chercher par NOM ou DESCRIPTION
        queryString = QString("SELECT * FROM PROJETCPP2A26.GS_SERVICE WHERE NOM LIKE '%%1%' OR DESCRIPTION LIKE '%%1%'").arg(recherche);
    }

    // Afficher la requête SQL générée dans le débogage
    qDebug() << "Requête SQL générée : " << queryString;

    // Exécuter la requête SQL
    query.prepare(queryString);
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête de recherche : " << query.lastError().text();
        QMessageBox::critical(this, "Erreur", "Recherche échouée.");
        return;
    }

    // Créer un modèle pour afficher les résultats dans le QTableView
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Vérifier si des résultats ont été trouvés
    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Aucun résultat", "Aucun service trouvé pour ce critère.");
    }

    // Afficher les résultats dans le QTableView
    ui->tableView_3->setModel(model);
}

void MainWindow::on_comboBox_tri_currentIndexChanged(const QString &selectedOption)
{
    Client client;
    QSqlQueryModel *model = nullptr;

    if (selectedOption == "nom") {
        model = client.trier_nom();
    } else if (selectedOption == "id") {
        model = client.trier_id();
    } else if (selectedOption == "adresse") {
        model = client.trier_adresse();
    }

    if (model) {
        ui->tableView_10->setModel(model);
    }
}


void MainWindow::on_btnAscendant_clicked()
{
    QString selectedOption = ui->comboBox_tri->currentText();
    Client client;

    QSqlQueryModel *model = nullptr;
    if (selectedOption == "nom") {
        model = client.trier_nom();
    } else if (selectedOption == "id") {
        model = client.trier_id();
    } else if (selectedOption == "adresse") {
        model = client.trier_adresse();
    }

    if (model) {
        ui->tableView_10->setModel(model);
    }
}

void MainWindow::on_btnDescendant_clicked()
{
    QString selectedOption = ui->comboBox_tri->currentText();
    Client client;

    QSqlQueryModel *model = nullptr;
    if (selectedOption == "nom") {
        // Tri décroissant par Nom
        model = client.trier_Denom();"nom";
    } else if (selectedOption == "id") {
        // Tri décroissant par CIN
        model = client.trier_Deid();"id";
    } else if (selectedOption == "adresse") {
        // Tri décroissant par Salaire
        model = client.trier_Deadresse();"adresse";
    }

    if (model) {
        ui->tableView_10->setModel(model);
    }
}


void MainWindow::on_pb_his_clicked()
{

    historique h;

    ui->textBrowser_2->show();
    ui->textBrowser_2->setPlainText(h.read());

    // connect(ui->clearButton, &QPushButton::clicked, &h, &historique::clearHistory);

}


void MainWindow::handleQuestion(const QString &question) {
    // Get a pointer to the QLineEdit that you want to use (ui->lineEdit_9)
    QLineEdit *answerLineEdit = ui->lineEdit_9;

    // Check for a valid QLineEdit pointer
    if (!answerLineEdit) {
        qWarning() << "Pointeur QLineEdit invalide !";
        return;
    }

    // Map of predefined questions and answers in French
    static QMap<QString, QString> answers = {
        {"Comment j'utilise cette application ?", "Pour utiliser cette application, consultez votre emploi du temps. Vous avez 3 maisons à nettoyer aujourd'hui. Utilisez les outils de gestion pour suivre vos tâches."},
        {"Ai-je tous les produits de nettoyage ?", "Il vous manque du produit pour les surfaces vitrées. Veuillez vérifier l'inventaire."},
        {"Puis-je reprogrammer un rendez-vous ?", "Oui, contactez le client pour confirmer une nouvelle heure et mettez à jour l'emploi du temps."},
        {"Que faire si je suis en retard ?", "Veuillez informer le client et ajuster l'emploi du temps en conséquence."},
        {"Comment nettoyer une tache tenace ?", "Utilisez un mélange de bicarbonate de soude et de vinaigre, appliquez-le sur la tache, laissez agir quelques minutes, puis frottez doucement."},
        {"Puis-je demander de l'aide pour des charges lourdes ?", "Oui, utilisez le système de binôme et respectez les protocoles de sécurité pour éviter les blessures."},
        {"Que faire si un client n'est pas satisfait ?", "Écoutez les préoccupations du client, proposez une solution ou faites remonter le problème à un superviseur."},
        {"Où trouver le planning de nettoyage ?", "Le planning est disponible dans le menu principal sous 'Emploi du temps'."},
        {"Que faire des déchets dangereux ?", "Suivez les consignes de l'entreprise pour l'élimination des déchets dangereux et utilisez les bacs de recyclage désignés."},
        {"Comment pointer à l'arrivée et au départ ?", "Utilisez la fonction de suivi du temps dans l'application sous 'Mon Profil'."},
        {"Puis-je prendre une pause ?", "Les pauses sont programmées selon les lois du travail. Consultez votre planning ou demandez à votre superviseur."},
        {"Et si j'ai oublié mes identifiants ?", "Utilisez la fonction 'Mot de passe oublié' sur la page de connexion ou contactez le service informatique."},
        {"Comment signaler un problème de maintenance ?", "Utilisez la fonction 'Signaler un problème' dans l'application ou contactez directement l'équipe de maintenance."},
        {"Quel est le code vestimentaire ?", "Le code vestimentaire est spécifié dans le manuel de l'employé. En général, portez votre uniforme et les équipements de protection appropriés."},
        // Add more predefined questions and answers as needed...
    };
    // Normalize the question (optional but helpful for consistent matching)
    QString normalizedQuestion = question.trimmed(); // Remove extra spaces at the beginning and end.

    // Check if the question exists in the map and set the corresponding answer in the QLineEdit
    if (answers.contains(normalizedQuestion)) {
        answerLineEdit->setText(answers[normalizedQuestion]);
    } else {
        answerLineEdit->setText("Désolé, je ne comprends pas cette question.");
    }
}

void MainWindow::populateListWidget()//list pour envoyer un message privé
{
    QSqlQuery query;
    query.prepare("SELECT NOM, PRENOM FROM PROJETCPP2A26.GS_EMPLOYE");

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    // Clear the list widget before adding new items
    ui->listWidget_2->clear();

    // Populate the list widget with the names
    while (query.next()) {
        QString nom2 = query.value(0).toString();
        QString prenom2 = query.value(1).toString();

        // Create a formatted string with NOM and PRENOM
        QString fullName = nom2 + " " + prenom2;

        // Create a new list widget item and add it to the list
        ui->listWidget_2->addItem(fullName);
    }
}

int  MainWindow::on_connect_clicked()//connection a l'interface du messagerie par id
{
    idc2=ui->lineEdit_10->text().toInt();
    if (recherche(idc2 )){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr(" Connexion reussie  .\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tabWidget_2->setVisible(true);
        ui->nomconnecte->setVisible(true);
        ui->nomid->setVisible(true);
        Employe e;
        e=e.recupere(idc2);
        QString str1 = e.getnom2();
        QString str2 = e.getprenom2();
        QString result = str1 + " " + str2;
        ui->nomid->setText(result);
        ui->label_67->setVisible(false);
        ui->connect->setVisible(false);
        populateListWidget();





        return idc2;
    }else {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr(" erreure de connexion   .\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);




        return 0;
    }
}
void MainWindow::on_send_clicked() {
    ;
    etc = etc.recupere(idc2);

    if (etc.getnom2().isEmpty() || etc.getprenom2().isEmpty()) {
        QMessageBox::warning(this, "Error", "Failed to retrieve employee details.");
        return;
    }

    QString senderNom = etc.getnom2();
    QString senderPrenom = etc.getprenom2();
    QString message = ui->messageg->text();

    if (message.isEmpty()) {
        QMessageBox::warning(this, "Error", "Message cannot be empty.");
        return;
    }

    bool sent = etc.sendMessageGeneral(senderNom, senderPrenom, message);

    if (sent) {
        ui->messageg->clear(); // Clear the message input field
        QMessageBox::information(this, "Success", "Message sent successfully.");
        //refreshMessages();

        // Refresh the public messages immediately
        QString messages = etc.getMessagesPublic(senderNom, senderPrenom);
        if (messages.isEmpty()) {
            ui->textedit1->setPlainText("No public messages available.");
        } else {
            ui->textedit1->setPlainText(messages);
        }
    } else {
        QMessageBox::critical(this, "Error", "Failed to send message.");
    }
}

void MainWindow::on_show_clicked()
{
    // Fetch messages and update UI
    refreshMessages();

    // Set up a timer to refresh messages every 5 seconds (5000 ms)
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::refreshMessages);
    timer->start(5000); // Refresh every 5 seconds
}

void MainWindow::refreshMessages()
{
    // Fetch the current employee and their messages
    Employe e;
    e = e.recupere(idc2);
    if (e.getnom2().isEmpty() || e.getprenom2().isEmpty()) {
        QMessageBox::warning(this, "Error", "Failed to retrieve employee details.");
        return;
    }

    QString messages = e.getMessagesPublic(e.getnom2(), e.getprenom2());

    // Display the messages in the QTextEdit widget
    if (messages.isEmpty()) {
        ui->textedit1->setPlainText("No public messages available.");
    } else {
        ui->textedit1->setPlainText(messages);
    }
}
void MainWindow::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item) {
    // Retrieve the text of the selected item (receiver's full name)
    recivername = item->text();

    // Split the receiver's name into first name and last name
    QStringList nameParts = recivername.split(' ');

    // Ensure the name is correctly formatted (i.e., at least first name and last name)
    if (nameParts.size() < 2) {
        QMessageBox::warning(this, "Error", "Receiver name must contain both first and last names.");
        return; // Exit if the name is not properly formatted
    }

    // Extract the receiver's first name and last name
    receiverNom = nameParts[0]; // First part is the last name
    receiverPrenom = nameParts[1]; // Second part is the first name

    // Debug output to verify
    qDebug() << "Receiver Nom:" << receiverNom;
    qDebug() << "Receiver Prenom:" << receiverPrenom;

    // Optionally, display a message box or debug the receiver name
    QMessageBox::information(this, "Item Selected", "You will send the message to: " + receiverNom);
}
void MainWindow::on_send_2_clicked() {

    etc = etc.recupere(idc2);

    if (etc.getnom2().isEmpty() || etc.getprenom2().isEmpty()) {
        QMessageBox::warning(this, "Error", "Failed to retrieve employee details.");
        return;
    }

    QString senderNom = etc.getnom2();
    QString senderPrenom = etc.getprenom2();
    QString message = ui->messageg_2->text();

    if (message.isEmpty()) {
        QMessageBox::warning(this, "Error", "Message cannot be empty.");
        return;
    }


    // Now, send the private message
    bool sent = etc.sendMessagePrivate(senderNom, senderPrenom, receiverNom, receiverPrenom, message);

    if (sent) {
        ui->messageg_2->clear(); // Clear the message input field
        QMessageBox::information(this, "Success", "Message sent successfully.");
        refreshMessages();

        // Refresh the private messages immediately
        QString messages = etc.getMessagesPrivate(senderNom, senderPrenom);
        if (messages.isEmpty()) {
            ui->textedit1_2->setPlainText("No private messages available.");
        } else {
            ui->textedit1_2->setPlainText(messages);
        }
    } else {
        QMessageBox::critical(this, "Error", "Failed to send message.");
    }
}

void MainWindow::refreshPrivateMessages() {
    Employe etc;
    etc = etc.recupere(idc2);

    QString senderNom = etc.getnom2();
    QString senderPrenom = etc.getprenom2();

    QString messages = etc.getMessagesPrivate(senderNom, senderPrenom);
    if (messages.isEmpty()) {
        ui->textedit1_2->setPlainText("No private messages available.");
    } else {
        ui->textedit1_2->setPlainText(messages);
    }
}

void MainWindow::on_show2_clicked() {
    bool isRefreshing= false ;
    if (isRefreshing) {
        return; // Prevent multiple refreshes if it's already running
    }

    isRefreshing = true;

    // Refresh messages (you can optimize this function to not block the UI)
    refreshPrivateMessages();

    // Reset flag after refreshing
    isRefreshing = false;

    // Set timer to call this again in 5 seconds
    QTimer::singleShot(5000, this, SLOT(on_show2_clicked()));  // Call the function again
}

void MainWindow::on_trier_clicked() //trier le nom alphabétiquement
{
    // Get the current model from the table view
    QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tableView_2->model());
    if (model) {
        // Create a QSortFilterProxyModel and set the source model
        QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(model);

        // Column index for the "NOM" column (assumed to be 1)
        int nomColumnIndex = 1;

        // Toggle between ascending and descending order
        static bool ascending = true;
        proxyModel->sort(nomColumnIndex, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
        ascending = !ascending;  // Toggle the order for next click

        // Set the proxy model as the model for the table view
        ui->tableView_2->setModel(proxyModel);
    }
}

void MainWindow::on_trier_2_clicked()
{
    // Get the current model from the table view
    QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tableView_2->model());
    if (model) {
        // Create a QSortFilterProxyModel and set the source model
        QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(model);

        // Column index for the "NOM" column (assumed to be 1)
        int nomColumnIndex = 4;

        // Toggle between ascending and descending order
        static bool ascending = true;
        proxyModel->sort(nomColumnIndex, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
        ascending = !ascending;  // Toggle the order for next click

        // Set the proxy model as the model for the table view
        ui->tableView_2->setModel(proxyModel);
    }
}//trier par post


void MainWindow::on_tabWidget_7_tabBarClicked(int index)
{
    // statistiques
    QAbstractItemModel *model = ui->tableView_2->model();

    if (!model) {
        return;  // Ensure the model exists
    }

    // Create a map to count the number of people by POST and to sum the SALAIRE by POST
    QMap<QString, int> postCountMap;
    QMap<QString, double> postSalaryMap;

    // Loop through rows in the model (starting from row 0 to model's row count)
    for (int row = 0; row < model->rowCount(); ++row) {
        QString post = model->data(model->index(row, 4)).toString();  // POST column (4)
        double salaire = model->data(model->index(row, 3)).toDouble();  // SALAIRE column (3)

        // Update the post count and post salary
        postCountMap[post]++;
        postSalaryMap[post] += salaire;
    }

    // Create a bar chart for the post count statistics
    QBarSeries *barSeries = new QBarSeries();
    QStringList categories;
    QBarSet *set = new QBarSet("Post Count");

    for (auto it = postCountMap.begin(); it != postCountMap.end(); ++it) {
        *set << it.value();
        categories << it.key();
    }

    barSeries->append(set);

    QChart *barChart = new QChart();
    barChart->addSeries(barSeries);
    barChart->setTitle("Number of People by Post");

    QBarCategoryAxis *axisXBar = new QBarCategoryAxis();
    axisXBar->append(categories);
    barChart->addAxis(axisXBar, Qt::AlignBottom);
    barSeries->attachAxis(axisXBar);

    QValueAxis *axisYBar = new QValueAxis();
    axisYBar->setLabelFormat("%i");
    axisYBar->setTitleText("Count");
    barChart->addAxis(axisYBar, Qt::AlignLeft);
    barSeries->attachAxis(axisYBar);

    // Create a chart view for the bar chart
    QChartView *barChartView = new QChartView(barChart);
    barChartView->setRenderHint(QPainter::Antialiasing);

    // Clear the previous layout in the bar chart widget (optional)
    QLayout *oldLayout = ui->widget->layout();
    if (oldLayout) {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    // Add bar chart view to your existing QWidget container (ui->barChartWidget)
    QVBoxLayout *barLayout = new QVBoxLayout(ui->widget);
    barLayout->addWidget(barChartView);

    // Create a pie chart for the salary distribution by post
    QPieSeries *pieSeries = new QPieSeries();
    QStringList colors = {"#FF0000", "#0000FF", "#008000", "#FFA500"}; // Red, Blue, Green, Orange
    int colorIndex = 0;
    double totalSalary = 0.0;

    // Calculate total salary for percentage calculation
    for (auto it = postSalaryMap.begin(); it != postSalaryMap.end(); ++it) {
        totalSalary += it.value();
    }

    for (auto it = postSalaryMap.begin(); it != postSalaryMap.end(); ++it) {
        QPieSlice *slice = pieSeries->append(it.key(), it.value());
        slice->setBrush(QColor(colors[colorIndex % colors.size()]));
        colorIndex++;

        // Calculate percentage and set the label
        double percentage = (it.value() / totalSalary) * 100;
        slice->setLabelVisible(true);
        slice->setLabel(QString("%1: %2%").arg(it.key()).arg(percentage, 0, 'f', 2)); // Show post and percentage
    }

    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->setTitle("Salary Distribution by Post");

    // Create a chart view for the pie chart
    QChartView *pieChartView = new QChartView(pieChart);
    pieChartView->setRenderHint(QPainter::Antialiasing);

    // Clear the previous layout in the pie chart widget (optional)
    oldLayout = ui->widget_2->layout();
    if (oldLayout) {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    // Add pie chart view to your existing QWidget container (ui->pieChartWidget)
    QVBoxLayout *pieLayout = new QVBoxLayout(ui->widget_2);
    pieLayout->addWidget(pieChartView);
}

bool MainWindow::salaireExists(int salaire) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM PROJETCPP2A26.GS_EMPLOYE WHERE SALAIRE = :salaire"); // Assuming your table is named 'employees' and the column is 'id'
    query.bindValue(":salaire", salaire);

    if (query.exec()) {
        if (query.next()) {
            int count = query.value(0).toInt();
            return count > 0; // Return true if count is greater than 0
        }
    }

    return false; // Return false if query execution fails or no records found
}

void MainWindow::on_recherchesal_clicked()
{
    int   sal ;

    sal=ui->salaireR->text().toInt();
    if (salaireExists(sal)){
        if (salaireExists(sal)) {
            // Prepare the query to get employees with the specific salary
            QSqlQueryModel* model = new QSqlQueryModel();
            model->setQuery(QString("SELECT * FROM PROJETCPP2A26.GS_EMPLOYE WHERE SALAIRE = %1").arg(sal));

            // Set the headers
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("SALAIRE"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("POSTE"));

            // Set the model to the table view
            ui->tableView_2->setModel(model); // Assuming your table v

        }
    }
}


bool MainWindow::posteExists(const QString &poste) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM PROJETCPP2A26.GS_EMPLOYE WHERE  POSTE= :poste "); //
    query.bindValue(":poste", poste);

    if (query.exec()) {
        if (query.next()) {
            int count = query.value(0).toInt();
            return count > 0; // Return true if count is greater than 0
        }
    }

    return false; // Return false if query execution fails or no records found
}

void MainWindow::on_recherchesal_2_clicked()
{
    QString poste = ui->postR->text();  // Get the POSTE from the UI

    if (posteExists(poste)) {
        // Prepare the query to get employees with the specific POSTE
        QSqlQuery query;
        query.prepare("SELECT * FROM PROJETCPP2A26.GS_EMPLOYE WHERE POSTE = :poste");
        query.bindValue(":poste", poste);

        // Execute the query
        if (query.exec()) {
            // Create a new model
            QSqlQueryModel* model = new QSqlQueryModel();

            // Manually set the query result
            model->setQuery(std::move(query));


            // Set headers for the table view
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("SALAIRE"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("POSTE"));

            // Set the model to the table view
            ui->tableView_2->setModel(model);
        } else {
            qDebug() << "Query failed: " << query.lastError().text();  // Debugging query error
        }
    } else {
        qDebug() << "Poste does not exist.";
    }
}

void MainWindow::on_trier_3_clicked()
{
    QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tableView_2->model());
    if (model) {
        // Create a QSortFilterProxyModel and set the source model
        QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(model);

        // Column index for the "SALAIRE" column (assumed to be 3)
        int salaireColumnIndex = 3;

        // Toggle between ascending and descending order
        static bool ascending = true;
        proxyModel->sort(salaireColumnIndex, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
        ascending = !ascending;  // Toggle the order for next click

        // Set the proxy model as the model for the table view
        ui->tableView_2->setModel(proxyModel);
    }

}



void MainWindow::on_comboBox_activated(int index)
{
    // Get the text of the selected item
    QString selectedText = ui->comboBox->currentText();

    // Use the selected text for your logic (e.g., update a label, print, etc.)
    qDebug() << "Selected text: " << selectedText;

    // Now call the handleQuestion function correctly
    handleQuestion( selectedText );

}

void MainWindow::on_pushButton_41_clicked()
{
    int num5 = ui->lineEdit_59->text().toInt();
    int prix5 = ui->lineEdit_60->text().toInt();
    int id_client5 = ui->lineEdit_62->text().toInt();
    QString etat5 = ui->lineEdit_64->text();
    QString type5 = ui->lineEdit_63->text();
    QDate date5 = ui->lineEdit_61->date();

    Commande commande(num5,prix5,id_client5,type5,etat5,date5);
    bool test5 = commande.ajouter5();

    if (test5) {
        ui->tableView_11->setModel(Etmp5.afficher5());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

}
void MainWindow::on_pushButton_68_clicked()
{
    int num5 = ui->lineEdit_250->text().toInt();
    bool test5 = Etmp5.supprimer5(num5);

    if (test5) {
        ui->tableView_11->setModel(Etmp5.afficher5());
        QMessageBox::information(this, "Succès", "Suppression effectuée.");
    } else {
        QMessageBox::critical(this, "Erreur", "Suppression non effectuée.");
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    QString idStr = ui->lineEdit_250->text();
    bool isNumber;
    int num5 = idStr.toInt(&isNumber);

    if (!isNumber) {
        QMessageBox::critical(this, "Erreur", "L'ID doit être un nombre entier valide.");
        return;
    }

    if (Etmp5.idExists5(num5)) {
        // Afficher les champs de modification si l'ID existe
        ui->PRENOMOD_4->setVisible(true);
        ui->ADRESSEMOD_4->setVisible(true);
        ui->TELEPHONEMOD_4->setVisible(true);
        ui->E_MAILMOD_4->setVisible(true);
        ui->PrixHT_50->setVisible(true);
        ui->PrixHT_51->setVisible(true);
        ui->PrixHT_52->setVisible(true);
        ui->PrixHT_53->setVisible(true);
        ui->Enregistrer_40->setVisible(true);
        ui->Annulermodif_40->setVisible(true);
    } else {
        QMessageBox::information(this, "Erreur", "L'num de commande n'existe pas. Veuillez entrer un ID valide.");
    }
}

void MainWindow::on_Enregistrer_40_clicked()
{
    int num5 = ui->lineEdit_250->text().toInt();
    int id_client5 = ui->lineEdit_251->text().toInt();
    QString etat5 = ui->PRENOMOD_4->text();
    QString type5 = ui->ADRESSEMOD_4->text();
    int prix5 = ui->TELEPHONEMOD_4->text().toInt();

    // Vérifier que les champs sont valides
    if (etat5.isEmpty() || type5.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Le nom et la description doivent être remplis.");
        return;
    }

    // Corriger la conversion de la date
    QDate date5 = QDate::fromString(ui->E_MAILMOD_4->text(), "dd-MM-yyyy");
    if (!date5.isValid()) {
        QMessageBox::critical(this, "Erreur", "Date invalide. Veuillez entrer une date correcte.");
        return;
    }

    Commande Co(num5, prix5,id_client5, type5, etat5, date5);
    bool test5 = Co.modifier5();

    if (test5) {
        ui->tableView_11->setModel(Etmp5.afficher5());
        // Masquer les champs après la modification
        ui->PRENOMOD_4->setVisible(false);
        ui->ADRESSEMOD_4->setVisible(false);
        ui->TELEPHONEMOD_4->setVisible(false);
        ui->E_MAILMOD_4->setVisible(false);
        ui->PrixHT_50->setVisible(false);
        ui->PrixHT_51->setVisible(false);
        ui->PrixHT_52->setVisible(false);
        ui->PrixHT_53->setVisible(false);
        ui->Enregistrer_40->setVisible(false);
        ui->Annulermodif_40->setVisible(false);

        // Réinitialiser les champs
        ui->PRENOMOD_4->clear();
        ui->ADRESSEMOD_4->clear();
        ui->TELEPHONEMOD_4->clear();
        ui->E_MAILMOD_4->clear();


        QMessageBox::information(this, "Succès", "Modification effectuée.");
    } else {
        QMessageBox::critical(this, "Erreur", "Modification non effectuée.");
    }
}

void MainWindow::on_Annulermodif_40_clicked()
{
    // Masquer les champs de modification si l'utilisateur annule
    ui->PRENOMOD_4->setVisible(false);
    ui->ADRESSEMOD_4->setVisible(false);
    ui->TELEPHONEMOD_4->setVisible(false);
    ui->E_MAILMOD_4->setVisible(false);
    ui->PrixHT_50->setVisible(false);
    ui->PrixHT_51->setVisible(false);
    ui->PrixHT_52->setVisible(false);
    ui->PrixHT_53->setVisible(false);
    ui->Enregistrer_40->setVisible(false);
    ui->Annulermodif_40->setVisible(false);

    // Réinitialiser les champs
    ui->PRENOMOD_4->clear();
    ui->ADRESSEMOD_4->clear();
    ui->TELEPHONEMOD_4->clear();
    ui->E_MAILMOD_4->clear();

}



void MainWindow::on_comboBox_tri_5_clicked(int index5)
{
    // Créer une requête pour trier les services
    QSqlQuery query;
    QString queryString;

    // Vérifier le choix de l'utilisateur dans le QComboBox
    if (index == 0) {  // Si l'utilisateur choisit "ID"
        queryString = "SELECT * FROM PROJETCPP2A26.GS_COMMANDE ORDER BY TYPE";
    } else if (index == 1) {  // Si l'utilisateur choisit "Nom"
        queryString = "SELECT * FROM PROJETCPP2A26.GS_COMMANDE ORDER BY ETAT";
    } else if (index == 2) {  // Si l'utilisateur choisit "DATE_COMMANDE"
        queryString = "SELECT * FROM PROJETCPP2A26.GS_COMMANDE ORDER BY DATE_COMMANDE";
    }

    // Afficher la requête SQL dans le débogage
    qDebug() << "Requête SQL générée : " << queryString;

    // Exécuter la requête SQL
    query.prepare(queryString);
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête de tri : " << query.lastError().text();
        return;
    }

    // Créer un modèle de requêtes pour afficher les données dans le QTableView
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Afficher les résultats dans le QTableView
    ui->tableView_11->setModel(model);
}


void MainWindow::on_pushButton_exporter_40_clicked()
{



    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer en PDF", "", "PDF Files (*.pdf);;All Files (*)");
    if (filePath.isEmpty()) {
        return;
    }


    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
        filePath += ".pdf";
    }


    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    if (!painter.isActive()) {
        QMessageBox::warning(this, "Erreur", "Impossible de créer le fichier PDF.");
        return;
    }


    QAbstractItemModel *model = ui->tableView_11->model();
    if (!model) {
        QMessageBox::warning(this, "Erreur", "Aucun modèle trouvé dans le tableau.");
        return;
    }


    int rows = model->rowCount();
    int cols = model->columnCount();

    int startX = 50;
    int startY = 50;
    int cellWidth = 120;
    int cellHeight = 30;

    int currentY = startY;


    for (int col = 0; col < cols; ++col) {
        QRect rect(startX + col * cellWidth, currentY, cellWidth, cellHeight);
        painter.drawRect(rect);
        painter.drawText(rect, Qt::AlignCenter, model->headerData(col, Qt::Horizontal).toString());
    }

    currentY += cellHeight;


    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            QRect rect(startX + col * cellWidth, currentY, cellWidth, cellHeight);
            painter.drawRect(rect);
            painter.drawText(rect, Qt::AlignCenter, model->data(model->index(row, col)).toString());
        }
        currentY += cellHeight;


        if (currentY + cellHeight > pdfWriter.height()) {
            pdfWriter.newPage();
            currentY = startY + cellHeight;
        }
    }

    painter.end();

    QMessageBox::information(this, "Succès", "Le tableau a été exporté avec succès en PDF !");
}






void MainWindow::on_tabWidget_40_currentChanged()
{
    QSqlQuery query;

    // Récupérer le nombre total de services dans la base de données
    query.prepare("SELECT COUNT(*) FROM PROJETCPP2A26.GS_COMMANDE");
    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération du nombre total de services : " << query.lastError().text();
        return;
    }

    query.next();
    int totalServices = query.value(0).toInt();
    qDebug() << "Total Services: " << totalServices;

    if (totalServices == 0) {
        QMessageBox::warning(this, "Aucun service", "Aucun service trouvé dans la base de données.");
        return;
    }

    // Création de la série de données pour le graphique circulaire (camembert)
    QPieSeries *series = new QPieSeries();

    // Récupérer le nombre de services par nom (type de service)
    query.prepare("SELECT NOM, COUNT(*) FROM PROJETCPP2A26.GS_COMMANDE GROUP BY ETAT");
    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des services par nom : " << query.lastError().text();
        return;
    }

    // Ajouter les services à la série
    while (query.next()) {
        QString serviceName = query.value(0).toString();  // NOM de service
        int serviceCount = query.value(1).toInt();  // Compter le nombre de services

        double percentage = (static_cast<double>(serviceCount) / totalServices) * 100;
        qDebug() << "Service: " << serviceName << ", Nombre: " << serviceCount << ", Pourcentage: " << percentage;

        // Ajouter la donnée à la série avec le nom et le nombre
        QPieSlice *slice = series->append(serviceName + ": " + QString::number(percentage, 'f', 2) + "%", serviceCount);

        // Rendre l'étiquette visible
        slice->setLabelVisible(true);

        // Ajouter une couleur pour rendre les labels visibles sur un fond blanc (optionnel)
        slice->setLabelColor(Qt::black);  // Changez la couleur si nécessaire
        slice->setLabelFont(QFont("Arial", 10));  // Police et taille du texte des labels
    }

    if (series->count() == 0) {
        qDebug() << "Aucune donnée à afficher dans la série";
        return;
    }

    // Création du graphique
    QChart *chart = new QChart();
    chart->setBackgroundBrush(QBrush(Qt::white));  // Fond blanc pour le graphique
    chart->setTitle("Répartition des services par nom");
    chart->addSeries(series);
    chart->legend()->hide();  // Masquer la légende

    // Création de la vue du graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  // Activer l'anticrénelage pour améliorer l'affichage
    chartView->setMinimumSize(400, 300);  // Définir une taille minimale pour s'assurer qu'il est visible

    // Vérification de la taille du widget parent
    qDebug() << "Taille de label_type: " << ui->label_type->size();
    ui->label_type->setMinimumSize(400, 300);  // Définir une taille minimale pour label_type

    // Suppression du layout précédent (s'il y en a un) et ajout du nouveau graphique dans label_type
    if (ui->label_type_20->layout() != nullptr) {
        delete ui->label_type_20->layout();
    }

    QVBoxLayout *layout = new QVBoxLayout(ui->label_type_20);
    layout->addWidget(chartView);
    ui->label_type_20->setLayout(layout);

    // Forcer le redessin du widget parent
    ui->label_type_20->repaint();

    // Configuration du son
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(1.0);  // Volume entre 0.0 et 1.0
    player->setSource(QUrl::fromLocalFile("C:/Users/HP/Downloads/intg/button.wav"));
    player->play();
}






void MainWindow::on_pushButton_rechercher12_2_clicked()
{
    // Récupérer le texte de la ligne de recherche
    QString recherche12 = ui->lineEdit_250->text().trimmed();

    // Créer une requête pour la recherche
    QSqlQuery query;
    QString queryString;

    // Vérifier si l'utilisateur a saisi quelque chose dans le champ de recherche
    if (recherche12.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un critère de recherche.");
        return;
    }

    // Vérifier si l'entrée est un entier (pour rechercher par ID_SERVICE)
    bool ok;
    int num5 = recherche12.toInt(&ok);
    if (ok) {
        // Recherche par ID_SERVICE
        queryString = QString("SELECT * FROM PROJETCPP2A26.GS_COMMANDE WHERE NUM_COMMANDE = %1").arg(num5);
    } else {
        // Si ce n'est pas un ID, chercher par NOM ou DESCRIPTION
        queryString = QString("SELECT * FROM PROJETCPP2A26.GS_COMMANDE WHERE ETAT LIKE '%%1%' OR ID_CLIENT LIKE '%%1%'").arg(recherche12);
    }

    // Afficher la requête SQL générée dans le débogage
    qDebug() << "Requête SQL générée : " << queryString;

    // Exécuter la requête SQL
    query.prepare(queryString);
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête de recherche : " << query.lastError().text();
        QMessageBox::critical(this, "Erreur", "Recherche échouée.");
        return;
    }

    // Créer un modèle pour afficher les résultats dans le QTableView
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Vérifier si des résultats ont été trouvés
    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Aucun résultat", "Aucun service trouvé pour ce critère.");
    }

    // Afficher les résultats dans le QTableView
    ui->tableView_11->setModel(model);
}



void MainWindow::on_pushButton_72_clicked()
{
    int id7 = ui->lineEdit_91->text().toInt();
    int prix_v = ui->lineEdit_93->text().toInt();
    int prix_a = ui->lineEdit_92->text().toInt();
    int quantite= ui->lineEdit_94->text().toInt();
    QString nom7 = ui->lineEdit_90->text();

    Produit P( nom7,id7,prix_v ,prix_a,quantite);
    bool test7 = P.ajouter7();

    if (test7) {
        ui->tableView_4->setModel(Etmp7.afficher7());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_pushButton_74_clicked()
{
    int id7 = ui->lineEdit_248->text().toInt();
    bool test7=Etmp7.supprimer7(id7);

    if (test7) {
        ui->tableView_4->setModel(Etmp7.afficher7());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("suppression effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("suppression non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


//void MainWindow::on_pushButton_3_clicked()
//{
//  int id = ui->lineEdit_ID_5->text().toInt();
//int nouveauPrix = ui->lineEdit_nouveauPRIX->text().toInt();
//int nouvelleDate = ui->lineEdit_nouvelleDATE->text().toInt();
//QString nouveauNom = ui->lineEdit_nouveauNOM->text();
//QString nouvelleDescription = ui->lineEdit_nouvelleDESCRIPTION->text();

//Service service; // Créez une instance de Service, ou récupérez l'instance que vous souhaitez modifier
//bool test = service.modifier(id, nouveauPrix, nouvelleDate, nouveauNom, nouvelleDescription);

//if (test) {
//  QMessageBox::information(this, tr("Succès"), tr("Service modifié avec succès."));
//} else {
//  QMessageBox::warning(this, tr("Erreur"), tr("Aucun service trouvé avec cet ID."));
//}
//}


void MainWindow::on_pushButton_73_clicked()
{
    QString idStr7 = ui->lineEdit_248->text(); // Get the text from the line edit
    bool isNumber; // Variable to check if the conversion is successful

    // Convert the input string to an integer
    int id7 = idStr7.toInt(&isNumber); // Convert to int and set isNumber based on success

    // Check if the input is not a valid number
    if (!isNumber) {
        QMessageBox::critical(nullptr, QObject::tr("Invalid Input"),
                              QObject::tr("L'ID doit être un nombre entier valide.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return; // Exit the function if the input is invalid
    }

    // Proceed to check if the ID exists
    if (Etmp7.idExists7(id7)) {
        // Show the fields for modification
        ui->Nommodifier_7->setVisible(true);
        ui->Prixmodifier_7->setVisible(true);
        ui->EMPLOYEmodifier_8->setVisible(true);
        ui->EMPLOYEmodifier_7->setVisible(true);
        ui->PrixHT_70->setVisible(true);
        ui->PrixHT_71->setVisible(true);
        ui->PrixHT_72->setVisible(true);
        ui->PrixHT_73->setVisible(true);
        ui->Enregistrer_7->setVisible(true);
        ui->Annulermodif_7->setVisible(true);



    } else {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Cette ID n'existe pas. Vous devez saisir une CIN valide.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_Enregistrer_7_clicked()
{
    int id7 = ui->lineEdit_248->text().toInt();  // Convert the entered string to an integer because the id attribute is of type int
    QString nom7=ui->Nommodifier_7->text();
    int prix_v=ui->Prixmodifier_7->text().toInt();
    int prix_a=ui->EMPLOYEmodifier_7->text().toInt();
    int quantite=ui->EMPLOYEmodifier_8->text().toInt();
    Produit P( nom7,id7,prix_v ,prix_a,quantite);
     bool test7=P.modifier7();
    if(test7) // Si requête exécutée => QMessageBox::information
    {

        ui->tableView_4->setModel(Etmp7.afficher7());
        ui->Nommodifier_7->setVisible(false);
        ui->Prixmodifier_7->setVisible(false);
        ui->EMPLOYEmodifier_8->setVisible(false);
        ui->EMPLOYEmodifier_7->setVisible(false);
        ui->PrixHT_70->setVisible(false);
        ui->PrixHT_71->setVisible(false);
        ui->PrixHT_72->setVisible(false);
        ui->PrixHT_73->setVisible(false);
        ui->PrixHT_19->setVisible(false);
        ui->Enregistrer_7->setVisible(false);
        ui->Annulermodif_7->setVisible(false);

        ui->Nommodifier_7->clear();
        ui->EMPLOYEmodifier_8->clear();
        ui->Prixmodifier_7->clear();
        ui->EMPLOYEmodifier_7->clear();
        ui->tableView_4->setModel(Etmp7.afficher7());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("modification effectué.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else // Si requête non exécutée => QMessageBox::critical
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("modification non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

}


void MainWindow::on_Annulermodif_7_clicked()
{

    ui->Nommodifier_7->setVisible(false);
    ui->Prixmodifier_7->setVisible(false);
    ui->EMPLOYEmodifier_8->setVisible(false);
    ui->EMPLOYEmodifier_7->setVisible(false);
    ui->PrixHT_70->setVisible(false);
    ui->PrixHT_71->setVisible(false);
    ui->PrixHT_72->setVisible(false);
    ui->PrixHT_73->setVisible(false);
    ui->PrixHT_19->setVisible(false);
    ui->Enregistrer_7->setVisible(false);
    ui->Nommodifier_7->clear();
    ui->EMPLOYEmodifier_8->clear();
    ui->Prixmodifier_7->clear();
    ui->EMPLOYEmodifier_7->clear();
}

void MainWindow::on_ComboBox_trier_7_clicked(int index7)
{
    // Créer une requête pour trier les services
    QSqlQuery query;
    QString queryString;

    // Vérifier le choix de l'utilisateur dans le QComboBox
    if (index7 == 0) {  // Si l'utilisateur choisit "ID"
        queryString = "SELECT * FROM PROJETCPP2A26.GS_PRODUIT ORDER BY ID_PRODUIT";
    } else if (index7 == 1) {  // Si l'utilisateur choisit "Nom"
        queryString = "SELECT * FROM PROJETCPP2A26.GS_PRODUIT ORDER BY NOM";
    } else if (index7 == 2) {  // Si l'utilisateur choisit "DATE_ESTIME"
        queryString = "SELECT * FROM PROJETCPP2A26.GS_PRODUIT ORDER BY QUANTITE";
    }

    // Afficher la requête SQL dans le débogage
    qDebug() << "Requête SQL générée : " << queryString;

    // Exécuter la requête SQL
    query.prepare(queryString);
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête de tri : " << query.lastError().text();
        return;
    }

    // Créer un modèle de requêtes pour afficher les données dans le QTableView
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Afficher les résultats dans le QTableView
    ui->tableView_4->setModel(model);
}


void MainWindow::on_pushButton_exporter_70_clicked()
{



    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer en PDF", "", "PDF Files (*.pdf);;All Files (*)");
    if (filePath.isEmpty()) {
        return;
    }


    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
        filePath += ".pdf";
    }


    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    if (!painter.isActive()) {
        QMessageBox::warning(this, "Erreur", "Impossible de créer le fichier PDF.");
        return;
    }


    QAbstractItemModel *model = ui->tableView_4->model();
    if (!model) {
        QMessageBox::warning(this, "Erreur", "Aucun modèle trouvé dans le tableau.");
        return;
    }


    int rows = model->rowCount();
    int cols = model->columnCount();

    int startX = 50;
    int startY = 50;
    int cellWidth = 120;
    int cellHeight = 30;

    int currentY = startY;


    for (int col = 0; col < cols; ++col) {
        QRect rect(startX + col * cellWidth, currentY, cellWidth, cellHeight);
        painter.drawRect(rect);
        painter.drawText(rect, Qt::AlignCenter, model->headerData(col, Qt::Horizontal).toString());
    }

    currentY += cellHeight;


    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            QRect rect(startX + col * cellWidth, currentY, cellWidth, cellHeight);
            painter.drawRect(rect);
            painter.drawText(rect, Qt::AlignCenter, model->data(model->index(row, col)).toString());
        }
        currentY += cellHeight;


        if (currentY + cellHeight > pdfWriter.height()) {
            pdfWriter.newPage();
            currentY = startY + cellHeight;
        }
    }

    painter.end();

    QMessageBox::information(this, "Succès", "Le tableau a été exporté avec succès en PDF !");
}
void MainWindow::on_tabWidget_70_currentChanged()
{
    QSqlQuery query;

    // Récupérer le nombre total de services dans la base de données
    query.prepare("SELECT COUNT(*) FROM PROJETCPP2A26.GS_PRODUIT");
    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération du nombre total de services : " << query.lastError().text();
        return;
    }

    query.next();
    int totalServices = query.value(0).toInt();
    qDebug() << "Total Services: " << totalServices;

    if (totalServices == 0) {
        QMessageBox::warning(this, "Aucun service", "Aucun service trouvé dans la base de données.");
        return;
    }

    // Création de la série de données pour le graphique circulaire (camembert)
    QPieSeries *series = new QPieSeries();

    // Récupérer le nombre de services par nom (type de service)
    query.prepare("SELECT NOM, COUNT(*) FROM PROJETCPP2A26.GS_PRODUIT GROUP BY NOM");
    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des services par nom : " << query.lastError().text();
        return;
    }

    // Ajouter les services à la série
    while (query.next()) {
        QString serviceName = query.value(0).toString();  // NOM de service
        int serviceCount = query.value(1).toInt();  // Compter le nombre de services

        double percentage = (static_cast<double>(serviceCount) / totalServices) * 100;
        qDebug() << "Service: " << serviceName << ", Nombre: " << serviceCount << ", Pourcentage: " << percentage;

        // Ajouter la donnée à la série avec le nom et le nombre
        QPieSlice *slice = series->append(serviceName + ": " + QString::number(percentage, 'f', 2) + "%", serviceCount);

        // Rendre l'étiquette visible
        slice->setLabelVisible(true);

        // Ajouter une couleur pour rendre les labels visibles sur un fond blanc (optionnel)
        slice->setLabelColor(Qt::black);  // Changez la couleur si nécessaire
        slice->setLabelFont(QFont("Arial", 10));  // Police et taille du texte des labels
    }

    if (series->count() == 0) {
        qDebug() << "Aucune donnée à afficher dans la série";
        return;
    }

    // Création du graphique
    QChart *chart = new QChart();
    chart->setBackgroundBrush(QBrush(Qt::white));  // Fond blanc pour le graphique
    chart->setTitle("Répartition des services par nom");
    chart->addSeries(series);
    chart->legend()->hide();  // Masquer la légende

    // Création de la vue du graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  // Activer l'anticrénelage pour améliorer l'affichage
    chartView->setMinimumSize(400, 300);  // Définir une taille minimale pour s'assurer qu'il est visible

    // Vérification de la taille du widget parent
    qDebug() << "Taille de label_type: " << ui->label_type_7->size();
    ui->label_type_7->setMinimumSize(400, 300);  // Définir une taille minimale pour label_type

    // Suppression du layout précédent (s'il y en a un) et ajout du nouveau graphique dans label_type
    if (ui->label_type_7->layout() != nullptr) {
        delete ui->label_type_7->layout();
    }

    QVBoxLayout *layout = new QVBoxLayout(ui->label_type_7);
    layout->addWidget(chartView);
    ui->label_type_7->setLayout(layout);

    // Forcer le redessin du widget parent
    ui->label_type_7->repaint();

    // Configuration du son
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(1.0);  // Volume entre 0.0 et 1.0
    player->setSource(QUrl::fromLocalFile("C:/Users/HP/Downloads/intg/button.wav"));
    player->play();
}

void MainWindow::on_pushButton_rechercher70_clicked()
{

    QString recherche = ui->lineEdit_248->text().trimmed();


    QSqlQuery query;
    QString queryString;


    if (recherche.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un critère de recherche.");
        return;
    }


    bool ok;
    int id7 = recherche.toInt(&ok);
    if (ok) {

        queryString = QString("SELECT * FROM PROJETCPP2A26.GS_PRODUIT WHERE ID_PRODUIT= %1").arg(id7);
    } else {

        queryString = QString("SELECT * FROM PROJETCPP2A26.GS_PRODUIT WHERE NOM LIKE '%%1%' OR QUANTITE LIKE '%%1%'").arg(recherche);
    }


    qDebug() << "Requête SQL générée : " << queryString;


    query.prepare(queryString);
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête de recherche : " << query.lastError().text();
        QMessageBox::critical(this, "Erreur", "Recherche échouée.");
        return;
    }


    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Vérifier si des résultats ont été trouvés
    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Aucun résultat", "Aucun service trouvé pour ce critère.");
    }


    ui->tableView_4->setModel(model);
}


