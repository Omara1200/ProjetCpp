#include "formation.h"
#include <QSqlQuery>

#include <QTableView>
#include <QHeaderView>
FORMATION::FORMATION()
{
ID_FORMATION=0;
NB_PLACE=0;
ID_FOR=0;
DUREE="";
TYPE="";
DATE_FORMATION=QDate::currentDate();

}

FORMATION::FORMATION(int ID_FORMATION,QString TYPE,QDate DATE_FORMATION,QString DUREE,int NB_PLACE,int ID_FOR)
{

    this->ID_FORMATION=ID_FORMATION;
    this->TYPE=TYPE;
    this->DATE_FORMATION=DATE_FORMATION;
    this->DUREE=DUREE;
   this-> NB_PLACE=NB_PLACE;
    this->ID_FOR=ID_FOR;

}
int FORMATION:: getID_FORMATION(){return ID_FORMATION;}
QString FORMATION::getTYPE(){return  TYPE ;}
QDate FORMATION::getDATE_FORMATION(){return DATE_FORMATION ;}
QString FORMATION::getDUREE(){return   DUREE;}
int FORMATION::getNB_PLACE(){return  NB_PLACE ;}
int FORMATION::getID_FOR(){return   ID_FOR;}


void FORMATION::setID_FORMATION(int ID_FORMATION) {this->ID_FORMATION=ID_FORMATION;}
void FORMATION::setTYPE(QString   TYPE){this-> TYPE= TYPE ;}
void FORMATION::setDATE_FORMATION(QDate DATE_FORMATION){this->DATE_FORMATION=DATE_FORMATION;}
void FORMATION::setDUREE(QString DUREE){this->DUREE=DUREE;}
void FORMATION::setNB_PLACE(int NB_PLACE){this-> NB_PLACE= NB_PLACE;}
void FORMATION::setID_FOR(int ID_FOR){this-> ID_FOR=ID_FOR ;}

bool FORMATION::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO FORMATION (ID_FORMATION,TYPE,DATE_FORMATION,DUREE,NB_PLACE,ID_FOR) "
                  "VALUES (:ID, :TYPE, :DATE_FORMATION, :DUREE, :NB_PLACE, :ID_FOR)");

    query.bindValue(":ID", ID_FORMATION);
    query.bindValue(":TYPE", TYPE);
    query.bindValue(":DATE_FORMATION", DATE_FORMATION);
    query.bindValue(":DUREE", DUREE);
    query.bindValue(":NB_PLACE",NB_PLACE);
    query.bindValue(":ID_FOR",ID_FOR);
    return query.exec();
}


QSqlQueryModel* FORMATION::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT * FROM FORMATION");
     model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
     model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TYPE"));
     model->setHeaderData(2, Qt::Horizontal,QObject:: tr("DATE_FORMATION"));
     model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DUREE"));
     model->setHeaderData(4, Qt::Horizontal,QObject:: tr("NB_PLACE"));
     model->setHeaderData(5, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
     // Create a table view
     QTableView* tableView = new QTableView;
     tableView->setModel(model);

     // Get the header view
     QHeaderView* headerView =tableView->horizontalHeader();
     headerView->setSectionResizeMode(QHeaderView::Stretch);

return model;

}



bool FORMATION::supprimer(int id)
{QSqlQuery query;
query.prepare("Delete FROM FORMATION where ID_FORMATION=:id");
query.bindValue(0,id);
return query.exec();
}

bool FORMATION::idExists(int id)
{
QSqlQuery query;
query.prepare("SELECT COUNT(*) FROM FORMATION WHERE ID_FORMATION = :id");
query.bindValue(":id", id);

if (query.exec() && query.next()) {
    int count = query.value(0).toInt();
    return count > 0;
}

return false;
}

bool FORMATION::modifier(int ID_FORMATION,QString TYPE,QDate DATE_FORMATION,QString DUREE,int NB_PLACE,int ID_FOR)
{
QSqlQuery query;


query.prepare("UPDATE FORMATION SET TYPE=:TYPE , DATE_FORMATION=:DATE_FORMATION, DUREE=:DUREE , NB_PLACE=:NB_PLACE ,ID_FOR=:ID_FOR  where ID_FORMATION=:ID_FORMATION");
query.bindValue(":ID_FORMATION", ID_FORMATION);
query.bindValue(":TYPE", TYPE);
query.bindValue(":DATE_FORMATION", DATE_FORMATION);
query.bindValue(":DUREE", DUREE);
query.bindValue(":NB_PLACE",NB_PLACE);
query.bindValue(":ID_FOR",ID_FOR);


  if (query.exec()) {
      // Commit the transaction
      QSqlDatabase::database().commit();
      return true;
  } else {
      // Rollback the transaction in case of an error
      QSqlDatabase::database().rollback();
      return false;
  }


}

QSqlQueryModel* FORMATION::tri_id_formation()
{
QSqlQueryModel* model = new QSqlQueryModel();
model->setQuery("SELECT * FROM FORMATION ORDER BY ID_FORMATION ASC");
model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TYPE"));
model->setHeaderData(2, Qt::Horizontal,QObject:: tr("DATE_FORMATION"));
model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DUREE"));
model->setHeaderData(4, Qt::Horizontal,QObject:: tr("NB_PLACE"));
model->setHeaderData(5, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
// Create a table view
QTableView* tableView = new QTableView;
tableView->setModel(model);

// Get the header view
QHeaderView* headerView =tableView->horizontalHeader();
headerView->setSectionResizeMode(QHeaderView::Stretch);

return model;
}
QSqlQueryModel* FORMATION::tri_type()
{
QSqlQueryModel* model = new QSqlQueryModel();
model->setQuery("SELECT * FROM FORMATION ORDER BY TYPE ASC");
model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TYPE"));
model->setHeaderData(2, Qt::Horizontal,QObject:: tr("DATE_FORMATION"));
model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DUREE"));
model->setHeaderData(4, Qt::Horizontal,QObject:: tr("NB_PLACE"));
model->setHeaderData(5, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
// Create a table view
QTableView* tableView = new QTableView;
tableView->setModel(model);

// Get the header view
QHeaderView* headerView =tableView->horizontalHeader();
headerView->setSectionResizeMode(QHeaderView::Stretch);

return model;
}

QSqlQueryModel* FORMATION::tri_nb_place()
{
QSqlQueryModel* model = new QSqlQueryModel();
model->setQuery("SELECT * FROM FORMATION ORDER BY NB_PLACE ASC");
model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TYPE"));
model->setHeaderData(2, Qt::Horizontal,QObject:: tr("DATE_FORMATION"));
model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DUREE"));
model->setHeaderData(4, Qt::Horizontal,QObject:: tr("NB_PLACE"));
model->setHeaderData(5, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
// Create a table view
QTableView* tableView = new QTableView;
tableView->setModel(model);

// Get the header view
QHeaderView* headerView =tableView->horizontalHeader();
headerView->setSectionResizeMode(QHeaderView::Stretch);

return model;
}


QSqlQueryModel* FORMATION::afficher_id(const QString &text)
{
QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT * FROM FORMATION WHERE ID_FORMATION LIKE '%" + text + "%' ");
     model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
     model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TYPE"));
     model->setHeaderData(2, Qt::Horizontal,QObject:: tr("DATE_FORMATION"));
     model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DUREE"));
     model->setHeaderData(4, Qt::Horizontal,QObject:: tr("NB_PLACE"));
     model->setHeaderData(5, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));

return model;
}

QSqlQueryModel* FORMATION::afficher_type(const QString &text)
{
QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT * FROM FORMATION WHERE TYPE LIKE '%" + text + "%' ");
     model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
     model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TYPE"));
     model->setHeaderData(2, Qt::Horizontal,QObject:: tr("DATE_FORMATION"));
     model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DUREE"));
     model->setHeaderData(4, Qt::Horizontal,QObject:: tr("NB_PLACE"));
     model->setHeaderData(5, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));

return model;
}

QSqlQueryModel* FORMATION::afficher_nb_place(const QString &text)
{
QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT * FROM FORMATION WHERE NB_PLACE LIKE '%" + text + "%' ");
     model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
     model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TYPE"));
     model->setHeaderData(2, Qt::Horizontal,QObject:: tr("DATE_FORMATION"));
     model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DUREE"));
     model->setHeaderData(4, Qt::Horizontal,QObject:: tr("NB_PLACE"));
     model->setHeaderData(5, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));


return model;
}

int FORMATION::countType(const QString& type)
{
    int count = 0;

    QSqlQuery query;
    query.prepare("SELECT COUNT(\"DUREE\") FROM FORMATION WHERE \"DUREE\" = :DUREE");
    query.bindValue(":DUREE", type);

    if (query.exec() && query.next()) {
        count = query.value(0).toInt();
    }

    return count;
}



QSqlQueryModel* FORMATION::afficherd(QDate date)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM FORMATION WHERE DATE_FORMATION = :date");
    query.bindValue(":date", date);

    if (query.exec())
    {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
        model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TYPE"));
        model->setHeaderData(2, Qt::Horizontal,QObject:: tr("DATE_FORMATION"));
        model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DUREE"));
        model->setHeaderData(4, Qt::Horizontal,QObject:: tr("NB_PLACE"));
        model->setHeaderData(5, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
    }

    return model;
}



QList<QDate> FORMATION::getDatesFromDatabase()
{
    QList<QDate> datesList;
    QSqlQuery query("SELECT DATE_FORMATION FROM FORMATION");

    while (query.next())
    {
        QDate date = query.value(0).toDate();

        if (date.isValid())
        {
            datesList.append(date);
        }
    }



    return datesList;
}
