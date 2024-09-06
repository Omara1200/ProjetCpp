#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "formateur.h"
#include "formation.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bt_ajouter_clicked();
    void remplir_comobo_id_gestion_formation();
    void remplir_comobo_id_supprimer_gestion_formation();


    void on_bt_update_clicked();

    void on_bt_supprimer_clicked();

    void on_PDF_clicked();

    void on_TRI_clicked();

    void on_chercher_textChanged(const QString &arg1);

    void on_bt_gestion_formateur_clicked();
    void GESTION_FORMATION_STATISTIQUE();

    void on_bt_calendrier_clicked();

    void on_return_formation_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_tableView_formation_activated(const QModelIndex &index);

    void on_bt_gestion_formation_clicked();

    void on_bt_ajouter_formateur_clicked();

    void remplir_comobo_id_supprimer_gestion_formateur();

    void on_bt_update_formateur_clicked();

    void on_bt_supprimer_formateur_clicked();

    void on_PDF_formateur_clicked();

    void on_TRI_formateur_clicked();

    void on_chercher_formateur_textChanged(const QString &arg1);
    void GESTION_FORMATEUR_STATISTIQUE();







private:
    Ui::MainWindow *ui;
    FORMATION f;
    FORMATEUR FR;
};
#endif // MAINWINDOW_H
