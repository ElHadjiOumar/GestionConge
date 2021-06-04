#include "user.h"



User::User()
{}

User::User(uint _id,uint _nbre_conge,QString _matricule, QString _nom, QString _prenom, QDate _date_naiss,QDate _date_inscription,QString  _addresse, QString  _mail,QString _password,QString _type):
    id(_id), nbre_conge(_nbre_conge),matricule(_matricule), nom(_nom), prenom(_prenom), date_naiss(_date_naiss),date_inscription(_date_inscription), addresse(_addresse) , mail(_mail) , password(_password) ,type(_type)
{}

/*QString User::getMatricule(){
    return matricule;
}*/
User::User(uint _nbre_conge,QString _matricule, QString _nom, QString _prenom, QDate _date_naiss,QDate _date_inscription,QString  _addresse, QString  _mail,QString _password,QString _type):
     nbre_conge(_nbre_conge),matricule(_matricule), nom(_nom), prenom(_prenom), date_naiss(_date_naiss),date_inscription(_date_inscription), addresse(_addresse) , mail(_mail) , password(_password) ,type(_type)
{}
