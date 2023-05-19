#include "intro.h"
//#include <QWebEngineSettings>
//#include <QtWebEngineWidgets>

#include <QApplication>

int main(int argc, char *argv[])
{
    //QCoreApplication::setOrganizationName("QtExamples");
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication a(argc, argv);
    //QApplication app(argc, argv);
    intro w;
    w.show();
    return a.exec();
}
