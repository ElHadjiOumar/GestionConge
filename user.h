#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>
class User
{


public:
    User();
    User(uint, QString,QString, QString, QString,QDate,QString, QString,QString,QString);
    User(QString, QString,QString, QString,QDate,QString,QString,QString,QString);

    uint getId() { return id; }
    QString getNbre_conge() { return nbre_conge; }
    QString getMatricule() { return matricule; }
    QString getNom() { return nom; }
    QString getPrenom() { return prenom; }
    QDate getDate_naiss() { return date_naiss; }
    QString getAddresse() { return addresse; }
    QString getMail()  {return mail;}
    QString getPassword()  {return password; }
    QString getType()  {return type; }

    void setId(uint id) { this->id = id; }
    void setNbre_conge(QString nbre_conge) { this->nbre_conge = nbre_conge; }
    void setMatricule(QString matricule) { this->matricule = matricule; }
    void setNom(QString nom) { this->nom = nom; }
    void setPrenom(QString prenom) { this->prenom = prenom; }
    void setDate_naiss(QDate date_naiss) { this->date_naiss = date_naiss; }
    void setAdresse(QString addresse) { this->addresse = addresse; }
    void setMail(QString mail) { this->mail = mail; }
    void setPassword(QString password) { this->password = password; }
    void setType(QString type) { this->type = type; }


private:
    //Ui::User *ui;
    uint id ;
    QString nbre_conge;
    QString matricule;
    QString nom;
    QString prenom;
    QDate date_naiss;
    QString addresse;
    QString mail ;
    QString password;
    QString type;
};
#endif // USER_H
