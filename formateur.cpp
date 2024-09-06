#include "formateur.h"
#include <QTableView>
#include <QHeaderView>
#include <QSqlQuery>
FORMATEUR::FORMATEUR()
{
ID_FORMATEUR=0;
NOM="";
PRENOM="";
SPECIALITE="";
NUMERO="";
EMAIL="";
}
  FORMATEUR::FORMATEUR(int ID_FORMATEUR ,QString NOM,QString PRENOM,QString SPECIALITE,QString NUMERO,QString EMAIL)
   {


      this->ID_FORMATEUR=ID_FORMATEUR;
      this->NOM=NOM;
      this->PRENOM=PRENOM;
      this->SPECIALITE=SPECIALITE;
     this-> NUMERO=NUMERO;
      this->EMAIL=EMAIL;

   }

  int FORMATEUR:: getID_FORMATEUR(){return ID_FORMATEUR;}
  QString FORMATEUR::getNOM(){return  NOM ;}
  QString FORMATEUR::getPRENOM(){return PRENOM ;}
  QString FORMATEUR::getSPECIALITE(){return   SPECIALITE;}
  QString FORMATEUR::getNUMERO(){return  NUMERO ;}
  QString FORMATEUR::getEMAIL(){return   EMAIL;}


  void FORMATEUR::setID_FORMATEUR(int ID_FORMATEUR) {this->ID_FORMATEUR=ID_FORMATEUR;}
  void FORMATEUR::setNOM(QString   NOM){this-> NOM= NOM ;}
  void FORMATEUR::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
  void FORMATEUR::setSPECIALITE(QString SPECIALITE){this->SPECIALITE=SPECIALITE;}
  void FORMATEUR::setNUMERO(QString NUMERO){this-> NUMERO= NUMERO;}
  void FORMATEUR::setEMAIL(QString EMAIL){this-> EMAIL=EMAIL ;}


  bool FORMATEUR::ajouter()
  {
      QSqlQuery query;

      query.prepare("INSERT INTO FORMATEUR (ID_FORMATEUR,NOM,PRENOM,SPECIALITE,NUMERO,EMAIL) "
                    "VALUES (:ID_FORMATEUR, :NOM, :PRENOM, :SPECIALITE, :NUMERO, :EMAIL)");

      query.bindValue(":ID_FORMATEUR", ID_FORMATEUR);
      query.bindValue(":NOM", NOM);
      query.bindValue(":PRENOM", PRENOM);
      query.bindValue(":SPECIALITE", SPECIALITE);
      query.bindValue(":NUMERO",NUMERO);
      query.bindValue(":EMAIL",EMAIL);
      return query.exec();
  }


  QSqlQueryModel* FORMATEUR::afficher()
  {
  QSqlQueryModel* model=new QSqlQueryModel();

       model->setQuery("SELECT * FROM FORMATEUR");
       model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
       model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
       model->setHeaderData(3, Qt::Horizontal,QObject:: tr("SPECIALITE"));
       model->setHeaderData(4, Qt::Horizontal,QObject:: tr("NUMERO"));
       model->setHeaderData(5, Qt::Horizontal,QObject:: tr("EMAIL"));


  return model;

  }



  bool FORMATEUR::supprimer(int id)
  {QSqlQuery query;
  query.prepare("Delete FROM FORMATEUR where ID_FORMATEUR=:id");
  query.bindValue(0,id);
  return query.exec();
  }

  bool FORMATEUR::idExists(int id)
  {
  QSqlQuery query;
  query.prepare("SELECT COUNT(*) FROM FORMATEUR WHERE ID_FORMATEUR = :id");
  query.bindValue(":id", id);

  if (query.exec() && query.next()) {
      int count = query.value(0).toInt();
      return count > 0;
  }

  return false;
  }

  bool FORMATEUR::modifier(int ID_FORMATEUR,QString NOM,QString PRENOM,QString SPECIALITE,QString NUMERO,QString EMAIL)
  {
  QSqlQuery query;


  query.prepare("UPDATE FORMATEUR SET NOM=:NOM , PRENOM=:PRENOM, SPECIALITE=:SPECIALITE , NUMERO=:NUMERO ,EMAIL=:EMAIL  where ID_FORMATEUR=:ID_FORMATEUR");
  query.bindValue(":ID_FORMATEUR", ID_FORMATEUR);
  query.bindValue(":NOM", NOM);
  query.bindValue(":PRENOM", PRENOM);
  query.bindValue(":SPECIALITE", SPECIALITE);
  query.bindValue(":NUMERO",NUMERO);
  query.bindValue(":EMAIL",EMAIL);


 return query.exec();


  }

  QSqlQueryModel* FORMATEUR::tri_nom()
  {
  QSqlQueryModel* model = new QSqlQueryModel();
  model->setQuery("SELECT * FROM FORMATEUR ORDER BY NOM ASC");
  model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
  model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
  model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
  model->setHeaderData(3, Qt::Horizontal,QObject:: tr("SPECIALITE"));
  model->setHeaderData(4, Qt::Horizontal,QObject:: tr("NUMERO"));
  model->setHeaderData(5, Qt::Horizontal,QObject:: tr("EMAIL"));


  return model;
  }
  QSqlQueryModel* FORMATEUR::tri_prenom()
  {
  QSqlQueryModel* model = new QSqlQueryModel();
  model->setQuery("SELECT * FROM FORMATEUR ORDER BY PRENOM ASC");
  model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
  model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
  model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
  model->setHeaderData(3, Qt::Horizontal,QObject:: tr("SPECIALITE"));
  model->setHeaderData(4, Qt::Horizontal,QObject:: tr("NUMERO"));
  model->setHeaderData(5, Qt::Horizontal,QObject:: tr("EMAIL"));


  return model;
  }

  QSqlQueryModel* FORMATEUR::tri_specialite()
  {
  QSqlQueryModel* model = new QSqlQueryModel();
  model->setQuery("SELECT * FROM FORMATEUR ORDER BY SPECIALITE ASC");
  model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
  model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
  model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
  model->setHeaderData(3, Qt::Horizontal,QObject:: tr("SPECIALITE"));
  model->setHeaderData(4, Qt::Horizontal,QObject:: tr("NUMERO"));
  model->setHeaderData(5, Qt::Horizontal,QObject:: tr("EMAIL"));


  return model;
  }


  QSqlQueryModel* FORMATEUR::afficher_nom(const QString &text)
  {
  QSqlQueryModel* model=new QSqlQueryModel();

       model->setQuery("SELECT * FROM FORMATEUR WHERE NOM LIKE '%" + text + "%' ");
       model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
       model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
       model->setHeaderData(3, Qt::Horizontal,QObject:: tr("SPECIALITE"));
       model->setHeaderData(4, Qt::Horizontal,QObject:: tr("NUMERO"));
       model->setHeaderData(5, Qt::Horizontal,QObject:: tr("EMAIL"));

  return model;
  }

  QSqlQueryModel* FORMATEUR::afficher_prenom(const QString &text)
  {
  QSqlQueryModel* model=new QSqlQueryModel();

       model->setQuery("SELECT * FROM FORMATEUR WHERE PRENOM LIKE '%" + text + "%' ");
       model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
       model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
       model->setHeaderData(3, Qt::Horizontal,QObject:: tr("SPECIALITE"));
       model->setHeaderData(4, Qt::Horizontal,QObject:: tr("NUMERO"));
       model->setHeaderData(5, Qt::Horizontal,QObject:: tr("EMAIL"));
  return model;
  }

  QSqlQueryModel* FORMATEUR::afficher_specialite(const QString &text)
  {
  QSqlQueryModel* model=new QSqlQueryModel();

       model->setQuery("SELECT * FROM FORMATEUR WHERE SPECIALITE LIKE '%" + text + "%' ");
       model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
       model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
       model->setHeaderData(3, Qt::Horizontal,QObject:: tr("SPECIALITE"));
       model->setHeaderData(4, Qt::Horizontal,QObject:: tr("NUMERO"));
       model->setHeaderData(5, Qt::Horizontal,QObject:: tr("EMAIL"));


  return model;
  }

  int FORMATEUR::countType(const QString& type)
  {
      int count = 0;

      QSqlQuery query;
      query.prepare("SELECT COUNT(\"SPECIALITE\") FROM FORMATEUR WHERE \"SPECIALITE\" = :SPECIALITE");
      query.bindValue(":SPECIALITE", type);

      if (query.exec() && query.next()) {
          count = query.value(0).toInt();
      }

      return count;
  }



