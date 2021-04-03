#include "employeui.h"
#include "ui_employeui.h"

#include <QDebug>
#include <QSqlRecord>
#include <QSqlField>
#include <QMessageBox>

EmployeUI::EmployeUI(QWidget *parent) : QMainWindow(parent),ui(new Ui::EmployeUI)
{
    ui->setupUi(this);
}
EmployeUI::EmployeUI(User *user ,QObject *controller) : ui(new Ui::EmployeUI)
{
    ui->setupUi(this);
    this->setUpTableView();


    //connect(ui->pushButtonCancel, SIGNAL(clicked()), controller, SLOT(onUIAdminCancel()));
    connect(ui->pushButtonProfil, SIGNAL(clicked()), controller, SLOT(onProfilClicked()));
    connect(ui->pushButtonSubmit, SIGNAL(clicked()), controller, SLOT(onSubmitEmployeClicked()));
    connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(onClearClicked()));
    connect(ui->tableViewUsers, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));

    //ui->lineEditId->setText(user.getMatricule());
    //user.setId(employe_id.toUInt());

    model->readConge(user);
    qDebug() << "EmployeUI Object is created. l'id est " << user->getMatricule();
}

void EmployeUI::setUpTableView()
{
    model = new CongeModel(DBAccess::getInstance());

    ui->tableViewUsers->setModel(model);
    //ui->tableViewUsers->hideColumn(4); // don't show the Password
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
    QDate date_debut = ui->dateEditDebut->date();
    QDate date_fin = ui->dateEditFin->date();
    QString status = ui->lineEditStatus->text();
    QString motif = ui->plainTextEdit->toPlainText();

    if ( date_debut.isNull() || date_fin.isNull() || motif.isEmpty()  )
    {
        QMessageBox::critical(this, "Error", "Veuillez remplir tous les champs!");
        return false;
    }

    conge->setNbre_conge(date_debut.daysTo(date_fin));
    conge->setDate_debut(date_debut);
    conge->setDate_fin(date_fin);
    conge->setMotif(motif);


    //qDebug() << "Nbre de jour  " << date_debut.daysTo(date_fin) ;
    return true;
}


void EmployeUI::createConge(User *user)
{
    Conge conge;
    if (true == getInformations(&conge))
    {
        model->create(*user, conge);
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

void EmployeUI::validerCommande(User *user)
{
        createConge(user);
        clear();
}


void EmployeUI::populate(uint row)
{
    QSqlRecord record = model->record(row);
    QSqlField field = record.field(0);

    ui->dateEditDebut->setDate(record.field(3).value().toDate());
    ui->dateEditFin->setDate(record.field(4).value().toDate());
    ui->lineEditStatus->setText(record.field(5).value().toString());
    ui->plainTextEdit->setPlainText(record.field(6).value().toString());
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
}


void EmployeUI::clear()
{

    ui->dateEditDebut->clear();
    ui->dateEditFin->clear();
    ui->lineEditStatus->clear();
    ui->plainTextEdit->clear();

}


EmployeUI::~EmployeUI()
{
    delete ui;

    qDebug() << "AdminUI Object has been deleted!";
}

