#include "serieslist.h"

SeriesList::SeriesList(QObject *parent) :
    QObject(parent)
{
}

void SeriesList::addSeries(Series * series)
{
    mSeries.append(series);
}


Series * SeriesList::getSeries(int row) const
{
    return mSeries.get(row);
}

SignalList<Series *> & SeriesList::series()
{
    return mSeries;
}
