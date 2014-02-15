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

SignalList<Series *> * SeriesList::series()
{
    return &mSeries;
}


void SeriesList::saveSeries(QString fileName) const
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream flux(&file);
    for(auto series : mSeries) flux<<series->name()<<"\n";
    file.close();
}

void SeriesList::loadSeries(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    while (!file.atEnd()) addSeries(new Series(QString::fromUtf8(file.readLine()).trimmed()));
    file.close();
}
