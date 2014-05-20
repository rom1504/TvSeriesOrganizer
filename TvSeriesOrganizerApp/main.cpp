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
    QGuiApplication::setApplicationVersion("1.3.0");

    QString datadir="";
    QString size="";
    bool maximize=false;

#if !defined(Q_OS_ANDROID)
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption(QCommandLineOption("data-dir",QGuiApplication::translate("main", "Directory where data are saved"),QGuiApplication::translate("main", "directory")));
    parser.addOption(QCommandLineOption("size",QGuiApplication::translate("main", "Size of the application (default to 580x880)"),QGuiApplication::translate("main", "widthxheight"),"580x880"));
    parser.addOption(QCommandLineOption("maximize",QGuiApplication::translate("main", "Maximize the window")));
    parser.process(app);

    datadir=parser.value("data-dir");
    size=parser.value("size");
    maximize=parser.isSet("maximize");
#endif

    Controller c(datadir,size,maximize);
    c.run();

    return app.exec();
}
