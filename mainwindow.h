#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"commande.h"
#include "produit.h"
#include "arduino.h"
#include <QMainWindow>
#include"QLabel"
#include<QTimer>
#include<QScrollArea>
#include <QProxyStyle>

#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QLabel>


#include "service.h"
#include "Facture.h"

#include "email.h"
#include <QDateEdit>
#include <QTableView>
#include <QFileDialog>
#include <QTextDocument>

#include <QtSql/QSqlQueryModel>       // Pour utiliser QSqlQueryModel pour les requêtes SQL
#include <QtCharts/QPieSeries>        // Pour la série de graphique en camembert (pie chart)
#include <QtCharts/QPieSlice>         // Pour les morceaux individuels du graphique en camembert              // Pour lire un son lors du clic
#include <QPen>

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSqlQueryModel>
#include <QPieSeries>
#include <QChart>
#include <QChartView>
#include <QTableWidget>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QVBoxLayout>
#include <QListWidget>
#include <QObject>
#include<QTimer>
#include <qdatetime.h>
#include <QDateTime>
#include "client.h"       // Include Client class header
#include "arduino.h"      // Include Arduino class header
#include "historique.h"
#include "employe.h"
#include "maintenance.h"


namespace Ui {
class MainWindow;
}

class SentimentAnalyzer {
public:
    QMap<QString, int> positiveWords;
    QMap<QString, int> negativeWords;

    SentimentAnalyzer();

    int analyseSentiment(const QString &text);
    QString obtenirSentiment(const QString &text);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Rendre updateHistoriqueLabel publique
    void updateHistoriqueLabel(const QString &historiqueText);
    void appendHistorique(const QString &historiqueText);


private slots:

    void on_pushButton_save_clicked();
    void on_pushButton_supprimer_clicked();
    void on_comboBox_type_activated(int index);
    bool getCommandeData(const QString &code, QString &id_client, QString &etat, QString &type, float &prix_total, QDate &date_commande);
    void on_comboBox_etat_activated(int index);
    void updateFields();
    void onPushButtonAnnulerClicked();
    void on_tableView_5_clicked(const QModelIndex &index);
    void validateID();
    void validatePrix();
    void validateCO();
    void validateidClient();
    void searchAndDisplayCommande();
    void on_comboBox_tri_currentIndexChanged(int index);
    void envoyerEmailFeedback(const QString &id_client, const QString &code_commande) ;
    void envoyerEmailAvecPython(const QString& emailClient, const QString& code);
    void on_pushButton_exporter_clicked();
    void genererStatistiquesParEtat();
    void updateCommandeStatus();
    void mettreAJourScrollArea();
    void executerScriptPython();
    void rechercherCommandeParCode();
    void afficherGraphiqueSentiments();
    void on_pushButton_actualiser_clicked();
    void showEmployePage();
    void showClientPage();
    void showCommandePage();
    void showproduitPage();
    void showservicePage();
    void showmaintenancePage();
    void onButtonClicked();
    void readFromArduino();
    void displayMachineStatus(int id, const QString &etat);
    //**************************************************************************************//
    void on_Ajouter_clicked();
    void on_supprimer_clicked();
    void on_rechercheri_clicked();
    void on_rechercherq_clicked();
    void on_recherchern_clicked();
    void on_exporter_clicked();
    void on_Update_clicked();
    void on_btn_statistiques_clicked();
    void refreshTableView();
    void on_ModifierButton_clicked();
    void on_pushButtonCalculer_clicked();

    void on_pb_historique_clicked();
    void on_sort_clicked();
    void on_trieprix_clicked();
    void on_triequantite_clicked();
    QString getHistorique();
    QLabel* getHistoriqueLabel();
//arduino
    //void sendMessageToArduino();
    void updateMachineStatus();
    //*******//
    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_Enregistrer_2_clicked();

    void on_Annulermodif_2_clicked();

    void on_ComboBox_trier_clicked(int index);

    void on_pushButton_exporter_3_clicked();

    void on_tabWidget_22_currentChanged();


    void on_ajouterFactureButton_clicked();
    void on_exporterFactureButton_clicked();
    void updateTableView();

    void on_pushButton_rechercher_clicked();

    void on_comboBox_tri_currentIndexChanged(const QString &selectedOption);

    // Button click handlers
    void on_pushButton_90_clicked();
    void on_pushButton_67_clicked();
    void on_pushButton_10_clicked();
    void on_Enregistrer_3_clicked();
    void on_Annulermodif_3_clicked();

    // Sort buttons
    void on_btnAscendant_clicked();
    void on_btnDescendant_clicked();

    // Export and search button handlers
    void on_pushButton_exporter_4_clicked();
    void on_pushButton_rechercher12_clicked();

    // Historical data button
    void on_pb_his_clicked();

    // Tab switch event
    void on_tabWidget_26_currentChanged();

    QString getNomEmploye(int id_employe);

    void on_pushButton_7_clicked();
    void on_ajoutemploye_clicked();
    void on_modifier_clicked();
    void on_enregistrer_clicked();
    void on_annulermodif_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_4_clicked();
    void on_trier_clicked();
    void on_comboBox_activated(int index);
    void handleQuestion(const QString &question);
    int on_connect_clicked();
    void on_send_clicked();
    void populateListWidget();
    void on_listWidget_2_itemDoubleClicked(QListWidgetItem *item);
    void on_show_clicked();
    void refreshMessages();
    void refreshPrivateMessages();
    void on_send_2_clicked();
    void on_show2_clicked();
    void on_trier_2_clicked();
    bool salaireExists(int salaire);
    bool posteExists(const QString &post);
    void on_tabWidget_7_tabBarClicked(int index);
    void on_recherchesal_clicked();
    void on_recherchesal_2_clicked();
    void on_refresh_clicked();
    void on_trier_3_clicked();
    //void startCommunication();

    void on_ajouter_clicked();
    void on_supprimer_2_clicked();
    void on_afficher_clicked();
    void on_comboBox_currentIndexChanged(int index);




private:
    Ui::MainWindow *ui;
    Commande cmd,c;
    void actualiserAffichage();
    QLabel *idErrorLabel;    // Error label for ID
    QLabel *prixErrorLabel;
    //QLabel *codeErrorLabel;
    QLabel *clientError;
    QTimer *searchTimer;
    QTabWidget *tabw;
    QTabWidget *tabCmd;
    //***
    produit p;
    QSystemTrayIcon *trayIcon;

    Arduino arduino;
    //***//
    Service Etmp;
    Client Etmp1;
    Employe Emp2;
    QString lastSelectedItemText;
    Employe etc;
    int idc2;
    QString recivername;
    QString receiverNom;
    QString receiverPrenom;
    int index;
    QTimer readTimer;
    QDateTime highTempDetectedTime;

    QTimer *temperatureCheckTimer;
    bool highTempFlag = false;  // Flag to track if temperature was high
    QDateTime timeSinceLastUpdate;  // Store the time when the temperature dropped below 30°C
    int machineId;  // Store the

    QTableView *tableView;
    Maintenance m,mt;






};

#endif // MAINWINDOW_H
