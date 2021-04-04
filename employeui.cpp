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
    this->setUpTableViewNonlu();
    modelLu->readCongeNonLU(user);

    this->setUpTableViewLu();
    modelNonlu->readCongeLU(user);


    //connect(ui->pushButtonCancel, SIGNAL(clicked()), controller, SLOT(onUIAdminCancel()));
    connect(ui->pushButtonProfil, SIGNAL(clicked()), controller, SLOT(onProfilClicked()));
    connect(ui->pushButtonSubmit, SIGNAL(clicked()), controller, SLOT(onSubmitEmployeClicked()));
    connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(onClearClicked()));
    connect(ui->tableViewUsers, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClickedNonlu(const QModelIndex &)));
    connect(ui->tableViewUsers_2, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClickedLu(const QModelIndex &)));




    qDebug() << "EmployeUI Object is created. l'id est " << user->getMatricule();
}

void EmployeUI::setUpTableViewNonlu()
{
    modelNonlu = new CongeModel(DBAccess::getInstance());

    ui->tableViewUsers->setModel(modelNonlu);
    ui->tableViewUsers->show();

    selectFirstRowNonlu();
}

void EmployeUI::setUpTableViewLu()
{
    modelLu = new CongeModel(DBAccess::getInstance());

    ui->tableViewUsers_2->setModel(modelLu);
    ui->tableViewUsers_2->show();

    selectFirstRowLu();
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
        modelNonlu->create(*user, conge);
        clear();
    }
}

void EmployeUI::selectFirstRowNonlu()
{
    if (modelNonlu->rowCount() > 0)
    {
        populateNonlu(0);
    }
    else
    {
        clear();
    }
}

void EmployeUI::selectFirstRowLu()
{
    if (modelLu->rowCount() > 0)
    {
        populateNonlu(0);
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


void EmployeUI::populateNonlu(uint row)
{
    QSqlRecord record = modelNonlu->record(row);
    QSqlField field = record.field(0);

    ui->dateEditDebut->setDate(record.field(3).value().toDate());
    ui->dateEditFin->setDate(record.field(4).value().toDate());
    ui->plainTextEdit->setPlainText(record.field(6).value().toString());
}

void EmployeUI::populateLu(uint row)
{
    QSqlRecord record = modelLu->record(row);
    QSqlField field = record.field(0);

    ui->dateEditDebutLu->setDate(record.field(3).value().toDate());
    ui->dateEditFinLu->setDate(record.field(4).value().toDate());
    ui->lineEditStatusLu->setText(record.field(5).value().toString());
    ui->plainTextEditLu->setPlainText(record.field(6).value().toString());
}

void EmployeUI::onTableClickedNonlu(const QModelIndex &index)
{
    if (index.isValid())
    {
        populateNonlu(index.row());
    }
}

void EmployeUI::onTableClickedLu(const QModelIndex &index)
{
    if (index.isValid())
    {
        populateLu(index.row());
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
    ui->plainTextEdit->clear();

}


EmployeUI::~EmployeUI()
{
    delete ui;
    delete modelLu;
    delete modelNonlu;

    qDebug() << "EmployeUI Object has been deleted!";
}

