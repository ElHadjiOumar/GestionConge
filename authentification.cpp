

#include "authentification.h"
#include "ui_authentification.h"
#include "usermodel.h"

#include <QDebug>
#include <QMessageBox>

Authentification::Authentification(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Authentification)
{
    ui->setupUi(this);
}


Authentification::Authentification(QObject * controller) :
    ui(new Ui::Authentification)
{
    ui->setupUi(this);
    connect(ui->pushButtonSubmit, SIGNAL(clicked()), controller, SLOT(onAuthentificationSubmit()));

    qDebug() << "Authentification Object is created.";
}
Authentification::~Authentification()
{
    delete ui;
    qDebug() << "Authentification Object has been deleted!";
}

bool Authentification::validate()
{
    QString connection;

    QString login = ui->userLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if(login.isEmpty() || password.isEmpty())
    {
        QMessageBox::critical(this, "Authentification",
                              "Veuillez renseignez tous les champs svp !");
        return false;
    }

    UserModel userModel(DBAccess::getInstance());
    User user;

    if (login.compare("admin") == 0 && password.compare("admin") == 0)
    {
        QMessageBox::information(this, "Authentification",
                                 "Welcome default admin !");
        return true;

    }
    else if (true == userModel.readBy(login, password, &user))
    {
        this->setUser(user);
        if (user.getType().compare("administrateur") == 0)
        {
            QMessageBox::information(this, "Authentification",
                                     "Welcome Administrateur : " + user.getNom() + " " + user.getPrenom() + " !");
        }
        else if (user.getType().compare("manager") == 0)
        {
            QMessageBox::information(this, "Authentification",
                                     "Welcome Manager : " + user.getNom() + " " + user.getPrenom() + " !");
        }
        else if (user.getType().compare("drh") == 0)
        {
            QMessageBox::information(this, "Authentification",
                                     "Welcome DRH : " + user.getNom() + " " + user.getPrenom() + " !");
        }
        else
        {
            QMessageBox::information(this, "Authentification",
                                     "Welcome Employe : " + user.getNom() + " " + user.getPrenom() +  " !");
        }
    }
    else
    {
        QMessageBox::critical(this, "Authentification",
                              "Incorrect Login/Password, please try again !");
        return false;
    }

    return true;
}

bool Authentification::closeConfirmation()
{
    if (QMessageBox::Yes == QMessageBox::information(this, "Authentification",
                                 "Voulez-vous vraiment quitter ?", QMessageBox::Button::Yes, QMessageBox::Button::Cancel))
    {
        return true;
    }

    return false;
}
