#include "directeurrh.h"
#include "ui_directeurrh.h"

#include "user.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlField>
#include <QMessageBox>

#include <QSqlQuery>
#include <QStandardItemModel>
#include <QPainter>
#include <QtDebug>
#include <QVariant>
#include <QString>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QPrinter>
#include <QPrintDialog>

DirecteurRH::DirecteurRH(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DirecteurRH)
{
    ui->setupUi(this);
}

DirecteurRH::DirecteurRH(QObject *controller) : ui(new Ui::DirecteurRH)
{
    ui->setupUi(this);

    this->setUpTableView();
    modelUser->readAll();

    connect(ui->pushButtonPrint, SIGNAL(clicked()), controller, SLOT(onPrintClicked()));
    connect(ui->pushButtonExtract, SIGNAL(clicked()), this, SLOT(onExtractClicked()));

    connect(ui->pushButtonPrint_2, SIGNAL(clicked()), controller, SLOT(onPrintClickedConge()));
    connect(ui->pushButtonExtract_2, SIGNAL(clicked()), this, SLOT(onExtractClickedConge()));

    this->setUpTableViewConge();
    modelConge->readAllConge();

    qDebug() << "DRHUI Object is created ";
}

void DirecteurRH::setUpTableView()
{
    modelUser = new UserModel(DBAccess::getInstance());

    ui->tableViewUsers->setModel(modelUser);
    ui->tableViewUsers->show();

}

void DirecteurRH::setUpTableViewConge()
{
    modelConge = new UserModel(DBAccess::getInstance());

    ui->tableViewUsers_2->setModel(modelConge);
    ui->tableViewUsers_2->show();

}
void DirecteurRH::onExtractClicked()
{
    auto filename = QFileDialog::getSaveFileName(this,"Save", QDir::rootPath(), "CSV File (*.csv)");

        if(filename.isEmpty())
        {
            return;
        }
        QFile file(filename);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return;
        }
        QTextStream xout(&file);
        const int rowCount =  modelUser->rowCount();
        const int colCount =  modelUser->columnCount();
        for(int jx =0; jx< rowCount ; ++jx)
        {
            xout << modelUser->headerData(jx, Qt::Horizontal).toString() << ";" ;


            }
            xout<< "\n";

            for (int ix=0; ix < rowCount ; ix++)
            {
                xout << getValueAt(ix,0).toString();
                for(int jx = 1; jx < colCount ; jx++)
                {
                    xout << ";" << getValueAt(ix,jx).toString();
                }
                xout <<"\n" ;
        }
        file.flush();
        file.close();
}

QVariant DirecteurRH::getValueAt(int ix, int jx)
{
    QSqlRecord rec = modelUser->record(ix);
    QVariant valeur = rec.field(jx).value();
    if(valeur.isNull())
    {
        return "";
    }
    return valeur;
}

void DirecteurRH::onPrintClicked()
{
    QPrinter printer;
           printer.setPrinterName("Nom_Imprimante");

            QPrintDialog dialog(&printer, this);


            if(dialog.exec() == QDialog::Rejected) return;

            ui->tableViewUsers->render(&printer);
}
void DirecteurRH::onExtractClickedConge()
{
    auto filename = QFileDialog::getSaveFileName(this,"Save", QDir::rootPath(), "CSV File (*.csv)");

        if(filename.isEmpty())
        {
            return;
        }
        QFile file(filename);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return;
        }
        QTextStream xout(&file);
        const int rowCount =  modelConge->rowCount();
        const int colCount =  modelConge->columnCount();
        for(int jx =0; jx< rowCount ; ++jx)
        {
            xout << modelConge->headerData(jx, Qt::Horizontal).toString() << ";" ;


            }
            xout<< "\n";

            for (int ix=0; ix <= rowCount ; ix++)
            {
                xout << getValueAt(ix,0).toString();
                for(int jx = 1; jx < colCount ; jx++)
                {
                    xout << ";" << getValueAt(ix,jx).toString();
                }
                xout <<"\n" ;
        }
        file.flush();
        file.close();
}

void DirecteurRH::onPrintClickedConge()
{
    QPrinter printer;
           printer.setPrinterName("Nom_Imprimante");

            QPrintDialog dialog(&printer, this);


            if(dialog.exec() == QDialog::Rejected) return;

            ui->tableViewUsers->render(&printer);
}

DirecteurRH::~DirecteurRH()
{
    delete ui;
}
