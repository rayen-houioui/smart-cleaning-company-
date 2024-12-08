#include "mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QRegularExpression>
#include <QSortFilterProxyModel>
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QPrinter>
#include <QPainter>
#include <QSqlTableModel>
#include <QMap>
#include <QTableView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include<QPieSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QBluetoothLocalDevice>
#include <QBluetoothAddress>
#include <QBluetoothUuid>
#include <QDebug>
#include <qsqlerror.h>
#include<QTimer>
#include "arduino.h"
#include <QTimer>
using namespace std ;

MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent)
     ,ui(new Ui::MainWindow),
     highTempFlag(false)




{
    qDebug() << "Setting up UI";
    ui->setupUi(this);
    qDebug() << "UI setup complete";
    startCommunication();


    ui->tableView->setModel(Emp.afficher());
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


}
Arduino a = *new Arduino();

void MainWindow::on_refresh_clicked() {
    // Prepare the query to fetch all employees
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYE");  // Assuming you want to show all employees

    // Set the headers
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("POSTE"));

    // Set the model to the table view to refresh the data
    ui->tableView->setModel(model);  // Assuming your table view is named tableView

    // Optionally, reset any filters or selections here if necessary
    ui->tableView->reset();  // Resets the table view to its initial state
}

bool recherche  (int id ){
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE ID = :id"); // Assuming your table is named 'employees' and the column is 'id'
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.next()) {
            int count = query.value(0).toInt();
            return count > 0; // Return true if count is greater than 0
        }
    }

    return false; // Return false if query execution fails or no records found
}

void MainWindow::on_ajoutemploye_clicked()
{
    QString idStr = ui->cinE->text();
    QString nom = ui->nomE->text();
    QString prenom = ui->prenomE->text();
    QString poste = lastSelectedItemText ;
    QString salaireStr = ui->salaireE->text();

    // Define static regular expressions
    static const QRegularExpression reInt("^[0-9]+$"); // Pattern for integers
    static const QRegularExpression reStr("^[a-zA-Z]+$"); // Pattern for alphabetic strings

    // Check if ID is an integer and has a length of 8
    if (!reInt.match(idStr).hasMatch() || idStr.length() != 8) {
        QString errorMessage;
        if (idStr.length() != 8) {
            errorMessage += QObject::tr("L'ID doit avoir une longueur de 8 caractères.\n");
        }
        if (!reInt.match(idStr).hasMatch()) {
            errorMessage += QObject::tr("L'ID doit être un nombre entier valide.\n");
        }
        errorMessage += QObject::tr("Click Cancel to exit.");

        QMessageBox::critical(nullptr, QObject::tr("Invalid Input"), errorMessage, QMessageBox::Cancel);
        return;

    }
    int id = idStr.toInt();
    if (recherche(id )){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr(" Cette id deja existe .\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        return ;
    }

    // Check if name contains only letters
    if (!reStr.match(nom).hasMatch()) {
        QMessageBox::critical(nullptr, QObject::tr("Invalid Input"),
                              QObject::tr("nom doit etre seulement des caractéres.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }
    // Check if surname contains only letters
    if (!reStr.match(prenom).hasMatch()) {
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

    Employe E(id, salaire, nom, prenom, poste);
    if (E.idExists(id)) {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr(" ID.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        bool test = E.ajouter();
        if (test) // If query executed => QMessageBox::information
        {
            ui->tableView->setModel(Emp.afficher());
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


void MainWindow::on_pushButton_6_clicked() //supression
{

    int id = ui->lineEdit_15->text().toInt();
    if (Emp.idExists(id)) {
        bool test = Emp.supprimer(id);  // Call the supprimer() method via the Etmp attribute

        if (test)
        {
            ui->tableView->setModel(Emp.afficher());
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

void MainWindow::on_modifier_clicked()
{
    QString idStr = ui->lineEdit_15->text(); // Get the text from the line edit
    bool isNumber; // Variable to check if the conversion is successful

    // Convert the input string to an integer
    int id = idStr.toInt(&isNumber); // Convert to int and set isNumber based on success

    // Check if the input is not a valid number
    if (!isNumber) {
        QMessageBox::critical(nullptr, QObject::tr("Invalid Input"),
                              QObject::tr("L'ID doit être un nombre entier valide.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return; // Exit the function if the input is invalid
    }

    // Proceed to check if the ID exists
    if (Emp.idExists(id)) {
        Employe E;
        E=E.recupere(id);
        QString employeeName = E.getnom();
        QString employeeprenom=E.getprenom();
        double employeesalair=E.getsalair();
        QString str = QString::number(employeesalair);
        QString employeepost=E.getpost();
        qDebug() << "Employee Name: " << employeeName;  // Ensure this prints the correct name
        ui->nommodifier->setText(employeeName);
        ui->nommodifier->repaint();
        ui->prenommodifier->setText(employeeprenom);
        ui->nommodifier->repaint();
        ui->salairemodifier->setText(str);
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

void MainWindow::on_enregistrer_clicked()
{
int id = ui->lineEdit_15->text().toInt();  // Convert the entered string to an integer because the id attribute is of type int

    QString nom=ui->nommodifier->text();
    QString prenom=ui->prenommodifier->text();
    QString poste=ui->postemodifier->text();
    int salaire=ui->salairemodifier->text().toInt();
    Employe E(id,salaire,nom,prenom,poste);
    bool test=E.modifier();
    if(test) // Si requête exécutée => QMessageBox::information
    {
        ui->tableView->setModel(Emp.afficher());
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
    model->setQuery("SELECT ID FROM EMPLOYE");  // Only select the ID column from the EMPLOYE table

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
    ui->tableView->setModel(model);

    // Render the table view to the printer
    ui->tableView->render(&painter);

    painter.end();

    QMessageBox::information(this, tr("Export Completed"), tr("PDF export completed successfully."));
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

void MainWindow::on_comboBox_activated(int index)
{
    // Get the text of the selected item
    QString selectedText = ui->comboBox->currentText();

    // Use the selected text for your logic (e.g., update a label, print, etc.)
    qDebug() << "Selected text: " << selectedText;

    // Now call the handleQuestion function correctly
    handleQuestion( selectedText );

}
void MainWindow::populateListWidget()//list pour envoyer un message privé
{
    QSqlQuery query;
    query.prepare("SELECT NOM, PRENOM FROM EMPLOYE");

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    // Clear the list widget before adding new items
    ui->listWidget_2->clear();

    // Populate the list widget with the names
    while (query.next()) {
        QString nom = query.value(0).toString();
        QString prenom = query.value(1).toString();

        // Create a formatted string with NOM and PRENOM
        QString fullName = nom + " " + prenom;

        // Create a new list widget item and add it to the list
        ui->listWidget_2->addItem(fullName);
    }
}

int  MainWindow::on_connect_clicked()//connection a l'interface du messagerie par id
{
     idc=ui->lineEdit_10->text().toInt();
    if (recherche(idc )){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr(" Connexion reussie  .\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
     ui->tabWidget_2->setVisible(true);
     ui->nomconnecte->setVisible(true);
     ui->nomid->setVisible(true);
     Employe e;
     e=e.recupere(idc);
     QString str1 = e.getnom();
     QString str2 = e.getprenom();
     QString result = str1 + " " + str2;
     ui->nomid->setText(result);
     ui->label_67->setVisible(false);
     ui->connect->setVisible(false);
     populateListWidget();





     return idc;
    }else {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr(" erreure de connexion   .\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);




        return 0;
    }
}
void MainWindow::on_send_clicked() {
    ;
    etc = etc.recupere(idc);

    if (etc.getnom().isEmpty() || etc.getprenom().isEmpty()) {
        QMessageBox::warning(this, "Error", "Failed to retrieve employee details.");
        return;
    }

    QString senderNom = etc.getnom();
    QString senderPrenom = etc.getprenom();
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
    e = e.recupere(idc);

    if (e.getnom().isEmpty() || e.getprenom().isEmpty()) {
        QMessageBox::warning(this, "Error", "Failed to retrieve employee details.");
        return;
    }

    QString messages = e.getMessagesPublic(e.getnom(), e.getprenom());

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

    etc = etc.recupere(idc);

    if (etc.getnom().isEmpty() || etc.getprenom().isEmpty()) {
        QMessageBox::warning(this, "Error", "Failed to retrieve employee details.");
        return;
    }

    QString senderNom = etc.getnom();
    QString senderPrenom = etc.getprenom();
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
    etc = etc.recupere(idc);

    QString senderNom = etc.getnom();
    QString senderPrenom = etc.getprenom();

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
    QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tableView->model());
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
        ui->tableView->setModel(proxyModel);
    }
}

void MainWindow::on_trier_2_clicked()
{
    // Get the current model from the table view
    QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tableView->model());
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
        ui->tableView->setModel(proxyModel);
    }
}//trier par post


void MainWindow::on_tabWidget_7_tabBarClicked(int index)
{
    // statistiques
    QAbstractItemModel *model = ui->tableView->model();

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
    query.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE SALAIRE = :salaire"); // Assuming your table is named 'employees' and the column is 'id'
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
                model->setQuery(QString("SELECT * FROM EMPLOYE WHERE SALAIRE = %1").arg(sal));

                // Set the headers
                model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
                model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
                model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
                model->setHeaderData(3, Qt::Horizontal, QObject::tr("SALAIRE"));
                model->setHeaderData(4, Qt::Horizontal, QObject::tr("POSTE"));

                // Set the model to the table view
                ui->tableView->setModel(model); // Assuming your table v

        }
    }
 }


 bool MainWindow::posteExists(const QString &post) {
     QSqlQuery query;
     query.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE  POSTE= :post "); //
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
         query.prepare("SELECT * FROM EMPLOYE WHERE POSTE = :poste");
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
             ui->tableView->setModel(model);
         } else {
             qDebug() << "Query failed: " << query.lastError().text();  // Debugging query error
         }
     } else {
         qDebug() << "Poste does not exist.";
     }
 }

 void MainWindow::on_trier_3_clicked()
 {
     QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tableView->model());
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
         ui->tableView->setModel(proxyModel);
 }

 }
 MainWindow::~MainWindow()
 {
     delete ui;

 }
 void MainWindow::startCommunication()
 {
     // Try to connect to Arduino via the defined serial port
     int connectionStatus = a.connect_arduino();
     if (connectionStatus != 0) {
         QMessageBox::critical(this, "Connection Error", "Failed to connect to Arduino.");
         return;
     }

     // Start a timer to regularly read from the Arduino
     connect(&readTimer, &QTimer::timeout, this, &MainWindow::readFromArduino);
     readTimer.start(1000); // Check every second (1000 ms)
 }

 void MainWindow::readFromArduino() {
     QByteArray data = a.read_from_arduino();  // Assuming 'a' is correctly defined elsewhere in your code
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



