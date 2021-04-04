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
    void updateNonLU(Conge conge);
    void updateLU(Conge conge);
    void copie(Conge conge);
    void removeNonLU(uint id);
    void removeLU(uint id);
    void removeMAX();
    QString countNonlu();
    QString countLu();
    void readAll();
    void readAllLu();
    void readCongeNonLU(User *user);
    void readCongeLU(User *user);
};

#endif // CONGEMODEL_H
