#include "profilui.h"
#include "ui_profilui.h"

ProfilUI::ProfilUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProfilUI)
{
    ui->setupUi(this);
}

ProfilUI::~ProfilUI()
{
    delete ui;
}
