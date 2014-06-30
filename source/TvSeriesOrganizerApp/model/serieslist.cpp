#include "serieslist.h"
#include "adapter/signallistfilter.h"


SeriesList::SeriesList(TheTvDBAPI* theTvDBAPI, SeriesList* filterBySeriesList,QObject *parent) :
    QObject(parent),mAutocompleteModel(new QStringListModel),mSeries([](Series* a,Series * b){return a->name().toLower()<b->name().toLower();}),mFilterBySeriesList(filterBySeriesList),mTheTvDBAPI(theTvDBAPI)
{
}



SeriesList::SeriesList(TheTvDBAPI* theTvDBAPI, bool /* not sorted */,SeriesList* filterBySeriesList, QObject *parent) :
    QObject(parent),mAutocompleteModel(new QStringListModel),mFilterBySeriesList(filterBySeriesList),mTheTvDBAPI(theTvDBAPI)
{
}


bool SeriesList::added(int id) const
{
    return mIds.contains(id);
}

int SeriesList::addSeries(Series * series)
{
    Q_ASSERT(series!=nullptr);
    int id=series->id();
    if(mIds.contains(id)) return -1;
    mIds<<id;
    int insertionIndex=mSeries.append(series);
    connect(series,&Series::seenChanged,[series,this](){mSeries.elementChanged(series);});
    emit seriesCountChanged();
    return insertionIndex;
}


QAbstractItemModel * SeriesList::autocompleteModel()
{
    return mAutocompleteModel;
}


void SeriesList::updateAutocompleteModel(const QString &beginSeriesName)
{
    mTheTvDBAPI->liveSearchSeries(beginSeriesName,[this](QStringList* stringList)
    {
        mAutocompleteModel->setStringList(*stringList);
    });
}


QString SeriesList::genre() const
{
    return mGenre;
}


void SeriesList::setGenre(QString genre)
{
    mGenre=genre;
    emit genreChanged();
}

Series * SeriesList::getSeries(int row) const
{
    Series * series=mSeries.get(row);
    Q_ASSERT(series!=nullptr);
    return series;
}


int SeriesList::seriesCount() const
{
    return mSeries.size();
}


QAbstractItemModel * SeriesList::seriesListFilteredModel()
{
    Q_ASSERT(mFilterBySeriesList!=nullptr);
    SignalListFilter<Series*> * filteredModel=new SignalListFilter<Series*>();
    filteredModel->setFilter([this](Series* series){return !mFilterBySeriesList->added(series->id());});
    filteredModel->setSourceModel(seriesListModelT());
    return filteredModel;
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


void SeriesList::removeSeries(Series *series)
{
    mIds.remove(series->id());
    mSeries.remove(series);
    emit seriesCountChanged();
}

void SeriesList::removeSaveSeries(Series *series)
{
    removeSeries(series);
    saveSeries();
}


SignalList<Series *> * SeriesList::series()
{
    return &mSeries;
}


void SeriesList::completeAddSaveSeries(Series* series)
{
    connect(series,&Series::completed,[this,series](){
        int index=addSeries(series);
        if(index!=-1)
        {
            saveSeries();
            emit seriesAdded(index);
        }
    });
    mTheTvDBAPI->loadSeries(series,[series](){series->loadSeriesSeenFile();},[series](){emit series->completed();});
}


void SeriesList::searchSeries(const QString &seriesName)
{
    mTheTvDBAPI->searchSeries(seriesName,[this](SignalList<Series*> * searchList){
        SignalListAdapter<Series*> * searchListModel=new SignalListAdapter<Series*>(searchList,"series");
        emit searchCompleted(searchListModel,searchList->size());
    });
}

void SeriesList::saveSeries(QString fileName) const
{
    fileName=fileName=="" ? mSaveFileName : fileName;
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream flux(&file);
    for(auto series : mSeries) flux<<series->id()<<"\n";
    file.close();
}

void SeriesList::loadSeries(QString fileName)
{
    fileName=fileName=="" ? mSaveFileName : fileName;
    mSaveFileName=fileName;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    while (!file.atEnd())
    {
        Series * series=new Series(QString::fromUtf8(file.readLine()).trimmed().toInt(),this);
        mTheTvDBAPI->loadSeries(series,[series](){series->loadSeriesSeenFile();},[series](){emit series->completed();});
        addSeries(series);
    }
    file.close();
}
