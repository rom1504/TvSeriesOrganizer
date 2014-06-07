#include "thetvdbapi.h"
#include "model/diskcache.h"

// http://thetvdb.com/wiki/index.php/Multi_Language
QSet<QString> TheTvDBAPI::mTheTvDBSupportedLanguages={"en","sv","no","da","fi","nl","de","it","es","fr","pl","hu","el","tr","ru","he"
                                                 ,"ja","pt","zh","cs","sl","hr","ko"};

TheTvDBAPI::TheTvDBAPI(QString cachePath, QString server, QString APIKey, QObject *parent) :
    QObject(parent),mServer(server),mCachePath(cachePath),mAPIKey(APIKey),mLastAutocompletion("")
{

}

void TheTvDBAPI::loadSeries(int id,QObject * parent,std::function<void(void)> almostLoaded,std::function<void(void)> loaded)
{
    loadSeries(new Series(id,parent),almostLoaded,loaded);
}

void TheTvDBAPI::loadSeries(Series* series,std::function<void(void)> almostLoaded,std::function<void(void)> loaded)
{
    DiskCache::loadLocallyOrRemotely(mCachePath+"/"+QString::number(series->id())+currentTheTvDBLanguage()+".xml",QUrl(mServer+"/api/"+mAPIKey+"/series/"+QString::number(series->id())+"/all/"+currentTheTvDBLanguage()+".xml"),[series,this,loaded,almostLoaded](QString content)
    {
        QXmlStreamReader xml(content);
        QSet<QString> seriesWantedFields={"banner","SeriesName","Overview","FirstAired","Network"};
        QSet<QString> episodeWantedFields={"Combined_season","EpisodeNumber","EpisodeName","Overview","filename","FirstAired"};
        Season * currentSeason=nullptr;
        while(!xml.atEnd())
        {
            xml.readNext();
            if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Series")
            {
                QMap<QString,QString>* fields=getFields(xml,"Series",seriesWantedFields);
                if(fields==nullptr) continue;
                series->setBanner(new Image(fields->value("banner")));
                series->setName(fields->value("SeriesName"));
                series->setOverview(fields->value("Overview"));
                series->setFirstAired(QDate::fromString(fields->value("FirstAired"),"yyyy-MM-dd"));
                series->setNetwork(fields->value("Network"));
            }
            else if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Episode")
            {
                QMap<QString,QString>* fields=getFields(xml,"Episode",episodeWantedFields);
                if(fields==nullptr) continue;
                QString seasonNumber=fields->value("Combined_season");
                QString episodeBanner=fields->value("filename");
                currentSeason=series->findSeason(seasonNumber.toInt());
                if(currentSeason==nullptr)
                {
                    Q_ASSERT(seasonNumber!="");
                    currentSeason=new Season(seasonNumber.toInt(),series->banner(),nullptr,series);
                    series->addSeason(currentSeason);
                }
                currentSeason->addEpisode(new Episode(fields->value("EpisodeNumber").toInt(),fields->value("EpisodeName"),fields->value("Overview"),episodeBanner=="" ? currentSeason->banner() : new Image(episodeBanner),QDate::fromString(fields->value("FirstAired"),"yyyy-MM-dd"),currentSeason));
            }
        }
        almostLoaded();
        loadBanners(series,loaded);
    });
}


void TheTvDBAPI::loadBanners(Series * series,std::function<void(void)> loaded)
{
    DiskCache::loadLocallyOrRemotely(mCachePath+"/"+QString::number(series->id())+"_banners.xml",QUrl(mServer+"/api/"+mAPIKey+"/series/"+QString::number(series->id())+"/banners.xml"),[this,series,loaded](QString content){
        QXmlStreamReader xml(content);
        QSet<QString> bannerWantedFields={"BannerType","BannerType2","BannerPath","ThumbnailPath","Season","Language"};
        bool seriesPosterAlreadySet=false;
        while(!xml.atEnd())
        {
            xml.readNext();
            QMap<QString,QString>* fields=getFields(xml,"Banner",bannerWantedFields);
            if(fields==nullptr) continue;
            QString bannerType=fields->value("BannerType");
            QString bannerType2=fields->value("BannerType2");
            QString bannerPath=fields->value("BannerPath");
            QString language=fields->value("Language");
            if(language=="en" || language==currentTheTvDBLanguage())
            {
                if(bannerType=="poster")
                {
                    Image * poster=new Image(bannerPath);
                    if(!seriesPosterAlreadySet)
                    {
                        seriesPosterAlreadySet=true;
                        series->setPoster(poster);
                    }
                    series->addPoster(poster);
                }
                else if(bannerType=="season")
                {
                    Season * season=series->findSeason(fields->value("Season").toInt());
                    if(season!=nullptr)
                    {
                        if(bannerType2=="seasonwide") season->setBanner(new Image(bannerPath));
                        else if(bannerType2=="season") season->setPoster(new Image(bannerPath));
                    }
                }
                else if(bannerType=="fanart") series->addFanArt(new Image(QUrl(mServer+"/banners/"+fields->value("ThumbnailPath")),mServer+"/banners/"+bannerPath));
            }
        }
        loadActors(series,loaded);
    });
}

QMap<QString,QString>* TheTvDBAPI::getFields(QXmlStreamReader & xml,QString containerElementName,QSet<QString>& wantedFields)
{
    if(!(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()==containerElementName)) return nullptr;
    QMap<QString,QString>* fields=new QMap<QString,QString>;
    while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()==containerElementName))
    {
        xml.readNext();
        if(xml.tokenType()==QXmlStreamReader::StartElement && wantedFields.contains(xml.name().toString())) fields->insert(xml.name().toString(),xml.readElementText());
    }
    return fields;
}

void TheTvDBAPI::loadActors(Series * series,std::function<void(void)> loaded)
{
    DiskCache::loadLocallyOrRemotely(mCachePath+"/"+QString::number(series->id())+"_actors.xml",QUrl(mServer+"/api/"+mAPIKey+"/series/"+QString::number(series->id())+"/actors.xml"),[this,series,loaded](QString content)
    {
        QXmlStreamReader xml(content);
        QSet<QString> actorWantedFields={"id","Image","Name","Role","SortOrder"};
        while(!xml.atEnd())
        {
            xml.readNext();
            QMap<QString,QString>* fields=getFields(xml,"Actor",actorWantedFields);
            if(fields!=nullptr) series->addActor(new Actor(fields->value("id").toInt(),new Image(fields->value("Image")),fields->value("Name"),fields->value("Role"),fields->value("SortOrder").toInt()));
        }
        loaded();
    });
}

void TheTvDBAPI::searchSeries(QString seriesName, std::function<void(SignalList<Series *> *)> callback)
{
    DiskCache::loadLocallyOrRemotely(mCachePath+"/"+seriesName+currentTheTvDBLanguage()+"_search.xml",QUrl(mServer+"/api/GetSeries.php?seriesname="+seriesName+"&language="+currentTheTvDBLanguage()),[this,seriesName,callback](QString content)
    {
        QXmlStreamReader xml(content);
        SignalList<Series*> * searchList=new SignalList<Series*>;
        QSet<int> ids;
        QSet<QString> searchSeriesWantedFields={"banner","id","SeriesName","Overview","FirstAired","Network"};
        while(!xml.atEnd())
        {
            xml.readNext();
            Series * series=new Series();
            QMap<QString,QString>* fields=getFields(xml,"Series",searchSeriesWantedFields);
            if(fields!=nullptr)
            {
                int id=fields->value("id").toInt();
                if(ids.contains(id)) continue;
                else ids<<id;
                series->setBanner(new Image(fields->value("banner")));
                series->setId(fields->value("id").toInt());
                series->setName(fields->value("SeriesName"));
                series->setOverview(fields->value("Overview"));
                series->setFirstAired(QDate::fromString(fields->value("FirstAired"),"yyyy-MM-dd"));
                series->setNetwork(fields->value("Network"));
                series->setPoster(new Image("posters/"+QString::number(series->id())+"-1.jpg"));
                searchList->append(series);
            }
        }
        callback(searchList);
    });
}

void TheTvDBAPI::liveSearchSeries(QString beginSeriesName,std::function<void(QStringList*)> callback)
{
    mLastAutocompletion=beginSeriesName;
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished,[this,beginSeriesName,callback](QNetworkReply* reply){
        if(beginSeriesName!=mLastAutocompletion || beginSeriesName=="") return;
        QString jsonContent=reply->readAll();
        jsonContent=jsonContent.replace("results:","\"results\":").replace("id:","\"id\":").replace("value:","\"value\":").replace("info:","\"info\":").replace(",\n]","]");

        QJsonDocument doc=QJsonDocument::fromJson(jsonContent.toUtf8());
        QJsonArray results=doc.object()["results"].toArray();
        QStringList * stringList=new QStringList;
        for(QJsonValue result : results) stringList->append(result.toObject()["value"].toString());

        callback(stringList);
    });
    manager->get(QNetworkRequest(mServer+"/livesearch.php?q="+beginSeriesName));
}

bool TheTvDBAPI::isAThetvdbSupportedLanguages(QString language)
{
    return mTheTvDBSupportedLanguages.contains(language);
}

QString TheTvDBAPI::currentTheTvDBLanguage()
{
    QString language=QLocale().bcp47Name();
    return isAThetvdbSupportedLanguages(language) ? language : "en";
}


