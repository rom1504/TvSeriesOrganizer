#include <QQmlContext>
#include <QDebug>
#include <QQuickItem>
#include <QQmlEngine>
#include <QDir>

#include "controller.h"

#include "adapter/signallistadapter.h"

#include "model/qqmlnetworkaccessmanagerfactorywithcache.h"


#include <QQmlEngine>

#include <QtQml>


QString Controller::cachePath;
QString Controller::filesPath;

Controller::Controller(bool demo, QObject *parent) :
    QObject(parent)
{
    qmlRegisterInterface<QAbstractItemModel >("QAbstractItemModel");

#if defined(Q_OS_ANDROID)
    QDir current=QDir::current();
    current.cdUp();
    Controller::cachePath=current.absolutePath()+"/cache";
    Controller::filesPath=current.absolutePath()+"/files";
#else
    Controller::cachePath=QCoreApplication::applicationDirPath();
    Controller::filesPath=QCoreApplication::applicationDirPath();
#endif

    QQmlNetworkAccessManagerFactoryWithCache * factory=new QQmlNetworkAccessManagerFactoryWithCache();
    mViewer.engine()->setNetworkAccessManagerFactory(factory);

    if(demo)
    {
        QFile file(Controller::filesPath+"/mydemoseries.txt");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream flux(&file);
        flux<<"suits\nbreaking bad\nthe big bang theory\n";
        file.close();
    }

    mSeriesList=new SeriesList;
    mSeriesList->loadSeries(demo ? Controller::filesPath+"/mydemoseries.txt" : Controller::filesPath+"/myseries.txt");
    showSeriesList();
}

void Controller::willShowSeriesList()
{
    mTimer.setSingleShot(1);
    mTimer.setInterval(1);
    disconnectConnections();
    mConnections<<connect(&mTimer,&QTimer::timeout,[this](){showSeriesList();});
    mTimer.start();
}

void Controller::showSeriesList()
{
    SignalListAdapter<Series*> * adapter=new SignalListAdapter<Series*>(mSeriesList->series(),"series");

    QQmlContext *ctxt = mViewer.rootContext();
    ctxt->setContextProperty("seriesList", adapter);
    mViewer.setSource(QUrl("qrc:/view/SeriesList.qml"));
    QObject *seriesDetails = mViewer.rootObject();
    disconnectConnections();
    mConnections<<connect(seriesDetails, SIGNAL(seriesClicked(const int)),this,SLOT(willShowSeriesDetails(const int)));
}


void Controller::willShowSeriesDetails(const int row)
{
    mTimer.setSingleShot(1);
    mTimer.setInterval(1);
    disconnectConnections();
    mConnections<<connect(&mTimer,&QTimer::timeout,[this,row](){showSeriesDetails(row);});
    mTimer.start();
}

void Controller::showSeriesDetails(const int row)
{
    if(row!=-1) mCurrentSeries=mSeriesList->getSeries(row);
    SignalListAdapter<Season*> * adapter=new SignalListAdapter<Season*>(mCurrentSeries->seasons(),"season");


    QQmlContext *ctxt = mViewer.rootContext();
    ctxt->setContextProperty("seriesModel", adapter);
    ctxt->setContextProperty("series", mCurrentSeries);
    mViewer.setSource(QUrl("qrc:/view/SeriesDetails.qml"));
    QObject *seriesDetails = mViewer.rootObject();
    disconnectConnections();
    mConnections<<connect(seriesDetails, SIGNAL(seasonClicked(const int)),this,SLOT(willShowSeasonDetails(const int)));
    mConnections<<connect(seriesDetails,SIGNAL(back()),this,SLOT(willShowSeriesList()));
}


void Controller::willShowSeasonDetails(const int row)
{
    mTimer.setSingleShot(1);
    mTimer.setInterval(1);
    disconnectConnections();
    mConnections<<connect(&mTimer,&QTimer::timeout,[this,row](){showSeasonDetails(row);});
    mTimer.start();
}

void Controller::showSeasonDetails(const int row)
{
    if(row!=-1)
    {
        mCurrentSeason=mCurrentSeries->getSeason(row);
        mCurrentSeasonRow=row;
    }
    SignalListAdapter<Episode*> * adapter= new SignalListAdapter<Episode*>(mCurrentSeason->episodes(),"episode");
    QQmlContext *ctxt = mViewer.rootContext();

    ctxt->setContextProperty("seasonModel", adapter);
    ctxt->setContextProperty("seasonIndex",mCurrentSeasonRow);
    ctxt->setContextProperty("season", mCurrentSeason);
    mViewer.setSource(QUrl("qrc:/view/SeasonDetails.qml"));
    QObject *seasonDetails = mViewer.rootObject();
    disconnectConnections();
    mConnections<<connect(seasonDetails, SIGNAL(episodeClicked(const int)),this,SLOT(willShowEpisodeDetails(const int)));
    mConnections<<connect(seasonDetails,SIGNAL(back()),this,SLOT(willShowSeriesDetails()));
    mConnections<<connect(seasonDetails,SIGNAL(seasonChanged(int)),this,SLOT(changeCurrentSeason(int)));
}

void Controller::changeCurrentSeason(int row)
{
    mCurrentSeason=mCurrentSeries->getSeason(row);
    mCurrentSeasonRow=row;
}

void Controller::disconnectConnections()
{
    for(auto connection : mConnections) disconnect(connection);
    mConnections.clear();
}

void Controller::willShowEpisodeDetails(const int row)
{
    mTimer.setSingleShot(1);
    mTimer.setInterval(1);
    disconnectConnections();
    mConnections<<connect(&mTimer,&QTimer::timeout,[this,row](){showEpisodeDetails(row);});
    mTimer.start();
}

void Controller::showEpisodeDetails(const int row)
{
    QQmlContext *ctxt = mViewer.rootContext();
    ctxt->setContextProperty("episode",mCurrentSeason->getEpisode(row));
    ctxt->setContextProperty("episodeIndex",row);
    mViewer.setSource(QUrl("qrc:/view/EpisodeDetails.qml"));
    QObject *episodeDetails = mViewer.rootObject();
    disconnectConnections();
    mConnections<<connect(episodeDetails,SIGNAL(back()),this,SLOT(willShowSeasonDetails()));
}

void Controller::run()
{
    mViewer.showExpanded();
}
