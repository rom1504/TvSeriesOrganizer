#include "season.h"

Season::Season(QObject *parent) :
    QObject(parent)
{
}


void Season::addEpisode(Episode * episode)
{
    mEpisodes.append(episode);
}


SignalList<Episode *> & Season::episodes()
{
    return mEpisodes;
}
