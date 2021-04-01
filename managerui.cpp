#include "managerui.h"
#include "ui_managerui.h"

#include "user.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlField>
#include <QMessageBox>

ManagerUI::ManagerUI(QWidget *parent) :QMainWindow(parent),ui(new Ui::ManagerUI)
{
    ui->setupUi(this);
}

ManagerUI::ManagerUI(QObject *controller) : ui(new Ui::ManagerUI)
{
    ui->setupUi(this);
    this->setUpTableView();


    connect(ui->pushButtonSubmit, SIGNAL(clicked()), this, SLOT(onSubmitClicked()));
    connect(ui->tableViewUsers, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));

    model->readAll();
    qDebug() << "ManagerUI Object is created ";
}

void ManagerUI::setUpTableView()
{
    model = new CongeModel(DBAccess::getInstance());

    ui->tableViewUsers->setModel(model);
    //ui->tableViewUsers->hideColumn(4); // don't show the Password
    ui->tableViewUsers->show();

    selectFirstRow();
}

bool ManagerUI::getInformations(Conge *conge)
{
    QString employe_id =ui->lineEditEmploye->text();
    QString nbre_conge = ui->lineEditConge->text();
    QString date_debut = ui->lineEditDebut->text();
    QString date_fin = ui->lineEditFin->text();
    QString motif = ui->plainTextEdit->toPlainText();

    QString identifiant = ui->lineEditIdentifiant->text();
    if (identifiant.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Veuillez sélectionner un conge svp!");
        return false;
    }

    conge->setId(identifiant.toUInt());
    conge->setEmploye_id(employe_id);
    conge->setNbre_conge(nbre_conge.toUInt());
    conge->setDate_debut(date_debut);
    conge->setDate_fin(date_fin);


    if (ui->statusBox->currentText() == "Refusé")
    {
        conge->setStatus("refuse");
    }
    else if(ui->statusBox->currentText() == "Accepté")
    {
        conge->setStatus("accepte");
    }
    conge->setMotif(motif);

    return true;
}

bool ManagerUI::closeConfirmation()
{
    if (QMessageBox::Yes == QMessageBox::information(this, "Authentification",
                                 "Voulez-vous vraiment quitter ?", QMessageBox::Button::Yes, QMessageBox::Button::Cancel))
    {
        return true;
    }

    return false;
}


void ManagerUI::updateConge()
{
    Conge conge;
    if (true == getInformations(&conge))
    {
        model->update(conge);
    }
}

void ManagerUI::selectFirstRow()
{
    if (model->rowCount() > 0)
    {
        populate(0);
    }
    }

void ManagerUI::onSubmitClicked()
{
        updateConge();
}


void ManagerUI::populate(uint row)
{
    QSqlRecord record = model->record(row);
    QSqlField field = record.field(0);
    ui->lineEditIdentifiant->setText(field.value().toString());
    ui->lineEditEmploye->setText(record.field(1).value().toString());
    ui->lineEditConge->setText(record.field(2).value().toString());
    ui->lineEditDebut->setText(record.field(3).value().toString());
    ui->lineEditFin->setText(record.field(4).value().toString());
    ui->plainTextEdit->setPlainText(record.field(6).value().toString());
}

void ManagerUI::onTableClicked(const QModelIndex &index)
{
    if (index.isValid())
    {
        populate(index.row());
    }
}






ManagerUI::~ManagerUI()
{
    delete ui;
}
