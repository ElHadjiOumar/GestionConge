
#include "flowcontroller.h"
#include "dbaccess.h"
#include <QDebug>

FlowController::FlowController() : authentification(nullptr) , adminUI (nullptr),employeUI(nullptr),managerUI(nullptr)
{
     connection = DBAccess::getInstance()->database().connectionName();
}

void FlowController::onAuthentificationSubmit()
{
    if (true == authentification->validate())
    {
        authentification->close();
        QString userType = authentification->getUser().getType();

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
    }

    DBAccess::release();
    QSqlDatabase::removeDatabase(connection);
}
