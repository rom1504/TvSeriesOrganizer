#include <QQmlContext>
#include <QDebug>
#include <QQuickItem>

#include "controller.h"

#include "adapter/signallistadapter.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{

    Season * season1=new Season(1);
    season1->addEpisode(new Episode(1,"First episode","First description"));
    season1->addEpisode(new Episode(2,"Second episode","Second description"));
    season1->addEpisode(new Episode(3,"Third episode","Third description"));
    season1->addEpisode(new Episode(4,"Fourth episode","Fourth description"));

    Series * series1=new Series("Series 1");
    series1->addSeason(season1);

    mSeriesList=new SeriesList;
    mSeriesList->addSeries(series1);


    //showEpisodeDetails(0);
    //showSeasonDetails();
    //showSeriesDetails();
    showSeriesList();
}

void Controller::showSeriesList()
{
    SignalListAdapter<Series*> adapter(&(mSeriesList->series()),"series");

    QQmlContext *ctxt = mViewer.rootContext();
    ctxt->setContextProperty("seriesList", &adapter);
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
    mCurrentSeries=mSeriesList->getSeries(row);
    SignalListAdapter<Season*> adapter(&(mCurrentSeries->seasons()),"season");

    QQmlContext *ctxt = mViewer.rootContext();
    ctxt->setContextProperty("series", &adapter);
    mViewer.setSource(QUrl("qrc:/view/SeriesDetails.qml"));
    QObject *seriesDetails = mViewer.rootObject();
    connect(seriesDetails, SIGNAL(seasonClicked(const int)),this,SLOT(willShowSeasonDetails(const int)));
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
    mCurrentSeason=mCurrentSeries->getSeason(row);
    SignalListAdapter<Episode*> adapter(&(mCurrentSeason->episodes()),"episode");

    QQmlContext *ctxt = mViewer.rootContext();
    ctxt->setContextProperty("season", &adapter);
    mViewer.setSource(QUrl("qrc:/view/SeasonDetails.qml"));
    QObject *seasonDetails = mViewer.rootObject();
    connect(seasonDetails, SIGNAL(episodeClicked(const int)),this,SLOT(willShowEpisodeDetails(const int)));
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
}

void Controller::run()
{
    mViewer.show();
}
