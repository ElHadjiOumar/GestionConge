#include "conge.h"


Conge::Conge()
{}

Conge::Conge(uint _id, QString _employe_id, uint _nbre_conge, QDate _date_debut,QDate  _date_fin,QString _status,QString _motif):
    id(_id), employe_id(_employe_id), nbre_conge(_nbre_conge), date_debut(_date_debut), date_fin(_date_fin),status(_status),motif(_motif)
{}

Conge::Conge(QString _employe_id, uint _nbre_conge, QDate _date_debut,QDate  _date_fin,QString _status,QString _motif):
    employe_id(_employe_id), nbre_conge(_nbre_conge), date_debut(_date_debut), date_fin(_date_fin),status(_status),motif(_motif)
{}
