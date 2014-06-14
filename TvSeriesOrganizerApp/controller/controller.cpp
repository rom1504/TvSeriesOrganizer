#include <QQmlContext>
#include <QDebug>
#include <QQuickItem>
#include <QQmlEngine>
#include <QDir>
#include <QtQml>
#include <QNetworkAccessManager>

#include "model/qqmlnetworkaccessmanagerfactorywithcache.h"
#include "controller.h"
#include "model/serieslistlist.h"
#include "model/plugin.h"
#include "model/signallist.h"
#include "model/settings.h"
#include "adapter/signallistadapter.h"

#define TheTvDBAPIKey "CDD6BACEDE53AF9F"
#define TraktTvAPIKey "f9201fd7c6183a624a27ccba01555310"

QString Controller::cachePath;
QString Controller::dataPath;

Controller::Controller(QString datadir, QString size, bool maximize, QObject *parent) :
    QObject(parent)
{

    qRegisterMetaType<Image*>("Image");
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

    Series::dataPath=Controller::dataPath;

    QQmlNetworkAccessManagerFactoryWithCache * factory=new QQmlNetworkAccessManagerFactoryWithCache(cachePath);
    mViewer.engine()->setNetworkAccessManagerFactory(factory);
    QQmlContext *ctxt = mViewer.rootContext();
#if defined(Q_OS_ANDROID)
    mViewer.showExpanded();
    ctxt->setContextProperty("awidth",mViewer.width());
    ctxt->setContextProperty("aheight",mViewer.height());
#else
    QStringList cSize=size.split("x");
    ctxt->setContextProperty("awidth",cSize[0].toInt());
    ctxt->setContextProperty("aheight",cSize[1].toInt());
    if(maximize)
    {
        QTimer * maximizeTimer=new QTimer();
        maximizeTimer->setInterval(0);
        maximizeTimer->setSingleShot(true);
        connect(maximizeTimer,&QTimer::timeout,[this](){mViewer.showMaximized();});
        maximizeTimer->start();
    }
#endif



    SignalList<Plugin*> * pluginList=new SignalList<Plugin*>();
    QDir pluginDir(QCoreApplication::applicationDirPath()+"/plugin/");
    for(QFileInfo fileInfo : pluginDir.entryInfoList(QDir::Files))
    {
        QPluginLoader loader(fileInfo.absoluteFilePath());
        QObject *plugin = loader.instance();
        if(plugin)
        {
            AbstractPlugin * plug = qobject_cast<AbstractPlugin *>(plugin);
            Plugin * plug2=new Plugin(plug,this);
            pluginList->append(plug2);
        }
    }

    ctxt->setContextProperty("noPlugin",pluginList->size()==0);
    ctxt->setContextProperty("pluginModel",new SignalListAdapter<Plugin*>(pluginList,"plugin"));

    QNetworkAccessManager * networkAccessManager=new QNetworkAccessManager(this);

    DiskCache * diskCache=new DiskCache(networkAccessManager,this);

    TheTvDBAPI * theTvDBAPI=new TheTvDBAPI(Controller::cachePath,"http://thetvdb.com",TheTvDBAPIKey,networkAccessManager,diskCache,this);
    theTvDBAPI->updateCache([this,theTvDBAPI,ctxt,maximize,diskCache]()
    {
        mSeriesList=new SeriesList(theTvDBAPI,nullptr,this);
        mSeriesList->loadSeries(Controller::dataPath+"/myseries.txt");


        ctxt->setContextProperty("seriesList", mSeriesList);


        TraktTvAPI* traktTvAPI = new TraktTvAPI(Controller::cachePath,mSeriesList,"http://api.trakt.tv",TraktTvAPIKey,theTvDBAPI,diskCache,this);

        SeriesListList * seriesListList=new SeriesListList(traktTvAPI,this);

        ctxt->setContextProperty("seriesListList", seriesListList);

        Settings::declareSettingsQml();
        Settings * settings=new Settings(dataPath,this);

        ctxt->setContextProperty("settings", settings);

        mViewer.setSource(QUrl("qrc:/view/MainView.qml"));


    #if !defined(Q_OS_ANDROID)
       if(!maximize) mViewer.showExpanded();
    #endif
        //qDebug()<<mViewer.size();
        //mViewer.setMaximumSize(mViewer.size());
        //mViewer.setMinimumSize(mViewer.size()-QSize(10,10));
    });
}

void Controller::run()
{

}
