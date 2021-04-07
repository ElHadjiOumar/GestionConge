
#include "flowcontroller.h"
#include "dbaccess.h"
#include <QDebug>

FlowController::FlowController() : authentification(nullptr) , adminUI (nullptr),employeUI(nullptr),managerUI(nullptr),directeurRH(nullptr)
{
     connection = DBAccess::getInstance()->database().connectionName();
}

void FlowController::onAuthentificationSubmit()
{
    if (true == authentification->validate())
    {
        authentification->close();
        QString userType = authentification->getUser().getType();
        qDebug() << userType ;

        User user = authentification->getUser();

        if (userType.compare("administrateur")==0 ){
            adminUI = new AdminUI(this);
            adminUI->show();
        }
         else if(userType.compare("employe")==0){

            employeUI = new EmployeUI(&user ,this);
            employeUI->show();
        }else if(userType.compare("manager")==0){

            managerUI = new ManagerUI(this);
            managerUI->show();
        }else if(userType.compare("drh")==0){
            directeurRH = new DirecteurRH(this);
            directeurRH->show();
        }

    }
}

void FlowController::onSubmitEmployeClicked()
{
    User employe = authentification->getUser();
    employeUI->validerCommande(&employe);


}
void FlowController::onProfilClicked()
{
    User user = authentification->getUser();

    profileUI = new ProfilUI(&user ,this);
    profileUI->show();

}

void FlowController::onUIAdminCancel()
{
    if (adminUI->closeConfirmation() == true)
    {
        adminUI->close();
    }
}
void FlowController::onUIEmployeCancel()
{
    if (employeUI->closeConfirmation() == true)
    {
        employeUI->close();
    }
}
void FlowController::onUIManagerCancel()
{
    if (managerUI->closeConfirmation() == true)
    {
        managerUI->close();
    }
}

void FlowController::exec()
{
    authentification = new Authentification(this);
    authentification->show();
}

FlowController::~FlowController()
{
    if (authentification != nullptr)
    {
        delete authentification;
    }else if (employeUI != nullptr)
    {
        delete employeUI;
    }else if (managerUI != nullptr)
    {
        delete managerUI;
    }else if (directeurRH != nullptr)
    {
        delete directeurRH;
    }

    DBAccess::release();
    QSqlDatabase::removeDatabase(connection);
}
