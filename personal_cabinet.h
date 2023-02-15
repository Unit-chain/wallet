#ifndef PERSONAL_CABINET_H
#define PERSONAL_CABINET_H

#include <QDialog>

#include <sstream>
#include <iostream>
#include <QTimer>
#include "qdebug.h"
#include <string>
#include <QTime>


namespace Ui {
class personal_cabinet;
}

class personal_cabinet : public QDialog
{
    Q_OBJECT

public:
    explicit personal_cabinet(QWidget *parent = nullptr);
    ~personal_cabinet();
     std::string m_balance;

    std::string getBalance() { return m_balance; }

signals:
    void balanceChanged(std::string newBalance);

private:
    Ui::personal_cabinet *ui;
    void updateBalanceLabel();

protected:
    void setBalance(std::string *balance);
};

#endif // PERSONAL_CABINET_H
