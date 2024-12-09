#include "mainwindow.h"
#include "ui_commande.h"
#include"arduino.h"
#include"commande.h"
#include"QMessageBox"
#include<Qstring>
#include"QDate"
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QSqlTableModel>
#include <QSqlError>
#include<QIntValidator>
#include"QRegularExpression"
#include<QTimer>
#include <QtNetwork>
#include <QtSql>
#include <QProcess>
#include <QStringList>
#include<QStandardItemModel>
#include<QPainter>
#include<QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
//******
#include<QSqlTableModel>
#include <QSqlError>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>
#include <QtSql>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QAction>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QCursor>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QDialog>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QSqlQuery>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include "service.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDate>
#include <QPageSize>
#include <QTableView>
#include <QTextDocument>
#include <QPrinter>
#include "facture.h"
#include <QtSql/QSqlQueryModel>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QPen>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSqlQueryModel>
#include <QPieSeries>
#include <QChart>
#include <QChartView>
#include "email.h"
#include "client.h"
#include "historique.h"
#include "employe.h"
#include <QTimer>
#include <QtCharts/QLineSeries>
#include <QSortFilterProxyModel>




#include <QMap>
SentimentAnalyzer::SentimentAnalyzer() {
    // Initialiser les mots-clés positifs et négati
    positiveWords = {
        {"heureux", 1}, {"tres bien", 1}, {"excellent", 1}, {"satisfait", 1},
        {"joyeux", 1}, {"parfait", 1}, {"merci", 1}
    };
    negativeWords = {
        {"mauvais", -1}, {"horrible", -1}, {"déçu", -1}, {"problème", -1},
        {"moche", -1}, {"triste", -1}, {"insatisfait", -1}
    };
}

#include <QRegularExpression>

int SentimentAnalyzer::analyseSentiment(const QString &text) {
    int score = 0;

    // Convertir le texte en mots en utilisant QRegularExpression
    QRegularExpression re("\\W+"); // Expression régulière pour diviser par les non-lettres
    QStringList words = text.split(re);

    // Analyser chaque mot
    for (const QString &word : words) {
        QString lowerWord = word.toLower();

        // Si le mot est positif
        if (positiveWords.contains(lowerWord)) {
            score += positiveWords[lowerWord];
        }

        // Si le mot est négatif
        if (negativeWords.contains(lowerWord)) {
            score += negativeWords[lowerWord];
        }
    }

    return score; // Score > 0 : Positif, < 0 : Négatif, = 0 : Neutre
}

QString SentimentAnalyzer::obtenirSentiment(const QString &text) {
    int score = analyseSentiment(text);

    if (score > 0)
        return "Positif";
    else if (score < 0)
        return "Négatif";
    else
        return "Neutre";
}


#include <QTabWidget>
#include <QWidget>
#include <QVBoxLayout>
#include<QStackedWidget>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this); // Set up the UI

    // Connecter les boutons aux pages du QStackedWidget
    connect(ui->pushButton_employe, &QPushButton::clicked, this, &MainWindow::showEmployePage);
    connect(ui->pushButton_client, &QPushButton::clicked, this, &MainWindow::showClientPage);
    connect(ui->pushButton_commande, &QPushButton::clicked, this, &MainWindow::showCommandePage);
     connect(ui->pushButton_produit, &QPushButton::clicked, this, &MainWindow::showproduitPage);
      connect(ui->pushButton_service, &QPushButton::clicked, this, &MainWindow::showservicePage);
       connect(ui->pushButton_maintenance, &QPushButton::clicked, this, &MainWindow::showmaintenancePage);

      connect(ui->pushButton_employe, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
      connect(ui->pushButton_client, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
      connect(ui->pushButton_commande, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
      connect(ui->pushButton_produit, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
      connect(ui->pushButton_service, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
      connect(ui->pushButton_maintenance, &QPushButton::clicked, this, &MainWindow::onButtonClicked);


    // Page initiale affichée par défaut (exemple : employé)
    ui->stackedWidget->setCurrentIndex(0);

on_comboBox_tri_currentIndexChanged(ui->comboBox_tri->currentIndex());
    // Set the model for tableView_5
    ui->tableView_6->setModel(p.Afficher());

    // Connect signals and slots for buttons
    connect(ui->pushButtonCalculer, &QPushButton::clicked, this, &MainWindow::on_pushButtonCalculer_clicked);
    connect(ui->supprimer, &QPushButton::clicked, this, &MainWindow::on_supprimer_clicked);
    //connect(ui->ModifierButton, &QPushButton::clicked, this, &MainWindow::on_ModifierButton_clicked);
    connect(ui->pushButton_ajouter, &QPushButton::clicked, this, &MainWindow::on_pushButton_save_clicked);

    connect(ui->pushButton_exporter, &QPushButton::clicked, this, &MainWindow::on_pushButton_exporter_clicked);
    connect(ui->rechercheri, &QPushButton::clicked, this, &MainWindow::on_rechercheri_clicked);
    connect(ui->Update, &QPushButton::clicked, this, &MainWindow::on_Update_clicked);

    // Tray Icon Setup
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/images/tray_icon.png"));
    trayIcon->show();



    // Set up scroll area
    if (!ui->scrollArea->widget()->layout()) {
        QVBoxLayout *scrollLayout = new QVBoxLayout();
        ui->scrollArea->widget()->setLayout(scrollLayout);
    }

    // Call external functions
    executerScriptPython();
    mettreAJourScrollArea();
    afficherGraphiqueSentiments();
    updateCommandeStatus();

    // Table View Settings
    ui->tableView_5->setAlternatingRowColors(true);
    ui->tableView_5->setModel(cmd.afficher());

    // Search Timer Setup
    searchTimer = new QTimer(this);
    searchTimer->setInterval(1500);
    searchTimer->setSingleShot(true);  // Trigger once after the user stops typing

    // Connect textChanged signal to start the timer
    connect(ui->lineEdit_code, &QLineEdit::textChanged, this, [=]() {
        searchTimer->start();
    });
    connect(searchTimer, &QTimer::timeout, this, &MainWindow::searchAndDisplayCommande);

    // Error labels for input validation
    ui->idErrorLabel->setStyleSheet("QLabel { color : red; }");
    ui->idErrorLabel->setText("");
    ui->prixErrorLabel->setStyleSheet("QLabel { color : red; }");
    ui->prixErrorLabel->setText("");
    ui->clientError->setStyleSheet("QLabel { color : red; }");
    ui->clientError->setText("");
    ui->codeErrorLabel->setStyleSheet("QLabel { color : red; }");
    ui->codeErrorLabel->setText("");
    ui->error->setStyleSheet("QLabel { color : red; }");
    ui->error->setText("");

    // Connect textChanged signals for validation
    connect(ui->lineEdit_num, &QLineEdit::textChanged, this, &MainWindow::validateID);
    connect(ui->lineEdit_prix, &QLineEdit::textChanged, this, &MainWindow::validatePrix);
    connect(ui->lineEdit_client, &QLineEdit::textChanged, this, &MainWindow::validateidClient);
    connect(ui->line_code, &QLineEdit::textChanged, this, &MainWindow::validateCO);

    // Connect comboBox for sorting
    connect(ui->comboBox_tri, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_tri_currentIndexChanged(int)));

    // Connect button for generating statistics
    connect(ui->pushButton_stat, &QPushButton::clicked, this, &MainWindow::genererStatistiquesParEtat);

    // Connect search button for command search
    connect(ui->pushButton_rechercher, &QPushButton::clicked, this, &MainWindow::rechercherCommandeParCode);

    // Connect textChanged signal for line_code to update scroll area
    connect(ui->line_code, &QLineEdit::textChanged, this, &MainWindow::mettreAJourScrollArea);

    connect(ui->lineEdit_num, &QLineEdit::textChanged, this, &MainWindow::updateFields);
    connect(ui->pushButton_actualiser, &QPushButton::clicked, this, &MainWindow::on_pushButton_actualiser_clicked);




    // Initialisation d'Arduino
   /* if (arduino.connectArduino() != 0) {
        qDebug() << "[ERREUR] Connexion à Arduino échouée.";
        // Optionnel : désactiver le bouton envoyer si Arduino n'est pas connecté
        ui->sendButton->setEnabled(false);
    }*/
   // connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendMessageToArduino);
    connect(ui->pushButton_update, &QPushButton::clicked, this, &MainWindow::updateMachineStatus);
    connect(ui->pushButton_annuler, &QPushButton::clicked, this, &MainWindow::onPushButtonAnnulerClicked);

//******************************************************************//
    connect(ui->ComboBox_trier, SIGNAL(currentIndexChanged(int)), this, SLOT(on_ComboBox_trier_clicked(int)));

    tableView = new QTableView(this);
    ui->verticalLayout->addWidget(tableView);


    updateTableView();
    // Initialiser l'affichage de la table
    ui->tableView_3->setModel(Etmp.afficher());
    ui->tableView_10->setModel(Etmp1.afficher1());
    ui->tableView_2->setModel(Emp2.afficher2());
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
    ui->tabWidget_maintenance->setVisible(false);
    ui->nomconnecte->setVisible(false);
    ui->nomid->setVisible(false );
    temperatureCheckTimer = new QTimer(this);

    temperatureCheckTimer->start(10000); // Chec
}


void MainWindow::showEmployePage()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::showClientPage()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::showCommandePage()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::showproduitPage()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::showservicePage()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::showmaintenancePage()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->tabWidget_maintenance->show();
}

void MainWindow::onButtonClicked() {
    // Réinitialiser le style de tous les boutons
    ui->pushButton_employe->setStyleSheet("background: #1f77b4; color: white; border: 2px solid #005a9e;");
   ui-> pushButton_client->setStyleSheet("background: #1f77b4; color: white; border: 2px solid #005a9e;");
    ui->pushButton_commande->setStyleSheet("background: #1f77b4; color: white; border: 2px solid #005a9e;");
   ui->pushButton_produit->setStyleSheet("background: #1f77b4; color: white; border: 2px solid #005a9e;");
    ui->pushButton_service->setStyleSheet("background: #1f77b4; color: white; border: 2px solid #005a9e;");
     ui->pushButton_maintenance->setStyleSheet("background: #1f77b4; color: white; border: 2px solid #005a9e;");

    // Appliquer le style au bouton cliqué
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton) {
        clickedButton->setStyleSheet("background: #80cfff; color: white; border: 2px solid #005a9e;"); // Couleur bleu clair
    }
}
//****arduino***************************//
/*void MainWindow::sendMessageToArduino()
{
    QString id_machine = ui->lineEdit_id->text();
    if (id_machine.isEmpty()) {
        qDebug() << "[ATTENTION] L'ID est vide.";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT etat FROM gs_machine WHERE id_machine = :id_machine");
    query.bindValue(":id_machine", id_machine);

    if (!query.exec()) {
        qDebug() << "[ERREUR] Échec de l'exécution de la requête SQL :" << query.lastError().text();
        QMessageBox::critical(this, "Erreur Base de Données", "Impossible de récupérer l'état.");
        return;
    }

    if (!query.next()) {
        qDebug() << "[ATTENTION] Aucun état trouvé pour l'ID :" << id_machine;
        QString message = "ID: " + id_machine + ",n'existe pas";  // Message for non-existing ID
        arduino.write_to_arduino(message.toUtf8());
        return;
    }

    QString etat = query.value("etat").toString();
    QString message = "ID: " + id_machine + ", Etat: " + etat;
    qDebug() << "Message construit :" << message;

    arduino.write_to_arduino(message.toUtf8());
}*/
void MainWindow::readFromArduino() {
    QByteArray data = arduino.read_from_arduino();  // Assuming 'a' is correctly defined elsewhere in your code
    if (!data.isEmpty()) {
        // Convert the data to a QString for easier manipulation
        QString dataStr = QString::fromUtf8(data);

        // Look for the "Temperature: " keyword in the data and extract the value
        if (dataStr.contains("Temperature: ")) {
            // Extract the substring that follows "Temperature: "
            QString tempStr = dataStr.split("Temperature: ").last();  // Get the part after "Temperature: "
            tempStr = tempStr.split(" ")[0];  // Get the part before the space (in case of other strings after the temperature)

            bool ok;
            float temperature = tempStr.toFloat(&ok);  // Convert the string to float

            if (ok) {  // If conversion is successful
                qDebug() << "Temperature read from Arduino: " << temperature;

                // If temperature is above 30°C
                if (temperature > 30.0) {
                    if (!highTempFlag) {  // If high temperature detected for the first time
                        QString etat = "panne";
                        machineId = 123; // Use your actual machine ID here

                        // Update machine state in the database
                        QSqlQuery query;
                        query.prepare("UPDATE GS_MACHINE SET ETAT = :etat WHERE ID_MACHINE = :id");
                        query.bindValue(":etat", etat);
                        query.bindValue(":id", QString::number(machineId));

                        if (!query.exec()) {
                            qDebug() << "Error updating record:" << query.lastError();
                        } else {
                            qDebug() << "Record updated successfully!";
                        }

                        // Show a warning message
                        QMessageBox::warning(this, "Warning", "Haute température détectée! Machine en panne.");

                        // Display the machine ID and state on your interface
                        displayMachineStatus(machineId, etat);

                        // Record the time when high temperature was detected
                        highTempDetectedTime = QDateTime::currentDateTime();
                        highTempFlag = true;
                    }
                } else {
                    // If the temperature drops below 30°C, record the time it happened
                    if (highTempFlag && temperature <= 30.0) {
                        if (timeSinceLastUpdate.isNull()) {
                            timeSinceLastUpdate = QDateTime::currentDateTime();  // Store the time when temperature drops below 30
                        }

                        // Check if the temperature has been below 30°C for at least 30 seconds
                        if (timeSinceLastUpdate.isValid() && timeSinceLastUpdate.secsTo(QDateTime::currentDateTime()) >= 20) {
                            // Change the machine status to 'disponible' after 30 seconds
                            QString etat = "disponible";
                            QSqlQuery query;
                            query.prepare("UPDATE GS_MACHINE SET ETAT = :etat WHERE ID_MACHINE = :id");
                            query.bindValue(":etat", etat);
                            query.bindValue(":id", QString::number(machineId));

                            if (!query.exec()) {
                                qDebug() << "Error updating record:" << query.lastError();
                            } else {
                                qDebug() << "Record updated successfully!";
                            }

                            // Show a message box when the machine becomes available again
                            QMessageBox::information(this, "Machine Status", "Machine maintenant disponible.");

                            // Display the machine ID and state on your interface
                            displayMachineStatus(machineId, etat);

                            // Reset the flag and the time
                            highTempFlag = false;
                            timeSinceLastUpdate = QDateTime();  // Clear the time
                        }
                    }
                }
            } else {
                qDebug() << "Error: Could not convert temperature value!";
            }
        }
    }
}

// New method to update the display with machine status
void MainWindow::displayMachineStatus(int id, const QString &etat) {
    // Assuming you have a QLabel or other widget to display the status
    ui->label_etat->setText(QString("Machine ID: %1, État: %2").arg(id).arg(etat));
}

void MainWindow::updateMachineStatus()
{
// Étape 1 : Lire l'ID depuis lineEdit_id
    QString id_machine = ui->lineEdit_id->text();
    if (id_machine.isEmpty()) {
        qDebug() << "[ATTENTION] L'ID est vide.";
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID de machine.");
        return;
    }


    QSqlQuery query;
    query.prepare("SELECT etat FROM gs_machine WHERE id_machine = :id_machine");
    query.bindValue(":id_machine", id_machine);

    if (!query.exec()) {
        qDebug() << "[ERREUR] Échec de l'exécution de la requête SQL :" << query.lastError().text();
        QMessageBox::critical(this, "Erreur Base de Données", "Impossible de récupérer l'état.");
        return;
    }

    if (!query.next()) {
        qDebug() << "[ATTENTION] Aucun état trouvé pour l'ID :" << id_machine;
        QMessageBox::warning(this, "État Introuvable", "L'ID spécifié n'existe pas.");
        return;
    }

    QString etat = query.value("etat").toString();
    qDebug() << "État récupéré depuis la base de données :" << etat;


    if (etat.trimmed().toLower() == "en panne") {

        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE gs_machine SET etat = 'ok' WHERE id_machine = :id_machine");
        updateQuery.bindValue(":id_machine", id_machine);

        if (!updateQuery.exec()) {
            qDebug() << "[ERREUR] Échec de la mise à jour de l'état :" << updateQuery.lastError().text();
            QMessageBox::critical(this, "Erreur Base de Données", "Impossible de mettre à jour l'état.");
            return;
        }

        qDebug() << "État de la machine mis à jour avec succès.";
        QMessageBox::information(this, "Succès", "L'état a été mis à jour en 'ok'.");


        QString message = "ID: " + id_machine + ", Etat: ok";
        arduino.write_to_arduino(message.toUtf8());
    } else {
        qDebug() << "[INFO] L'état n'est pas 'en panne'. Aucun changement effectué.";
        QMessageBox::information(this, "Aucun Changement", "L'état de la machine n'est pas 'en panne'.");
    }
}




MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_type_activated(int index)
{
    switch (index)
    {
    case 0:
        ui->comboBox_type->setCurrentText("Produit");
        break;
    case 1:
        ui->comboBox_type->setCurrentText("Service");
        break;
    default:
        break;
    }
}
void MainWindow::on_comboBox_etat_activated(int index)
{
    switch (index)
    {
    case 0:
        ui->comboBox_etat->setCurrentText("terminee");
        break;
    case 1:
        ui->comboBox_etat->setCurrentText("en cours");
        break;
    case 2:
        ui->comboBox_etat->setCurrentText("annulee");
        break;
    default:
        break;
    }
}
void MainWindow::on_pushButton_supprimer_clicked()
{
    QString idText;

    // Vérifiez si une ligne est sélectionnée dans le tableau
    QItemSelectionModel *selectionModel = ui->tableView_5->selectionModel();
    if (selectionModel && selectionModel->hasSelection()) {
        QModelIndex index = selectionModel->currentIndex();
        if (index.isValid()) {
            idText = ui->tableView_5->model()->data(ui->tableView_5->model()->index(index.row(), 0)).toString(); // Supposons que la colonne 0 contient l'ID
        }
    } else {
        // Si aucune ligne n'est sélectionnée, utilisez l'ID saisi dans le champ
        idText = ui->lineEdit_code->text();
    }

    if (idText.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un élément dans le tableau ou entrer un ID.");
        return;
    }

    // Confirmation de suppression
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment supprimer cet élément?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        bool test = cmd.supprimer(idText);
        if (test) {
            ui->tableView_5->setModel(cmd.afficher());
            updateCommandeStatus(); // Met à jour le statut des commandes
            QMessageBox::information(this, "Succès", "Suppression effectuée avec succès.");
        } else {
            QMessageBox::critical(this, "Erreur", "La suppression n'a pas été effectuée.");
        }
    }
}


void MainWindow::on_pushButton_save_clicked()
{
    // Validation du code avant de récupérer les données
    validateID();
    QString code = ui->lineEdit_num->text();

    // Vérifiez si le code est valide
    if (!ui->idErrorLabel->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez vérifier le code. Format attendu : 3 caractères-3 chiffres.");
        return; // Arrêter le processus si le code est invalide
    }

    // Récupération des données des champs
    QString id_client = ui->lineEdit_client->text();
    QString etat = ui->comboBox_etat->currentText();
    QString type = ui->comboBox_type->currentText();
    float prix_total = ui->lineEdit_prix->text().toFloat();
    QDate date_commande = ui->dateEdit->date();

    // Validation des champs obligatoires
    if (id_client.isEmpty() || etat.isEmpty() || type.isEmpty() || prix_total <= 0.0) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM gs_client WHERE id = :id_client");
    query.bindValue(":id_client", id_client);

    // Vérification si le client existe
    if (!query.exec() || !query.next() || query.value(0).toInt() <= 0) {
        QMessageBox::warning(this, "Erreur", "Le client n'existe pas.");
        return;
    }

    // Vérification du nombre de commandes du client
    QSqlQuery discountQuery;
    discountQuery.prepare("SELECT COUNT(*) FROM gs_commande WHERE id_client = :id_client");
    discountQuery.bindValue(":id_client", id_client);

    int nb_commandes = 0;
    if (discountQuery.exec() && discountQuery.next()) {
        nb_commandes = discountQuery.value(0).toInt();
    }

    // Appliquer la réduction si le client a passé 3 commandes
    if (nb_commandes >= 3) {
        prix_total -= prix_total * 0.1; // Réduction de 10%
        QMessageBox::information(this, "Réduction", "Ce client est éligible à une réduction de 10% !");
    }

    // Vérification si la commande existe déjà
    QString dummyEtat, dummyType;
    float dummyPrix;
    QDate dummyDate;
    QString dummyIdClient;

    if (getCommandeData(code, dummyIdClient, dummyEtat, dummyType, dummyPrix, dummyDate)) {
        // L'ID existe, on effectue une modification
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE gs_commande SET id_client = :id_client, etat = :etat, type = :type, prix_total = :prix_total, date_commande = :date_commande WHERE code = :code");
        updateQuery.bindValue(":code", code);
        updateQuery.bindValue(":id_client", id_client);
        updateQuery.bindValue(":etat", etat);
        updateQuery.bindValue(":type", type);
        updateQuery.bindValue(":prix_total", prix_total);
        updateQuery.bindValue(":date_commande", date_commande);

        if (updateQuery.exec()) {
            QMessageBox::information(this, "Modification", "Modification effectuée avec succès.");
            ui->tableView_5->setModel(cmd.afficher());

            if (etat == "terminee" || etat == "annulee") {
                envoyerEmailFeedback(id_client, code);
            }
        } else {
            qDebug() << "Erreur lors de la modification : " << updateQuery.lastError().text();
            QMessageBox::critical(this, "Erreur", "Échec de la modification.");
        }
    } else {
        // L'ID n'existe pas, on effectue un ajout
        Commande c(code, type, date_commande, prix_total, etat, id_client);
        if (c.ajouter()) {
            QMessageBox::information(this, "Ajout", "Ajout effectué avec succès.");
            ui->tableView_5->setModel(cmd.afficher());

            if (etat == "terminee" || etat == "annulee") {
                envoyerEmailFeedback(id_client, code);
            }
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de l'ajout.");
        }
    }

    // Réinitialisation des champs après opération
    ui->lineEdit_num->clear();
    ui->lineEdit_client->clear();
    ui->comboBox_etat->setCurrentIndex(-1);
    ui->comboBox_type->setCurrentIndex(-1);
    ui->lineEdit_prix->clear();
    ui->dateEdit->setDate(QDate::currentDate());

    // Débloquer les champs pour permettre des modifications futures
    ui->lineEdit_num->setReadOnly(false);
    ui->lineEdit_client->setReadOnly(false);
}




bool MainWindow::getCommandeData(const QString &code, QString &id_client, QString &etat, QString &type, float &prix_total, QDate &date_commande)
{
    QSqlQuery query;
    query.prepare("SELECT id_client, etat, type, prix_total, date_commande FROM gs_commande WHERE code = :code");
    query.bindValue(":code", code);

    if (query.exec() && query.next()) {
        // Récupérer les données de la commande existante
        id_client = query.value("id_client").toString();
        etat = query.value("etat").toString();
        type = query.value("type").toString();
        prix_total = query.value("prix_total").toFloat();
        date_commande = query.value("date_commande").toDate();
        return true;
    }
    return false;
}

void MainWindow::onPushButtonAnnulerClicked()
{
    // Effacer tous les champs
    ui->lineEdit_num->clear();
    ui->lineEdit_client->clear();
    ui->comboBox_type->setCurrentIndex(-1);
    ui->comboBox_etat->setCurrentIndex(-1);
    ui->lineEdit_prix->clear();
    ui->dateEdit->setDate(QDate::currentDate());

    // Débloquer les champs en rétablissant leur état modifiable
    ui->lineEdit_num->setReadOnly(false);
    ui->lineEdit_client->setReadOnly(false);
}

// Nouvelle méthode pour récupérer les données à chaque changement
void MainWindow::updateFields()
{
    QString code = ui->lineEdit_num->text();
    QString id_client, etat, type;
    float prix_total;
    QDate date_commande;

    if (!code.isEmpty() && getCommandeData(code, id_client, etat, type, prix_total, date_commande)) {
        // Si les données sont récupérées, les remplir dans les champs
        ui->lineEdit_client->setText(id_client);
        ui->comboBox_etat->setCurrentText(etat);
        ui->comboBox_type->setCurrentText(type);
        ui->lineEdit_prix->setText(QString::number(prix_total));
        ui->dateEdit->setDate(date_commande);
    } else {
        // Effacer les champs si aucune donnée n'est récupérée
        ui->lineEdit_client->clear();
        ui->comboBox_etat->setCurrentIndex(-1);
        ui->comboBox_type->setCurrentIndex(-1);
        ui->lineEdit_prix->clear();
        ui->dateEdit->setDate(QDate::currentDate());
    }
}




void MainWindow::on_tableView_5_clicked(const QModelIndex &index) {
    if (!index.isValid())
        return;

    // Récupérer le modèle et vérifier la validité de la sélection
    QAbstractItemModel *model = ui->tableView_5->model();
    if (!model)
        return;

    int row = index.row(); // Ligne sélectionnée

    // Récupérer les données de la commande sélectionnée
    QString code = model->data(model->index(row, 0)).toString();
    QString type = model->data(model->index(row, 2)).toString();
    QString etat = model->data(model->index(row, 5)).toString();
    float prixTotal = model->data(model->index(row, 4)).toFloat();
    QDate dateCommande = QDate::fromString(model->data(model->index(row, 3)).toString(), "dd/MM/yyyy");

    // Remplir les champs du formulaire
    ui->lineEdit_num->setText(code);
    ui->comboBox_type->setCurrentText(type);
    ui->lineEdit_prix->setText(QString::number(prixTotal, 'f', 2));
    ui->comboBox_etat->setCurrentText(etat);
    ui->dateEdit->setDate(dateCommande);

    // Récupérer l'id_client associé
    QString idClient = Commande::recupererIdClient(code);
    if (!idClient.isEmpty()) {
        ui->lineEdit_client->setText(idClient);
    }

    // Si vous souhaitez rendre les champs non modifiables
    ui->lineEdit_num->setReadOnly(true);
    ui->lineEdit_client->setReadOnly(true);
}








void MainWindow::actualiserAffichage() {
    ui->tableView_5->setModel(cmd.afficher());
}



void MainWindow::validateidClient() {
    QString id_client = ui->lineEdit_client->text();


    static QRegularExpression regex("^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{10}$");


    if (id_client.isEmpty()) {
        ui->clientError->clear();
    } else if (!regex.match(id_client).hasMatch()) {

        ui->clientError->setText("id  doit être 10 caractères(chiffres et lettres)");
    } else {
        ui->clientError->clear();
    }
}
void MainWindow::validateID() {
    QString code = ui->lineEdit_num->text();

     static QRegularExpression regex("^[A-Za-z]{3}-\\d{3}$");

    if (code.isEmpty()) {
        ui->idErrorLabel->clear();
    } else if (!regex.match(code).hasMatch()) {
        ui->idErrorLabel->setText("code doit etre 3 caractere-3chiffres");
    } else {
        ui->idErrorLabel->clear();
    }
}
void MainWindow::validateCO() {
    QString code = ui->line_code->text();

    static QRegularExpression regex("^[A-Za-z]{3}-\\d{3}$");

    if (code.isEmpty()) {
        ui->error->clear();
    } else if (!regex.match(code).hasMatch()) {
        ui->error->setText("code doit etre 3 caractere-3chiffres");
    } else {
        ui->error->clear();
    }
}





void MainWindow::validatePrix() {
    bool ok;

    ui->lineEdit_prix->text().toFloat(&ok);

    if (ui->lineEdit_prix->text().isEmpty()) {
        ui->prixErrorLabel->clear();
    } else if (!ok) {
        ui->prixErrorLabel->setText("Le prix doit être un nombre décimal.");
    } else {
        ui->prixErrorLabel->clear();
    }
}




#include <QRegularExpression>


void MainWindow::searchAndDisplayCommande() {
    QString criterion = ui->comboBox->currentText().trimmed();
    QString value = ui->lineEdit_code->text().trimmed();
    bool valid = true;
    ui->codeErrorLabel->clear();

    if (value.isEmpty()) {
        ui->tableView_5->setModel(cmd.afficher());
        return;
    }

    QSqlQuery query;
    QString queryString;

    if (criterion == "recherche par code:") {
        QRegularExpression codeRegex("[A-Za-z]{3}-[0-9]{3}");
        if (!codeRegex.match(value).hasMatch()) {
            valid = false;
            ui->codeErrorLabel->setText("Le code doit être de la forme XXX-XXX ");
            ui->codeErrorLabel->setStyleSheet("color: red;");
        }
        queryString = "SELECT gs_commande.code, "
                      "gs_client.nom || ' ' || gs_client.prenom AS client, "
                      "gs_commande.type, "
                      "gs_commande.date_commande, "
                      "gs_commande.prix_total, "  // Prix total ajouté
                      "gs_commande.etat "
                      "FROM gs_commande "
                      "INNER JOIN gs_client ON gs_commande.id_client = gs_client.id "
                      "WHERE gs_commande.code = :value";
    }

    else if (criterion == "recherche par etat:") {
        QStringList validStates = {"en cours", "terminee", "annulee"};
        if (!validStates.contains(value.toLower())) {
            valid = false;
            ui->codeErrorLabel->setText("Erreur : L'état n'est pas valide");
            ui->codeErrorLabel->setStyleSheet("color: red;");
        }
        queryString = "SELECT gs_commande.code, "
                      "gs_client.nom || ' ' || gs_client.prenom AS client, "
                      "gs_commande.type, "
                      "gs_commande.date_commande, "
                      "gs_commande.prix_total, "  // Prix total ajouté
                      "gs_commande.etat "
                      "FROM gs_commande "
                      "INNER JOIN gs_client ON gs_commande.id_client = gs_client.id "
                      "WHERE gs_commande.etat = :value";
    }

    else if (criterion == "recherche par client:") {
        queryString = "SELECT gs_commande.code, "
                      "gs_client.nom || ' ' || gs_client.prenom AS client, "
                      "gs_commande.type, "
                      "gs_commande.date_commande, "
                      "gs_commande.prix_total, "  // Prix total ajouté
                      "gs_commande.etat "
                      "FROM gs_commande "
                      "INNER JOIN gs_client ON gs_commande.id_client = gs_client.id "
                      "WHERE gs_client.nom LIKE :value OR gs_client.prenom LIKE :value "
                      "OR gs_client.nom || ' ' || gs_client.prenom LIKE :value";

        query.prepare(queryString);
        query.bindValue(":value", "%" + value + "%");  // Recherche partielle
    }

    else {
        QMessageBox::critical(this, "Erreur", "Le critère de recherche n'est pas valide.");
        return;
    }

    if (valid) {
        query.prepare(queryString);
        query.bindValue(":value", value);

        if (query.exec()) {
            QStandardItemModel *model = new QStandardItemModel();

            // Définir les en-têtes de colonne dans l'ordre correct
            model->setHorizontalHeaderLabels({"Code", "Client", "Type", "Date Commande", "Prix total", "Etat actuel"});

            while (query.next()) {
                QList<QStandardItem*> row;

                row.append(new QStandardItem(query.value(0).toString()));  // Code
                row.append(new QStandardItem(query.value(1).toString()));  // Client
                row.append(new QStandardItem(query.value(2).toString()));  // Type
                row.append(new QStandardItem(query.value(3).toDate().toString("dd/MM/yyyy")));  // Date
                row.append(new QStandardItem(query.value(4).toString()));  // Prix total

                // Récupérer et afficher l'état avec l'icône
                QString etat = query.value(5).toString();
                QStandardItem* etatItem = new QStandardItem(etat);

                QPixmap pixmap(20, 20);
                pixmap.fill(Qt::transparent);  // Remplir de transparence

                QPainter painter(&pixmap);
                painter.setRenderHint(QPainter::Antialiasing);  // Antialiasing pour les bords lisses
                painter.setBrush(Qt::transparent);  // Fond transparent
                painter.setPen(Qt::NoPen);  // Pas de bordure

                // Choisir la couleur selon l'état
                if (etat == "terminee") {
                    painter.setBrush(QBrush(Qt::darkGreen));  // Vert pour "terminee"
                } else if (etat == "en cours") {
                    painter.setBrush(QBrush(Qt::yellow));  // Jaune pour "en cours"
                } else if (etat == "annulee") {
                    painter.setBrush(QBrush(Qt::red));  // Rouge pour "annulee"
                }

                painter.drawEllipse(0, 0, 12, 12);  // Dessiner un cercle
                painter.end();
                QIcon icon(pixmap);
                etatItem->setIcon(icon);

                row.append(etatItem);  // Ajouter l'icône d'état

                model->appendRow(row);  // Ajouter la ligne au modèle
            }

            ui->tableView_5->setModel(model);  // Appliquer le modèle au QTableView
        }
    }
}




void MainWindow::on_comboBox_tri_currentIndexChanged(int index)
{
    QString queryStr;

    // Définir la requête SQL en fonction de l'index sélectionné
    switch (index) {
    case 1:  // Tri par type
        queryStr = "SELECT gs_commande.code, "
                   "gs_client.nom || ' ' || gs_client.prenom AS client, "
                   "gs_commande.type, "
                   "gs_commande.date_commande, "
                   "gs_commande.prix_total, "
                   "gs_commande.etat "
                   "FROM gs_commande "
                   "INNER JOIN gs_client ON gs_commande.id_client = gs_client.id "
                   "ORDER BY CASE gs_commande.type "
                   "WHEN 'produit' THEN 1 "
                   "WHEN 'service' THEN 2 "
                   "ELSE 3 END";
        break;

    case 2:  // Tri par date
        queryStr = "SELECT gs_commande.code, "
                   "gs_client.nom || ' ' || gs_client.prenom AS client, "
                   "gs_commande.type, "
                   "gs_commande.date_commande, "
                   "gs_commande.prix_total, "
                   "gs_commande.etat "
                   "FROM gs_commande "
                   "INNER JOIN gs_client ON gs_commande.id_client = gs_client.id "
                   "ORDER BY gs_commande.date_commande DESC";
        break;

    case 3:  // Tri par état
        queryStr = "SELECT gs_commande.code, "
                   "gs_client.nom || ' ' || gs_client.prenom AS client, "
                   "gs_commande.type, "
                   "gs_commande.date_commande, "
                   "gs_commande.prix_total, "
                   "gs_commande.etat "
                   "FROM gs_commande "
                   "INNER JOIN gs_client ON gs_commande.id_client = gs_client.id "
                   "ORDER BY CASE gs_commande.etat "
                   "WHEN 'en cours' THEN 1 "
                   "WHEN 'terminee' THEN 2 "
                   "WHEN 'annulee' THEN 3 "
                   "ELSE 4 END";
        break;

    default:
        return;
    }

    QSqlQuery query;
    if (query.exec(queryStr)) {
        QStandardItemModel *model = new QStandardItemModel();

        // Définir les en-têtes de colonne
        model->setHorizontalHeaderLabels({"Code", "Client", "Type", "Date Commande", "Prix total", "Etat actuel"});

        while (query.next()) {
            QList<QStandardItem*> row;

            // Remplir les colonnes avec les données
            row.append(new QStandardItem(query.value(0).toString()));  // Code
            row.append(new QStandardItem(query.value(1).toString()));  // Client
            row.append(new QStandardItem(query.value(2).toString()));  // Type

            // Formater la date
            QString rawDate = query.value(3).toString();
            QString pureDate = rawDate.split("T").at(0);
            QDate date = QDate::fromString(pureDate, "yyyy-MM-dd");
            QString formattedDate = (date.isValid()) ? date.toString("dd/MM/yyyy") : pureDate;

            row.append(new QStandardItem(formattedDate));  // Date commande
            row.append(new QStandardItem(query.value(4).toString()));  // Prix total

            // Ajouter une icône pour l'état
            QString etat = query.value(5).toString();
            QStandardItem* etatItem = new QStandardItem(etat);

            QPixmap pixmap(20, 20);
            pixmap.fill(Qt::transparent);

            QPainter painter(&pixmap);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setBrush(Qt::transparent);
            painter.setPen(Qt::NoPen);

            if (etat == "terminee") {
                painter.setBrush(QBrush(Qt::darkGreen));
            } else if (etat == "en cours") {
                painter.setBrush(QBrush(Qt::yellow));
            } else if (etat == "annulee") {
                painter.setBrush(QBrush(Qt::red));
            }

            painter.drawEllipse(0, 0, 12, 12);
            painter.end();
            QIcon icon(pixmap);
            etatItem->setIcon(icon);

            row.append(etatItem);  // Ajouter l'état avec icône
            model->appendRow(row);
        }

        // Appliquer le modèle à la vue
        ui->tableView_5->setModel(model);
    }
}





void MainWindow::envoyerEmailFeedback(const QString& id_client, const QString& code_commande) {

    QSqlQuery query;
    query.prepare("SELECT e_mail FROM gs_client WHERE TRIM(id) = :id_client");
    query.bindValue(":id_client", id_client);


    if (query.exec() && query.next()) {
        QString emailClient = query.value("e_mail").toString();

        if (!emailClient.isEmpty()) {
            envoyerEmailAvecPython(emailClient, code_commande);
        } else {
            QMessageBox::warning(this, tr("Erreur"), tr("Client sans email."));
        }
    } else {
        QMessageBox::warning(this, tr("Erreur"), tr("Client non trouvé."));
    }
}


void MainWindow::envoyerEmailAvecPython(const QString& emailClient, const QString& code_commande) {

    QString pythonPath = "C:/Users/Lenovo/anaconda3/python.exe";
    QString pythonScript = QDir::toNativeSeparators("C:/Users/Lenovo/Documents/metiers/send_email.py");

    QStringList arguments;
    arguments << pythonScript << emailClient << code_commande;

    QProcess *process = new QProcess(this);

    connect(process, &QProcess::readyReadStandardOutput, [process]() {
        QString output = process->readAllStandardOutput();
        qDebug() << "Sortie du script Python:" << output;
    });

    connect(process, &QProcess::readyReadStandardError, [process]() {
        QString errorOutput = process->readAllStandardError();
        qDebug() << "Erreur du script Python:" << errorOutput;
    });

    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [process](int exitCode, QProcess::ExitStatus exitStatus) {
                if (exitStatus == QProcess::NormalExit && exitCode == 0) {
                    qDebug() << "Script Python terminé avec succès.";
                } else {
                    qDebug() << "Script Python terminé avec une erreur.";
                }
                process->deleteLater();
            });

    process->start(pythonPath, arguments);

    if (!process->waitForStarted()) {
        qDebug() << "Erreur lors du démarrage du script Python.";
        process->deleteLater();
        return;
    }

    qDebug() << "Script Python lancé pour envoyer l'email.";
}



#include<QPdfWriter>
#include<QFileDialog>
#include<QPainter>
void MainWindow::on_pushButton_exporter_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr("Exporter en PDF"), "", "*.pdf");

    if (fileName.isEmpty()) {
        return;
    }

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(200);

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);


    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    painter.setFont(titleFont);


    QString title = "Liste des commandes";
    int yPosition = 50;
    painter.drawText(100, yPosition, pdfWriter.width() - 200, 50, Qt::AlignCenter, title);

    yPosition += 120;


    QFont font;
    font.setPointSize(14);
    painter.setFont(font);

    QFontMetrics fontMetrics(font);
    int cellHeight = fontMetrics.height() + 20;
    int rowCount = ui->tableView_5->model()->rowCount();
    int columnCount = ui->tableView_5->model()->columnCount();

    int cellWidth = pdfWriter.width() / columnCount;


    int tableWidth = columnCount * cellWidth;
    int pageWidth = pdfWriter.width();
    int xStart = (pageWidth - tableWidth) / 2;


    painter.setBrush(QColor(144, 238, 144));
    int xPosition = xStart;
    for (int col = 0; col < columnCount; ++col) {
        QString headerData = ui->tableView_5->model()->headerData(col, Qt::Horizontal).toString();
        painter.drawRect(xPosition, yPosition, cellWidth, cellHeight);
        painter.drawText(xPosition, yPosition, cellWidth, cellHeight, Qt::AlignCenter, headerData);
        xPosition += cellWidth;
    }

    painter.setBrush(Qt::NoBrush);
    yPosition += cellHeight;


    for (int row = 0; row < rowCount; ++row) {
        xPosition = xStart;

        for (int col = 0; col < columnCount; ++col) {
            QString cellData = ui->tableView_5->model()->data(ui->tableView_5->model()->index(row, col)).toString();
            painter.drawRect(xPosition, yPosition, cellWidth, cellHeight);
            painter.drawText(xPosition, yPosition, cellWidth, cellHeight, Qt::AlignCenter, cellData);
            xPosition += cellWidth;
        }

        yPosition += cellHeight;
    }

    painter.end();

    QMessageBox::information(this, "Exportation réussie", "L'affichage a été exporté en PDF avec succès.");
}
#include <QPieSeries>
#include <QChart>
#include <QChartView>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

void MainWindow::genererStatistiquesParEtat()
{
    // Récupération des dates depuis les QDateEdit
    QDate dateDebut = ui->datedebut->date();
    QDate dateFin = ui->datefin->date();

    // Vérification des dates
    if (dateDebut > dateFin) {
        QMessageBox::warning(this, "Erreur", "La date de début doit être antérieure à la date de fin.");
        return;
    }

    // Requête SQL pour récupérer les données regroupées par état
    QSqlQuery query;
    query.prepare("SELECT etat, COUNT(*) AS nombre "
                  "FROM gs_commande "
                  "WHERE date_commande BETWEEN TO_DATE(:dateDebut, 'YYYY-MM-DD') AND TO_DATE(:dateFin, 'YYYY-MM-DD') "
                  "GROUP BY etat");

    query.bindValue(":dateDebut", dateDebut.toString("yyyy-MM-dd"));
    query.bindValue(":dateFin", dateFin.toString("yyyy-MM-dd"));


    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        return;
    }

    // Création de la série pour le graphique
    QPieSeries *series = new QPieSeries();
    int total = 0;

    while (query.next()) {
        QString etat = query.value(0).toString();  // État (terminée, annulée, en cours)
        int nombre = query.value(1).toInt();      // Nombre de commandes pour cet état

        // Ajout des données à la série
        series->append(etat + " (" + QString::number(nombre) + ")", nombre);
        total += nombre;
    }

    // Vérification des données avant de continuer
    if (series->slices().isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucune commande trouvée pour la période sélectionnée.");
        return;
    }

    // Afficher les labels
    for (auto slice : series->slices()) {
        slice->setLabelVisible(true);
    }

    // Création du graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des commandes (total: " + QString::number(total) + ")");
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Configuration de la vue
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Affichage dans un layout existant
    if (ui->layout_statistiques->layout() != nullptr) {
        delete ui->layout_statistiques->layout();
    }
    QVBoxLayout *layout = new QVBoxLayout(ui->layout_statistiques);
    layout->addWidget(chartView);
    ui->layout_statistiques->setLayout(layout);
}
void MainWindow::updateCommandeStatus() {
    QSqlQuery query;


    query.prepare("SELECT COUNT(*) FROM gs_commande");
    int totalCommandes = 0;
    if (query.exec() && query.next()) {
        totalCommandes = query.value(0).toInt();
    }


    query.prepare("SELECT COUNT(*) FROM gs_commande WHERE etat = 'en cours'");
    int enCoursCommandes = 0;
    if (query.exec() && query.next()) {
        enCoursCommandes = query.value(0).toInt();
    }

    query.prepare("SELECT COUNT(*) FROM gs_commande WHERE etat = 'terminee'");
    int termineCommandes = 0;
    if (query.exec() && query.next()) {
        termineCommandes = query.value(0).toInt();
    }


    query.prepare("SELECT COUNT(*) FROM gs_commande WHERE etat = 'annulee'");
    int annuleCommandes = 0;
    if (query.exec() && query.next()) {
        annuleCommandes = query.value(0).toInt();
    }


    QString labelTextTotal = QString(
                                 "<span style='font-size: 14px; color: black;'>●</span> "
                                 "<span style='font-weight: bold; color: black;'>%1</span> commande(s)"
                                 ).arg(totalCommandes);

    QString labelTextEnCours = QString(
                                   "<span style='font-size: 14px; color: yellow;'>●</span> "
                                   "<span style='font-weight: bold; color: black;'>%1</span> en cours de traitement"
                                   ).arg(enCoursCommandes);

    QString labelTextTerminee = QString(
                                    "<span style='font-size: 14px; color: green;'>●</span> "
                                    "<span style='font-weight: bold; color: black;'>%1</span> terminée(s)"
                                    ).arg(termineCommandes);

    QString labelTextAnnulee = QString(
                                   "<span style='font-size: 14px; color: red;'>●</span> "
                                   "<span style='font-weight: bold; color: black;'>%1</span> annulée(s)"
                                   ).arg(annuleCommandes);


    ui->note->setText(labelTextTotal);
    ui->note2->setText(labelTextEnCours);
    ui->note1->setText(labelTextTerminee);
    ui->note3->setText(labelTextAnnulee);
}


void MainWindow::executerScriptPython()
{
    // Chemin du script Python
    QString pythonPath = "C:/Users/Lenovo/anaconda3/python.exe"; // Assure-toi que Python est accessible ici
    QString scriptPath = "C:/Users/Lenovo/Documents/metiers/read_email.py";

    // Liste des arguments à passer au script (si nécessaire)
    QStringList arguments;
    arguments << scriptPath;

    // Créer un processus pour exécuter le script Python
    QProcess *process = new QProcess(this);

    // Connexion pour récupérer la sortie standard (pour débogage)
    connect(process, &QProcess::readyReadStandardOutput, [process]() {
        QString output = process->readAllStandardOutput();
        qDebug() << "Sortie du script Python:" << output;
    });

    // Connexion pour récupérer la sortie d'erreur (pour débogage)
    connect(process, &QProcess::readyReadStandardError, [process]() {
        QString errorOutput = process->readAllStandardError();
        qDebug() << "Erreur du script Python:" << errorOutput;
    });

    // Connexion à la fin du processus pour savoir s'il a réussi ou échoué
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [process](int exitCode, QProcess::ExitStatus exitStatus) {
                if (exitStatus == QProcess::NormalExit && exitCode == 0) {
                    qDebug() << "Script Python terminé avec succès.";
                } else {
                    qDebug() << "Script Python terminé avec une erreur.";
                }
                process->deleteLater();
            });

    // Démarrer le processus avec le chemin vers Python et le script
    process->start(pythonPath, arguments);

    // Vérifier si le processus a bien démarré
    if (!process->waitForStarted()) {
        qDebug() << "Erreur lors du démarrage du script Python.";
        process->deleteLater();
        return;
    }

    qDebug() << "Script Python lancé pour exécuter le traitement.";
}




#include<QTextEdit>

    void MainWindow::mettreAJourScrollArea() {
    SentimentAnalyzer sentimentAnalyzer;

    // Récupérer le layout de la ScrollArea
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(ui->scrollArea->widget()->layout());
    if (!layout) {
        qDebug() << "Erreur : Aucun layout trouvé pour la scroll area.";
        return;
    }

    // Effacer le contenu existant
    while (QLayoutItem *item = layout->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    // Charger les données depuis la base de données
    QSqlQuery query;
    query.prepare("SELECT code, nom, prenom, reponse FROM gs_commande "
                  "JOIN gs_client ON gs_commande.id_client = gs_client.id "
                  "WHERE reponse IS NOT NULL AND LENGTH(TRIM(reponse)) > 0");

    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des commandes :" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString code = query.value("code").toString();
        QString nom = query.value("nom").toString();
        QString prenom = query.value("prenom").toString();
        QString reponse = query.value("reponse").toString();

        // Calculer le sentiment
        QString sentiment = sentimentAnalyzer.obtenirSentiment(reponse);

        // Ajouter le code de la commande
        QLabel *labelCode = new QLabel("Commande : " + code);
        labelCode->setStyleSheet("font-weight: bold; font-size: 14px; color: #1f77b4;");
        layout->addWidget(labelCode);

        // Ajouter le nom et prénom du client
        QLabel *labelClient = new QLabel("Client : " + nom + " " + prenom);
        labelClient->setStyleSheet("font-size: 14px; color: #006400;");
        layout->addWidget(labelClient);

        // Ajouter la réponse
        QTextEdit *textReponse = new QTextEdit(reponse);
        textReponse->setReadOnly(true);
        textReponse->setStyleSheet(
            "background-color: #f0f8ff; color: black; font-weight: bold; border: 2px solid #1f77b4; border-radius: 8px; padding: 10px;");
        layout->addWidget(textReponse);

        // Ajouter le sentiment
        QLabel *labelSentiment = new QLabel("Sentiment : " + sentiment);
        labelSentiment->setStyleSheet("font-size: 14px; color: " + QString(sentiment == "Positif" ? "#28a745" : (sentiment == "Négatif" ? "#dc3545" : "#ffc107")) + ";");

        layout->addWidget(labelSentiment);

        // Espacement
        layout->addSpacing(20);
    }

    ui->scrollArea->widget()->update();
}
 void MainWindow::on_pushButton_actualiser_clicked() {

        executerScriptPython();


        mettreAJourScrollArea();

        afficherGraphiqueSentiments();
    }

#include <QSqlQuery>
#include <QBarSet>
#include <QBarSeries>
#include <QChartView>
#include <QChart>
#include <QPixmap>
#include <QPainter>
#include<QValueAxis>
#include<QBarCategoryAxis>

    void MainWindow::afficherGraphiqueSentiments() {
        SentimentAnalyzer sentimentAnalyzer;

        int positiveCount = 0;
        int negativeCount = 0;
        int neutralCount = 0;

        // Charger les données depuis la base de données
        QSqlQuery query;
        query.prepare("SELECT reponse FROM gs_commande "
                      "JOIN gs_client ON gs_commande.id_client = gs_client.id "
                      "WHERE reponse IS NOT NULL AND LENGTH(TRIM(reponse)) > 0");

        if (!query.exec()) {
            qDebug() << "Erreur lors de la récupération des réponses :" << query.lastError().text();
            return;
        }

        while (query.next()) {
            QString reponse = query.value("reponse").toString();
            QString sentiment = sentimentAnalyzer.obtenirSentiment(reponse);

            if (sentiment == "Positif") {
                positiveCount++;
            } else if (sentiment == "Négatif") {
                negativeCount++;
            } else {
                neutralCount++;
            }
        }

        // Créer les ensembles de données pour le graphique
        QBarSet *positiveSet = new QBarSet("Satisfaits");
        QBarSet *negativeSet = new QBarSet("Non Satisfaits");
        QBarSet *neutralSet = new QBarSet("Neutres");

        *positiveSet << positiveCount;
        *negativeSet << negativeCount;
        *neutralSet << neutralCount;

        // Définir les couleurs des barres
        positiveSet->setColor(Qt::green);
        negativeSet->setColor(Qt::red);
        neutralSet->setColor(QColor(255, 165, 0)); // Couleur orange

        QBarSeries *series = new QBarSeries();
        series->append(positiveSet);
        series->append(negativeSet);
        series->append(neutralSet);

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Répartition des Sentiments des Clients");
        chart->createDefaultAxes();

        // Configurer les axes
        chart->axes(Qt::Vertical).first()->setTitleText("Nombre de Clients");
        chart->axes(Qt::Horizontal).first()->setTitleText("Sentiments");

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setMinimumSize(600, 400); // Taille minimale

        // Afficher le graphique dans QLabel
        if (ui->labelGraphique) {
            // Effacer l'ancienne pixmap pour le graphique
            ui->labelGraphique->clear();

            // Définir une nouvelle pixmap pour le graphique
            ui->labelGraphique->setPixmap(chartView->grab()); // Prendre une capture du graphique
            ui->labelGraphique->update(); // Mettre à jour l'affichage
        } else {
            qDebug() << "Erreur : QLabel pour le graphique non trouvé.";
        }

        // Optionnel : Si vous souhaitez ajouter le graphique à une mise en page
        // layout->addWidget(chartView); // Ajoutez cela si vous utilisez un layout
    }



void MainWindow::rechercherCommandeParCode()
{
    // Récupérer le layout de la ScrollArea
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->scrollArea->widget()->layout());
    if (!layout) {
        qDebug() << "Erreur : Aucun layout trouvé pour la scroll area.";
        return;
    }

    // Effacer le contenu existant dans la ScrollArea
    while (QLayoutItem *item = layout->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    // Récupérer le code de commande entré dans le QLineEdit
    QString codeCommande = ui->line_code->text().trimmed();

    // Si aucun code n'est entré, afficher un message dans la ScrollArea au lieu d'un QMessageBox
    if (codeCommande.isEmpty()) {
        QLabel *noInputLabel = new QLabel("Veuillez entrer un code de commande.");
        noInputLabel->setAlignment(Qt::AlignCenter);
        noInputLabel->setStyleSheet("font-size: 14px; color: #ff0000; font-weight: bold;");
        layout->addWidget(noInputLabel);
        return;
    }

    // Requête SQL pour rechercher une commande par son code
    QSqlQuery query;
    query.prepare("SELECT code, nom, prenom, reponse FROM gs_commande "
                  "JOIN gs_client ON gs_commande.id_client = gs_client.id "
                  "WHERE code = :codeCommande AND reponse IS NOT NULL AND LENGTH(TRIM(reponse)) > 0");
    query.bindValue(":codeCommande", codeCommande);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des commandes :" << query.lastError().text();
        return;
    }

    // Si aucun résultat n'est trouvé
    if (!query.next()) {
        QLabel *noResultsLabel = new QLabel("Aucune commande trouvée pour le code saisi.");
        noResultsLabel->setAlignment(Qt::AlignCenter);
        noResultsLabel->setStyleSheet("font-size: 14px; color: #ff0000; font-weight: bold;");
        layout->addWidget(noResultsLabel);
        return;
    }

    // Parcours des résultats de la requête
    QString code = query.value("code").toString();
    QString nom = query.value("nom").toString();
    QString prenom = query.value("prenom").toString();
    QString reponse = query.value("reponse").toString();

    // Label pour le code de la commande (en bleu foncé)
    QLabel *labelCode = new QLabel("Commande : " + code);
    labelCode->setStyleSheet("font-weight: bold; font-size: 14px; color: #1f77b4;");
    layout->addWidget(labelCode);

    // Label pour le nom et prénom du client (en vert)
    QLabel *labelClient = new QLabel("Client : " + nom + " " + prenom);
    labelClient->setStyleSheet("font-size: 14px; color: #006400;");
    layout->addWidget(labelClient);

    // Zone de texte pour la réponse (en noir, texte en gras)
    QTextEdit *textReponse = new QTextEdit(reponse);
    textReponse->setReadOnly(true);
    textReponse->setStyleSheet(
        "background-color: #f0f8ff; "  // Bleu clair pour le fond
        "color: black; "               // Texte en noir
        "font-weight: bold; "          // Texte en gras
        "border: 2px solid #1f77b4; " // Bordure bleue foncée
        "border-radius: 8px; "         // Coins arrondis
        "padding: 10px; "              // Espacement intérieur
        );
    layout->addWidget(textReponse);

    // Espacement entre les éléments
    layout->addSpacing(20);
}

//*************************produit

//
void MainWindow::on_Ajouter_clicked()
{
    QString nom = ui->nom->text();
    int id = ui->id->text().toInt();
    int quantite = ui->quantite->text().toInt();
    float prixdachat = ui->pa->text().toFloat();
    float prixdevente = ui->pv->text().toFloat();

    if (nom.isEmpty() || id <= 0 || quantite < 0 || prixdachat < 0 || prixdevente < 0) {
        QMessageBox::critical(this, "Erreur", "Vérifiez les données saisies.");
        return;
    }

    produit p(nom, id, quantite, prixdachat, prixdevente);
    bool test = p.Ajouter();

    if (test) {
        ui->tableView_6->setModel(p.Afficher());
        //notifyUser("Ajout réussi", "Produit ajouté avec succès.", QSystemTrayIcon::Information);
        ui->nom->clear();
        ui->id->clear();
        ui->quantite->clear();
        ui->pv->clear();
        ui->pa->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du produit.");

    }
}
void MainWindow::updateHistoriqueLabel(const QString &historiqueText)
{
    // Assurez-vous que la QLabel est correctement mise à jour avec le texte
    ui->historique->setText(historiqueText);  // Ou selon le nom de votre QLabel
}


void MainWindow::refreshTableView() {
    // Exemple de code pour actualiser le tableau
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM GS_PRODUIT"); // Ou une autre requête pour récupérer les données mises à jour
    ui->tableView_6->setModel(model);
}
QLabel* MainWindow::getHistoriqueLabel()
{
    return ui->historique;  // Assurez-vous que "historiqueLabel" est un QLabel dans votre UI
}

void MainWindow::on_supprimer_clicked() {
    // Étape 1 : Récupérer l'ID du produit à supprimer
    bool ok;
    int idProduit = ui->taper->text().toInt(&ok);  // Récupère l'ID de la QLineEdit

    // Vérifier si l'ID est valide et non nul
    if (!ok || idProduit == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID différent de 0.");
        return;
    }

    // Vérifier si l'ID est positif
    if (idProduit < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID positif.");
        return;
    }

    // Étape 2 : Vérifier si l'ID existe dans la base de données
    QSqlQuery query;
    query.prepare("SELECT * FROM GS_PRODUIT WHERE id = ?");
    query.addBindValue(idProduit);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Erreur", "Produit introuvable. Veuillez réessayer.");
        return;
    }

    // Étape 3 : Supprimer le produit de la base de données
    produit p;
    if (p.Supprimer(idProduit)) {
        // Si la suppression est réussie, afficher un message de succès
        QMessageBox::information(this, "Succès", "Produit supprimé avec succès.");
    } else {
        // Si la suppression échoue, afficher un message d'erreur
        QMessageBox::warning(this, "Erreur", "Échec de la suppression du produit.");
    }

    // Étape 4 : Actualiser la vue pour refléter la suppression
    refreshTableView();  // Actualiser la table ou la vue du produit
}




//
void MainWindow::on_ModifierButton_clicked() {
    // Étape 1 : Récupérer l'ID du produit à modifier
    int idProduit = ui->taper->text().toInt();  // Récupère l'ID de la QLineEdit

    // Vérifier si l'ID est valide
    if (idProduit == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID différent de 0.");
        return;
    }
    if (idProduit < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID positif.");
        return;
    }

    // Étape 2 : Vérifier si l'ID existe dans la base de données
    QSqlQuery query;
    query.prepare("SELECT * FROM GS_PRODUIT WHERE id = ?");
    query.addBindValue(idProduit);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Erreur", "Produit introuvable. Veuillez réessayer.");
        return;
    }

    // Étape 3 : Demander les nouvelles valeurs (prix d'achat, quantité, prix de vente)
    bool ok;
    double nouveauPrixAchat = QInputDialog::getDouble(this, "Nouveau prix d'achat",
                                                      "Entrez le nouveau prix d'achat :",
                                                      query.value("prixdachat").toDouble(),
                                                      0.0, 10000.0, 2, &ok);

    if (!ok || nouveauPrixAchat == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un prix d'achat different de 0.");
        return;
    }

    double nouvelleQuantite = QInputDialog::getDouble(this, "Nouvelle quantité",
                                                      "Entrez la nouvelle quantité :",
                                                      query.value("quantite").toDouble(),
                                                      0.0, 10000.0, 0, &ok);
    if (!ok || nouvelleQuantite == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une quantité différente de 0.");
        return;
    }


    double nouveauPrixVente = QInputDialog::getDouble(this, "Nouveau prix de vente",
                                                      "Entrez le nouveau prix de vente :",
                                                      query.value("prixdevente").toDouble(),
                                                      0.0, 10000.0, 2, &ok);
    if (!ok || nouveauPrixVente ==0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un prix de vente different de 0.");
        return;
    }

    // Étape 4 : Vérification de la validité des valeurs saisies
    if (nouveauPrixAchat <= 0 || nouvelleQuantite <= 0 || nouveauPrixVente <= 0) {
        QMessageBox::warning(this, "Erreur", "Les valeurs saisies doivent être positives.");
        return;
    }

    // Étape 5 : Mise à jour des valeurs dans la base de données
    query.prepare("UPDATE GS_PRODUIT SET prixdachat = ?, quantite = ?, prixdevente = ? WHERE id = ?");
    query.addBindValue(nouveauPrixAchat);
    query.addBindValue(nouvelleQuantite);
    query.addBindValue(nouveauPrixVente);
    query.addBindValue(idProduit);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Produit modifié avec succès.");
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la mise à jour du produit : " + query.lastError().text());
    }

    // Étape 6 : Actualiser le tableau pour refléter les changements
    refreshTableView();  // Appelle une fonction qui met à jour ta vue (tableau, liste, etc.)
}



//




void MainWindow::on_rechercheri_clicked() {

    bool ok;
    int idRecherche = ui->lineEdit->text().toInt(&ok); // "lineEdit_id" est un exemple, utilisez l'ID réel de votre champ QLineEdit
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }
    produit prod;
    if (prod.rechercherParId(idRecherche)) {
        QMessageBox::information(this, "Produit trouvé", "Le produit avec l'ID " + QString::number(idRecherche) + " existe.");
    } else {
        QMessageBox::warning(this, "Produit non trouvé", "Aucun produit trouvé avec l'ID " + QString::number(idRecherche));
    }
}



//
void MainWindow::on_rechercherq_clicked() {

    bool ok;
    int quantiteRecherche= ui->lineEdit->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une quantite valide.");
        return;
    }
    produit prod;
    if (prod.rechercheQuantite(quantiteRecherche)) {
        QMessageBox::information(this, "Produit trouvé", "Le produit avec le quantite " + QString::number(quantiteRecherche) + " existe.");
    } else {
        QMessageBox::warning(this, "Produit non trouvé", "Aucun produit trouvé avec le quantite " + QString::number(quantiteRecherche));
    }
}
//

void MainWindow::on_recherchern_clicked() {
    QString nomRecherche = ui->lineEdit->text();  // Récupérer le texte saisi par l'utilisateur

    if (nomRecherche.isEmpty()) {  // Vérifier si le champ de recherche est vide
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un nom.");
        return;
    }

    produit prod;
    if (prod.rechercherParNom(nomRecherche)) {
        QMessageBox::information(this, "Produit trouvé", "Le produit avec le nom '" + nomRecherche + "' existe.");
    } else {
        QMessageBox::warning(this, "Produit non trouvé", "Aucun produit trouvé avec le nom '" + nomRecherche + "'.");
    }
}







void MainWindow::on_Update_clicked() {
    QSqlQuery query;
    query.prepare("SELECT id, nom, quantite FROM GS_PRODUIT WHERE quantite = 0");  // Recherche des produits avec une quantité de 0
    if (query.exec()) {
        bool foundZeroQuantity = false;
        while (query.next()) {
            int id = query.value(0).toInt();
            QString nom = query.value(1).toString();

            // Afficher un message de notification
            QMessageBox::information(this, "Produit à quantité 0",
                                     QString("Le produit \"%1\" (ID: %2) a une quantité de 0.").arg(nom).arg(id));

            // Mettre à jour la base de données (optionnel) - par exemple, réapprovisionner le produit à 10
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE GS_PRODUIT SET quantite = 10 WHERE id = :id");
            updateQuery.bindValue(":id", id);
            if (updateQuery.exec()) {
                qDebug() << "Quantité mise à jour pour le produit avec ID:" << id;
            } else {
                qDebug() << "Erreur de mise à jour pour le produit avec ID:" << id;
            }

            foundZeroQuantity = true;
        }

        if (!foundZeroQuantity) {
            QMessageBox::information(this, "Aucune mise à jour", "Il n'y a aucun produit avec une quantité de 0.");
        }

    } else {
        qDebug() << "Erreur de requête pour rechercher les produits à quantité 0: " << query.lastError().text();
        QMessageBox::critical(this, "Erreur", "Erreur lors de la recherche des produits à quantité 0.");
    }}
void MainWindow::on_exporter_clicked()
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
    QString title = "Liste des produits (Quantité = 0)";
    int yPosition = 50; // Position verticale pour le titre
    painter.drawText(100, yPosition, pdfWriter.width() - 200, 50, Qt::AlignCenter, title);

    // Ajuster yPosition pour laisser de l'espace après le titre
    yPosition += 120; // Ajustez cette valeur pour contrôler l'espace après le titre

    // Définir les dimensions du tableau
    QFont font;
    font.setPointSize(14); // Taille de police pour une meilleure lisibilité
    painter.setFont(font);

    QFontMetrics fontMetrics(font);
    int cellHeight = fontMetrics.height() + 20; // Hauteur des cellules
    int columnCount = ui->tableView_5->model()->columnCount();

    // Calcul de la largeur des cellules pour remplir la page A4
    int cellWidth = pdfWriter.width() / columnCount;

    // Calcul pour centrer le tableau horizontalement
    int tableWidth = columnCount * cellWidth;  // Largeur totale du tableau
    int pageWidth = pdfWriter.width();         // Largeur de la page
    int xStart = (pageWidth - tableWidth) / 2; // Position horizontale de départ

    // Dessiner l'en-tête des colonnes avec fond vert clair
    painter.setBrush(QColor(144, 238, 144)); // Vert clair pour l'en-tête
    int xPosition = xStart;
    for (int col = 0; col < columnCount; ++col) {
        QString headerData = ui->tableView_5->model()->headerData(col, Qt::Horizontal).toString();
        painter.drawRect(xPosition, yPosition, cellWidth, cellHeight); // Cadre de la cellule d'en-tête
        painter.drawText(xPosition, yPosition, cellWidth, cellHeight, Qt::AlignCenter, headerData);
        xPosition += cellWidth; // Déplacer horizontalement pour la prochaine cellule
    }

    painter.setBrush(Qt::NoBrush); // Enlever le pinceau après avoir dessiné l'en-tête
    yPosition += cellHeight; // Déplacer la position verticale après l'en-tête

    // Filtrer les lignes pour ne dessiner que celles dont la quantité est égale à 0
    int rowCount = ui->tableView_5->model()->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        // Récupérer la quantité de chaque produit (en supposant que la quantité est dans la 4e colonne, ajustez si nécessaire)
        QString quantityData = ui->tableView_5->model()->data(ui->tableView_5->model()->index(row, 4)).toString();  // 4 est l'index de la colonne "quantité"

        if (quantityData == "0") {  // Filtrer si la quantité est égale à 0
            xPosition = xStart; // Réinitialiser la position horizontale pour chaque ligne

            for (int col = 0; col < columnCount; ++col) {
                QString cellData = ui->tableView_5->model()->data(ui->tableView_5->model()->index(row, col)).toString();
                painter.drawRect(xPosition, yPosition, cellWidth, cellHeight); // Cadre de la cellule
                painter.drawText(xPosition, yPosition, cellWidth, cellHeight, Qt::AlignCenter, cellData);
                xPosition += cellWidth; // Déplacer horizontalement pour la prochaine cellule
            }

            yPosition += cellHeight; // Déplacer verticalement pour la prochaine ligne
        }
    }

    painter.end(); // Fin de la peinture du PDF

    // Message de confirmation
    QMessageBox::information(this, "Exportation réussie", "L'affichage a été exporté en PDF avec succès.");
}

void MainWindow::on_pushButtonCalculer_clicked() {
    // Récupérer l'ID du produit depuis le champ de texte
    bool conversionOk;
    int produitID = ui->taper->text().toInt(&conversionOk);  // Conversion du texte en entier

    // Si l'ID n'est pas valide ou si la conversion a échoué
    if (!conversionOk || produitID <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM GS_PRODUIT WHERE id = ?");
    query.addBindValue(produitID);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Erreur", "Produit introuvable. Veuillez réessayer.");
        return;
    }

    // Récupérer les données du produit
    QString nom = query.value(0).toString();
    double prixdachat = query.value(1).toDouble();
    double prixdevente = query.value(2).toDouble();
    int quantite = query.value(3).toInt();

    // Vérification de la quantité
    if (quantite == 0) {
        // Si la quantité est 0, on affiche un message de rupture de stock
        QMessageBox::warning(this, "Rupture de Stock", QString("Le produit \"%1\" est en rupture de stock.").arg(nom));
    } else {
        // Calcul du résultat : (prixdevente - prixdachat) * quantite
        double resultat = (prixdevente - prixdachat) * quantite;

        // Utiliser QString::number pour convertir le double en chaîne et afficher
        QString resultMessage = QString("Produit: %1\nID: %3\nPrix d'achat: %4\nPrix de vente: %5\nQuantité: 9\nRésultat du calcul: (%6 - %8) * %5 = %9")
                                    .arg(nom)               // Nom du produit
                                    .arg(produitID)         // ID du produit
                                    .arg(prixdachat)        // Prix d'achat
                                    .arg(prixdevente)       // Prix de vente
                                    .arg(quantite)          // Quantité
                                    .arg(prixdevente)       // Prix de vente (utilisé dans la formule)
                                    .arg(prixdachat)        // Prix d'achat (utilisé dans la formule)
                                    .arg(quantite)          // Quantité (utilisée dans la formule)
                                    .arg(resultat);         // Résultat du calcul

        // Afficher le message avec le calcul
        QMessageBox::information(this, "Calcul du Résultat", resultMessage);
    }
}

void MainWindow::on_pb_historique_clicked()
{
    // Afficher l'historique complet
    ui->historique->setText(ui->historique->text());
}

QString MainWindow::getHistorique()
{
    // Récupérer l'historique à partir d'une source (ici, pour simplifier, on le génère directement)
    // Vous pouvez adapter cette méthode pour récupérer des données d'une base de données ou autre
    QString historique = "Historique des actions:\n";
    QDateTime currentDateTime = QDateTime::currentDateTime();
    historique += currentDateTime.toString("yyyy-MM-dd hh:mm:ss") + " - Consultation de l'historique\n";

    // Vous pouvez aussi ajouter des actions passées ici, par exemple en récupérant des données d'une base de données
    return historique;
}


void MainWindow::on_sort_clicked()
{
    // Clear the model associated with the QTableView
    QSqlQueryModel *model = new QSqlQueryModel(this);

    // Query the database to fetch sorted stock data by stock ID (ascending order)
    QSqlQuery query;
    query.prepare("SELECT id, nom, quantite, prixdevente, prixdachat "
                  "FROM GS_PRODUIT "
                  "ORDER BY id ASC");  // Tri croissant par ID

    if (query.exec()) {
        model->setQuery(query); // Set the query to the model
        ui->tableView_6->setModel(model); // Set the model to the QTableView

        QMessageBox::information(this, "Sort Success", "Stock records sorted by ID.");
    } else {
        QMessageBox::critical(this, "Sort Error", "Failed to sort stocks by ID. " + query.lastError().text());

    }
}


void MainWindow::on_triequantite_clicked()
{
    // Clear the model associated with the QTableView
    QSqlQueryModel *model = new QSqlQueryModel(this);

    // Query the database to fetch sorted stock data by stock ID (ascending order)
    QSqlQuery query;
    query.prepare("SELECT id, nom, quantite, prixdevente, prixdachat "
                  "FROM GS_PRODUIT "
                  "ORDER BY  quantite ASC");  // Tri croissant par ID

    if (query.exec()) {
        model->setQuery(query); // Set the query to the model
        ui->tableView_6->setModel(model); // Set the model to the QTableView

        QMessageBox::information(this, "Sort Success", "Stock records sorted by quantite.");
    } else {
        QMessageBox::critical(this, "Sort Error", "Failed to sort stocks by quantite. " + query.lastError().text());

    }
}

void MainWindow::on_trieprix_clicked()
{
    // Clear the model associated with the QTableView
    QSqlQueryModel *model = new QSqlQueryModel(this);

    // Query the database to fetch sorted stock data by stock ID (ascending order)
    QSqlQuery query;
    query.prepare("SELECT id, nom, quantite, prixdevente, prixdachat "
                  "FROM GS_PRODUIT "
                  "ORDER BY  prixdachat ASC");  //

    if (query.exec()) {
        model->setQuery(query); // Set the query to the model
        ui->tableView_6->setModel(model); // Set the model to the QTableView

        QMessageBox::information(this, "Sort Success", "Stock records sorted by prixdachat.");
    } else {
        QMessageBox::critical(this, "Sort Error", "Failed to sort stocks by prixdachat. " + query.lastError().text());

    }
}

void MainWindow::on_btn_statistiques_clicked()
{
    // Requête SQL pour récupérer les données des produits (nom et quantités vendues)
    QSqlQuery query;
    query.prepare("SELECT nom, SUM(quantite) AS quantite_totale "
                  "FROM GS_PRODUIT "
                  "GROUP BY nom");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        return;
    }

    // Création du QBarSet pour le graphique à barres
    QBarSet *set = new QBarSet("Quantités");
    QStringList categories;  // Liste des produits

    while (query.next()) {
        QString nomProduit = query.value(0).toString();  // Nom du produit
        int quantite = query.value(1).toInt();  // Quantité totale vendue

        categories << nomProduit;  // Ajouter le nom du produit aux catégories
        *set << quantite;  // Ajouter la quantité au QBarSet
    }

    // Vérification que des données ont été récupérées
    if (set->count() == 0) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée trouvée.");
        return;
    }

    // Trouver la valeur maximale pour l'axe Y
    double maxValue = 0;
    for (int i = 0; i < set->count(); ++i) {
        double value = set->at(i);
        if (value > maxValue) {
            maxValue = value;
        }
    }

    // Création de la série et du graphique à barres
    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Quantités de produits vendus");

    // Configuration de l'axe des catégories (produits)
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Configuration de l'axe des valeurs (quantités)
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, maxValue);  // Plage Y basée sur la valeur maximale
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Création du QChartView pour afficher le graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Affichage du graphique dans un layout existant
    if (ui->layout_statistiques_2->layout() != nullptr) {
        delete ui->layout_statistiques_2->layout();
    }
    QVBoxLayout *layout = new QVBoxLayout(ui->layout_statistiques);
    layout->addWidget(chartView);
    ui->layout_statistiques_2->setLayout(layout);
}
void MainWindow::appendHistorique(const QString &historiqueText)
{
    // Ajoutez l'historique à la fin du texte existant dans le label
    ui->historique->setText(ui->historique->text() + "\n" + historiqueText);
}
//************//

void MainWindow::on_refresh_clicked() {
    // Prepare the query to fetch all employees
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM GS_EMPLOYE");  // Assuming you want to show all employees

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


bool recherche  (int id2 ){
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM GS_EMPLOYE WHERE ID = :id"); // Assuming your table is named 'employees' and the column is 'id'
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
    QString id_client = ui->lineEdit_CLIENT->text();
    if (!ok || id_client.isEmpty()) {
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
    QString poste = lastSelectedItemText ;
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
    QString id_client = ui->CLIENTmodifier->text();

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
        queryString = "SELECT * FROM GS_SERVICE ORDER BY ID_SERVICE";
    } else if (index == 1) {  // Si l'utilisateur choisit "Nom"
        queryString = "SELECT * FROM GS_SERVICE ORDER BY NOM";
    } else if (index == 2) {  // Si l'utilisateur choisit "DATE_ESTIME"
        queryString = "SELECT * FROM GS_SERVICE ORDER BY DATE_ESTIME";
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


void MainWindow::on_pushButton_exporter_3_clicked()
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



void MainWindow::on_pushButton_exporter_4_clicked()
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
        query.prepare("SELECT COUNT(*) FROM GS_CLIENT");
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
        query.prepare("SELECT ADRESSE, COUNT(*) FROM GS_CLIENT GROUP BY ADRESSE");
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
    query.prepare("SELECT NOM FROM GS_EMPLOYE WHERE ID = :id_employe");
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
    query.prepare("SELECT COUNT(*) FROM GS_SERVICE");
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
    query.prepare("SELECT NOM, COUNT(*) FROM GS_SERVICE GROUP BY NOM");
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
    QString id_client = ui->idClientLineEdit->text();
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
        queryString = QString("SELECT * FROM GS_CLIENT WHERE ID= %1").arg(id1);
    } else {
        // Si ce n'est pas un ID, chercher par NOM ou DESCRIPTION
        queryString = QString("SELECT * FROM GS_CLIENT WHERE NOM LIKE '%%1%' OR ADRESSE LIKE '%%1%'").arg(recherche);
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
        queryString = QString("SELECT * FROM GS_SERVICE WHERE ID_SERVICE = %1").arg(id);
    } else {
        // Si ce n'est pas un ID, chercher par NOM ou DESCRIPTION
        queryString = QString("SELECT * FROM GS_SERVICE WHERE NOM LIKE '%%1%' OR DESCRIPTION LIKE '%%1%'").arg(recherche);
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
    query.prepare("SELECT NOM, PRENOM FROM GS_EMPLOYE");

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
        ui->tabWidget_maintenance->setVisible(true);
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
    query.prepare("SELECT COUNT(*) FROM GS_EMPLOYE WHERE SALAIRE = :salaire"); // Assuming your table is named 'employees' and the column is 'id'
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
            model->setQuery(QString("SELECT * FROM GS_EMPLOYE WHERE SALAIRE = %1").arg(sal));

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


bool MainWindow::posteExists(const QString &post) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM GS_EMPLOYE WHERE  POSTE= :post "); //
    query.bindValue(":post", post);

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
        query.prepare("SELECT * FROM GS_EMPLOYE WHERE POSTE = :poste");
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

#include "maintenance.h"
void MainWindow::on_ajouter_clicked(){
    int id=ui->id->text().toInt();
    QString etat=ui->etat->text();
    QString nom=ui->nom->text();
    QString description=ui->description->text();
    QDate date = QDate::fromString(ui->date->text(), "yyyy-MM-dd");
    int duree=ui->duree->text().toInt();
    Maintenance m(id,nom,description,date,duree,etat);
    bool test=m.ajouter();
    if(test)
    {
        ui->tablee->setModel(mt.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("ajout effectué\n"
                                             "click cancel to exit."), QMessageBox::Cancel);
        // Réinitialiser les champs de saisie
        ui->id->clear();
        ui->etat->clear();
        ui->nom->clear();
        ui->description->clear();
        ui->date->clear();
        ui->duree->clear();

    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("ajout non effectue.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_supprimer_2_clicked(){
    Maintenance m;
    int id_supp=ui->supp->text().toInt();
    bool test=m.supprimer(id_supp);
    if(test)
    {
        ui->tablee->setModel(mt.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("supprission effectue\n"
                                             "click cancel to exit."), QMessageBox::Cancel);
        // Réinitialiser les champs de saisie
        ui->id->clear();
        ui->etat->clear();
        ui->nom->clear();
        ui->description->clear();
        ui->date->clear();
        ui->duree->clear();

    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("supprission non effectue.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
    }
}


void MainWindow::on_afficher_clicked(){
    Maintenance m;
    ui->tablee->setModel(mt.afficher());
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QSqlQueryModel * model=new QSqlQueryModel();



    switch (index) {
    case 0:
        model->setQuery("SELECT * FROM gs_maintenance ORDER BY id;");
        break;

    case 1:
        model->setQuery("SELECT * FROM gs_maintenance ORDER BY datee;");
        break;

    case 2:
        model->setQuery("SELECT * FROM gs_maintenance ORDER BY nom;");
        break;
    default:
        break;
    }

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("description"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("duree"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("etat"));
    ui->tablee->setModel(model);  // Set the model to the table view
}







