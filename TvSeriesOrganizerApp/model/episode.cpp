#include "episode.h"

Episode::Episode(int number, const QString & name, const QString& overview, Image *banner, QDate firstAired, Season *parent) :
    QObject((QObject*)parent),mNumber(number),mName(name),mOverview(overview),mBanner(banner),mFirstAired(firstAired),mSeen(false),mSeason(parent)
{
}

int Episode::number() const
{
    return mNumber;
}

QString Episode::name() const
{
    return mName;
}


Season* Episode::season() const
{
    return mSeason;
}

QString Episode::overview() const
{
    return mOverview;
}

Image *Episode::banner() const
{
    return mBanner;
}

QDate Episode::firstAired() const
{
    return mFirstAired;
}

bool Episode::seen() const
{
    return mSeen;
}

bool Episode::aired() const
{
    if(!(mFirstAired.isValid())) return true;
    return mFirstAired<=QDate::currentDate();
}


void Episode::setSeen(bool seen)
{
    mSeen=seen;
    emit seenChanged();
}
