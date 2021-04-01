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
    query.prepare("INSERT INTO t_conge (employe_id, nbre_conge, date_debut,date_fin,status,motif) "
                    "VALUES (:employe_id, :nbre_conge, :date_debut, :date_fin, :status ,:motif)");
    query.bindValue(":nbre_conge", conge.getNbre_conge());
    query.bindValue(":employe_id", user.getNom());
    query.bindValue(":date_debut", conge.getDate_debut());
    query.bindValue(":date_fin", conge.getDate_fin());
    query.bindValue(":status", conge.getStatus());
    query.bindValue(":motif", conge.getMotif());

    query.exec();

    readConge(&user);

    qDebug () << "Le conge avec le nbre de conge =  " << conge.getNbre_conge() << "created successfully!";
    dbAccess->close();
}

void CongeModel::readAll()
{
    dbAccess->open();

    QSqlDatabase database = dbAccess->database();
    this->setQuery("SELECT id, employe_id, nbre_conge, date_debut,date_fin,status,motif FROM t_conge ", database);

    this->setHeaderData(0, Qt::Horizontal, tr("Id"));
    this->setHeaderData(1, Qt::Horizontal, tr("Employe_id"));
    this->setHeaderData(2, Qt::Horizontal, tr("Nbre_conge"));
    this->setHeaderData(3, Qt::Horizontal, tr("Date de Debut"));
    this->setHeaderData(4, Qt::Horizontal, tr("Date de Fin"));
    this->setHeaderData(5, Qt::Horizontal, tr("Status"));


    qDebug () << "Conges displayed successfully!";
    dbAccess->close();
}

void CongeModel::readConge(User *user)
{
    dbAccess->open();

     QSqlDatabase database = dbAccess->database();
    this->setQuery("SELECT id,employe_id, nbre_conge, date_debut,date_fin,status,motif FROM t_conge WHERE employe_id=\""+user->getNom()+"\"", database);


     this->setHeaderData(0, Qt::Horizontal, tr("Id"));
     this->setHeaderData(1, Qt::Horizontal, tr("Nom"));
     this->setHeaderData(2, Qt::Horizontal, tr("Nbre_conge"));
     this->setHeaderData(3, Qt::Horizontal, tr("Date de Debut"));
     this->setHeaderData(4, Qt::Horizontal, tr("Date de Fin"));
     this->setHeaderData(5, Qt::Horizontal, tr("Status"));


    qDebug () << "Conges displayed successfully!";
    dbAccess->close();
}


/*void CongeModel::update(Conge conge)
{
    dbAccess->open();

    QSqlQuery query(dbAccess->database());
    query.prepare("UPDATE t_users SET nom=:nom, prenom=:prenom, date_naiss=:date_naiss, addresse=:addresse,nbre_conges=:nbre_conges, mail=:mail,password=:password,type=:type WHERE id=:id");
    query.bindValue(":nom", user.getNom());
    query.bindValue(":prenom", user.getPrenom());
    query.bindValue(":date_naiss", user.getDate_naiss());
    query.bindValue(":addresse", user.getAddresse());
    query.bindValue(":mail", user.getMail());
    query.bindValue(":password", user.getPassword());
    query.bindValue(":nbre_conges", user.getNbre_conges());
    query.bindValue(":type", user.getType());
    query.bindValue(":id", user.getId());
    query.exec();

    readAll();

    qDebug () << "User" << user.getNom() << " updated successfully!" ;
    dbAccess->close();
}*/



void CongeModel::clear()
{
    dbAccess->open();

    QSqlDatabase database = dbAccess->database();
    this->setQuery("SELECT id, employe_id, nbre_conge, date_debut,date_fin,status,motif  FROM t_conge WHERE id=-1", database);

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
