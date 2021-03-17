#include "user.h"



User::User()
{}

User::User(uint _id, QString _nom, QString _prenom, QString _date_naiss,QString  _addresse,uint _nbre_conges, QString  _mail,QString _password,QString _type):
    id(_id), nom(_nom), prenom(_prenom), date_naiss(_date_naiss), addresse(_addresse),nbre_conges(_nbre_conges) , mail(_mail) , password(_password) ,type(_type)
{}

User::User(QString _nom, QString _prenom, QString _date_naiss,QString  _addresse,uint _nbre_conges, QString  _mail,QString _password,QString _type):
     nom(_nom), prenom(_prenom), date_naiss(_date_naiss), addresse(_addresse),nbre_conges(_nbre_conges) , mail(_mail) , password(_password) ,type(_type)
{}
