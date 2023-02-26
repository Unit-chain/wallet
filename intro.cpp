#include "intro.h"
#include "./ui_intro.h"

intro::intro(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::intro) {
    ui->setupUi(this);


    // Setting up App Name
    QCoreApplication::setApplicationName("Unit");
    QGuiApplication::setApplicationDisplayName(QCoreApplication::applicationName());
    QCoreApplication::setOrganizationName("OOO Unit");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);



    auto pathToStore = QString("Unit");
    auto rebornIni = QString("unitIni");

    // Setting up Settings folder
    QSettings parameters(QSettings::IniFormat, QSettings::UserScope,
                         pathToStore, rebornIni);


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

    ui->setupUi(this);


    std::string kDBPath = parameters.fileName().toStdString();
    kDBPath = kDBPath.substr(0, kDBPath.find_last_of("\\/"));
    kDBPath = kDBPath + "/db";

    blockWriter = unit::BasicDB(kDBPath);
    std::shared_ptr<rocksdb::WriteBatch> txBatch = unit::BasicDB::getBatch();
    std::shared_ptr<rocksdb::WriteBatch> blockBatchPtr = DBWriter::getBatch();

    std::string quest = "Address";
    blockBatchPtr->Put(rocksdb::Slice(quest), rocksdb::Slice("baz"));
    blockWriter.commit(blockBatchPtr);

//    std::cout << "waiting for response..." << std::endl;
    std::string resp = blockWriter.get(quest); // not working
//    std::cout << "resp = " << resp << std::endl;


//    std::cout << "response = " << resp << std::endl;
    this->blockWriter.commit(blockBatchPtr); //  использвоать

    keyCtrlw = new QShortcut(this);
    keyCtrlw->setKey(Qt::CTRL + Qt::Key_W);

    ui->stackedWidget->insertWidget(1, &mnemonic_page);
    ui->stackedWidget->insertWidget(2, &personal);


//    QPixmap logo(LOGO_PATH);
//    ui->icon_label->setPixmap(logo);
//    ui->icon_label->setScaledContents(true);
//    ui->icon_label->setFixedSize(100,30);

//    QSvgWidget("/home/yourgod/Programming/qt/unit/Unit/icon/logo-07-cropped.svg", ui->icon_label);
    auto _parentWidget = ui->icon_widget;
    QSvgWidget *svgWidget = new QSvgWidget(_parentWidget);
    svgWidget->load(QString(LOGO_PATH));

    svgWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    svgWidget->setFixedSize(QSize(150,60));

    QVBoxLayout *layout = new QVBoxLayout(_parentWidget);
    layout->addWidget(svgWidget);
    _parentWidget->setLayout(layout);

    ui->line_edit_mnemonic->setPlaceholderText(QString("Insert Mnemonic Phrase"));
    ui->line_edit_password->setPlaceholderText(QString("Insert Password Phrase"));
    ui->pshButton_no_mnemonic->setText(QString("No Mnemonic?"));



    ui->pshButton_no_mnemonic->setFixedWidth(150);
//    pixmap.fill(Qt::transparent);

//    QPainter painter(&pixmap);
//    painter.setRenderHint(QPainter::Antialiasing, true);

//    auto r = svgRenderer.defaultSize();
//    QRect rect = painter.viewport();
//    auto size = ui->icon_label->size();
//    ui->icon_label->
//    painter.setViewport(rect.x(), rect.y(),size.width(), size.height());
//    QSize size = svgRenderer.size();

//    svgRenderer.setViewBox();


//    size(rect.size(), Qt::KeepAspectRatio);
//    painter.setViewport(rect.x(), rect.y(),r.width(), r.height());
//    painter.setWindow(svgRenderer.rect());
//    painter.drawImage(0, 0, svgRenderer);
//    svgRenderer.render(&painter);

//    ui->icon_label->setPixmap(pixmap);
//    auto a = ui->icon_label;

//    ui->icon_label->

//    QPixmap pic(LOGO_PATH);
//    QSvgGenerator generator;
//    generator.setFileName(LOGO_PATH);
//    QPainter painter;
//    painter.begin(&generator);
//    ui->icon_label->paint(painter);
//    painter.end();

//      QPixmap pic(LOGO_PATH);
//      pic.setDevicePixelRatio(this->devicePixelRatio());
//    int img_size = 150;
//    ui->icon_label->setPixmap(pic.scaled(img_size, img_size, Qt::KeepAspectRatio));


//    QString newPath = QFileDialog::getSaveFileName(this, tr("Save SVG"),
//            path, tr("SVG files (*.svg)"));

//        if (newPath.isEmpty())
//            return;

//        path = newPath;
            // Prepare a QImage with desired characteritisc
//            QImage image(500, 200, QImage::Format_ARGB32);

            // Get QPainter that paints to the image
//            QPainter painter(&image);
//            painter.begin(ui->icon_label);
//            renderer.render(&painter);
//        painter.end();

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


    connect(ui->pshButton_check_mnemonic, SIGNAL(clicked(bool)), this, SLOT(on_pshButton_check_mnemonic_clicked()));
    connect(ui->pshButton_no_mnemonic, SIGNAL(clicked(bool)), this, SLOT(on_pshButton_no_mnemonic_clicked()));
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

bool intro::isValidPasphrase(std::string s) {
    return !s.empty();
}

void intro::handleButton() {
    qDebug("I am alive");
}

void intro::moveHome() {
    ui->line_edit_mnemonic->clear();
    ui->line_edit_password->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

void intro::on_pshButton_check_mnemonic_clicked() {
    qDebug("ok, check mnemonic");

    std::string mnemonic = ui->line_edit_mnemonic->text().toStdString();
    std::string passphrase = ui->line_edit_password->text().toStdString();

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

void intro::on_pshButton_no_mnemonic_clicked() {
    qDebug("no mnemonic, create it");

    ui->stackedWidget->setCurrentIndex(1);
}

void intro::slotShortcutCtrlw() {
    this->close();
}
