#ifndef EMPLOYEUI_H
#define EMPLOYEUI_H

#include <QSqlTableModel>
#include <QMainWindow>
#include "dbaccess.h"

#include <QSqlQueryModel>
#include "authentification.h"
#include "dbaccess.h"
#include <user.h>
#include "congemodel.h"

namespace Ui {
class EmployeUI;
}

class EmployeUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmployeUI(QWidget *parent = nullptr);

    explicit EmployeUI(User *user,QObject *controller);

    bool closeConfirmation();
   /* void activateCreate();
    void activateUpdate();*/
    ~EmployeUI();
    void validerCommande(User *user);

private slots:
    void onTableClicked(const QModelIndex &index);
    //void onRadioCreateClicked();
    //void onRadioUpdateClicked();
    //void onSubmitClicked();
    //void onDeleteClicked();
    void onClearClicked();
    //void onSearchClicked();

private:
    Ui::EmployeUI *ui;
    CongeModel *model;
    Authentification *authentification;



    void setInformation();
    bool getInformations(Conge *conge);
    void setUpTableView();
    void populate(uint row);
    void createConge(User *user);
    void updateConge();
    void clear();
    void selectFirstRow();
};

#endif // EMPLOYEUI_H
