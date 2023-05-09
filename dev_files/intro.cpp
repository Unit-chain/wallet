#include "intro.h"
#include "./ui_intro.h"


/*
 * Context:
 * fixing "rocksdb status is NOT OK, sleep while it become OK" with wrong KDBPath;
 */

intro::intro(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::intro) {
    ui->setupUi(this);


    // Setting up App Name QCoreApplication::setApplicationName("Unit");
    QGuiApplication::setApplicationDisplayName(QCoreApplication::applicationName());
    QCoreApplication::setOrganizationName("OOO Unit");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);



// key - Mnemonic; value - AES256 <mnemonic phrase>
// key - Password; value - sha3_256 <password phrase>
// key - transactions; value - { []<transaction> }
// key - user; value { <nonce>, ... }

    auto pathToStore = QString("Unit");
    auto rebornIni = QString("unitIni");

    // Setting up Settings folder
    QSettings parameters(QSettings::IniFormat, QSettings::UserScope,
                         pathToStore, rebornIni);


    aad = CPUID::vendor().c_str();
    const QString group = QString("Main parameters of Rocks DB");
    const QString key = QString("Path to Rocks DB");
    const QString value = QString("path");

    // Запись группа - ключ - значение
    parameters.beginGroup(group);
    parameters.setValue(key, value);
    parameters.endGroup();

    // Сохранение записи
    parameters.sync();

    parameters.beginGroup(group);
    QString fileValue = parameters.value(key).toString();
    parameters.endGroup();

    kDBPath = parameters.fileName().toStdString().substr(0, parameters.fileName().toStdString().find_last_of("\\/"))+"/db";

    qDebug() << kDBPath.c_str();
//    setUpLocalStorage();
//    setUpDB();
    blockWriter = unit::BasicDB(kDBPath); // путь к БД
    blockBatchPtr = DBWriter::getBatch(); // обертка над БД. аккумулятор.


    setUpHotKeys();

    this->resize(QSize(1920,1080));
    ui->stackedWidget->insertWidget(1, &mnemonic_page);
    ui->stackedWidget->insertWidget(2, &personal);

    auto _parentWidget = ui->icon_widget;
    QSvgWidget *svgWidget = new QSvgWidget(_parentWidget);
    svgWidget->load(QString(LOGO_PATH));

    svgWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    svgWidget->setFixedSize(QSize(150,60));

    QVBoxLayout *layout = new QVBoxLayout(_parentWidget);
    layout->addWidget(svgWidget);
    _parentWidget->setLayout(layout);

    ui->line_edit_mnemonic->setPlaceholderText(QString("Your mnemonic phrase"));
    ui->line_edit_password->setPlaceholderText(QString("Your password"));
    ui->pshButton_no_mnemonic->setText(QString("No mnemonic?"));



    ui->stackedWidget->setStyleSheet(
                "background-color: #171717 !important;");
    ui->pshButton_no_mnemonic->setFixedWidth(150);
    ui->pshButton_check_mnemonic->setStyleSheet(
            "background-color: #003dff;"
            "border: 1px solid #003dff;"
            "border-radius: 5px;"
            "color:white;"
    );
    ui->line_edit_mnemonic->setStyleSheet(
            "background-color: #373737;"
            "border: 1px solid #373737;"
            "border-radius: 5px;"
            "color: white;"
            "padding-left: 5%;"
            "font-size: 14px;"
            "height: 25%;"
    );

    ui->line_edit_password->setStyleSheet(
            "background-color: #373737;"
            "border: 1px solid #373737;"
            "border-radius: 5px;"
            "color: white;"
            "padding-left: 5%;"
            "font-size: 14px;"
    );
    ui->pshButton_no_mnemonic->setStyleSheet(
            "background-color: rgba(255,255,255,0);"
            "color: #003dff;"
            "font:inherit;"
    );


    connect(ui->pshButton_check_mnemonic, SIGNAL(clicked()), this, SLOT(on_pshButton_check_mnemonic_clicked_()));
    connect(ui->pshButton_no_mnemonic, SIGNAL(clicked(bool)), this, SLOT(on_pshButton_no_mnemonic_clicked_()));
    connect(&mnemonic_page, SIGNAL(HomeClicked()), this, SLOT(moveHome()));
    connect(&personal, SIGNAL(HomeClicked()), this, SLOT(moveHome()));

    connect(keyCtrlw, SIGNAL(activated()), this, SLOT(slotShortcutCtrlw()));
}

intro::~intro() {
    delete ui;
}

bool intro::isValidMnemonic(std::string s) {
    return !s.empty();
}

void intro::setUpLocalStorage() {
//    auto pathToStore = QString("Unit");
//    auto rebornIni = QString("unitIni");

//    // Setting up Settings folder
//    QSettings parameters(QSettings::IniFormat, QSettings::UserScope,
//                         pathToStore, rebornIni);


//    aad = CPUID::vendor().c_str();
//    const QString group = QString("Main parameters of Rocks DB");
//    const QString key = QString("Path to Rocks DB");
//    const QString value = QString("path");

//    // Запись группа - ключ - значение
//    parameters.beginGroup(group);
//    parameters.setValue(key, value);
//    parameters.endGroup();

//    // Сохранение записи
//    parameters.sync();

//    parameters.beginGroup(group);
//    QString fileValue = parameters.value(key).toString();
//    parameters.endGroup();

//    kDBPath = parameters.fileName().toStdString();
//    kDBPath = kDBPath.substr(0, kDBPath.find_last_of("\\/"));
//    kDBPath += "/db";


}

void intro::setUpDB() {
    // DB initialization
//    printf("kDBPath = %s\n", kDBPath);
//    blockWriter = unit::BasicDB(kDBPath); // путь к БД
//    blockBatchPtr = DBWriter::getBatch(); // обертка над БД. аккумулятор.

}
//void intro::setUp() {}
void intro::setUpHotKeys() {
    keyCtrlw = new QShortcut(this);
    keyCtrlw->setKey(Qt::CTRL + Qt::Key_W);
}

void intro::setUpUI() {

//    this->resize(QSize(1920,1080));
//    ui->stackedWidget->insertWidget(1, &mnemonic_page);
//    ui->stackedWidget->insertWidget(2, &personal);

//    auto _parentWidget = ui->icon_widget;
//    QSvgWidget *svgWidget = new QSvgWidget(_parentWidget);
//    svgWidget->load(QString(LOGO_PATH));

//    svgWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//    svgWidget->setFixedSize(QSize(150,60));

//    QVBoxLayout *layout = new QVBoxLayout(_parentWidget);
//    layout->addWidget(svgWidget);
//    _parentWidget->setLayout(layout);

//    ui->line_edit_mnemonic->setPlaceholderText(QString("Your mnemonic phrase"));
//    ui->line_edit_password->setPlaceholderText(QString("Your password"));
//    ui->pshButton_no_mnemonic->setText(QString("No mnemonic?"));



//    ui->pshButton_no_mnemonic->setFixedWidth(150);
//    ui->pshButton_check_mnemonic->setStyleSheet(
//            "background-color: #003dff;"
//            "border: 1px solid #003dff;"
//            "border-radius: 5px;"
//            "color:white;"
//    );
//    ui->line_edit_mnemonic->setStyleSheet(
//            "background-color: #373737;"
//            "border: 1px solid #373737;"
//            "border-radius: 5px;"
//            "color: white;"
//            "padding-left: 5%;"
//            "font-size: 14px;"
//            "height: 25%;"
//    );

//    ui->line_edit_password->setStyleSheet(
//            "background-color: #373737;"
//            "border: 1px solid #373737;"
//            "border-radius: 5px;"
//            "color: white;"
//            "padding-left: 5%;"
//            "font-size: 14px;"
//    );
//    ui->pshButton_no_mnemonic->setStyleSheet(
//            "background-color: rgba(255,255,255,0);"
//            "color: #003dff;"
//            "font:inherit;"
//    );



}

bool intro::isValidPasphrase(std::string s) {
    return !s.empty();
}


void intro::moveHome() {
    ui->line_edit_mnemonic->clear();
    ui->line_edit_password->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

void intro::on_pshButton_check_mnemonic_clicked_() {
    bool flagToShowNextPage = false;

    cout << "check clicked\n";
    // Get mnemonic and password from user
    std::string mnemonic = ui->line_edit_mnemonic->text().toStdString();
    std::string password = ui->line_edit_password->text().toStdString();
    if (!isValidMnemonic(mnemonic) || !isValidPasphrase(password)) {
    // If user pass and mnemonic does not exist -> create them
    // Check if mnemonic and password are of required length and strongivity

        cout << "not valid\n";
        qDebug("you have to type in eiher password or mnemonic");
        // TODO: show required input data properties

        return;
        }

        string _password_key = password;

        string password_key = get_N_width_string(_password_key, _password_key.length(), 32);

        cout << "password_key = " << password_key << "\n";
        //PTX.length
        int plaintext_length = mnemonic.length();
        // PSSW.length
        int password_key_length = password_key.length();

        // AAD
        string iv_str = password_key;

        CryptoPP::SHA256 some_hash;
        CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
        some_hash.Update((const CryptoPP::byte*)iv_str.data(), iv_str.size());
        some_hash.Final(digest);

        // IV
        memcpy(iv, digest, sizeof(iv));




    // Check if a user already has wallet
    string resp_pass;
    string resp_mnemonic;
    string resp_iv;

    // Get user pass and mnemonic if they exist
    try {
            resp_pass = blockWriter.getWithIO(password_hash_3_256_name_in_DB);
            resp_mnemonic = blockWriter.getWithIO(mnemonic_cipher_name_in_DB);
            resp_iv = blockWriter.getWithIO(iv_name_in_DB);
    } catch(unit::error::DBCorruption *e) {
        cout << "error with DB corruption: " << e << '\n';
    } catch (unit::error::DBIOError *e){
        cout << "error wirh IO in DB: " << e << '\n';
    } catch(...) {
        printf(" ///Exception with gettin pass and mnemonic\n\
/// It could either not exist, or DB did not start well\n\
/// Creating new DB with specified pass and mnemonic\n");
    }
    // TODO: show that either pass or mnemonic is wrong

   // If user pass and mnemonic exist already -> check them with input pass and mnemonic
    if (resp_pass == sha384(password_key) && aes_256_GCM::decode(resp_mnemonic, aad, stringToByte(password_key), password_key_length, iv, sizeof(iv)) == mnemonic) {
        cout << "resp == pass\n";
        flagToShowNextPage = true;
        } else if (resp_pass == "" && resp_pass == ""){

        cout << "resp and pass are empty\n";
        // Generate wallet from mnemonic and password
        BIP39Result bip39Result = BIP39Result(mnemonic, password);
        BIP44 bip44 = BIP44();
        BIP44Result bip44Result = bip44.generateAddress(bip39Result, 0, EXTERNAL_CHANGE, 0);

        // stone security primary moment celery escape lobster penalty enjoy lyrics save grass drama together youth enact cotton drink mammal lawsuit agent brass ecology raccoon
        // 01234567890123456789012345678901

        // Encoding mnemonic and password with aes-256 and sha384 respectively
         auto mnemonic_cipher = aes_256_GCM::encode(aad, mnemonic, stringToByte(password_key), password_key_length, iv, sizeof(iv));
         auto password_hash_3_256 = sha384(password_key);

         // Preparing mnemonic, password, iv to be put to db
         blockBatchPtr->Put(rocksdb::Slice(mnemonic_cipher_name_in_DB), rocksdb::Slice(mnemonic_cipher));
         blockBatchPtr->Put(rocksdb::Slice(password_hash_3_256_name_in_DB), rocksdb::Slice(password_hash_3_256));
         blockBatchPtr->Put(rocksdb::Slice(iv_name_in_DB), rocksdb::Slice(byteToString(iv, sizeof(iv))));

         // Commiting data to db
         blockWriter.commit(blockBatchPtr);

        // Let user to go to next page
         flagToShowNextPage = true;
        }

    // Show user next page
    if (flagToShowNextPage) {
            ui->stackedWidget->setCurrentIndex(2);
    }
}

void intro::on_pshButton_no_mnemonic_clicked_() {
    clickCounter++;
    qDebug() << "no mnemonic, create i, click count: " << clickCounter;
    ui->stackedWidget->setCurrentIndex(1);
}
// When user has no mnemonic, that button will be pushed
//void intro::on_pshButton_no_mnemonic_clicked() {
//    qDebug("no mnemonic, create it");

//    ui->stackedWidget->setCurrentIndex(1);
//}

// Close app with `ctrl + w` combination
void intro::slotShortcutCtrlw() {
    this->close();
}

std::string sha384(const string& input_string) {
    // Create a SHA-384 object
       CryptoPP::SHA384 hash;

       // Hash the input string
       std::string hashed_string;
       CryptoPP::StringSource(input_string, true,
           new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(
               new CryptoPP::StringSink(hashed_string))));

       // Return the hashed string
       return hashed_string;
}

// Converts typename string to typename CryptoPP::byte
CryptoPP::byte* stringToByte(const std::string& input_loc) {
    auto input = to_hex(input_loc);
    static CryptoPP::HexDecoder decoder;
    static std::vector<CryptoPP::byte> output(input.size());

    decoder.Put((byte*)input.data(), input.size());
    decoder.MessageEnd();
    decoder.Get(output.data(), output.size());

    return output.data();
}

std::string byteToString(const CryptoPP::byte* bytes, size_t size) {
    std::ostringstream ss;
    ss << std::hex << std::setfill('0');
    for (size_t i = 0; i < size; i++) {
        ss << std::setw(2) << static_cast<int>(bytes[i]);
    }
    return ss.str();
}

std::string intro::get_N_width_string(std::string input_string, size_t string_size, int desired_width)
{
    // If input string is already at desired width, return it
    if (input_string.size() == desired_width)
        return input_string;

    // If input string is shorter than desired width, repeat it
    if (input_string.size() < desired_width)
    {
        std::string output_string; // Create output string

        // Calculate output size
        float output_size_f = desired_width / input_string.size();
        int output_size_i = std::round(output_size_f);

        output_string.reserve(input_string.size()*output_size_i);

        std::copy_n(input_string.begin(), input_string.size(), std::back_inserter(output_string)); // Copy input to output
        int input_size = input_string.size();
        for (int i = 0; i < output_size_i; i++) {    // Append to output to desired_width
            std::copy_n(input_string.begin(), input_size, std::back_inserter(output_string));
        }
        output_string.resize(desired_width); // Resize to desired width
        return output_string;
    }

    // If input string is longer than desired width, crop it
    return input_string.substr(0, desired_width);
}
