#ifndef FORMATEUR_H
#define FORMATEUR_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
class FORMATEUR
{
public:
    FORMATEUR();
    FORMATEUR(int,QString,QString,QString,QString,QString);

    int getID_FORMATEUR();
    void setID_FORMATEUR(int);

    QString getNOM();
    void setNOM(QString);
    QString getPRENOM();
    void setPRENOM(QString);
    QString getSPECIALITE();
    void setSPECIALITE(QString);
    QString getNUMERO();
    void setNUMERO(QString);
    QString getEMAIL();
    void setEMAIL(QString);


    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool idExists(int id);
    bool modifier(int ID_FORMATEUR,QString NOM,QString PRENOM,QString SPECIALITE,QString NUMERO,QString EMAIL);

    //metier
    QSqlQueryModel* tri_nom();
        QSqlQueryModel* tri_prenom();
            QSqlQueryModel* tri_specialite();
            int countType(const QString& type);
             QSqlQueryModel* afficher_nom(const QString &text);
              QSqlQueryModel* afficher_prenom(const QString &text);
               QSqlQueryModel* afficher_specialite(const QString &text);


private:
int ID_FORMATEUR;
QString NOM,PRENOM,SPECIALITE,NUMERO,EMAIL;
};

#endif // FORMATEUR_H
