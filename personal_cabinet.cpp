#include "personal_cabinet.h"
#include "ui_personal_cabinet.h"

personal_cabinet::personal_cabinet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::personal_cabinet)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);

    QObject::connect(timer, &QTimer::timeout,this,&personal_cabinet::updateBalanceLabel);

    timer->start(1000);
}

personal_cabinet::~personal_cabinet()
{
    delete ui;
}

void personal_cabinet::updateBalanceLabel()
{
    QTime timee = QTime::currentTime();
   std::stringstream ss;
   ss << "Hello ";
   ss << std::to_string(timee.second());
   ui->balanceLabel->setText(QString::fromStdString(ss.str()));
}

void personal_cabinet::setBalance(std::string *balance)
{
    qDebug("setBalance");
    m_balance = *balance;
}
