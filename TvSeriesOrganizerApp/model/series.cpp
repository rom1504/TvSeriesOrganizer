#include "series.h"

Series::Series(QString name, QUrl banner, QObject *parent) :
    QObject(parent),mName(name),mBanner(banner)
{
}

void Series::addSeason(Season * season)
{
    mSeasons.append(season);
}


Season * Series::getSeason(int row) const
{
    return mSeasons.get(row);
}

SignalList<Season *> & Series::seasons()
{
    return mSeasons;
}
QString Series::name() const
{
    return mName;
}

QUrl Series::banner() const
{
    return mBanner;
}
