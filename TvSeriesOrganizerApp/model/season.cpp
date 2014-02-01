#include "season.h"

Season::Season(QObject *parent) :
    QObject(parent)
{
}


void Season::addEpisode(Episode * episode)
{
    mEpisodes.append(episode);
}


Episode * Season::getEpisode(int row) const
{
    return mEpisodes.get(row);
}

SignalList<Episode *> & Season::episodes()
{
    return mEpisodes;
}
