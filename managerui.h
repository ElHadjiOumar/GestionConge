#ifndef MANAGERUI_H
#define MANAGERUI_H

#include <QSqlTableModel>
#include <QMainWindow>
#include "dbaccess.h"

#include <QSqlQueryModel>
#include "authentification.h"
#include "dbaccess.h"
#include <user.h>
#include "congemodel.h"

namespace Ui {
class ManagerUI;
}

class ManagerUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerUI(QWidget *parent = nullptr);
     explicit ManagerUI(User *user,QObject *controller);

    bool closeConfirmation();
   /* void activateCreate();
    void activateUpdate();*/

    void validerCommande(User *user);

    ~ManagerUI();

private slots:
    //void onTableClicked(const QModelIndex &index);
    //void onRadioCreateClicked();
    //void onRadioUpdateClicked();
    //void onSubmitClicked();
    //void onDeleteClicked();
    //void onClearClicked();

private:
    Ui::ManagerUI *ui;
    CongeModel *model;
    Authentification *authentification;

    void setInformation();
    bool getInformations(Conge *conge);
    void setUpTableView();
    void populate(uint row);
    void updateConge(User *user);
    void clear();
    void selectFirstRow();
};

#endif // MANAGERUI_H
