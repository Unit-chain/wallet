#ifndef INTRO_H
#define INTRO_H

// System QT libs
#include <QMainWindow>
#include <QPushButton>
#include <qstackedwidget.h>
#include "qsettings.h"
#include <QShortcut>
#include <QMessageBox>
#include "qdebug.h"
#include <QImage>
#include <QSvgRenderer>
#include <QPainter>
#include <QRect>
#include <QSvgWidget>

// System libs
#include <sys/types.h>
#include <sys/stat.h>
#include <cmath>
#include <cryptopp/sha.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>

// Local qt libs
#include "no_mnemonic_page.h"
#include "personal_cabinet.h"

// Local libs
#include "./Unit/libdevcore/bip44/BIP44.hpp"
#include "./Unit/libdevcore/bip44/BIP39.hpp"
#include "./Unit/libdevcore/bip44/BIP32.hpp"
#include "./Unit/libdevcore/db/DB.h"
#include "./Unit/libdevcore/datastructures/concurrency/DBWriter.h"
#include "rocksdb/db.h"
#include "aes_256_GCM.h"
#include "cpuid.h"

using CryptoPP::byte;

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

    const int cpuss = (int) std::thread::hardware_concurrency();

    std::string get_N_width_string(std::string input_string, size_t string_size, int desired_width);

  private slots:


    void moveHome();

    void on_pshButton_check_mnemonic_clicked();

    void on_pshButton_no_mnemonic_clicked_();

    void slotShortcutCtrlw();

  private:
    Ui::intro *ui;
    QStackedWidget *stk;
    no_mnemonic_page mnemonic_page;
    personal_cabinet personal;
    QSettings settings;
    QShortcut *keyCtrlw;
    unit::BasicDB blockWriter;
    std::string path_db;
//    const std::vector<std::string> columnFamiliesNames = {"Address", "balance"};
    std::shared_ptr<rocksdb::WriteBatch>  blockBatchPtr;
    string aad = CPUID::vendor().c_str();
    string kDBPath;
    string mnemonic_cipher_name_in_DB = "mnemonic_cipher";
    string password_hash_3_256_name_in_DB = "password_hash";
    string iv_name_in_DB = "iv";
//    string password_key;   // For aes_256_gcm decode / encode as a key value


    CryptoPP::byte iv[12];
    int clickCounter = 0;

    void setUpUI();
    void setUpHotKeys();
    void setUpDB();
    void setUpLocalStorage();
};

std::string sha384(const string& input_string);

CryptoPP::byte* stringToByte(const std::string& input);

std::string byteToString(const CryptoPP::byte* bytes, size_t size);

#endif // INTRO_H
