#ifndef PERSONAL_CABINET_H
#define PERSONAL_CABINET_H

#include <QDialog>

#include <sstream>
#include <iostream>
#include <QTimer>
#include "qdebug.h"
#include <string>
#include <QTime>
#include <QWebEngineView>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/QWebEngineProfile>
#include <QtWebEngineWidgets/QWebEngineSettings>
#include <QFileDialog>

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

private:
    Ui::personal_cabinet *ui;
    void updateBalanceLabel();

private slots:
    void pshBtn_home_clicked();

signals:
    void HomeClicked();
    void balanceChanged(std::string newBalance);

protected:
    void setBalance(std::string *balance);
};

#endif // PERSONAL_CABINET_H
