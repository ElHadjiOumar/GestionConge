#ifndef USERMODEL_H
#define USERMODEL_H

#include <QSqlQueryModel>

#include "dbaccess.h"
#include <user.h>


class UserModel : public QSqlQueryModel
{
private:
    DBAccess *dbAccess;
public:
    UserModel(DBAccess *dbAccess);
    ~UserModel();

    void clear();
    QString getConnection();

    // CRUD methods
    void create(User user);
    void update(User user);
    void remove(uint id);
    bool readBy(QString nom);
    bool readBy(QString mail, QString password, User *user);
    void readAll();
};

#endif // USERMODEL_H
