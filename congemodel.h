#ifndef CONGEMODEL_H
#define CONGEMODEL_H

#include <QSqlQueryModel>

#include "dbaccess.h"
#include <conge.h>
#include <user.h>


class CongeModel : public QSqlQueryModel
{
private:
    DBAccess *dbAccess;
public:
    CongeModel(DBAccess *dbAccess);
    ~CongeModel();

    void clear();
    QString getConnection();

    // CRUD methods
    void create(User user,Conge conge);
    void update(Conge conge);
    //void remove(uint id);
    //bool readBy(QString employe_id);
    //bool readBy(QString mail, QString password, User *user);
    void readAll();
    void readConge(User *user);
};

#endif // CONGEMODEL_H
