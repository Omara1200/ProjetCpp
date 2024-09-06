#ifndef FORMATION_H
#define FORMATION_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
class FORMATION
{
public:
    FORMATION();
    FORMATION(int,QString,QDate,QString,int,int);

    int getID_FORMATION();
    void setID_FORMATION(int);

    int getNB_PLACE();
    void setNB_PLACE(int);
    int getID_FOR();
    void setID_FOR(int);
    QString getDUREE();
    void setDUREE(QString);
    QString getTYPE();
    void setTYPE(QString);
    QDate getDATE_FORMATION();
    void setDATE_FORMATION(QDate);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool idExists(int id);
    bool modifier(int ID_FORMATION,QString TYPE,QDate DATE_FORMATION,QString DUREE,int NB_PLACE,int ID_FOR);

    //metier
    QSqlQueryModel* tri_id_formation();
        QSqlQueryModel* tri_type();
            QSqlQueryModel* tri_nb_place();
            int countType(const QString& type);
             QSqlQueryModel* afficher_id(const QString &text);
              QSqlQueryModel* afficher_type(const QString &text);
               QSqlQueryModel* afficher_nb_place(const QString &text);

               //metier avance
               QList<QDate> getDatesFromDatabase();
               QSqlQueryModel* afficherd(QDate date);
private:
 int ID_FORMATION,NB_PLACE,ID_FOR;
 QString DUREE,TYPE;
 QDate DATE_FORMATION;


};

#endif // FORMATION_H
