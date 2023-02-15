#ifndef INTRO_H
#define INTRO_H

#include <QMainWindow>
#include <QPushButton>
#include <qstackedwidget.h>
#include "qsettings.h"
#include <QShortcut>
#include <QMessageBox>
#include "qdebug.h"

#include "no_mnemonic_page.h"

#include "./Unit/libdevcore/bip44/BIP44.hpp"
#include "./Unit/libdevcore/bip44/BIP39.hpp"
#include "./Unit/libdevcore/bip44/BIP32.hpp"
//#include "./Unit/libdevcore/db/DB.h"
//#include "rocksdb/db.h"




QT_BEGIN_NAMESPACE
namespace Ui { class intro; }
QT_END_NAMESPACE

class intro : public QMainWindow
{
    Q_OBJECT

public:
    intro(QWidget *parent = nullptr);
    ~intro();
    bool isValidMnemonic(std::string s);
    bool isValidPasphrase(std::string s);
  private slots:

    void handleButton();

    void moveHome();

    void on_pshButton_check_mnemonic_clicked();

    void on_pshButton_no_mnemonic_clicked();

    void slotShortcutCtrlw();

  private:
    Ui::intro *ui;
    QPushButton *m_button;
    QStackedWidget *stk;
    no_mnemonic_page mnemonic_page;
//    personalCabinet personal;
    QSettings settings;
    QShortcut *keyCtrlw ;

};
#endif // INTRO_H
