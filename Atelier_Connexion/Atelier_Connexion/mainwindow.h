#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "service.h"
#include "Facture.h"
#include <QMainWindow>
#include "email.h"
#include <QDateEdit>
#include "commande.h"

#include <QPdfWriter>
#include <QPainter>
#include <QTableView>
#include <QFileDialog>
#include <QTextDocument>

#include <QtSql/QSqlQueryModel>       // Pour utiliser QSqlQueryModel pour les requêtes SQL
#include <QtCharts/QChart>            // Pour la création du graphique
#include <QtCharts/QChartView>        // Pour afficher le graphique
#include <QtCharts/QPieSeries>        // Pour la série de graphique en camembert (pie chart)
#include <QtCharts/QPieSlice>         // Pour les morceaux individuels du graphique en camembert
#include <QMediaPlayer>               // Pour lire un son lors du clic
#include <QPen>

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSqlQueryModel>
#include <QPieSeries>
#include <QChart>
#include <QChartView>

#include <QTableWidget>
#include <QPushButton>

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSqlQueryModel>
#include <QPieSeries>
#include <QChart>
#include <QChartView>
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
#include "produit.h"

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getNomEmploye(int id_employe);
private slots:

    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_Enregistrer_2_clicked();

    void on_Annulermodif_2_clicked();

    void on_ComboBox_trier_clicked(int index);

    void on_pushButton_exporter_clicked();

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
    void on_pushButton_exporter_3_clicked();
    void on_pushButton_rechercher12_clicked();

    // Historical data button
    void on_pb_his_clicked();

    // Tab switch event
    void on_tabWidget_26_currentChanged();



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
    bool posteExists(const QString &poste);
    void on_tabWidget_7_tabBarClicked(int index);
    void on_recherchesal_clicked();
    void on_recherchesal_2_clicked();
    void on_refresh_clicked();
    void on_trier_3_clicked();
    //void startCommunication();

    void on_pushButton_41_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_68_clicked();
    void on_Enregistrer_40_clicked();
    void on_Annulermodif_40_clicked();
    //void on_ComboBox_trier_3_clicked(int index);
    void on_pushButton_exporter_40_clicked();
    void on_pushButton_rechercher12_2_clicked();
    void on_tabWidget_40_currentChanged();
    void on_comboBox_tri_5_clicked(int index5);


    void on_pushButton_72_clicked();

    void on_pushButton_73_clicked();

    void on_pushButton_74_clicked();

    void on_Enregistrer_7_clicked();

    void on_Annulermodif_7_clicked();

    void on_ComboBox_trier_7_clicked(int index7);

    void on_pushButton_exporter_70_clicked();

    void on_pushButton_rechercher70_clicked();

    void on_tabWidget_70_currentChanged();






private:
    Ui::MainWindow *ui;
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
    Commande Etmp5;
    Produit Etmp7;
};
#endif // MAINWINDOW_H
