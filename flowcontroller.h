#ifndef FLOWCONTROLLER_H
#define FLOWCONTROLLER_H

#include <QObject>
#include "adminui.h"
#include "employeui.h"
#include "managerui.h"
#include "drhui.h"
#include "authentification.h"


class FlowController : public QObject
{
    Q_OBJECT


private:
    Authentification *authentification;
    AdminUI *adminUI;
    EmployeUI *employeUI;
    ManagerUI *managerUI;
    DrhUI *drhUI;
    QString connection;

private slots:
    void onAuthentificationSubmit();
    void onSubmitEmployeClicked();



public:
    void exec();

    FlowController();
    ~FlowController();
};

#endif // FLOWCONTROLLER_H
