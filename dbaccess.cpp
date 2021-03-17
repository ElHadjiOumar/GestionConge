#include "dbaccess.h"
#include <QDebug>

// Here we define the static DBAccess pointer
DBAccess* DBAccess::instance = nullptr;

DBAccess* DBAccess::getInstance() {
   if (instance == nullptr) {
      instance = new DBAccess();
   }

   return instance;
}

void DBAccess::release() {
   if (instance != nullptr) {
      delete instance;
   }
}


DBAccess::DBAccess()
{
    /*
     * Créer une base de données SQLITE avec "DB browser for SQLite"
    */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("gestionconge.db");
    //db.setDatabaseName("C:/Users/HP 450 G5/Documents/MPSI/C++/QT/GestionProjet/build-GestionConge-Desktop_Qt_5_14_0_MinGW_32_bit-Debug/gestionconge.db");

    qDebug() << "DBAccess Object created and 'users.db' has been added as default database!";
}

bool DBAccess::open()
{
    if (db.isOpen()) return true;

    if (db.open())
    {
       qDebug() << "Connection opened with QSQLITE Database [OK]";
       return true;
    }
    else
    {
       qDebug() << "Connection failure with QSQLITE Database [KO]";
       return false;
    }
}

void DBAccess::close()
{
    if (!db.isOpen()) return;

    db.close();
    qDebug() << "Connection closed with QSQLITE Database [OK]";
}

DBAccess::~DBAccess()
{
    qDebug() << "DBAccess Object has been deleted !";
}
