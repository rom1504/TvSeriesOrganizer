#include <QQmlContext>
#include <QDebug>
#include <QQuickItem>

#include "controller.h"

#include "adapter/signallistadapter.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{

    mSeason1.addEpisode(new Episode(1,"First episode","First description"));
    mSeason1.addEpisode(new Episode(2,"Second episode","Second description"));
    mSeason1.addEpisode(new Episode(3,"Third episode","Third description"));
    mSeason1.addEpisode(new Episode(4,"Fourth episode","Fourth description"));



    //showEpisodeDetails(0);
    showSeasonDetails();
}

void Controller::showSeasonDetails()
{
    SignalListAdapter<Episode*> adapter(&(mSeason1.episodes()),"episode");

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
    ctxt->setContextProperty("episode",mSeason1.getEpisode(row));
    mViewer.setSource(QUrl("qrc:/view/EpisodeDetails.qml"));
}

void Controller::run()
{
    mViewer.show();
}
