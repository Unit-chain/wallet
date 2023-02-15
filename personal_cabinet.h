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

private:
    Ui::personal_cabinet *ui;
};

#endif // PERSONAL_CABINET_H
