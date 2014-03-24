#include <QDomDocument>
#include <QDomElement>

#include "serieslist.h"
#include "adapter/signallistfilter.h"
#include "controller/controller.h"

SeriesList::SeriesList(QObject *parent) :
    QObject(parent),mLastAutocompletion(""),mAutocompleteModel(new QStringListModel),mSeries([](Series* a,Series * b){return a->name().toLower()<b->name().toLower();})
{
}

int SeriesList::addSeries(Series * series)
{
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
    mLastAutocompletion=beginSeriesName;
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished,[this,beginSeriesName](QNetworkReply* reply){
        if(beginSeriesName!=mLastAutocompletion || beginSeriesName=="") return;
        QString jsonContent=reply->readAll();
        jsonContent=jsonContent.replace("results:","\"results\":").replace("id:","\"id\":").replace("value:","\"value\":").replace("info:","\"info\":").replace(",\n]","]");

        QJsonDocument doc=QJsonDocument::fromJson(jsonContent.toUtf8());
        QJsonArray results=doc.object()["results"].toArray();
        QStringList * stringList=new QStringList;
        for(QJsonValue result : results) stringList->append(result.toObject()["value"].toString());

        mAutocompleteModel->setStringList(*stringList);
    });
    manager->get(QNetworkRequest("http://thetvdb.com/livesearch.php?q="+beginSeriesName));
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
    while (!file.atEnd()) addSeries(new Series(QString::fromUtf8(file.readLine()).trimmed().toInt(),this));
    file.close();
}
