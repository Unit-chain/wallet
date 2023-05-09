#ifndef NO_MNEMONIC_PAGE_H
#define NO_MNEMONIC_PAGE_H

#include <QDialog>
#include <QClipboard>
#include <QShortcut>


#include <iostream>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/crypto.h>
#include <openssl/rand.h>
#include <sstream>


namespace Ui {
class no_mnemonic_page;
}

class no_mnemonic_page : public QDialog
{
    Q_OBJECT

public:
    explicit no_mnemonic_page(QWidget *parent = nullptr);
    ~no_mnemonic_page();


private slots:
  void on_push_button_generate_mnemonic_clicked();

  void on_push_button_home_clicked();

signals:
  void HomeClicked();

private:
    Ui::no_mnemonic_page *ui;
    void createMnemonicPhrase();
    QShortcut *keyEsc;
    void copy_mnemonic();
    void setUpUI();
    void setUpHotKeys();
};

#endif // NO_MNEMONIC_PAGE_H
