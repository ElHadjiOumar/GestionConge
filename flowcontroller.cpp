
#include "flowcontroller.h"
#include "dbaccess.h"
#include <QDebug>

FlowController::FlowController() : authentification(nullptr) , adminUI (nullptr),employeUI(nullptr)
{
     connection = DBAccess::getInstance()->database().connectionName();
}

void FlowController::onAuthentificationSubmit()
{
    if (true == authentification->validate())
    {
        authentification->close();
        QString userType = authentification->getUser().getType();
        QString matricule = authentification->getUser().getMatricule();

        //User user = authentification->getUser();
        User employe = authentification->getUser();

        if (userType.compare("administrateur")==0 ){
            adminUI = new AdminUI(this);
            adminUI->show();
        }
         if(userType.compare("employe")==0){
            employeUI = new EmployeUI(&employe ,this);

            employeUI->show();
        }
    }
}

void FlowController::onSubmitEmployeClicked()
{
    User employe = authentification->getUser();
    employeUI->validerCommande(&employe);


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
    }

    DBAccess::release();
    QSqlDatabase::removeDatabase(connection);
}
