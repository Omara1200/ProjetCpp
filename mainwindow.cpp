#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formation.h"
#include <QMessageBox>
#include <QSqlQuery>

#include <QTextStream>
#include <QPrinter>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextDocument>

#include <QPieSeries>
#include <QChartView>
#include <QChart>
#include <QPieSlice>

#include <QDebug>
#include "Qrcode.hpp"
using namespace QtCharts;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView_formation->setModel(f.afficher());
remplir_comobo_id_gestion_formation();
remplir_comobo_id_supprimer_gestion_formation();

// Adjust the header view as needed
QHeaderView* headerView = ui->tableView_formation->horizontalHeader();
headerView->setSectionResizeMode(QHeaderView::Stretch);


ui->dateEdit->setDate(QDate::currentDate());
GESTION_FORMATION_STATISTIQUE();

    //calendrier

    QCalendarWidget* calendarWidget = ui->calendarWidget;

    // Clear existing date text formats
    calendarWidget->setDateTextFormat(QDate(), QTextCharFormat());

    QList<QDate> datesList = f.getDatesFromDatabase();

    for (const QDate& targetDate : datesList)
    {
        QTextCharFormat format = calendarWidget->dateTextFormat(targetDate); //yemchy lel calendrier bch ye5oo el text mta el date hakyyy (targetdate)
        format.setForeground(Qt::white);   // bch ibedl el couleur   du text fel date haky iredo white
        calendarWidget->setDateTextFormat(targetDate, format);   // bch yraj3 ell date , o text mta3ha el jdid
    }





    // Adjust the header view as needed
    QHeaderView* headerView1 = ui->tableView_formateur->horizontalHeader();
    headerView1->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView_formateur->setModel(FR.afficher());
remplir_comobo_id_supprimer_gestion_formateur();
GESTION_FORMATEUR_STATISTIQUE();




    ui->g_calendrier->hide();
    ui->gestion_formateur->hide();
    ui->gestion_formation->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bt_ajouter_clicked()
{
    int x=0;//nb  du faute dans controle saisie
    int ID_FORMATION=ui->lineEDIT_ID_FORMATION->text().toInt();
    QString TYPE=ui->lineEDIT_TYPE->text();
    QDate DATE_FORMATION=ui->dateEdit->date();
    QString DUREE=ui->comboBox_duree->currentText();
    int nb_place=ui->lineEDIT_NB_PLACE->text().toInt();
    int id_for=ui->comboBox_ID_FORMATEUR->currentText().toInt();

    //controle de saisie
    if(f.idExists(ID_FORMATION))
    {
        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ID deja existe"), QMessageBox::Ok);
        return;

    }
    if(ID_FORMATION==0  )
    {

        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ne mets pas 0"), QMessageBox::Ok);
        return;
    }
    if(ui->lineEDIT_ID_FORMATION->text().isEmpty())
    {

        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("tu ne peux pas mettre une pièce d'identité vide"), QMessageBox::Ok);
        return;
    }


    if(ui->lineEDIT_TYPE->text().isEmpty())
    {

        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide TYPE"), QObject::tr("tu ne peux pas mettre une type vide"), QMessageBox::Ok);
        return;
    }

    if(nb_place==0  )
    {

        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide nb_place"), QObject::tr("ne mets pas 0"), QMessageBox::Ok);
        return;
    }

    if(x==0) //si il n' y a pas problem dans le controle de saisie
    {FORMATION f(ID_FORMATION,TYPE,DATE_FORMATION,DUREE,nb_place,id_for);

    bool test=f.ajouter();
       QMessageBox msgBox;
       if(test)
        {msgBox.setText("Ajout avec succes.");
              ui->tableView_formation->setModel(f.afficher());
  remplir_comobo_id_supprimer_gestion_formation();
GESTION_FORMATION_STATISTIQUE();

//calendrier

QCalendarWidget* calendarWidget = ui->calendarWidget;

// Clear existing date text formats
calendarWidget->setDateTextFormat(QDate(), QTextCharFormat());

QList<QDate> datesList = f.getDatesFromDatabase();

for (const QDate& targetDate : datesList)
{
    QTextCharFormat format = calendarWidget->dateTextFormat(targetDate);
    format.setForeground(Qt::white);
    calendarWidget->setDateTextFormat(targetDate, format);
}


              ui->lineEDIT_ID_FORMATION->clear();
         ui->lineEDIT_TYPE->clear();
         ui->lineEDIT_NB_PLACE->clear();
   msgBox.exec();
        }

        else
            msgBox.setText("echec d'ajout");


   msgBox.exec();
    }





}

void MainWindow::remplir_comobo_id_gestion_formation()
{
    //repetition
     ui->comboBox_ID_FORMATEUR->clear();

    QSqlQuery query;
        query.exec("SELECT ID_FORMATEUR FROM FORMATEUR");
        while (query.next()) {
            QString ID = query.value(0).toString();
            ui->comboBox_ID_FORMATEUR->addItem(ID);

        }
}
void MainWindow::remplir_comobo_id_supprimer_gestion_formation()
{
    //repetition
     ui->supprimer_id->clear();

    QSqlQuery query;
        query.exec("SELECT ID_FORMATION FROM FORMATION");
        while (query.next()) {
            QString id = query.value(0).toString();
            ui->supprimer_id->addItem(id);

        }
}

void MainWindow::on_bt_update_clicked()
{
    int x=0;//nb  du faute dans controle saisie
    int ID_FORMATION=ui->lineEDIT_ID_FORMATION->text().toInt();
    QString TYPE=ui->lineEDIT_TYPE->text();
    QDate DATE_FORMATION=ui->dateEdit->date();
    QString DUREE=ui->comboBox_duree->currentText();
    int nb_place=ui->lineEDIT_NB_PLACE->text().toInt();
    int id_for=ui->comboBox_ID_FORMATEUR->currentText().toInt();

    //controle de saisie
    if(f.idExists(ID_FORMATION)==false)
    {
        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ID n' existe pas"), QMessageBox::Ok);
        return;

    }
    if(ID_FORMATION==0  )
    {

        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ne mets pas 0"), QMessageBox::Ok);
        return;
    }
    if(ui->lineEDIT_ID_FORMATION->text().isEmpty())
    {

        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("tu ne peux pas mettre une pièce d'identité vide"), QMessageBox::Ok);
        return;
    }


    if(ui->lineEDIT_TYPE->text().isEmpty())
    {

        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide TYPE"), QObject::tr("tu ne peux pas mettre une type vide"), QMessageBox::Ok);
        return;
    }

    if(nb_place==0  )
    {

        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide nb_place"), QObject::tr("ne mets pas 0"), QMessageBox::Ok);
        return;
    }

    if(x==0) //si il n' y a pas problem dans le controle de saisie
    {

    bool test=f.modifier(ID_FORMATION,TYPE,DATE_FORMATION,DUREE,nb_place,id_for);
       QMessageBox msgBox;
       if(test)
        {msgBox.setText("modification avec succes.");
              ui->tableView_formation->setModel(f.afficher());
  remplir_comobo_id_supprimer_gestion_formation();
GESTION_FORMATION_STATISTIQUE();

              ui->lineEDIT_ID_FORMATION->clear();
         ui->lineEDIT_TYPE->clear();
         ui->lineEDIT_NB_PLACE->clear();

         //calendrier

         QCalendarWidget* calendarWidget = ui->calendarWidget;

         // Clear existing date text formats
         calendarWidget->setDateTextFormat(QDate(), QTextCharFormat());

         QList<QDate> datesList = f.getDatesFromDatabase();

         for (const QDate& targetDate : datesList)
         {
             QTextCharFormat format = calendarWidget->dateTextFormat(targetDate);
             format.setForeground(Qt::white);
             calendarWidget->setDateTextFormat(targetDate, format);
         }
  msgBox.exec();
        }

        else
            msgBox.setText("echec d'ajout");
        msgBox.exec();


    }
}

void MainWindow::on_bt_supprimer_clicked()
{
    int id=ui->supprimer_id->currentText().toInt();
    bool test=f.supprimer(id);
     QMessageBox msgBox;
     if(test)
     {
          msgBox.setText("suppresion avec succes.");
                ui->tableView_formation->setModel(f.afficher());
             remplir_comobo_id_supprimer_gestion_formation();
                 GESTION_FORMATION_STATISTIQUE();
                 //calendrier

                 QCalendarWidget* calendarWidget = ui->calendarWidget;

                 // Clear existing date text formats
                 calendarWidget->setDateTextFormat(QDate(), QTextCharFormat());

                 QList<QDate> datesList = f.getDatesFromDatabase();

                 for (const QDate& targetDate : datesList)
                 {
                     QTextCharFormat format = calendarWidget->dateTextFormat(targetDate);
                     format.setForeground(Qt::white);
                     calendarWidget->setDateTextFormat(targetDate, format);
                 }

          }
         else
             {msgBox.setText("echec d'ajout");}
         msgBox.exec();
}

void MainWindow::on_PDF_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_formation->model()->rowCount();
    const int columnCount = ui->tableView_formation->model()->columnCount();

    out << "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           "<title>%1</title>\n"
           "<style>\n"
           "table {\n"
           "    width: 100%;\n"
           "    border-collapse: collapse;\n"
           "}\n"
           "th, td {\n"
           "    padding: 8px;\n"
           "    text-align: left;\n"
           "    border-bottom: 1px solid #ddd;\n"
           "}\n"
           "tr:nth-child(even) {\n"
           "    background-color: #f2f2f2;\n"
           "}\n"
           "</style>\n"
           "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<center> <H1>Liste des formations</H1></center><br/><br/>\n"
           "<table>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
    {
        if (!ui->tableView_formation->isColumnHidden(column))
        {
            out << QString("<th>%1</th>").arg(ui->tableView_formation->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr> <td>" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView_formation->isColumnHidden(column))
            {
                QString data = ui->tableView_formation->model()->data(ui->tableView_formation->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }



    QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);

}

void MainWindow::on_TRI_clicked()
{
    if(ui->choix->currentText()=="ID")
    {

        ui->tableView_formation->setModel(f.tri_id_formation());
   }
    if(ui->choix->currentText()=="TYPE")
    {
        ui->tableView_formation->setModel(f.tri_type());
   }
    if(ui->choix->currentText()=="NB_PLACE")
    {
        ui->tableView_formation->setModel(f.tri_nb_place());
       }
         // Adjust the header view as needed
       QHeaderView* headerView = ui->tableView_formation->horizontalHeader();
         headerView->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_chercher_textChanged(const QString &text)
{
    if(ui->choix->currentText()=="ID")
    { ui->tableView_formation->setModel( f.afficher_id(text));
}
    if(ui->choix->currentText()=="TYPE")
    {ui->tableView_formation->setModel( f.afficher_type(text));
    }
    if(ui->choix->currentText()=="NB_PLACE")
    {ui->tableView_formation->setModel( f.afficher_nb_place(text));
}
}


void MainWindow::on_bt_gestion_formateur_clicked()
{
    ui->g_calendrier->hide();
    ui->gestion_formation->hide();
    ui->gestion_formateur->show();
}

void MainWindow::GESTION_FORMATION_STATISTIQUE()
{
    QList<QWidget*> childWidgets = ui->gestion_formation_label_32->findChildren<QWidget*>();
        for (QWidget* childWidget : childWidgets) {
            childWidget->deleteLater();

        }
        //the clear didnt work, but my goal is when i second click this button it deleted old chart and renders a new one
        ui->gestion_formation_label_32->clear();
        ui->gestion_formation_label_32->hide();

    int s0, s1,s2,s3,s4;

    s0 = f.countType("3 jour");
    s1 = f.countType("7 jour");
    s2 = f.countType("1 mois");
    s3 = f.countType("2 mois");
    s4 = f.countType("6 mois");



    int stat = s0 + s1 + s2 + s3 + s4 ;
    // Calculate percentages
        float x = (stat != 0) ? (s0 * 100.0f) / stat : 0.0f;
        float x1 = (stat != 0) ? (s1 * 100.0f) / stat : 0.0f;
        float x2 = (stat != 0) ? (s2 * 100.0f) / stat : 0.0f;
   float x3 = (stat != 0) ? (s3 * 100.0f) / stat : 0.0f;
      float x4 = (stat != 0) ? (s4 * 100.0f) / stat : 0.0f;

        // Adjust the percentages to ensure they sum up to 100%
        float totalPercentage = x + x1+ x2+x3+x4  ;
        if (totalPercentage != 100.0f && stat != 0) {
            float correction = 100.0f - totalPercentage;   //100 - 99.99 = 0.01
            x += correction;
        }


//qDebug() <<  x <<endl;
//3 jour 33%
    QString ch1 = QString("3 jour %1%").arg(QString::number(x, 'f', 2));
    QString ch2 = QString("7 jour %2%").arg(QString::number(x1, 'f', 2));
    QString ch3 = QString("1 mois %3%").arg(QString::number(x2, 'f', 2));
    QString ch4 = QString("2 mois %4%").arg(QString::number(x3, 'f', 2));
    QString ch5 = QString("6 mois %5%").arg(QString::number(x4, 'f', 2));




    QPieSeries *series=new QPieSeries();
    series->setHoleSize(0.35);

    QPieSlice *slice= series->append(ch1,x);
    slice->setLabelVisible();
    slice->setLabelColor(QColor("#FFFFFF"));
        slice->setBrush(QColor(189, 76, 224, 1));

    QPieSlice *slice1= series->append(ch2,x1);
    slice1->setLabelVisible();
    slice1->setLabelColor(QColor("#FFFFFF"));
    slice1->setBrush(QColor(84, 16, 149, 1));

    QPieSlice *slice2= series->append(ch3,x2);
    slice2->setLabelVisible();

    slice2->setLabelColor(QColor(Qt::white));
    slice2->setBrush(QColor(119, 82, 254));

    QPieSlice *slice3= series->append(ch4,x3);
    slice3->setLabelVisible();
    slice3->setLabelColor(QColor(Qt::white));
    slice3->setBrush(QColor(77, 76, 125));

    QPieSlice *slice4= series->append(ch5,x4);
    slice4->setLabelVisible();
    slice4->setLabelColor(QColor(Qt::white));
    slice4->setBrush(QColor(255,255,255));


    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBrush backgroundBrush(QColor(187,93,87,0));
    chart->setBackgroundBrush(backgroundBrush);
    QChartView *chartview=new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setFixedSize(ui->gestion_formation_label_32->size());
    chartview->setParent(ui->gestion_formation_label_32);
    ui->gestion_formation_label_32->setStyleSheet("background:transparent; color:white; ");
    ui->gestion_formation_label_32->show();

}

void MainWindow::on_bt_calendrier_clicked()
{
    ui->gestion_formateur->hide();
    ui->gestion_formation->hide();
    ui->g_calendrier->show();
}

void MainWindow::on_return_formation_clicked()
{
    ui->gestion_formateur->hide();
    ui->g_calendrier->hide();
    ui->gestion_formation->show();
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
        ui->tableView_calendrier->setModel(f.afficherd(date));
}

void MainWindow::on_tableView_formation_activated(const QModelIndex &index)
{
             using namespace qrcodegen;


                QString val = ui->tableView_formation->model()->data(index).toString();
                QSqlQuery qry;
                qry.prepare("select * from FORMATION where ID_FORMATION='" + val + "'");

                if (qry.exec()) {
                    while (qry.next()) {
                        // Assuming these are the attributes of the Facture class
                        int id = qry.value(0).toInt();
                        QString type = qry.value(1).toString();
                        QDate debut = qry.value(2).toDate();
                          QString duree = qry.value(3).toString();
                          int nb = qry.value(4).toInt();
                          int formateur = qry.value(5).toInt();


            QString dateString = debut.toString("yyyy-MM-dd");
            QString debutString = QString::fromStdString(dateString.toStdString());

                        // Using QrCodegen to create a QR code from Facture attributes
                        QString text = "ID: " + QString::number(id) + "\n"
                                        "type: " + type + "\n"
                                        "debut : " + debutString + "\n"
                                        "duree : " + duree + "\n"
                                         "NB_PLACE: " + QString::number(nb) + "\n";
                                               "ID_FORMATEUR: " + QString::number(formateur) + "\n";

                        QrCode qr = QrCode::encodeText(text.toUtf8().data(), QrCode::Ecc::MEDIUM);

                        qint32 sz = qr.getSize();
                        QImage im(sz, sz, QImage::Format_RGB32);
                        QRgb black = qRgb(0, 0, 0);
                        QRgb white = qRgb(255, 255, 255);

                        for (int y = 0; y < sz; y++) {
                            for (int x = 0; x < sz; x++) {
                                im.setPixel(x, y, qr.getModule(x, y) ? black : white);
                            }
                        }
                        ui->qrcode->setPixmap(QPixmap::fromImage(im.scaled(200, 200, Qt::KeepAspectRatio, Qt::FastTransformation), Qt::MonoOnly));


                    }
                }

}

void MainWindow::on_bt_gestion_formation_clicked()
{
    ui->g_calendrier->hide();
    ui->gestion_formateur->hide();
    ui->gestion_formation->show();
}

void MainWindow::on_bt_ajouter_formateur_clicked()
{
    int x=0;//nb  du faute dans controle saisie
    int ID_FORMATEUR=ui->lineEDIT_ID_FORMATEUR->text().toInt();
    QString NOM=ui->lineEDIT_NOM->text();
    QString PRENOM=ui->lineEDIT_PRENOM->text();
    QString specialite=ui->comboBox_specialite->currentText();
    QString NUMERO=ui->lineEDIT_NUMERO->text();
    QString email=ui->lineEDIT_EMAIL->text();

    //controle de saisie
    if(FR.idExists(ID_FORMATEUR))
    {
        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ID deja existe"), QMessageBox::Ok);
        return;

    }
    if(ID_FORMATEUR==0  )
    {

        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ne mets pas 0"), QMessageBox::Ok);
        return;
    }
    if(ui->lineEDIT_ID_FORMATEUR->text().isEmpty())
    {

        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("tu ne peux pas mettre une pièce d'identité vide"), QMessageBox::Ok);
        return;
    }


    if(ui->lineEDIT_NOM->text().isEmpty())
    {

        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide nom"), QObject::tr("tu ne peux pas mettre une nom vide"), QMessageBox::Ok);
        return;
    }
    if(ui->lineEDIT_PRENOM->text().isEmpty())
    {

        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide prenom"), QObject::tr("tu ne peux pas mettre une prenom vide"), QMessageBox::Ok);
        return;
    }

    // numero de telephone 8 chiffre

    if (NUMERO.length() != 8)
    {
        QMessageBox::critical(nullptr, QObject::tr("Numéro invalide"), QObject::tr("Le numéro doit contenir 8 chiffres."), QMessageBox::Cancel);
        return;
    }

    if (!NUMERO.contains(QRegularExpression("^\\d+$")))
    {
        QMessageBox::critical(nullptr, QObject::tr("Numéro invalide"), QObject::tr("Le numéro ne doit contenir que des chiffres."), QMessageBox::Cancel);
        return;
    }



    // Vérifier si l'e-mail est valide
    QRegularExpression emailRegex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}\\b");
    QRegularExpressionMatch match = emailRegex.match(email);
    if (!match.hasMatch())
    {
    QMessageBox::critical(nullptr, QObject::tr("Email invalide"), QObject::tr("Le format de l'e-mail est invalide. Veuillez entrer un e-mail valide."), QMessageBox::Cancel);
    return;
    }

    if(x==0) //si il n' y a pas problem dans le controle de saisie
    {FORMATEUR FR(ID_FORMATEUR,NOM,PRENOM,specialite,NUMERO,email);

    bool test=FR.ajouter();
       QMessageBox msgBox;
       if(test)
        {msgBox.setText("Ajout avec succes.");
              ui->tableView_formateur->setModel(FR.afficher());
  remplir_comobo_id_supprimer_gestion_formateur();
  GESTION_FORMATEUR_STATISTIQUE();
remplir_comobo_id_gestion_formation();


              ui->lineEDIT_ID_FORMATEUR->clear();
         ui->lineEDIT_NOM->clear();
        ui->lineEDIT_PRENOM->clear();
         ui->lineEDIT_NUMERO->clear();
      ui->lineEDIT_EMAIL->clear();
        }

        else
            msgBox.setText("echec d'ajout");
        msgBox.exec();


    }

}
void MainWindow::remplir_comobo_id_supprimer_gestion_formateur()
{
    //repetition
     ui->supprimer_id_formateur->clear();

    QSqlQuery query;
        query.exec("SELECT ID_FORMATEUR FROM FORMATEUR");
        while (query.next()) {
            QString id = query.value(0).toString();
            ui->supprimer_id_formateur->addItem(id);

        }
}

void MainWindow::on_bt_update_formateur_clicked()
{
    int x=0;//nb  du faute dans controle saisie
    int ID_FORMATEUR=ui->lineEDIT_ID_FORMATEUR->text().toInt();
    QString NOM=ui->lineEDIT_NOM->text();
    QString PRENOM=ui->lineEDIT_PRENOM->text();
    QString specialite=ui->comboBox_specialite->currentText();
    QString NUMERO=ui->lineEDIT_NUMERO->text();
    QString email=ui->lineEDIT_EMAIL->text();

    //controle de saisie
    if(FR.idExists(ID_FORMATEUR)==false)
    {
        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ID deja existe"), QMessageBox::Ok);
        return;

    }
    if(ID_FORMATEUR==0  )
    {

        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ne mets pas 0"), QMessageBox::Ok);
        return;
    }
    if(ui->lineEDIT_ID_FORMATEUR->text().isEmpty())
    {

        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("tu ne peux pas mettre une pièce d'identité vide"), QMessageBox::Ok);
        return;
    }


    if(ui->lineEDIT_NOM->text().isEmpty())
    {

        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide nom"), QObject::tr("tu ne peux pas mettre une nom vide"), QMessageBox::Ok);
        return;
    }
    if(ui->lineEDIT_PRENOM->text().isEmpty())
    {

        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide prenom"), QObject::tr("tu ne peux pas mettre une prenom vide"), QMessageBox::Ok);
        return;
    }

    // numero de telephone 8 chiffre

    if (NUMERO.length() != 8)
    {
        QMessageBox::critical(nullptr, QObject::tr("Numéro invalide"), QObject::tr("Le numéro doit contenir 8 chiffres."), QMessageBox::Cancel);
        return;
    }

    if (!NUMERO.contains(QRegularExpression("^\\d+$")))
    {
        QMessageBox::critical(nullptr, QObject::tr("Numéro invalide"), QObject::tr("Le numéro ne doit contenir que des chiffres."), QMessageBox::Cancel);
        return;
    }



    // Vérifier si l'e-mail est valide
    QRegularExpression emailRegex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}\\b");
    QRegularExpressionMatch match = emailRegex.match(email);
    if (!match.hasMatch())
    {
    QMessageBox::critical(nullptr, QObject::tr("Email invalide"), QObject::tr("Le format de l'e-mail est invalide. Veuillez entrer un e-mail valide."), QMessageBox::Cancel);
    return;
    }


    if(x==0) //si il n' y a pas problem dans le controle de saisie
    {

    bool test=FR.modifier(ID_FORMATEUR,NOM,PRENOM,specialite,NUMERO,email);
       QMessageBox msgBox;
       if(test)
        {msgBox.setText("modification avec succes.");
              ui->tableView_formateur->setModel(FR.afficher());
  remplir_comobo_id_supprimer_gestion_formateur();
  GESTION_FORMATEUR_STATISTIQUE();
remplir_comobo_id_gestion_formation();
  ui->lineEDIT_ID_FORMATEUR->clear();
ui->lineEDIT_NOM->clear();
ui->lineEDIT_PRENOM->clear();
ui->lineEDIT_NUMERO->clear();
ui->lineEDIT_EMAIL->clear();



        }

        else
            msgBox.setText("echec d'ajout");
        msgBox.exec();


    }
}

void MainWindow::on_bt_supprimer_formateur_clicked()
{
    int id=ui->supprimer_id_formateur->currentText().toInt();
    bool test=FR.supprimer(id);
     QMessageBox msgBox;
    if(test)
    {
         msgBox.setText("suppresion avec succes.");
               ui->tableView_formateur->setModel(FR.afficher());
            remplir_comobo_id_supprimer_gestion_formateur();
            GESTION_FORMATEUR_STATISTIQUE();
remplir_comobo_id_gestion_formation();

         }
         else
             {msgBox.setText("echec de suppression");}
         msgBox.exec();
}

void MainWindow::on_PDF_formateur_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_formateur->model()->rowCount();
    const int columnCount = ui->tableView_formateur->model()->columnCount();

    out << "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           "<title>%1</title>\n"
           "<style>\n"
           "table {\n"
           "    width: 100%;\n"
           "    border-collapse: collapse;\n"
           "}\n"
           "th, td {\n"
           "    padding: 8px;\n"
           "    text-align: left;\n"
           "    border-bottom: 1px solid #ddd;\n"
           "}\n"
           "tr:nth-child(even) {\n"
           "    background-color: #f2f2f2;\n"
           "}\n"
           "</style>\n"
           "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<center> <H1>Liste des formateurs</H1></center><br/><br/>\n"
           "<table>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
    {
        if (!ui->tableView_formateur->isColumnHidden(column))
        {
            out << QString("<th>%1</th>").arg(ui->tableView_formateur->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr> <td>" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView_formateur->isColumnHidden(column))
            {
                QString data = ui->tableView_formateur->model()->data(ui->tableView_formateur->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }



    QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);

}

void MainWindow::on_TRI_formateur_clicked()
{
    if(ui->choix_formateur->currentText()=="NOM")
    {

        ui->tableView_formateur->setModel(FR.tri_nom());
    }
    if(ui->choix_formateur->currentText()=="PRENOM")
    {
        ui->tableView_formateur->setModel(FR.tri_prenom());
    }
    if(ui->choix_formateur->currentText()=="SPECIALITE")
    {
        ui->tableView_formateur->setModel(FR.tri_specialite());
       }
         // Adjust the header view as needed
       QHeaderView* headerView = ui->tableView_formateur->horizontalHeader();
         headerView->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_chercher_formateur_textChanged(const QString &text)
{
    if(ui->choix_formateur->currentText()=="NOM")
    { ui->tableView_formateur->setModel(FR.afficher_nom(text));
    }
    if(ui->choix_formateur->currentText()=="PRENOM")
    {ui->tableView_formateur->setModel(FR.afficher_prenom(text));
    }
    if(ui->choix_formateur->currentText()=="SPECIALITE")
    {ui->tableView_formateur->setModel(FR.afficher_specialite(text));
    }
}


void MainWindow::GESTION_FORMATEUR_STATISTIQUE()
{
    QList<QWidget*> childWidgets = ui->gestion_formateur_label_32->findChildren<QWidget*>();
        for (QWidget* childWidget : childWidgets) {
            childWidget->deleteLater();

        }
        //the clear didnt work, but my goal is when i second click this button it deleted old chart and renders a new one
        ui->gestion_formateur_label_32->clear();
        ui->gestion_formateur_label_32->hide();

    int s0, s1,s2;

    s0 = FR.countType("C++");
    s1 = FR.countType("C");
    s2 = FR.countType("PYTHON");


qDebug()<<s0<<endl;
qDebug()<<s1<<endl;
qDebug()<<s2<<endl;

    int stat = s0 + s1 + s2 ;
    // Calculate percentages
        float x = (stat != 0) ? (s0 * 100.0f) / stat : 0.0f;
        float x1 = (stat != 0) ? (s1 * 100.0f) / stat : 0.0f;
        float x2 = (stat != 0) ? (s2 * 100.0f) / stat : 0.0f;


        // Adjust the percentages to ensure they sum up to 100%
        float totalPercentage = x + x1+ x2  ;
        if (totalPercentage != 100.0f && stat != 0) {
            float correction = 100.0f - totalPercentage;
            x += correction;  // Apply correction to one of the slices (usually the largest one)
        }



    QString ch1 = QString("C++ %1%").arg(QString::number(x, 'f', 2));
    QString ch2 = QString("C %2%").arg(QString::number(x1, 'f', 2));
    QString ch3 = QString("PYTHON %3%").arg(QString::number(x2, 'f', 2));





    QPieSeries *series=new QPieSeries();
    series->setHoleSize(0.35);

    QPieSlice *slice= series->append(ch1,x);
    slice->setLabelVisible();
    slice->setLabelColor(QColor("#FFFFFF"));
        slice->setBrush(QColor(189, 76, 224, 1));

    QPieSlice *slice1= series->append(ch2,x1);
    slice1->setLabelVisible();
    slice1->setLabelColor(QColor("#FFFFFF"));
    slice1->setBrush(QColor(84, 16, 149, 1));

    QPieSlice *slice2= series->append(ch3,x2);
    slice2->setLabelVisible();

    slice2->setLabelColor(QColor(Qt::white));
    slice2->setBrush(QColor(119, 82, 254));



    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBrush backgroundBrush(QColor(187,93,87,0));
    chart->setBackgroundBrush(backgroundBrush);
    QChartView *chartview=new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setFixedSize(ui->gestion_formateur_label_32->size());
    chartview->setParent(ui->gestion_formateur_label_32);
    ui->gestion_formateur_label_32->setStyleSheet("background:transparent; color:white; ");
    ui->gestion_formateur_label_32->show();

}




