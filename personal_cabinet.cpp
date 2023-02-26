#include "personal_cabinet.h"
#include "ui_personal_cabinet.h"

personal_cabinet::personal_cabinet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::personal_cabinet)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);


    ui->label_current_balance->setStyleSheet(
            "background-color: #373737;"
            "border: 1px solid #373737;"
            "border-radius: 5px;"
            "color: white;"
            "padding-left: 5%;"
            "font-size: 14px;"
            "height: 25%;"
    );


    ui->pshBtn_main_menu->setText(QString("Go back"));
    ui->pshBtn_main_menu->setStyleSheet(
                "color: white;"
                "border: 1px solid black;"
                );
    ui->label_balance->setStyleSheet(
                "color: white;");
    ui->label_send_to->setStyleSheet(
                "color: white;");
    ui->line_send_to->setPlaceholderText(QString("Search, public address (0x)"));

    QObject::connect(timer, &QTimer::timeout,this,&personal_cabinet::updateBalanceLabel);
    connect(ui->pshBtn_main_menu, SIGNAL(clicked()), this, SLOT(pshBtn_home_clicked()));

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
   ui->label_current_balance->setText(QString::fromStdString(ss.str()));
}

void personal_cabinet::setBalance(std::string *balance)
{
    qDebug("setBalance");
    m_balance = *balance;
}

void personal_cabinet::pshBtn_home_clicked() {
    emit HomeClicked();
//    ui->stackedWidget->setCurrentIndex(0);
}
