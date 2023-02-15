#include "intro.h"
#include "./ui_intro.h"

intro::intro(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::intro)
{
    ui->setupUi(this);
    // NOT implemented feature
    // AWARE: if true, you will have to exit the program in order to close running app
//    if (FRAME_LESS_WINDOW) setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::ToolTip);
    //

    auto pathToStore = QString("Reborn");
    auto rebornIni = QString("rebornIni");

    QSettings parameters(QSettings::IniFormat, QSettings::UserScope,
                             pathToStore, rebornIni);

        // Группа
        const QString group = QString("Main parameters of Rocks DB");
        const QString key = QString("Path to Rocks DB");
        const QString value = QString("path");

        // Запись группа - ключ - значение
        parameters.beginGroup(group);
        parameters.setValue(key, value);
        parameters.endGroup();

        // Сохранение записи
        parameters.sync();

        // вывод пути, по которому сохранен файл
        qDebug() << parameters.fileName();


        parameters.beginGroup(group);
        QString fileValue = parameters.value(key).toString();
        parameters.endGroup();

        // Вывод значения в консоль
        qDebug() << value << fileValue << (value == fileValue);

    ui->setupUi(this);
    keyCtrlw = new QShortcut(this);
    keyCtrlw->setKey(Qt::CTRL + Qt::Key_W);

    ui->stackedWidget->insertWidget(1, &mnemonic_page);
//    ui->stackedWidget->insertWidget(2, &personal);


    connect(ui->pshButton_no_mnemonic, SIGNAL(clicked(bool)), this, SLOT(on_pshButton_no_mnemonic_clicked()));
    connect(&mnemonic_page, SIGNAL(HomeClicked()), this, SLOT(moveHome()));
    connect(keyCtrlw, SIGNAL(activated()), this, SLOT(slotShortcutCtrlw()));
}

intro::~intro()
{
    delete ui;
}

bool intro::isValidMnemonic(std::string s)
{
    return !s.empty();
}

bool intro::isValidPasphrase(std::string s)
{
    return !s.empty();
}

void intro::handleButton()
{
    qDebug("I am alive");
}

void intro::moveHome()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void intro::on_pshButton_check_mnemonic_clicked()
{
    qDebug("ok, check mnemonic");
   std::string mnemonic = ui->line_edit_mnemonic->text().toStdString();
    std::string passphrase = ui->Line_edit_password->text().toStdString();
    if (!isValidMnemonic(mnemonic) || !isValidPasphrase(passphrase)) {
        qDebug("you have to type in");
    } else {
    BIP39Result bip39Result = BIP39Result(mnemonic, passphrase);
    BIP44 bip44 = BIP44();
    BIP44Result bip44Result = bip44.generateAddress(bip39Result, 0, EXTERNAL_CHANGE, 0);
    std::cout << "address = (" << bip44Result.address << ")" << std::endl;

    ui->stackedWidget->setCurrentIndex(2);
    }
}

void intro::on_pshButton_no_mnemonic_clicked()
{
    qDebug("no mnemonic, create it");

    ui->stackedWidget->setCurrentIndex(1);
}

void intro::slotShortcutCtrlw()
{
     this->close();
}

