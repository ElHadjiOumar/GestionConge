#include "usermodel.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>

UserModel::UserModel(DBAccess *dbAccess)
{
    this->dbAccess = dbAccess;
    clear();
}

void UserModel::create(User user)
{
    dbAccess->open();

    QSqlQuery query(dbAccess->database());
    query.prepare("INSERT INTO t_users (matricule,nom, prenom, date_naiss,addresse,mail,password, type) "
                    "VALUES (:matricule, :nom, :prenom, :date_naiss,:addresse,:mail,:password,:type)");
    query.bindValue(":matricule", user.getMatricule());
    query.bindValue(":nom", user.getNom());
    query.bindValue(":prenom", user.getPrenom());
    query.bindValue(":date_naiss", user.getDate_naiss());
    query.bindValue(":addresse", user.getAddresse());
    query.bindValue(":mail", user.getMail());
    query.bindValue(":password", user.getPassword());
    query.bindValue(":type", user.getType());

    query.exec();

    readAll();

    qDebug () << "User" << user.getNom() <<" matricule : "<< user.getMatricule()<< "created successfully!";
    dbAccess->close();
}

void UserModel::readAll()
{
    dbAccess->open();

    QSqlDatabase database = dbAccess->database();
    this->setQuery("SELECT id,matricule, nom, prenom, date_naiss,addresse,mail,password,type FROM t_users", database);

    this->setHeaderData(0, Qt::Horizontal, tr("Id"));
    this->setHeaderData(1, Qt::Horizontal, tr("Matricule"));
    this->setHeaderData(2, Qt::Horizontal, tr("Nom"));
    this->setHeaderData(3, Qt::Horizontal, tr("Prenom"));
    this->setHeaderData(4, Qt::Horizontal, tr("Date de Naissance"));
    this->setHeaderData(5, Qt::Horizontal, tr("Addresse"));
    this->setHeaderData(6, Qt::Horizontal, tr("Mail"));
    this->setHeaderData(7, Qt::Horizontal, tr("Password"));
    this->setHeaderData(8, Qt::Horizontal, tr("Type"));

    qDebug () << "Users displayed successfully!";
    dbAccess->close();
}

void UserModel::update(User user)
{
    dbAccess->open();

    QSqlQuery query(dbAccess->database());
    query.prepare("UPDATE t_users SET matricule=:matricule,nom=:nom, prenom=:prenom, date_naiss=:date_naiss, addresse=:addresse, mail=:mail,password=:password,type=:type WHERE id=:id");
    query.bindValue(":nom", user.getNom());
    query.bindValue(":matricule", user.getMatricule());
    query.bindValue(":nom", user.getNom());
    query.bindValue(":prenom", user.getPrenom());
    query.bindValue(":date_naiss", user.getDate_naiss());
    query.bindValue(":addresse", user.getAddresse());
    query.bindValue(":mail", user.getMail());
    query.bindValue(":password", user.getPassword());
    query.bindValue(":type", user.getType());
    query.bindValue(":id", user.getId());
    query.exec();

    readAll();

    qDebug () << "User" << user.getNom() << " updated successfully!" ;
    dbAccess->close();
}

void UserModel::remove(uint id)
{
    dbAccess->open();

    QSqlQuery query(dbAccess->database());
    query.prepare("DELETE FROM t_users WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();

    readAll();

    qDebug () << "User with id :" << id << " has been deleted successfully!" ;
    dbAccess->close();
}

bool UserModel::readBy(QString nom)
{
    dbAccess->open();

    QSqlQuery query(dbAccess->database());
    query.prepare("SELECT id AS Id,matricule AS Matricule nom AS Nom, prenom AS Prenom, date_naiss AS Date_naiss,addresse AS Addresse,mail AS Mail,password AS Password, type AS Type FROM t_users WHERE nom=:nom");
    query.bindValue(":nom", nom);
    query.exec();

    if (false == query.next()) // Aucun enregistrement trouvé
    {
        return false;
    }

    QSqlRecord record = query.record();
    this->setQuery(query);

    qDebug() << "Users with nom" << nom << "found.";
    dbAccess->close();

    return true;
}

bool UserModel::readBy(QString mail, QString password, User *user)
{
    dbAccess->open();

    QSqlQuery query(dbAccess->database());
    query.prepare("SELECT id,matricule, nom, prenom, date_naiss,addresse,mail,password,type FROM t_users WHERE mail=:mail AND password=:password");
    query.bindValue(":mail", mail);
    query.bindValue(":password", password);
    query.exec();

    if (false == query.next()) // Aucun enregistrement trouvé
    {
        return false;
    }

    QSqlRecord record = query.record();
    user->setNom(query.value(record.indexOf("nom")).toString());
    user->setPrenom(query.value(record.indexOf("prenom")).toString());
    user->setType(query.value(record.indexOf("type")).toString());

    qDebug() << "User with name" << user->getNom() << user->getPrenom() << "found.";
    dbAccess->close();

    return true;
}

void UserModel::clear()
{
    dbAccess->open();

    QSqlDatabase database = dbAccess->database();
    this->setQuery("SELECT id,matricule, nom, prenom, date_naiss,addresse,mail,password,type  FROM t_users WHERE id=-1", database);

    this->setHeaderData(0, Qt::Horizontal, tr("Id"));
    this->setHeaderData(1, Qt::Horizontal, tr("Matricule"));
    this->setHeaderData(2, Qt::Horizontal, tr("Nom"));
    this->setHeaderData(3, Qt::Horizontal, tr("Prenom"));
    this->setHeaderData(4, Qt::Horizontal, tr("Date de Naissance"));
    this->setHeaderData(5, Qt::Horizontal, tr("Addresse"));
    this->setHeaderData(6, Qt::Horizontal, tr("Mail"));
    this->setHeaderData(7, Qt::Horizontal, tr("Password"));
    this->setHeaderData(8, Qt::Horizontal, tr("Type"));


    dbAccess->close();
}

QString UserModel::getConnection()
{
    return dbAccess->database().connectionName();
}

UserModel::~UserModel()
{
    qDebug() << "UserModel Object has been deleted!";
}
