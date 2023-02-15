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

    auto pathToStore = QString("Unit");
    auto rebornIni = QString("unitIni");

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


    std::string kDBPath = parameters.fileName().toStdString();
    kDBPath = kDBPath.substr(0, kDBPath.find_last_of("\\/"));
    kDBPath = kDBPath + "/db";
    std::cout << "kDBPath = " << kDBPath << std::endl;

      setUpDB(kDBPath);
      blockWriter = unit::BasicDB(kDBPath);
      std::shared_ptr<rocksdb::WriteBatch> txBatch = unit::BasicDB::getBatch();
      std::shared_ptr<rocksdb::WriteBatch> blockBatchPtr = DBWriter::getBatch();

      std::string quest = "Address";
      blockBatchPtr->Put(rocksdb::Slice(quest), rocksdb::Slice("baz"));
      blockWriter.commit(blockBatchPtr);

     std::cout << "waiting for response..." << std:: endl;
     std::string resp = blockWriter.get(quest); // not working
     std::cout << "resp = " << resp << std::endl;




   std::cout << "response = " << resp << std::endl;
   this->blockWriter.commit(blockBatchPtr); //  использвоать




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

void intro::setUpDB(std::string kDBPath)
{
    std::cout << "setUpDB\n" << std::endl;
    struct stat info;
    const char* pathName = kDBPath.c_str();
    if (stat(pathName, &info) != 0) {
        printf("cannot access %s\n", pathName);
    } else if (info.st_mode & S_IFDIR ) {
        printf("%s is a directory\n", pathName);
        return;
    } else {
        printf("%s is not a directory", pathName);
        return;
    }
    std::cout << "test" << std::endl;
        rocksdb::Options options;
        options.create_if_missing = false;
        options.error_if_exists = false;
        options.IncreaseParallelism(cpuss);
        options.OptimizeLevelStyleCompaction();
        options.bottommost_compression = rocksdb::kNoCompression;
        options.compression = rocksdb::kLZ4Compression;
        options.create_if_missing = true;
        options.create_missing_column_families = true;
        options.max_background_jobs = cpuss;
        options.env->SetBackgroundThreads(cpuss);
        options.num_levels = 2;
        options.merge_operator = nullptr;
        options.compaction_filter = nullptr;
        options.compaction_filter_factory = nullptr;
        options.rate_limiter = nullptr;
        options.max_open_files = -1;
        options.max_write_buffer_number = 6;
        options.max_background_flushes = cpuss;
        options.level0_stop_writes_trigger = -1;
        options.level0_slowdown_writes_trigger = -1;
        options.max_open_files = -1;

        rocksdb::Options balance_options;
        balance_options.create_if_missing = false;
        balance_options.error_if_exists = false;
        balance_options.IncreaseParallelism(cpuss);
        balance_options.OptimizeLevelStyleCompaction();
        balance_options.bottommost_compression = rocksdb::kNoCompression;
        balance_options.compression = rocksdb::kNoCompression;
        balance_options.create_if_missing = true;
        balance_options.create_missing_column_families = true;
        balance_options.max_background_jobs = cpuss;
        balance_options.env->SetBackgroundThreads(cpuss);
        balance_options.num_levels = 2;
        balance_options.merge_operator = nullptr;
        balance_options.compaction_filter = nullptr;
        balance_options.compaction_filter_factory = nullptr;
        balance_options.rate_limiter = nullptr;
        balance_options.max_open_files = -1;
        balance_options.max_write_buffer_number = 6;
        balance_options.max_background_flushes = cpuss;
        balance_options.level0_stop_writes_trigger = -1;
        balance_options.level0_slowdown_writes_trigger = -1;
        balance_options.max_open_files = 5000;
        balance_options.create_if_missing = true;
        balance_options.create_missing_column_families = true;

        rocksdb::DB* db;
        rocksdb::Status status = rocksdb::DB::Open(options, kDBPath, &db);
        std::cout << "status of rocksdb = " << status.ok() << std::endl;
        for (const auto & columnFamiliesName : columnFamiliesNames) { // creating column families
                rocksdb::ColumnFamilyHandle* cf;
                std::cout << "Creating column families: " << columnFamiliesName << std::endl;
                status = db->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), columnFamiliesName, &cf);
                db->DestroyColumnFamilyHandle(cf); // delete ptr
         }
        delete db;
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

