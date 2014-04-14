#include "controller/controller.h"
#include "serieslistlist.h"

SeriesListList::SeriesListList(SeriesList * alreadyAddedSeriesList,QObject *parent) :
    QObject(parent),mAlreadyAddedSeriesList(alreadyAddedSeriesList)
{

    Series::loadLocallyOrRemotely(Controller::cachePath+"/trendingSeriesList.json",QUrl("http://api.trakt.tv/shows/trending.json/f9201fd7c6183a624a27ccba01555310"),std::bind(&SeriesListList::load,this,std::placeholders::_1),7);
}


void SeriesListList::load(QString jsonFileContent)
{
    SeriesList *seriesListTrending=new SeriesList(true,mAlreadyAddedSeriesList);
    seriesListTrending->setGenre(tr("Trending"));
    mSeriesListByGenre[tr("Trending")]=seriesListTrending;
    mSeriesListList.append(seriesListTrending);
    QJsonDocument doc=QJsonDocument::fromJson(jsonFileContent.toUtf8());
    QJsonArray seriesList=doc.array();
    for(QJsonValue seriesv : seriesList)
    {
        QJsonObject jseries=seriesv.toObject();
        Series * series=new Series();
        series->setId(jseries["tvdb_id"].toString().toInt());
        QString poster=jseries["poster"].toString();
        QString bigPoster=poster;
        poster=poster.section(".",0,-2)+"-138."+poster.section(".",-1);
        series->setPoster(new Image(QUrl(poster),QUrl(bigPoster)));
        series->setName(jseries["title"].toString());
        QJsonArray genreArray=jseries["genres"].toArray();
        for(QJsonValue genrev : genreArray)
        {
            QString genre=genrev.toString();
            if(genre != "")
            {
                SeriesList * seriesList=nullptr;
                if(mSeriesListByGenre.contains(genre)) seriesList=mSeriesListByGenre[genre];
                else
                {
                    seriesList=new SeriesList(true,mAlreadyAddedSeriesList);
                    seriesList->setGenre(genre);
                    mSeriesListByGenre[genre]=seriesList;
                    mSeriesListList.append(seriesList);
                }
                seriesList->addSeries(series);
            }
        }
        seriesListTrending->addSeries(series);
    }
}

QAbstractItemModel * SeriesListList::seriesListListModel()
{
    return new SignalListAdapter<SeriesList*>(&mSeriesListList,"seriesList");
}
