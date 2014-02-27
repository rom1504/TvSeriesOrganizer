#include "episode.h"

Episode::Episode(int number, const QString & name, const QString& overview, QUrl banner, QDate firstAired, QObject *parent) :
    QObject(parent),mNumber(number),mName(name),mOverview(overview),mBanner(banner),mFirstAired(firstAired),mSeen(false)
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

QString Episode::overview() const
{
    return mOverview;
}

QUrl Episode::banner() const
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


void Episode::setSeen(bool seen)
{
    mSeen=seen;
    emit seenChanged();
}
