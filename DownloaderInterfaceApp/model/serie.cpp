#include "serie.h"

Serie::Serie(QObject *parent) :
    QObject(parent)
{
}

void Serie::addSeason(Season * season)
{
    mSeasons.append(season);
}
