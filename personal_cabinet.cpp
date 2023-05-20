#include "personal_cabinet.h"
#include "ui_personal_cabinet.h"

personal_cabinet::personal_cabinet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::personal_cabinet)
{
    ui->setupUi(this);
//    for (int i = 0; i < 6; ++i)
//        ui->widget->addAction(QString("Action %1").arg(i),
//                              QIcon(QString(":/icons/icon%1").arg(i)));
    QTimer *timer = new QTimer(this);
// ui


        QString font_size_style = "font-size:14px;";
        QString color_text_white_style = "color:white;";
        QString color_text_white_minus1_style = "color:#78787A;";
        QString color_background = "background: #141414;";
        QString color_foreground = "background: #1C1D21;";
        QString color_buttons = "background: #BEB3FF;";
        QString color_graph = "background: #6A63A8;";
        QString menu_border_style = "border-radius: 5px;";
        QString menu_height_style = "height: 35%;";

        QString ui_debug_style = "color: red; font-size: 25px; font-family:roboto";

        QString menuStyle_group = font_size_style + color_text_white_style + color_foreground + menu_height_style + menu_border_style;
//        menuStyle_group = ui_debug_style;



        ui->accounts_pushButton->setStyleSheet(menuStyle_group);
        ui->accounts_pushButton_l->setStyleSheet(menuStyle_group);
        ui->explore_pushButton->setStyleSheet(menuStyle_group);
        ui->explore_pushButton_l->setStyleSheet(menuStyle_group);
        ui->birefcase_pushButton->setStyleSheet(menuStyle_group);
        ui->birefcase_pushButton_l->setStyleSheet(menuStyle_group);
        ui->market_pushButton->setStyleSheet(menuStyle_group);
        ui->market_pushButton_l->setStyleSheet(menuStyle_group);
        ui->settings_pushButton->setStyleSheet(menuStyle_group);
        ui->settings_pushButton_l->setStyleSheet(menuStyle_group);
        ui->receive_pushButton->setStyleSheet(menuStyle_group);
        ui->receive_pushButton_l->setStyleSheet(menuStyle_group);
        ui->selected_accounts_label->setStyleSheet(menuStyle_group);
        ui->selected_accounts_label_l->setStyleSheet(menuStyle_group);
        ui->trade_pushButton->setStyleSheet(menuStyle_group);
        ui->trade_pushButton_l->setStyleSheet(menuStyle_group);
        ui->send_pushButton->setStyleSheet(menuStyle_group);
        ui->send_pushButton_l->setStyleSheet(menuStyle_group);
        ui->menu_label->setStyleSheet(font_size_style + color_text_white_style);

        ui->widget_l->setStyleSheet(color_foreground);
        ui->widget->setStyleSheet(color_foreground);

        ui->line_send_to->setText(QString(""));
        ui->label_current_balance->setStyleSheet(
            "background-color: #373737;"
            "border: 1px solid #373737;"
            "border-radius: 5px;"
            "color: white;"
            "padding-left: 5%;"
            "font-size: 14px;"
            "height: 25%;"
        );


         ui->pshBtn_main_menu->setText(QString("Go back"));
         ui->pshBtn_main_menu->setStyleSheet(
            "background-color: #373737;"
            "border: 1px solid #373737;"
            "border-radius: 5px;"
            "color: white;"
            "font-size: 14px;"
            "height: 25%;"
               );
    ui->label_balance->setStyleSheet(
                "color: white;");
    ui->label_send_to->setStyleSheet(
                "color: white;");
    ui->line_send_to->setPlaceholderText(QString("Search, public address (0x)"));
//    ui->line_send_to->setTabOrder(ui->line_send_to, ui->pshBtn_send);

    ui->line_send_to->setStyleSheet(
            "background-color: #373737;"
            "border: 1px solid #373737;"
            "border-radius: 5px;"
            "color: white;"
            "font-size: 14px;"
            "height: 25%;"
   );
    ui->pshBtn_send->setStyleSheet(
            "background-color: #373737;"
            "border: 1px solid #373737;"
            "border-radius: 5px;"
            "color: white;"
            "font-size: 14px;"
            "height: 25%;"
    );



    QObject::connect(timer, &QTimer::timeout,this,&personal_cabinet::updateBalanceLabel);
    connect(ui->pshBtn_main_menu, SIGNAL(clicked()), this, SLOT(pshBtn_home_clicked()));

    QPushButton *button = new QPushButton("Добавить сайт");
    button->setStyleSheet(ui_debug_style);

    QWidget *buttonContainer = new QWidget();
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->addWidget(button);
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonContainer->setLayout(buttonLayout);



    // web engine
    QWebEngineView *webView = new QWebEngineView();

    webView->load(QUrl("https://in-space.ru/skyonline/"));

    QVBoxLayout *layout = new QVBoxLayout(ui->web_page);
    layout->addWidget(buttonContainer);  // Add the container widget, not the button
    layout->addWidget(webView);
    layout->setStretchFactor(webView, 1);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);


    QObject::connect(button, &QPushButton::clicked, [webView]() {
        QString fileName = QFileDialog::getOpenFileName(nullptr, "Выберите HTML-файл", QString(), "HTML-файлы (*.html)");
        if (!fileName.isEmpty()) {
            webView->load(QUrl::fromLocalFile(fileName));
        }
    });
    ui->web_page->show();





    timer->start(1000);
}

personal_cabinet::~personal_cabinet()
{
    delete ui;
}

void personal_cabinet::updateBalanceLabel()
{
    QTime timee = QTime::currentTime();
   std::stringstream ss;
   ss << "Hello ";
   ss << std::to_string(timee.second());
   ui->label_current_balance->setText(QString::fromStdString(ss.str()));
}

void personal_cabinet::setBalance(std::string *balance)
{
    qDebug("setBalance");
    m_balance = *balance;
}

void personal_cabinet::pshBtn_home_clicked() {
    emit HomeClicked();
//    ui->stackedWidget->setCurrentIndex(0);
}
