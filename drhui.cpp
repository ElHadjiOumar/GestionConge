#include "drhui.h"
#include "ui_drhui.h"

DrhUI::DrhUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DrhUI)
{
    ui->setupUi(this);
}

DrhUI::~DrhUI()
{
    delete ui;
}
