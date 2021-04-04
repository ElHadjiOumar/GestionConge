#include "congemodel.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>

CongeModel::CongeModel(DBAccess *dbAccess)
{
    this->dbAccess = dbAccess;
    clear();
}

void CongeModel::create(User user,Conge conge)
{
    dbAccess->open();

    QSqlQuery query(dbAccess->database());
    query.prepare("INSERT INTO t_conge_nonlu (employe_id, nbre_conge, date_debut,date_fin,status,motif) "
                    "VALUES (:employe_id, :nbre_conge, :date_debut, :date_fin, :status ,:motif)");
    query.bindValue(":nbre_conge", conge.getNbre_conge());
    query.bindValue(":employe_id", user.getMatricule());
    query.bindValue(":date_debut", conge.getDate_debut());
    query.bindValue(":date_fin", conge.getDate_fin());
    query.bindValue(":status", conge.getStatus());
    query.bindValue(":motif", conge.getMotif());

    query.exec();

    readCongeNonLU(&user);

    qDebug () << "Le conge avec le nbre de conge =  " << conge.getNbre_conge() << "created successfully!";
    dbAccess->close();
}

void CongeModel::copie(Conge conge)
{
    dbAccess->open();

    QSqlQuery query(dbAccess->database());
    query.prepare("INSERT INTO t_conge_lu (employe_id, nbre_conge, date_debut,date_fin,status,motif) "
                    "SELECT :employe_id, :nbre_conge, :date_debut, :date_fin, :status ,:motif FROM t_conge_nonlu");
    query.bindValue(":nbre_conge", conge.getNbre_conge());
    query.bindValue(":employe_id", conge.getEmploye_id());
    query.bindValue(":date_debut", conge.getDate_debut());
    query.bindValue(":date_fin", conge.getDate_fin());
    query.bindValue(":status", conge.getStatus());
    query.bindValue(":motif", conge.getMotif());
    query.exec();



    //readCongeNonLU(&user);

    qDebug () << "Copie Effectué ";
    dbAccess->close();
}

void CongeModel::readAll()
{
    dbAccess->open();

    QSqlDatabase database = dbAccess->database();
    this->setQuery("SELECT id, employe_id, nbre_conge, date_debut,date_fin,status,motif FROM t_conge_nonlu ", database);

    this->setHeaderData(0, Qt::Horizontal, tr("Id"));
    this->setHeaderData(1, Qt::Horizontal, tr("Employe_id"));
    this->setHeaderData(2, Qt::Horizontal, tr("Nbre_conge"));
    this->setHeaderData(3, Qt::Horizontal, tr("Date de Debut"));
    this->setHeaderData(4, Qt::Horizontal, tr("Date de Fin"));
    this->setHeaderData(5, Qt::Horizontal, tr("Status"));


    qDebug () << "Conges displayed successfully!";
    dbAccess->close();
}

void CongeModel::readCongeNonLU(User *user)
{
    dbAccess->open();

     QSqlDatabase database = dbAccess->database();
    this->setQuery("SELECT id,employe_id, nbre_conge, date_debut,date_fin,status,motif FROM t_conge_nonlu WHERE employe_id=\""+user->getMatricule()+"\"", database);


     this->setHeaderData(0, Qt::Horizontal, tr("Id"));
     this->setHeaderData(1, Qt::Horizontal, tr("Employe_id"));
     this->setHeaderData(2, Qt::Horizontal, tr("Nbre_conge"));
     this->setHeaderData(3, Qt::Horizontal, tr("Date de Debut"));
     this->setHeaderData(4, Qt::Horizontal, tr("Date de Fin"));
     this->setHeaderData(5, Qt::Horizontal, tr("Status"));


    qDebug () << "Conges displayed successfully!";
    dbAccess->close();
}


void CongeModel::updateLU(Conge conge)
{
    dbAccess->open();

    QSqlQuery query(dbAccess->database());
    query.prepare("UPDATE t_conge_nonlu SET employe_id=:employe_id, nbre_conge=:nbre_conge, date_debut=:date_debut, date_fin=:date_fin,status=:status, motif=:motif WHERE id=:id");
    query.bindValue(":employe_id", conge.getEmploye_id());
    query.bindValue(":nbre_conge", conge.getNbre_conge());
    query.bindValue(":date_debut", conge.getDate_debut());
    query.bindValue(":date_fin", conge.getDate_fin());
    query.bindValue(":status", conge.getStatus());
    query.bindValue(":motif", conge.getMotif());
    query.bindValue(":id", conge.getId());
    query.exec();

    copie(conge);
    removeMAX();
    //removeNonLU(conge.getId());
    readAll();

    qDebug () << "La demande de Conge de :" << conge.getEmploye_id() << " envoye avec succes !" ;
    dbAccess->close();
}

void CongeModel::removeMAX()
{
    dbAccess->open();

    QSqlQuery query(dbAccess->database());
    //query.prepare("DELETE FROM t_conge_lu WHERE id=(SELECT max(id) FROM t_conge_lu)");
       query.prepare("DELETE FROM t_conge_lu WHERE ID IN (SELECT id FROM t_conge_lu ORDER BY ID DESC LIMIT (SELECT COUNT(id)-1 FROM t_conge_nonlu))");
        query.exec();


    dbAccess->close();
}

void CongeModel::removeNonLU(uint id)
{
    dbAccess->open();

    QSqlQuery query(dbAccess->database());
    query.prepare("DELETE FROM t_conge_nonlu WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();

    dbAccess->close();
}
/*int CongeModel::count(){
    dbAccess->open();

    QSqlQuery query(dbAccess->database());
    int compter ;

    query.prepare("SELECT COUNT(id) FROM t_conge_lu");
    query.exec();
    query.first();
    compter = query.value(0).toUInt();

    qDebug () << "compter est : " << compter;

    return compter;
    dbAccess->close();
}*/

void CongeModel::clear()
{
    dbAccess->open();

    QSqlDatabase database = dbAccess->database();
    this->setQuery("SELECT id, employe_id, nbre_conge, date_debut,date_fin,status,motif  FROM t_conge_nonlu WHERE id=-1", database);

    this->setHeaderData(0, Qt::Horizontal, tr("Id"));
    this->setHeaderData(1, Qt::Horizontal, tr("Employe_id"));
    this->setHeaderData(2, Qt::Horizontal, tr("Nbre_conge"));
    this->setHeaderData(3, Qt::Horizontal, tr("Date de Debut"));
    this->setHeaderData(4, Qt::Horizontal, tr("Date de Fin"));
    this->setHeaderData(5, Qt::Horizontal, tr("Status"));

    dbAccess->close();
}

QString CongeModel::getConnection()
{
    return dbAccess->database().connectionName();
}

CongeModel::~CongeModel()
{
    qDebug() << "CongeModel Object has been deleted!";
}
