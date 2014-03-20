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

    QGuiApplication::setApplicationName("TvSeriesOrganizer");
    QGuiApplication::setApplicationVersion("0.9.0");

    QString datadir="";

#if !defined(Q_OS_ANDROID)
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    //parser.addPositionalArgument("data-dir", QCoreApplication::translate("main", "Directory where data are saved"));
    QCommandLineOption dataDirectoryOption(QStringList() << "data-dir",QGuiApplication::translate("main", "Directory where data are saved"),QGuiApplication::translate("main", "directory"));
    parser.addOption(dataDirectoryOption);
    parser.process(app);

    datadir = parser.value(dataDirectoryOption);
#endif

    Controller c(datadir);
    c.run();

    return app.exec();
}
