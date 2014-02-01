#include "series.h"

Series::Series(QString name, QObject *parent) :
    QObject(parent),mName(name)
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
