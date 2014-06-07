#include "trakttvapi.h"
#include "model/diskcache.h"

TraktTvAPI::TraktTvAPI(QString cachePath, SeriesList* alreadyAddedSeriesList, QString server, QString APIKey, QObject *parent) :
    QObject(parent),mCachePath(cachePath),mServer(server),mAPIKey(APIKey),mAlreadyAddedSeriesList(alreadyAddedSeriesList)
{
}


void TraktTvAPI::loadSeriesListList(SignalList<SeriesList *> * seriesListList, std::function<void(void)> callback)
{
    DiskCache::loadLocallyOrRemotely(mCachePath+"/trendingSeriesList.json",QUrl(mServer+"/shows/trending.json/"+mAPIKey),[seriesListList,this,callback](QString jsonFileContent)
    {
        SeriesList *seriesListTrending=new SeriesList(true,mAlreadyAddedSeriesList,this);
        seriesListTrending->setGenre(tr("Trending"));
        QMap<QString,SeriesList*> seriesListByGenre;
        seriesListByGenre[tr("Trending")]=seriesListTrending;
        seriesListList->append(seriesListTrending);
        QJsonDocument doc=QJsonDocument::fromJson(jsonFileContent.toUtf8());
        QJsonArray seriesList=doc.array();
        for(QJsonValue seriesv : seriesList)
        {
            QJsonObject jseries=seriesv.toObject();
            Series * series=new Series(this);
            series->setId(jseries["tvdb_id"].toString().toInt());
            QString poster=jseries["poster"].toString();
            QString bigPoster=poster;
            poster=poster.section(".",0,-2)+"-138."+poster.section(".",-1);
            series->setPoster(new Image(QUrl(poster),QUrl(bigPoster),series));
            series->setName(jseries["title"].toString());
            QJsonArray genreArray=jseries["genres"].toArray();
            for(QJsonValue genrev : genreArray)
            {
                QString genre=genrev.toString();
                if(genre != "")
                {
                    SeriesList * seriesList=nullptr;
                    if(seriesListByGenre.contains(genre)) seriesList=seriesListByGenre[genre];
                    else
                    {
                        seriesList=new SeriesList(true,mAlreadyAddedSeriesList,this);
                        seriesList->setGenre(genre);
                        seriesListByGenre[genre]=seriesList;
                        seriesListList->append(seriesList);
                    }
                    seriesList->addSeries(series);
                }
            }
            seriesListTrending->addSeries(series);
        }
        callback();
    },7);
}
