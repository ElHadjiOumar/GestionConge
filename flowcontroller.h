#ifndef FLOWCONTROLLER_H
#define FLOWCONTROLLER_H

#include <QObject>
#include "adminui.h"
#include "employeui.h"
#include "authentification.h"


class FlowController : public QObject
{
    Q_OBJECT


private:
    Authentification *authentification;
    AdminUI *adminUI;
    EmployeUI *employeUI;
    QString connection;

private slots:
    void onAuthentificationSubmit();


public:
    void exec();

    FlowController();
    ~FlowController();
};

#endif // FLOWCONTROLLER_H
