#include "season.h"

Season::Season(int number, QUrl banner, QObject *parent) :
    QObject(parent),mNumber(number),mBanner(banner)
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

QUrl Season::banner() const
{
    return mBanner;
}
