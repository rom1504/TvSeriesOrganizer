#include <QtGui/QGuiApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include "controller/controller.h"

//#define LANG "fr_FR"
//#define LANG "en_US"
//#define LANG "it_IT"
//#define LANG "zh"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QLocale locale=QLocale::system();
    //locale=QLocale(LANG);

    QTranslator translator;
    translator.load(locale,"TvSeriesOrganizer","_",":/translations/");
    QGuiApplication::installTranslator(&translator);

    QGuiApplication::setApplicationName("TvSeriesOrganizer");
    QGuiApplication::setApplicationVersion("1.2.0");

    QString datadir="";

#if !defined(Q_OS_ANDROID)
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption dataDirectoryOption(QStringList() << "data-dir",QGuiApplication::translate("main", "Directory where data are saved"),QGuiApplication::translate("main", "directory"));
    parser.addOption(dataDirectoryOption);
    parser.process(app);

    datadir = parser.value(dataDirectoryOption);
#endif

    Controller c(datadir);
    c.run();

    return app.exec();
}
