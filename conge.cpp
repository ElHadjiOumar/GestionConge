#include "conge.h"


Conge::Conge()
{}

Conge::Conge(uint _id, uint _employe_id, uint _nbre_conge, QString _date_debut,QString  _date_fin,QString _status,QString _motif):
    id(_id), employe_id(_employe_id), nbre_conge(_nbre_conge), date_debut(_date_debut), date_fin(_date_fin),status(_status),motif(_motif)
{}

Conge::Conge(uint _employe_id, uint _nbre_conge, QString _date_debut,QString  _date_fin,QString _status,QString _motif):
    employe_id(_employe_id), nbre_conge(_nbre_conge), date_debut(_date_debut), date_fin(_date_fin),status(_status),motif(_motif)
{}
