#include "directeurrh.h"
#include "ui_directeurrh.h"

DirecteurRH::DirecteurRH(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DirecteurRH)
{
    ui->setupUi(this);
}

DirecteurRH::~DirecteurRH()
{
    delete ui;
}
