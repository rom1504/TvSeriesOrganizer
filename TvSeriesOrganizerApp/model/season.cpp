#include "season.h"

Season::Season(int number,QObject *parent) :
    QObject(parent),mNumber(number)
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

int Season::number() const
{
    return mNumber;
}
