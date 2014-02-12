#include <QQmlContext>
#include <QDebug>
#include <QQuickItem>
#include <QQmlEngine>
#include <QDir>

#include "controller.h"

#include "adapter/signallistadapter.h"

#include "model/qqmlnetworkaccessmanagerfactorywithcache.h"


QString Controller::cachePath;

Controller::Controller(QObject *parent) :
    QObject(parent)
{

#if defined(Q_OS_ANDROID)
    QDir current=QDir::current();
    current.cdUp();
    Controller::cachePath=current.absolutePath()+"/cache";
#else
    Controller::cachePath=QCoreApplication::applicationDirPath();
#endif
    Series * suits=new Series("suits");
    Season * season1=new Season(1,QUrl("qrc:/images/season.jpg"),QUrl());
    season1->addEpisode(new Episode(1,"First episode","First description",QUrl("qrc:/images/episode.jpg"),QDate::fromString("2014/02/12","yyyy/MM/dd")));
    season1->addEpisode(new Episode(2,"Second episode","Second description",QUrl("qrc:/images/episode.jpg"),QDate::fromString("2014/02/12","yyyy/MM/dd")));



    season1->addEpisode(new Episode(3,"Third episode","Third description",QUrl("qrc:/images/episode.jpg"),QDate::fromString("2014/02/12","yyyy/MM/dd")));
    season1->addEpisode(new Episode(4,"Fourth episode","Fourth description",QUrl("qrc:/images/episode.jpg"),QDate::fromString("2014/02/12","yyyy/MM/dd")));

    Series * series1=new Series("Series 1",QUrl("qrc:/images/series.jpg"));
    series1->addSeason(season1);

    mSeriesList=new SeriesList;
    mSeriesList->addSeries(series1);
    mSeriesList->addSeries(suits);
    mSeriesList->addSeries(new Series("breaking bad"));
    QQmlNetworkAccessManagerFactoryWithCache * factory=new QQmlNetworkAccessManagerFactoryWithCache();
    mViewer.engine()->setNetworkAccessManagerFactory(factory);

    showSeriesList();
}

void Controller::willShowSeriesList()
{
    mTimer.setSingleShot(1);
    mTimer.setInterval(1);
    connect(&mTimer,&QTimer::timeout,[this](){showSeriesList();});
    mTimer.start();
}

void Controller::showSeriesList()
{
    SignalListAdapter<Series*> * adapter=new SignalListAdapter<Series*>(mSeriesList->series(),"series");

    QQmlContext *ctxt = mViewer.rootContext();
    ctxt->setContextProperty("seriesList", adapter);
    mViewer.setSource(QUrl("qrc:/view/SeriesList.qml"));
    QObject *seriesDetails = mViewer.rootObject();
    connect(seriesDetails, SIGNAL(seriesClicked(const int)),this,SLOT(willShowSeriesDetails(const int)));
}


void Controller::willShowSeriesDetails(const int row)
{
    mTimer.setSingleShot(1);
    mTimer.setInterval(1);
    connect(&mTimer,&QTimer::timeout,[this,row](){showSeriesDetails(row);});
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
    connect(seriesDetails, SIGNAL(seasonClicked(const int)),this,SLOT(willShowSeasonDetails(const int)));
    connect(seriesDetails,SIGNAL(back()),this,SLOT(willShowSeriesList()));
}


void Controller::willShowSeasonDetails(const int row)
{
    mTimer.setSingleShot(1);
    mTimer.setInterval(1);
    connect(&mTimer,&QTimer::timeout,[this,row](){showSeasonDetails(row);});
    mTimer.start();
}

void Controller::showSeasonDetails(const int row)
{
    if(row!=-1) mCurrentSeason=mCurrentSeries->getSeason(row);
    SignalListAdapter<Episode*> * adapter= new SignalListAdapter<Episode*>(mCurrentSeason->episodes(),"episode");
    QQmlContext *ctxt = mViewer.rootContext();
    ctxt->setContextProperty("seasonModel", adapter);
    ctxt->setContextProperty("season", mCurrentSeason);
    mViewer.setSource(QUrl("qrc:/view/SeasonDetails.qml"));
    QObject *seasonDetails = mViewer.rootObject();
    connect(seasonDetails, SIGNAL(episodeClicked(const int)),this,SLOT(willShowEpisodeDetails(const int)));
    connect(seasonDetails,SIGNAL(back()),this,SLOT(willShowSeriesDetails()));
}

void Controller::willShowEpisodeDetails(const int row)
{
    mTimer.setSingleShot(1);
    mTimer.setInterval(1);
    connect(&mTimer,&QTimer::timeout,[this,row](){showEpisodeDetails(row);});
    mTimer.start();
}

void Controller::showEpisodeDetails(const int row)
{
    QQmlContext *ctxt = mViewer.rootContext();
    ctxt->setContextProperty("episode",mCurrentSeason->getEpisode(row));
    mViewer.setSource(QUrl("qrc:/view/EpisodeDetails.qml"));
    QObject *episodeDetails = mViewer.rootObject();
    connect(episodeDetails,SIGNAL(back()),this,SLOT(willShowSeasonDetails()));
}

void Controller::run()
{
    mViewer.showExpanded();
}
