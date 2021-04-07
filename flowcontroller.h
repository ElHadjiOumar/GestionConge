#ifndef FLOWCONTROLLER_H
#define FLOWCONTROLLER_H

#include <QObject>
#include "adminui.h"
#include "employeui.h"
#include "managerui.h"
#include "profilui.h"
#include "authentification.h"
#include "directeurrh.h"


class FlowController : public QObject
{
    Q_OBJECT


private:
    Authentification *authentification;
    AdminUI *adminUI;
    EmployeUI *employeUI;
    ManagerUI *managerUI;
    DirecteurRH *directeurRH;
    ProfilUI *profileUI;
    QString connection;

private slots:
    void onAuthentificationSubmit();
    void onSubmitEmployeClicked();
    void onProfilClicked();
    void onUIEmployeCancel();
    void onUIAdminCancel();
    void onUIManagerCancel();



public:
    void exec();

    FlowController();
    ~FlowController();
};

#endif // FLOWCONTROLLER_H
