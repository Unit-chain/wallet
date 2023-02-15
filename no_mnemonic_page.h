#ifndef NO_MNEMONIC_PAGE_H
#define NO_MNEMONIC_PAGE_H

#include <QDialog>



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
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

signals:
  void HomeClicked();

private:
    Ui::no_mnemonic_page *ui;
    std::string createMnemonicPhrase();
};

#endif // NO_MNEMONIC_PAGE_H
