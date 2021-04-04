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
    modelNonlu->readCongeNonLU(user);

    this->setUpTableViewLu();
    modelLu->readCongeLU(user->getMatricule());


    //connect(ui->pushButtonCancel, SIGNAL(clicked()), controller, SLOT(onUIAdminCancel()));

    connect(ui->pushButtonProfil, SIGNAL(clicked()), controller, SLOT(onProfilClicked()));
    connect(ui->pushButtonSubmit, SIGNAL(clicked()), controller, SLOT(onSubmitEmployeClicked()));
    connect(ui->pushButtonSupprimer, SIGNAL(clicked()), this, SLOT(onDeleteClicked()));
    connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(onClearClicked()));
    connect(ui->tableViewUsers, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClickedNonlu(const QModelIndex &)));
    connect(ui->tableViewUsers_2, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClickedLu(const QModelIndex &)));

    QString demandeNonlu = modelNonlu->countNonluConge(user);
    QString demandeLu = modelLu->countLuConge(user);

    QMessageBox::information(this, "Messages Non lu",
                             "Bienvenue  "+user->getPrenom()+" "+ user->getNom()+""
                            " Vous avez : " + demandeNonlu +" demande(s) de congé(s) non lus"
                            " et " +demandeLu+" nouvelle(s) reponse(s) venant du manager ");




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

bool EmployeUI::getInformations(Conge *conge,User *user)
{
    QDate date_debut = ui->dateEditDebut->date();
    QDate date_fin = ui->dateEditFin->date();
    QString motif = ui->plainTextEdit->toPlainText();

    if ( date_debut.isNull() || date_fin.isNull() || motif.isEmpty()  )
    {
        QMessageBox::critical(this, "Error", "Veuillez remplir tous les champs!");
        return false;
    }
    int solde = user->getNbre_conge();
    int ecart = (date_debut.daysTo(date_fin) );
    if(solde >= ecart ){
        conge->setNbre_conge(ecart);
        int resultat;
        resultat = solde - ecart ;
        qDebug() << "solde  " << solde ;
        qDebug() << "ecart  " << ecart ;
        qDebug() << "resultat  " << resultat ;
        //QString soldeStr = (QString)solde ;
        //qDebug() << "soldeSTR  " << soldeStr ;
        user->setNbre_conge(resultat);

    }
    else{
        QMessageBox::critical(this, "Error", "Votre solde de conge est inferieur au nombre de jour demandé , veillez soumettre une plus petite plage");
        return false;
    }

    conge->setDate_debut(date_debut);
    conge->setDate_fin(date_fin);
    conge->setMotif(motif);


    //qDebug() << "Nbre de jour  " << date_debut.daysTo(date_fin) ;
    return true;
}


void EmployeUI::createConge(User *user)
{
    Conge conge;
    if (true == getInformations(&conge,user))
    {
        modelNonlu->create(*user, conge);
        modelNonlu->updateConge(user);
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

    ui->lineEditId->setText(field.value().toString());
    ui->lineEditEmploye_id->setText(record.field(1).value().toString());
    ui->lineEditConge->setText(record.field(2).value().toString());
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


void EmployeUI::onDeleteClicked()
{
    QString identifiant = ui->lineEditId->text();
    QString matricule = ui->lineEditEmploye_id->text();
    if (identifiant.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Veuillez sélectionner un utilisateur!");
    }
    else
    {
        if (QMessageBox::Yes == QMessageBox::information(this, "Confirmation", "Voulez-vous vraiment supprimer cette reponse , cette action est irreversible  ?",
                                                         QMessageBox::Button::Yes, QMessageBox::Button::Cancel))
        {
            modelLu->removeLU(identifiant.toUInt(),matricule);
            selectFirstRowLu();
        }
    }
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

