#ifndef USER_H
#define USER_H

#include <QString>
class User
{


public:
    User();
    User(uint, QString, QString, QString,QString,uint, QString,QString,QString);
    User(QString, QString, QString,QString,uint,QString,QString,QString);

    uint getId() { return id; }
    QString getNom() { return nom; }
    QString getPrenom() { return prenom; }
    QString getDate_naiss() { return date_naiss; }
    QString getAddresse() { return addresse; }
    uint getNbre_conges() { return nbre_conges; }
    QString getMail()  {return mail;}
    QString getPassword()  {return password; }
    QString getType()  {return type; }

    void setId(uint id) { this->id = id; }
    void setNom(QString nom) { this->nom = nom; }
    void setPrenom(QString prenom) { this->prenom = prenom; }
    void setDate_naiss(QString date_naiss) { this->date_naiss = date_naiss; }
    void setAdresse(QString addresse) { this->addresse = addresse; }
    void setNbre_conges(uint nbre_conges) { this->nbre_conges = nbre_conges; }
    void setMail(QString mail) { this->mail = mail; }
    void setPassword(QString password) { this->password = password; }
    void setType(QString type) { this->type = type; }


private:
    //Ui::User *ui;
    uint id ;
    QString nom;
    QString prenom;
    QString date_naiss;
    QString addresse;
    uint  nbre_conges;
    QString mail ;
    QString password;
    QString type;
};
#endif // USER_H
