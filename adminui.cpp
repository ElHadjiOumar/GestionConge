#include "adminui.h"
#include "ui_adminui.h"

#include <QDebug>
#include <QSqlRecord>
#include <QSqlField>
#include <QMessageBox>

AdminUI::AdminUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminUI)
{
    ui->setupUi(this);
}

AdminUI::AdminUI(QObject *controller) :
    ui(new Ui::AdminUI)
{
    ui->setupUi(this);
    this->setUpTableView();

    //connect(ui->pushButtonCancel, SIGNAL(clicked()), controller, SLOT(onUIAdminCancel()));
    connect(ui->pushButtonSubmit, SIGNAL(clicked()), this, SLOT(onSubmitClicked()));
    connect(ui->pushButtonDelete, SIGNAL(clicked()), this, SLOT(onDeleteClicked()));
    connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(onClearClicked()));
    connect(ui->pushButtonSearch, SIGNAL(clicked()), this, SLOT(onSearchClicked()));
    connect(ui->radioButtonCreate, SIGNAL(clicked()), this, SLOT(onRadioCreateClicked()));
    connect(ui->radioButtonUpdate, SIGNAL(clicked()), this, SLOT(onRadioUpdateClicked()));
    connect(ui->tableViewUsers, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));



    qDebug() << "AdminUI Object is created.";
}

void AdminUI::setUpTableView()
{
    model = new UserModel(DBAccess::getInstance());

    ui->tableViewUsers->setModel(model);
    //ui->tableViewUsers->hideColumn(4); // don't show the Password
    ui->tableViewUsers->show();

    selectFirstRow();
}

bool AdminUI::closeConfirmation()
{
    if (QMessageBox::Yes == QMessageBox::information(this, "Authentification",
                                 "Voulez-vous vraiment quitter ?", QMessageBox::Button::Yes, QMessageBox::Button::Cancel))
    {
        return true;
    }

    return false;
}

bool AdminUI::getUserInformations(User *user)
{
    QString matricule = ui->lineEditMatricule->text();
    QString nbre_conge = ui->lineEditConge->text();
    QString nom = ui->lineEditNom->text();
    QString prenom = ui->lineEditPrenom->text();
    QDate date_naiss = ui->dateEdit->date();
    QString addresse = ui->lineEditAdresse->text();
    QString login = ui->lineEditLogin->text();
    QString password = ui->lineEditPassword->text();

    if ( nbre_conge.isEmpty()||matricule.isEmpty()||nom.isEmpty() || prenom.isEmpty() || date_naiss.isNull() || addresse.isEmpty()  || login.isEmpty() || password.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Veuillez remplir tous les champs!");
        return false;
    }

    if (ui->radioButtonUpdate->isChecked()) // Update process ...
    {
        QString identifiant = ui->lineEditIdentifiant->text();
        if (identifiant.isEmpty())
        {
            QMessageBox::critical(this, "Error", "Veuillez sélectionner un utilisateur svp!");
            return false;
        }

        user->setId(identifiant.toUInt());
    }

    user->setNom(nom);
    user->setPrenom(prenom);
    user->setDate_naiss(date_naiss);
    user->setAdresse(addresse);
    user->setNbre_conge(nbre_conge);
    user->setMatricule(matricule);
    user->setMail(login);
    user->setPassword(password);

    if (ui->comboBox->currentText() == "Administrateur")
    {
        user->setType("administrateur");
    }
    else if(ui->comboBox->currentText() == "Manager")
    {
        user->setType("manager");
    }
    else if(ui->comboBox->currentText() == "Employe")
    {
        user->setType("employe");
    }
    else if(ui->comboBox->currentText() == "DRH")
    {
        user->setType("drh");
    }
    return true;
}

void AdminUI::createUser()
{
    User user;
    if (true == getUserInformations(&user))
    {
        model->create(user);
        clear();
    }
}

void AdminUI::onDeleteClicked()
{
    QString identifiant = ui->lineEditIdentifiant->text();
    if (identifiant.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Veuillez sélectionner un utilisateur!");
    }
    else
    {
        if (QMessageBox::Yes == QMessageBox::information(this, "Confirmation", "Voulez-vous vraiment supprimer cet utilisateur ?",
                                                         QMessageBox::Button::Yes, QMessageBox::Button::Cancel))
        {
            model->remove(identifiant.toUInt());
            selectFirstRow();
        }
    }
}

void AdminUI::selectFirstRow()
{
    if (model->rowCount() > 0)
    {
        populate(0);
        activateUpdate();
    }
    else
    {
        clear();
        activateCreate();
    }
}

void AdminUI::updateUser()
{
    User user;
    if (true == getUserInformations(&user))
    {
        model->update(user);
        clear();
    }
}

void AdminUI::onSubmitClicked()
{
    if (ui->radioButtonUpdate->isChecked())
    {
        updateUser();
    }
    else
    {
        createUser();
    }
}

void AdminUI::onRadioCreateClicked()
{
    clear();
    activateCreate();
}

void AdminUI::onRadioUpdateClicked()
{
    QString identifiant = ui->lineEditIdentifiant->text();
    if (identifiant.isEmpty())
    {
        activateCreate();
    }
}

void AdminUI::populate(uint row)
{
    QSqlRecord record = model->record(row);
    QSqlField field = record.field(0);

    ui->lineEditIdentifiant->setText(field.value().toString());
    ui->lineEditMatricule->setText(record.field(1).value().toString());
    ui->lineEditConge->setText(record.field(2).value().toString());
    ui->lineEditNom->setText(record.field(3).value().toString());
    ui->lineEditPrenom->setText(record.field(4).value().toString());
    ui->dateEdit->setDate(record.field(5).value().toDate());
    ui->lineEditAdresse->setText(record.field(6).value().toString());
    ui->lineEditLogin->setText(record.field(7).value().toString());
    ui->lineEditPassword->setText(record.field(8).value().toString());
}

void AdminUI::onTableClicked(const QModelIndex &index)
{
    if (index.isValid())
    {
        activateUpdate();
        populate(index.row());
    }
}

void AdminUI::onClearClicked()
{
    clear();
    model->clear();
}

void AdminUI::onSearchClicked()
{
    QString login = ui->lineEditSearch->text();
    if (login.isEmpty())
    {
        model->readAll();
        if (model->rowCount() <= 0)
        {
            QMessageBox::information(this, "Recherche", "Lsa liste des utilisateurs est vide!");
            activateCreate();
        }
        else
        {
            populate (0);
            activateUpdate();
        }
    }
    else if (model->readBy(login) == false)
    {
        QMessageBox::information(this, "Recherche", "Aucun utilisateur avec ce login n'a été trouvé!");
        return;
    }
}

void AdminUI::clear()
{

    ui->lineEditIdentifiant->clear();
    ui->lineEditNom->clear();
    ui->lineEditPrenom->clear();
    ui->dateEdit->clear();
    ui->lineEditAdresse->clear();
    ui->lineEditConge->clear();
    ui->lineEditMatricule->clear();
    ui->lineEditLogin->clear();
    ui->lineEditPassword->clear();
    ui->lineEditSearch->clear();

    activateCreate();
}

void AdminUI::activateCreate()
{
    ui->radioButtonCreate->setChecked(true);
    ui->pushButtonSubmit->setText("Create");
    ui->lineEditIdentifiant->setVisible(false);
    ui->labelId->setVisible(false);
}

void AdminUI::activateUpdate()
{
    ui->radioButtonUpdate->setChecked(true);
    ui->pushButtonSubmit->setText("Update");
    ui->lineEditIdentifiant->setVisible(true);
    ui->labelId->setVisible(true);
}

AdminUI::~AdminUI()
{
    delete ui;
    delete model;

    qDebug() << "AdminUI Object has been deleted!";
}
