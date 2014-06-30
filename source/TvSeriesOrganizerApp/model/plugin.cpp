#include "plugin.h"

#include "model/season.h"
#include "model/series.h"

Plugin::Plugin(AbstractPlugin * realPlugin,QObject *parent) :
    QObject(parent),mRealPlugin(realPlugin)
{

}

QString Plugin::buttonName() const
{
    return mRealPlugin->buttonName();
}

void Plugin::run(Episode * episode)
{
    EpisodePluginInterface * episodePluginInterface=new EpisodePluginInterface(episode->season()->series()->name(),episode->season()->number(),episode->number());
    connect(episodePluginInterface,&EpisodePluginInterface::seenChanged,[episode](bool seen){episode->setSeen(seen);});
    mRealPlugin->run(episodePluginInterface);
}
