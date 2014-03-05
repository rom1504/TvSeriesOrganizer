#include "serieslist.h"
#include "adapter/signallistfilter.h"

SeriesList::SeriesList(QObject *parent) :
    QObject(parent),mSeries([](Series* a,Series * b){return a->name()<b->name();})
{
}

void SeriesList::addSeries(Series * series)
{
    int insertionIndex=mSeries.append(series);
    connect(series,&Series::seenChanged,[insertionIndex,this](){emit mSeries.dataChanged(insertionIndex,insertionIndex);});
}


Series * SeriesList::getSeries(int row) const
{
    return mSeries.get(row);
}


SignalListAdapter<Series*> * SeriesList::seriesListModelT()
{
    return new SignalListAdapter<Series*>(&mSeries,"series");
}

QAbstractItemModel * SeriesList::seriesListModel()
{
    return seriesListModelT();
}


QAbstractItemModel * SeriesList::seriesListUpcomingModel()
{
    SignalListFilter<Series*> * filter=new SignalListFilter<Series*>();
    filter->setFilter([](Series* series){return !series->seen();});
    filter->setSourceModel(seriesListModelT());
    return filter;
}


void SeriesList::removeSeries(int row)
{
    mSeries.remove(row);
}

void SeriesList::removeSaveSeries(int row)
{
    removeSeries(row);
    saveSeries();
}


SignalList<Series *> * SeriesList::series()
{
    return &mSeries;
}


void SeriesList::addSeries(const QString& seriesName)
{
    addSeries(new Series(seriesName));
}

void SeriesList::addSaveSeries(const QString& seriesName)
{
    addSeries(seriesName);
    saveSeries();
}

void SeriesList::saveSeries(QString fileName) const
{
    fileName=fileName=="" ? mSaveFileName : fileName;
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream flux(&file);
    for(auto series : mSeries) flux<<series->name()<<"\n";
    file.close();
}

void SeriesList::loadSeries(QString fileName)
{
    fileName=fileName=="" ? mSaveFileName : fileName;
    mSaveFileName=fileName;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    while (!file.atEnd()) addSeries(new Series(QString::fromUtf8(file.readLine()).trimmed()));
    file.close();
}
