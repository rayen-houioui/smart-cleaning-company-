#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "employe.h"
#include <QMainWindow>
#include <QListWidget>
#include <QTableView>
#include <QObject>
#include<QTimer>
#include <qdatetime.h>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_6_clicked();
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
    void startCommunication();
    void readFromArduino();


private:
    Ui::MainWindow *ui;
    Employe Emp;
    QString lastSelectedItemText;
    Employe etc;
    int idc;
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

};

#endif // MAINWINDOW_H
