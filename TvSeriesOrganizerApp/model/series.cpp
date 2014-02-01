#include "series.h"

Series::Series(QObject *parent) :
    QObject(parent)
{
}

void Series::addSeason(Season * season)
{
    mSeasons.append(season);
}
