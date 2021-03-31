#include "user.h"



User::User()
{}

User::User(uint _id,QString _matricule, QString _nom, QString _prenom, QString _date_naiss,QString  _addresse, QString  _mail,QString _password,QString _type):
    id(_id), matricule(_matricule), nom(_nom), prenom(_prenom), date_naiss(_date_naiss), addresse(_addresse) , mail(_mail) , password(_password) ,type(_type)
{}

/*QString User::getMatricule(){
    return matricule;
}*/
User::User(QString _matricule, QString _nom, QString _prenom, QString _date_naiss,QString  _addresse, QString  _mail,QString _password,QString _type):
     matricule(_matricule), nom(_nom), prenom(_prenom), date_naiss(_date_naiss), addresse(_addresse) , mail(_mail) , password(_password) ,type(_type)
{}
