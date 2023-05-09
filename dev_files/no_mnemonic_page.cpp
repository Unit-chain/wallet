#include "no_mnemonic_page.h"
#include "ui_no_mnemonic_page.h"


#include "./Unit/libdevcore/bip44/ecdsa.hpp"
#include "./Unit/libdevcore/bip44/ecdsa.cpp"
#include "./Unit/libdevcore/bip44/BIP44.hpp"



no_mnemonic_page::no_mnemonic_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::no_mnemonic_page)
{
    ui->setupUi(this);

    setUpHotKeys();
    setUpUI();

    connect(ui->pshBtnGenerateMnemonic, SIGNAL(clicked(bool)),this,SLOT(on_push_button_generate_mnemonic_clicked()));
    connect(ui->pshBtnMainMenu, SIGNAL(clicked(bool)),this,SLOT(on_push_button_home_clicked()));
}



void no_mnemonic_page::copy_mnemonic() {
    ui->mnemonic_text->selectAll();
    ui->mnemonic_text->copy();
}

void no_mnemonic_page::setUpHotKeys() {
     keyEsc = new QShortcut(this);
    keyEsc->setKey(Qt::Key_Escape);
    connect(keyEsc, SIGNAL(activated()), this, NULL);
}

void no_mnemonic_page::setUpUI() {

    ui->pshBtnMainMenu->setText(QString("Main menu"));
    ui->pshBtnGenerateMnemonic->setText("Generate phrase");
    ui->mnemonic_text->setReadOnly(true);
    ui->mnemonic_text->copyAvailable(true);
    ui->mnemonic_text->setFixedSize(QSize(600,300));
    ui->mnemonic_text->setStyleSheet(
            "background-color: #373737;"
            "border: 1px solid #373737;"
            "border-radius: 5px;"
            "color:white;"
    );
    ui->mnemonic_text->setPlaceholderText(QString("Your mnemonic phrase will be here"));
    ui->pshBtnGenerateMnemonic->setStyleSheet(
            "background-color: #003dff;"
            "border: 1px solid #003dff;"
            "border-radius: 5px;"
            "color:white;"
    );
    ui->pshBtnMainMenu->setStyleSheet(
            "background-color: #003dff;"
            "border: 1px solid #003dff;"
            "border-radius: 5px;"
            "color:white;"
    );
    ui->pshBtnGenerateMnemonic->setFixedSize(150,30);
    ui->pshBtnMainMenu->setFixedSize(150,30);


}

no_mnemonic_page::~no_mnemonic_page()
{
    delete ui;
}

void no_mnemonic_page::on_push_button_generate_mnemonic_clicked()
{
    createMnemonicPhrase();
    copy_mnemonic();
}

void no_mnemonic_page::on_push_button_home_clicked()
{
    emit HomeClicked();
    ui->mnemonic_text->clear();

}

void no_mnemonic_page::createMnemonicPhrase()
{

    BIP44 bip44;
    BIP44Result r = bip44.generateWallet(PHRASE_24, 0, EXTERNAL_CHANGE);
    std::cout << "WALLET PATH: " << r.path << std::endl;
    std::cout << "WALLET PHRASE: " << r.mnemonic.phrase << std::endl;
    std::cout << "WALLET SEED: " << r.mnemonic.seed << std::endl;
    std::cout << "WALLET PRV: " << r.prv << std::endl;
    std::cout << "WALLET PUB: " << r.pub << std::endl;
    std::cout << "WALLET E_PRV: " << r.extended_prv << std::endl;
    std::cout << "WALLET E_PUB: " << r.extended_pub << std::endl;
    std::cout << "WALLET ADDRESS: " << r.address << std::endl;

    std::cout << "\nSigning message 'Hello!': \n";
    ECDSASignResult sig = ecdsa_sign_message("Hello!", r.prv);
    std::cout << "r: " << sig.r << std::endl;
    std::cout << "s: " << sig.s << std::endl;
    std::cout << "signature hash: " << sig.message_hash << std::endl;
    bool verified = ecdsa_verify_signature(sig.r, sig.s, "Hello!", r.address);
    std::cout << "Result of verification: "<<verified<<"\n";
    BIP44Result r2 = bip44.generateAddress(r.mnemonic, 0, EXTERNAL_CHANGE, 1);
    std::cout << "\n\nWALLET PATH: " << r2.path << std::endl;
    std::cout << "WALLET [[learning/crypto/seed|SEED]]: " << r2.mnemonic.seed << std::endl;
    std::cout << "WALLET E_XPRV: " << r2.extended_prv << std::endl;
    std::cout << "WALLET E_XPUB: " << r2.extended_pub << std::endl;
    std::cout << "WALLET ADDRESS: " << r2.address << std::endl;

    std::cout << "\nSigning message 'Hello!': \n";
    ECDSASignResult sig2 = ecdsa_sign_message("Hello!", r2.prv);
    std::cout << "r: " << sig2.r << std::endl;
    std::cout << "s: " << sig2.s << std::endl;
    bool verified2 = ecdsa_verify_signature(sig2.r, sig2.s, "Hello!", r2.address);
    std::cout << "Result of verification: "<<verified2<<"\n";

    ui->mnemonic_text->setText(QString::fromStdString(r.mnemonic.phrase));

}
