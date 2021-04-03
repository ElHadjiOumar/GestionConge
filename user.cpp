#include "user.h"



User::User()
{}

User::User(uint _id,QString _nbre_conge,QString _matricule, QString _nom, QString _prenom, QDate _date_naiss,QString  _addresse, QString  _mail,QString _password,QString _type):
    id(_id), nbre_conge(_nbre_conge),matricule(_matricule), nom(_nom), prenom(_prenom), date_naiss(_date_naiss), addresse(_addresse) , mail(_mail) , password(_password) ,type(_type)
{}

/*QString User::getMatricule(){
    return matricule;
}*/
User::User(QString _nbre_conge,QString _matricule, QString _nom, QString _prenom, QDate _date_naiss,QString  _addresse, QString  _mail,QString _password,QString _type):
     nbre_conge(_nbre_conge),matricule(_matricule), nom(_nom), prenom(_prenom), date_naiss(_date_naiss), addresse(_addresse) , mail(_mail) , password(_password) ,type(_type)
{}
