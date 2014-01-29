#include <QQmlContext>

#include "controller.h"

#include "model/season.h"
#include "adapter/episodesignallistadapter.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    Season season1;
    season1.addEpisode(new Episode(1,"First episode","First description"));
    season1.addEpisode(new Episode(2,"Second episode","Second description"));
    season1.addEpisode(new Episode(3,"Third episode","Third description"));
    season1.addEpisode(new Episode(4,"Fourth episode","Fourth description"));
    SignalListAdapter<Episode*> model(&(season1.episodes()));

    QQmlContext *ctxt = mViewer.rootContext();
    ctxt->setContextProperty("season", &model);

    mViewer.setSource(QUrl("qrc:qml/DownloaderInterface/main.qml"));
}

void Controller::run()
{
    mViewer.showExpanded();
}
