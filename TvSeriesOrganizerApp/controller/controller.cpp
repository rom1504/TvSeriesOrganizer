#include <QQmlContext>
#include <QDebug>
#include <QQuickItem>
#include <QQmlEngine>
#include <QDir>
#include <QtQml>

#include "model/qqmlnetworkaccessmanagerfactorywithcache.h"
#include "controller.h"




QString Controller::cachePath;
QString Controller::dataPath;

Controller::Controller(QString datadir, QObject *parent) :
    QObject(parent)
{
    qmlRegisterInterface<QAbstractItemModel >("QAbstractItemModel");

#if defined(Q_OS_ANDROID)
    QDir current=QDir::current();
    current.cdUp();
    Controller::cachePath=current.absolutePath()+"/cache";
    Controller::dataPath=current.absolutePath()+"/files";
#else
    mViewer.setIcon(QIcon(":/images/icon512.png"));
    QString baseBase=datadir!="" ? datadir : QDir::homePath()+"/.TvSeriesOrganizer";
    Controller::cachePath=baseBase+"/cache";
    Controller::dataPath=baseBase+"/data";
    QDir dir;
    dir.mkpath(Controller::cachePath);
    dir.mkpath(Controller::dataPath);
#endif

    QQmlNetworkAccessManagerFactoryWithCache * factory=new QQmlNetworkAccessManagerFactoryWithCache();
    mViewer.engine()->setNetworkAccessManagerFactory(factory);
    QQmlContext *ctxt = mViewer.rootContext();
#if defined(Q_OS_ANDROID)
    mViewer.showExpanded();
    ctxt->setContextProperty("awidth",mViewer.width());
    ctxt->setContextProperty("aheight",mViewer.height());
#else
    ctxt->setContextProperty("awidth",580);
    ctxt->setContextProperty("aheight",880);
#endif

    mSeriesList=new SeriesList;
    mSeriesList->loadSeries(Controller::dataPath+"/myseries.txt");
    ctxt->setContextProperty("seriesList", mSeriesList);
    mViewer.setSource(QUrl("qrc:/view/MainView.qml"));

#if !defined(Q_OS_ANDROID)
    mViewer.showExpanded();
#endif

}

void Controller::run()
{

}
