#include "profilui.h"
#include "ui_profilui.h"

#include <QDebug>

ProfilUI::ProfilUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProfilUI)
{
    ui->setupUi(this);
}

ProfilUI::ProfilUI(User *user ,QObject *controller) : ui(new Ui::ProfilUI)
{
    ui->setupUi(this);

    saisirCoordonnes(user);
    qDebug() << "ProfilUI Object is created. l'id est " << user->getNom();
}

void ProfilUI::saisirCoordonnes(User *employe)
{
    ui->label_Nom->setText(employe->getNom());
    ui->label_Prenom->setText(employe->getPrenom());
    ui->dateEdit->setDate(employe->getDate_naiss());
    ui->label_Adresse->setText(employe->getAddresse());
    ui->label_Mail->setText(employe->getMail());
    ui->spinBox->setValue(employe->getNbre_conge());


}


ProfilUI::~ProfilUI()
{
    delete ui;
}
