#include "thetvdbapi.h"
#include "model/diskcache.h"

// http://thetvdb.com/wiki/index.php/Multi_Language
QSet<QString> TheTvDBAPI::mTheTvDBSupportedLanguages={"en","sv","no","da","fi","nl","de","it","es","fr","pl","hu","el","tr","ru","he"
                                                 ,"ja","pt","zh","cs","sl","hr","ko"};

TheTvDBAPI::TheTvDBAPI(QString cachePath, QString server, QString APIKey,QNetworkAccessManager * networkAccessManager, DiskCache * diskCache, QObject *parent) :
    QObject(parent),mServer(server),mCachePath(cachePath),mAPIKey(APIKey),mLastAutocompletion(""),mNetworkAccessManager(networkAccessManager),mDiskCache(diskCache)
{

}


void TheTvDBAPI::updateCache(std::function<void(void)> finishedUpdating)
{
    QString updatePeriod=getUpdatePeriod();
    writeLastTimeOfUpdate();
    eraseUnvalidatedCacheFiles(updatePeriod,finishedUpdating);
}

void TheTvDBAPI::writeLastTimeOfUpdate()
{
    QFile file(mCachePath+"/timeOfLastUpdate.txt");
    qint64 currentTime=QDateTime::currentMSecsSinceEpoch();
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"Can't open timeOfLastUpdate.txt";
        return;
    }
    QTextStream out(&file);
    out<<currentTime;
    file.close();
}

void TheTvDBAPI::eraseUnvalidatedCacheFiles(QString updatePeriod, std::function<void(void)> finishedUpdating)
{
    if(updatePeriod=="nothing") finishedUpdating();
    else if(updatePeriod=="all")
    {
        QDir data7(mCachePath+"/data7");
        QDir prepared(mCachePath+"/prepared");
        data7.removeRecursively();
        prepared.removeRecursively();
        QDir path(mCachePath);
        QStringList filter;
        filter<<"*.xml";
        for(QString entry : path.entryList(filter,QDir::Files)) path.remove(entry);
    }
    else
    {
       QNetworkReply* reply=mNetworkAccessManager->get(QNetworkRequest(mServer+"/api/"+mAPIKey+"/updates/updates_"+updatePeriod+".xml"));
       connect(reply, &QNetworkReply::finished,[this,reply,finishedUpdating](){
            QString content=reply->readAll();
            // not reading the Episode fields: I only need to know a series has been updated
            // Banner fields : get the url and invalidate it in the cache
            // if series updated : actor and banner files deleted too
            QDir path(mCachePath);
            QNetworkDiskCache * cache=new QNetworkDiskCache(this);
            cache->setCacheDirectory(mCachePath);
            QXmlStreamReader xml(content);
            while(!xml.atEnd())
            {
                xml.readNext();
                if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Series")
                {
                    QString seriesId=getField(xml,"Series","id");
                    path.remove(seriesId+currentTheTvDBLanguage()+".xml");
                    path.remove(seriesId+"_actors.xml");
                    path.remove(seriesId+"_banners.xml");
                }
                else if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Banner")
                {
                    QString path=getField(xml,"Banner","path");
                    cache->remove(mServer+"/banners/_cache/"+path);
                    cache->remove(mServer+"/banners/"+path);
                }
                else if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Episode")
                {
                    while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Episode")) xml.readNext();
                }
            }
            delete cache;
            finishedUpdating();
        });
    }
}

QString TheTvDBAPI::getUpdatePeriod()
{
    QFile file(mCachePath+"/timeOfLastUpdate.txt");
    QString updatePeriod="";
    if(!file.open(QIODevice::ReadOnly)) updatePeriod="all";
    else
    {
        QString content=file.readAll();
        qint64 timeOfLastUpdate=content.toULongLong();
        qint64 currentTime=QDateTime::currentMSecsSinceEpoch();
        qint64 difference=currentTime-timeOfLastUpdate;
        qint64 day=Q_INT64_C(24*3600*1000);
        qint64 week=day*7;
        qint64 month=week*4;
        if(difference<day/2) updatePeriod="nothing";
        else if(difference<day) updatePeriod="day";
        else if(difference<week) updatePeriod="week";
        else if(difference<month) updatePeriod="month";
        else updatePeriod="all";
    }
    return updatePeriod;
}


void TheTvDBAPI::loadSeries(int id,QObject * parent,std::function<void(void)> almostLoaded,std::function<void(void)> loaded)
{
    loadSeries(new Series(id,parent),almostLoaded,loaded);
}

void TheTvDBAPI::loadSeries(Series* series,std::function<void(void)> almostLoaded,std::function<void(void)> loaded)
{
    mDiskCache->streamLocallyOrRemotely(mCachePath+"/"+QString::number(series->id())+currentTheTvDBLanguage()+".xml",QUrl(mServer+"/api/"+mAPIKey+"/series/"+QString::number(series->id())+"/all/"+currentTheTvDBLanguage()+".xml"),[series,this,loaded,almostLoaded](QIODevice* device)
    {
        QXmlStreamReader xml(device);
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
                series->setBanner(new Image(fields->value("banner"),series));
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
                currentSeason->addEpisode(new Episode(fields->value("EpisodeNumber").toInt(),fields->value("EpisodeName"),fields->value("Overview"),episodeBanner=="" ? currentSeason->banner() : new Image(episodeBanner,series),QDate::fromString(fields->value("FirstAired"),"yyyy-MM-dd"),currentSeason));
            }
        }
        device->close();
        almostLoaded();
        loadBanners(series,loaded);
    });
}


void TheTvDBAPI::loadBanners(Series * series,std::function<void(void)> loaded)
{
    mDiskCache->streamLocallyOrRemotely(mCachePath+"/"+QString::number(series->id())+"_banners.xml",QUrl(mServer+"/api/"+mAPIKey+"/series/"+QString::number(series->id())+"/banners.xml"),[this,series,loaded](QIODevice* device){
        QXmlStreamReader xml(device);
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
                    Image * poster=new Image(bannerPath,series);
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
                        if(bannerType2=="seasonwide") season->setBanner(new Image(bannerPath,series));
                        else if(bannerType2=="season") season->setPoster(new Image(bannerPath,series));
                    }
                }
                else if(bannerType=="fanart") series->addFanArt(new Image(QUrl(mServer+"/banners/"+fields->value("ThumbnailPath")),mServer+"/banners/"+bannerPath,series));
            }
        }
        device->close();
        loadActors(series,loaded);
    });
}

QString TheTvDBAPI::getField(QXmlStreamReader & xml,QString containerElementName,QString field)
{
    QSet<QString> fields;
    fields<<field;
    QMap<QString,QString>* gFields=getFields(xml,containerElementName,fields);
    if(gFields==nullptr) return "";
    return gFields->value(field);
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
    mDiskCache->streamLocallyOrRemotely(mCachePath+"/"+QString::number(series->id())+"_actors.xml",QUrl(mServer+"/api/"+mAPIKey+"/series/"+QString::number(series->id())+"/actors.xml"),[this,series,loaded](QIODevice* device)
    {
        QXmlStreamReader xml(device);
        QSet<QString> actorWantedFields={"id","Image","Name","Role","SortOrder"};
        while(!xml.atEnd())
        {
            xml.readNext();
            QMap<QString,QString>* fields=getFields(xml,"Actor",actorWantedFields);
            if(fields!=nullptr) series->addActor(new Actor(fields->value("id").toInt(),new Image(fields->value("Image"),series),fields->value("Name"),fields->value("Role"),fields->value("SortOrder").toInt(),series));
        }
        device->close();
        loaded();
    });
}

void TheTvDBAPI::searchSeries(QString seriesName, std::function<void(SignalList<Series *> *)> callback)
{
    mDiskCache->streamLocallyOrRemotely(mCachePath+"/"+seriesName+currentTheTvDBLanguage()+"_search.xml",QUrl(mServer+"/api/GetSeries.php?seriesname="+seriesName+"&language="+currentTheTvDBLanguage()),[this,seriesName,callback](QIODevice* device)
    {
        QXmlStreamReader xml(device);
        SignalList<Series*> * searchList=new SignalList<Series*>;
        QSet<int> ids;
        QSet<QString> searchSeriesWantedFields={"banner","id","SeriesName","Overview","FirstAired","Network"};
        while(!xml.atEnd())
        {
            xml.readNext();
            Series * series=new Series(this);
            QMap<QString,QString>* fields=getFields(xml,"Series",searchSeriesWantedFields);
            if(fields!=nullptr)
            {
                int id=fields->value("id").toInt();
                if(ids.contains(id)) continue;
                else ids<<id;
                series->setBanner(new Image(fields->value("banner"),series));
                series->setId(fields->value("id").toInt());
                series->setName(fields->value("SeriesName"));
                series->setOverview(fields->value("Overview"));
                series->setFirstAired(QDate::fromString(fields->value("FirstAired"),"yyyy-MM-dd"));
                series->setNetwork(fields->value("Network"));
                series->setPoster(new Image("posters/"+QString::number(series->id())+"-1.jpg",series));
                searchList->append(series);
            }
        }
        device->close();
        callback(searchList);
    },1);
}

void TheTvDBAPI::liveSearchSeries(QString beginSeriesName,std::function<void(QStringList*)> callback)
{
    mLastAutocompletion=beginSeriesName;
    QNetworkReply* reply=mNetworkAccessManager->get(QNetworkRequest(mServer+"/livesearch.php?q="+beginSeriesName));
    connect(reply, &QNetworkReply::finished,[this,beginSeriesName,callback,reply](){
        if(beginSeriesName!=mLastAutocompletion || beginSeriesName=="") return;
        QString jsonContent=reply->readAll();
        jsonContent=jsonContent.replace("results:","\"results\":").replace("id:","\"id\":").replace("value:","\"value\":").replace("info:","\"info\":").replace(",\n]","]");

        QJsonDocument doc=QJsonDocument::fromJson(jsonContent.toUtf8());
        QJsonArray results=doc.object()["results"].toArray();
        QStringList * stringList=new QStringList;
        for(QJsonValue result : results) stringList->append(result.toObject()["value"].toString());

        callback(stringList);
    });
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


