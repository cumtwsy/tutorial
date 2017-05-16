#include "utility.h"
#include "ui_utility.h"

Utility::Utility(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Utility)
{
    ui->setupUi(this);
}

Utility::~Utility()
{
    delete ui;
}
