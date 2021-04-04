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

    void validerCommande(User *user);
    ~EmployeUI();

private slots:
    void onTableClickedNonlu(const QModelIndex &index);
    void onTableClickedLu(const QModelIndex &index);
    void onClearClicked();

private:
    Ui::EmployeUI *ui;
    CongeModel *modelLu;
    CongeModel *modelNonlu;
    Authentification *authentification;



    void setInformation();
    bool getInformations(Conge *conge);
    void setUpTableViewLu();
    void setUpTableViewNonlu();
    void populateNonlu(uint row);
    void populateLu(uint row);
    void createConge(User *user);
    void updateConge();
    void clear();
    void selectFirstRowLu();
    void selectFirstRowNonlu();
};

#endif // EMPLOYEUI_H
