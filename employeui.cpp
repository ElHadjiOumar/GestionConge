#include "employeui.h"
#include "ui_employeui.h"

#include <QDebug>
#include <QSqlRecord>
#include <QSqlField>
#include <QMessageBox>

EmployeUI::EmployeUI(QWidget *parent) : QMainWindow(parent),ui(new Ui::EmployeUI),authentification(nullptr)
{
    ui->setupUi(this);
}
EmployeUI::EmployeUI(QObject *controller) : ui(new Ui::EmployeUI),authentification(nullptr)
{
    ui->setupUi(this);
    this->setUpTableView();

    //connect(ui->pushButtonCancel, SIGNAL(clicked()), controller, SLOT(onUIAdminCancel()));
    connect(ui->pushButtonSubmit, SIGNAL(clicked()), this, SLOT(onSubmitClicked()));
    connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(onClearClicked()));
    connect(ui->tableViewUsers, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));

    qDebug() << "AdminUI Object is created.";
}

void EmployeUI::setUpTableView()
{
    model = new CongeModel(DBAccess::getInstance());

    ui->tableViewUsers->setModel(model);
    ui->tableViewUsers->hideColumn(4); // don't show the Password
    ui->tableViewUsers->show();

    selectFirstRow();
}

bool EmployeUI::closeConfirmation()
{
    if (QMessageBox::Yes == QMessageBox::information(this, "Authentification",
                                 "Voulez-vous vraiment quitter ?", QMessageBox::Button::Yes, QMessageBox::Button::Cancel))
    {
        return true;
    }

    return false;
}

bool EmployeUI::getInformations(Conge *conge)
{

    QString employe_id = ui->lineEditEmploye->text();
    QString nbre_conge = ui->lineEditConge->text();
    QString date_debut = ui->lineEditDateDebut->text();
    QString date_fin = ui->lineEditDateFin->text();
    QString status = ui->lineEditStatus->text();

    if ( nbre_conge.isEmpty() ||date_debut.isEmpty() || date_fin.isEmpty()  )
    {
        QMessageBox::critical(this, "Error", "Veuillez remplir tous les champs!");
        return false;
    }
     employe_id = authentification->getUser().getId();
    ui->lineEditEmploye->setText(employe_id);


    /*if (ui->radioButtonUpdate->isChecked()) // Update process ...
    {
        QString identifiant = ui->lineEditIdentifiant->text();
        if (identifiant.isEmpty())
        {
            QMessageBox::critical(this, "Error", "Veuillez sélectionner un utilisateur svp!");
            return false;
        }

        user->setId(identifiant.toUInt());
    }*/
    conge->setEmploye_id(employe_id.toUInt());
    conge->setNbre_conge(nbre_conge.toUInt());
    conge->setDate_debut(date_debut);
    conge->setDate_fin(date_fin);

    return true;
}

void EmployeUI::createConge()
{
    Conge conge;
    if (true == getInformations(&conge))
    {
        model->create(conge);
        clear();
    }
}

void EmployeUI::selectFirstRow()
{
    if (model->rowCount() > 0)
    {
        populate(0);
    }
    else
    {
        clear();
    }
}

void EmployeUI::onSubmitClicked()
{
        createConge();
}


void EmployeUI::populate(uint row)
{
    QSqlRecord record = model->record(row);
    QSqlField field = record.field(0);

    ui->lineEditEmploye->setText(record.field(1).value().toString());
    ui->lineEditConge->setText(record.field(2).value().toString());
    ui->lineEditDateDebut->setText(record.field(3).value().toString());
    ui->lineEditDateFin->setText(record.field(4).value().toString());
    ui->lineEditStatus->setText(record.field(5).value().toString());
}

void EmployeUI::onTableClicked(const QModelIndex &index)
{
    if (index.isValid())
    {
        populate(index.row());
    }
}

void EmployeUI::onClearClicked()
{
    clear();
    model->clear();
}


void EmployeUI::clear()
{

    ui->lineEditEmploye->clear();
    ui->lineEditConge->clear();
    ui->lineEditDateDebut->clear();
    ui->lineEditDateFin->clear();
    ui->lineEditStatus->clear();

}


EmployeUI::~EmployeUI()
{
    delete ui;
    delete model;

    qDebug() << "AdminUI Object has been deleted!";
}

