#ifndef CONGE_H
#define CONGE_H

#include <QString>
class Conge
{
public:
    Conge();
    Conge(uint,uint,uint,QString,QString,QString,QString);
    Conge(uint,uint,QString,QString,QString,QString);

    uint getId() { return id; }
    uint getEmploye_id() {return employe_id;}
    uint getNbre_conge() {return nbre_conge;}
    QString getDate_debut() {return date_debut;}
    QString getDate_fin() {return date_fin;}
    QString getStatus() {return status;}
    QString getMotif() {return motif;}


    void setId(uint id) { this->id = id; }
    void setEmploye_id(uint employe_id) { this->employe_id = employe_id; }
    void setNbre_conge(uint nbre_conge) { this->nbre_conge = nbre_conge; }
    void setDate_debut(QString date_debut) { this->date_debut = date_debut; }
    void setDate_fin(QString date_fin) { this->date_fin = date_fin; }
    void setStatus(QString status) { this->status = status; }
    void setMotif(QString motif) { this->motif = motif; }


private:

    uint id;
    uint employe_id;
    uint nbre_conge;
    QString date_debut;
    QString date_fin;
    QString motif;
    QString status;
};
#endif // CONGE_H
