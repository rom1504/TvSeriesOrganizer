#include <QtGui/QGuiApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include "controller/controller.h"

//#define LANG "fr_FR"
//#define LANG "en_US"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QString locale = QLocale::system().name();
    //locale=LANG;
    QLocale::setDefault(QLocale(locale));

    QTranslator qtTranslator;
    qtTranslator.load(":/translation/qt_" + locale);
    QGuiApplication::installTranslator(&qtTranslator);


    QTranslator translator;
    translator.load(QString(":/translations/TvSeriesOrganizer_") + locale);
    QGuiApplication::installTranslator(&translator);

    Controller c;
    c.run();

    return app.exec();
}
