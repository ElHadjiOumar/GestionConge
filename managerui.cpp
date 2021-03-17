#include "managerui.h"
#include "ui_managerui.h"

ManagerUI::ManagerUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerUI)
{
    ui->setupUi(this);
}

ManagerUI::~ManagerUI()
{
    delete ui;
}
