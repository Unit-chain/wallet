#include "personal_cabinet.h"
#include "ui_personal_cabinet.h"

personal_cabinet::personal_cabinet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::personal_cabinet)
{
    ui->setupUi(this);
}

personal_cabinet::~personal_cabinet()
{
    delete ui;
}
