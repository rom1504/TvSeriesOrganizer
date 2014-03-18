#include <QDomDocument>
#include <QDomElement>

#include "serieslist.h"
#include "adapter/signallistfilter.h"
#include "controller/controller.h"

SeriesList::SeriesList(QObject *parent) :
    QObject(parent),mSeries([](Series* a,Series * b){return a->name().toLower()<b->name().toLower();})
{
}

int SeriesList::addSeries(Series * series)
{
    int id=series->id();
    if(mIds.contains(id)) return -1;
    mIds<<id;
    int insertionIndex=mSeries.append(series);
    connect(series,&Series::seenChanged,[insertionIndex,this](){emit mSeries.dataChanged(insertionIndex,insertionIndex);});
    emit seriesCountChanged();
    return insertionIndex;
}


Series * SeriesList::getSeries(int row) const
{
    return mSeries.get(row);
}

int SeriesList::seriesCount() const
{
    return mSeries.size();
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
    mIds.remove(mSeries.get(row)->id());
    mSeries.remove(row);
    emit seriesCountChanged();
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
    series->complete();
}


void SeriesList::searchSeries(const QString &seriesName)
{
    Series::loadLocallyOrRemotely(Controller::cachePath+"/"+seriesName+QLocale().bcp47Name()+"_search.xml",QUrl("http://thetvdb.com/api/GetSeries.php?seriesname="+seriesName+"&language="+QLocale().bcp47Name()),[this](QString xmlContent){
        SignalList<Series*> * searchList=new SignalList<Series*>;
        QDomDocument doc;
        doc.setContent(xmlContent);
        QDomElement root = doc.documentElement();
        root = root.firstChildElement();
        QSet<int> ids;
        while(!root.isNull())
        {
            int id=root.elementsByTagName("seriesid").at(0).toElement().text().toInt();
            if(ids.contains(id)) {root = root.nextSiblingElement();continue;}
            else ids<<id;
            Series * series=new Series(root,this);
            searchList->append(series);
            root = root.nextSiblingElement();
        }
        SignalListAdapter<Series*> * searchListModel=new SignalListAdapter<Series*>(searchList,"series");
        emit searchCompleted(searchListModel);
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
    while (!file.atEnd()) addSeries(new Series(QString::fromUtf8(file.readLine()).trimmed().toInt(),this));
    file.close();
}
