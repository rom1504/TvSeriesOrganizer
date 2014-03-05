#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <functional>
#include <QCoreApplication>

#include "series.h"
#include "controller/controller.h"
#include "adapter/signallistfilter.h"



Series::Series(QString name, QUrl banner, QObject *parent) :
    QObject(parent),mName(name),mBanner(banner),mSeasons([](Season* a,Season* b){return a->number()<b->number();})
{
    connect(this,&Series::seenChanged,this,&Series::seenRatioChanged);
}

Series::Series(QString name, QObject *parent) : QObject(parent),mName(name),mSeasons([](Season* a,Season* b){return a->number()<b->number();})
{
    connect(this,&Series::seenChanged,this,&Series::seenRatioChanged);
    loadLocallyOrRemotely(Controller::cachePath+"/"+mName+"_small.xml",QUrl("http://thetvdb.com/api/GetSeries.php?seriesname="+mName),std::bind(&Series::beginLoadingSeries,this,std::placeholders::_1));
}

void Series::beginLoadingSeries(QString xmlContent)
{
    QDomDocument doc;
    doc.setContent(xmlContent);
    QDomElement root = doc.documentElement();
    root = root.firstChildElement();
    root = root.firstChildElement();
    root = root.nextSiblingElement();
    while(!root.isNull())
    {
        if(root.tagName() == "banner") mBanner="http://thetvdb.com/banners/"+root.text();
        else if(root.tagName() == "id") mId=root.text();
        else if(root.tagName() == "SeriesName") setName(root.text());
        else if(root.tagName() == "Overview") setOverview(root.text());
        else if(root.tagName()=="FirstAired") mFirstAired=QDate::fromString(root.text(),"yyyy-MM-dd");
        else if(root.tagName()=="Network") mNetwork=root.text();
        root = root.nextSiblingElement();
    }
    loadLocallyOrRemotely(Controller::cachePath+"/"+mId+".xml",QUrl("http://thetvdb.com/api/CDD6BACEDE53AF9F/series/"+mId+"/all/en.xml"),std::bind(&Series::loadSeries,this,std::placeholders::_1));
}

void Series::setName(QString name)
{
    mName=name;
    emit nameChanged();
}

void Series::setOverview(QString overview)
{
    mOverview=overview;
    emit overviewChanged();
}


void Series::setPoster(QUrl poster)
{
    mPoster=poster;
    emit posterChanged();
}

void Series::loadLocallyOrRemotely(QString localFileName,QUrl remoteUrl,std::function<void(QString)> load)
{
    QFile xmlFile(localFileName);
    if(!xmlFile.exists())
    {
        xmlFile.close();
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        connect(manager, &QNetworkAccessManager::finished,[this,localFileName,load](QNetworkReply* reply){
            QString xmlContent=reply->readAll();
            QFile xmlFile(localFileName);
            xmlFile.open(QIODevice::WriteOnly|QIODevice::Text);
            QTextStream out(&xmlFile);
            out <<xmlContent;
            xmlFile.close();
            load(xmlContent);
        });
        manager->get(QNetworkRequest(remoteUrl));
    }
    else
    {
        xmlFile.open(QIODevice::ReadOnly|QIODevice::Text);
        load(xmlFile.readAll());
        xmlFile.close();
    }
}

void Series::loadBanners(QString xmlFileContent)
{
    QDomDocument doc;
    doc.setContent(xmlFileContent);
    QDomElement root = doc.documentElement();
    root = root.firstChildElement();
    while(!root.isNull())
    {
        if(root.tagName() == "Banner")
        {
            QDomElement bannerElement=root.firstChildElement();
            QString bannerType;
            QString bannerType2;
            QString bannerPath;
            QString language;
            QString thumbnailPath;
            int seasonNumber;
            while(!bannerElement.isNull())
            {
                if(bannerElement.tagName()=="BannerType") bannerType=bannerElement.text();
                else if(bannerElement.tagName()=="BannerType2") bannerType2=bannerElement.text();
                else if(bannerElement.tagName()=="BannerPath") bannerPath=bannerElement.text();
                else if(bannerElement.tagName()=="ThumbnailPath") thumbnailPath=bannerElement.text();
                else if(bannerElement.tagName()=="Season") seasonNumber=bannerElement.text().toInt();
                else if(bannerElement.tagName()=="Language") language=bannerElement.text();
                bannerElement=bannerElement.nextSiblingElement();
            }
            if(language=="en")
            {
                if(bannerType=="poster")
                {
                    if(!mPoster.isValid()) setPoster(QUrl("http://thetvdb.com/banners/"+bannerPath));
                    mPosters.append(QUrl("http://thetvdb.com/banners/"+bannerPath));
                }
                else if(bannerType=="season")
                {
                    Season * season=findSeason(seasonNumber);
                    if(bannerType2=="seasonwide") season->setBanner(QUrl("http://thetvdb.com/banners/"+bannerPath));
                    else if(bannerType2=="season") season->setPoster(QUrl("http://thetvdb.com/banners/"+bannerPath));
                }
                else if(bannerType=="fanart") mFanArts.append(QUrl("http://thetvdb.com/banners/"+thumbnailPath));
            }
        }
        root = root.nextSiblingElement();
    }
}

void Series::loadSeries(QString xmlFileContent)
{
    QDomDocument doc;
    doc.setContent(xmlFileContent);
    QDomElement root = doc.documentElement();
    root = root.firstChildElement();
    Season * currentSeason=nullptr;
    while(!root.isNull())
    {
        if(root.tagName() == "Episode")
        {
            QDomElement episodeElement=root.firstChildElement();
            QString seasonNumber;
            QString episodeNumber;
            QString episodeName;
            QString episodeOverview;
            QString episodeBanner;
            QString firstAired;
            while(!episodeElement.isNull())
            {
                if(episodeElement.tagName()=="Combined_season") seasonNumber=episodeElement.text();
                else if(episodeElement.tagName()=="EpisodeNumber") episodeNumber=episodeElement.text();
                else if(episodeElement.tagName()=="EpisodeName") episodeName=episodeElement.text();
                else if(episodeElement.tagName()=="Overview") episodeOverview=episodeElement.text();
                else if(episodeElement.tagName()=="filename") episodeBanner=episodeElement.text();
                else if(episodeElement.tagName()=="FirstAired") firstAired=episodeElement.text();
                episodeElement=episodeElement.nextSiblingElement();
            }
            currentSeason=findSeason(seasonNumber.toInt());
            if(currentSeason==nullptr)
            {
                currentSeason=new Season(seasonNumber.toInt(),banner(),QUrl());
                addSeason(currentSeason);
            }
            currentSeason->addEpisode(new Episode(episodeNumber.toInt(),episodeName,episodeOverview,QUrl(episodeBanner=="" ? currentSeason->banner() : "http://thetvdb.com/banners/"+episodeBanner),QDate::fromString(firstAired,"yyyy-MM-dd")));
        }
        root = root.nextSiblingElement();
    }
    loadLocallyOrRemotely(Controller::cachePath+"/"+mId+"_banners.xml",QUrl("http://thetvdb.com/api/CDD6BACEDE53AF9F/series/"+mId+"/banners.xml"),std::bind(&Series::loadBanners,this,std::placeholders::_1));
    loadSeriesSeenFile();
}


Season* Series::findSeason(int seasonNumber)
{
    auto seasonIt=std::find_if(mSeasons.begin(),mSeasons.end(),[seasonNumber](Season* season){return season->number()==seasonNumber;});
    if(seasonIt==mSeasons.end()) return nullptr;
    return *seasonIt;
}


void Series::loadSeriesSeenFile()
{
    QString fileName=Controller::filesPath+"/"+mId+"_seen.xml";
    QFile seriesSeenFile(fileName);
    if(seriesSeenFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString xmlFileContent=seriesSeenFile.readAll();
        seriesSeenFile.close();

        QDomDocument doc;
        doc.setContent(xmlFileContent);
        QDomElement root = doc.documentElement();
        root = root.firstChildElement();
        while(!root.isNull())
        {
            if(root.tagName() == "Season")
            {
                QString seasonNumber=root.attribute("number");
                Season * currentSeason=findSeason(seasonNumber.toInt());
                QDomElement episodeElement=root.firstChildElement();
                while(!episodeElement.isNull())
                {
                    if(episodeElement.tagName()=="Episode")
                    {
                        QString seen;
                        QString episodeNumber=episodeElement.attribute("number");
                        Episode* currentEpisode=currentSeason->findEpisode(episodeNumber.toInt());
                        seen=episodeElement.text();
                        currentEpisode->setSeen(seen=="Seen");
                        episodeElement=episodeElement.nextSiblingElement();
                    }
                }
            }
            root = root.nextSiblingElement();
        }
    }
    else emit seenChanged();
    connect(this,&Series::seenChanged,this,&Series::saveSeriesSeenFile);
}

void Series::saveSeriesSeenFile()
{
    QDomDocument doc("seriesSeen");
    QDomElement root = doc.createElement("Series");
    doc.appendChild(root);

    for(Season* season : mSeasons)
    {
        QDomElement tag = doc.createElement("Season");
        tag.setAttribute("number",season->number());
        root.appendChild(tag);

        for(Episode* episode : *(season->episodes()))
        {
            QDomElement tag2 = doc.createElement("Episode");
            tag2.setAttribute("number",episode->number());
            tag.appendChild(tag2);

            QDomText t = doc.createTextNode(episode->seen() ? "Seen" : "NotSeen");
            tag2.appendChild(t);
        }
    }

    QString xmlContent = doc.toString();


    QString fileName=Controller::filesPath+"/"+mId+"_seen.xml";
    QFile seriesSeenFile(fileName);
    seriesSeenFile.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&seriesSeenFile);
    out<<xmlContent;
    seriesSeenFile.close();
}

void Series::addSeason(Season * season)
{
    int insertionIndex=mSeasons.append(season);
    connect(season,&Season::seenChanged,[insertionIndex,this](){emit mSeasons.dataChanged(insertionIndex,insertionIndex);});
    connect(season,&Season::seenChanged,this,&Series::seenChanged);
    emit seasonCountChanged();
}


Season * Series::getSeason(int row) const
{
    return mSeasons.get(row);
}


bool Series::seen() const
{
    for(Season * season : mSeasons) if(!season->seen()) return false;
    return true;
}

int Series::episodeSeenCount() const
{
    return std::accumulate(mSeasons.begin(),mSeasons.end(),0,[](int acc,Season* season){return acc+season->episodeSeenCount();});
}

int Series::episodeCount() const
{
    return std::accumulate(mSeasons.begin(),mSeasons.end(),0,[](int acc,Season* season){return acc+season->episodeCount();});
}

double Series::seenRatio() const
{
    return double(episodeSeenCount())/double(episodeCount());
}

void Series::setSeen(bool seen)
{
    for(Season * season : mSeasons)
    {
        disconnect(season,&Season::seenChanged,this,&Series::seenChanged);
        season->setSeen(seen);
        connect(season,&Season::seenChanged,this,&Series::seenChanged);
    }
    emit seenChanged();
}

SignalList<Season *> *Series::seasons()
{
    return &mSeasons;
}

QString Series::overview() const
{
    return mOverview;
}

QAbstractItemModel *Series::fanArts()
{
    return new SignalListAdapter<QUrl>(&mFanArts,"fanArt");
}


QAbstractItemModel * Series::posters()
{
    return new SignalListAdapter<QUrl>(&mPosters,"poster");
}

QString Series::name() const
{
    return mName;
}

QUrl Series::banner() const
{
    return mBanner;
}


QUrl Series::poster() const
{
    return mPoster;
}


int Series::seasonCount() const
{
   return mSeasons.size();
}


QDate Series::firstAired() const
{
    return mFirstAired;
}

QString Series::network() const
{
    return mNetwork;
}


QAbstractItemModel * Series::seriesModel()
{
    return seriesModelT();
}


QAbstractItemModel * Series::seriesUpcomingModel()
{
    SignalListFilter<Season*> * filter=new SignalListFilter<Season*>();
    filter->setFilter([](Season* season){return !season->seen();});
    filter->setSourceModel(seriesModelT());
    return filter;
}


SignalListAdapter<Season*> * Series::seriesModelT()
{
    return new SignalListAdapter<Season*>(&mSeasons,"season");
}
