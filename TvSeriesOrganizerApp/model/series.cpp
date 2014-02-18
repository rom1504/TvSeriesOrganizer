#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <functional>
#include <QCoreApplication>

#include "series.h"
#include "controller/controller.h"



Series::Series(QString name, QUrl banner, QObject *parent) :
    QObject(parent),mName(name),mBanner(banner)
{
}

Series::Series(QString name, QObject *parent) : QObject(parent),mName(name)
{
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
            int season;
            while(!bannerElement.isNull())
            {
                if(bannerElement.tagName()=="BannerType") bannerType=bannerElement.text();
                else if(bannerElement.tagName()=="BannerType2") bannerType2=bannerElement.text();
                else if(bannerElement.tagName()=="BannerPath") bannerPath=bannerElement.text();
                else if(bannerElement.tagName()=="Season") season=bannerElement.text().toInt();
                else if(bannerElement.tagName()=="Language") language=bannerElement.text();
                bannerElement=bannerElement.nextSiblingElement();
            }
            if(language=="en")
            {
                if(bannerType=="poster" && !mPoster.isValid()) setPoster(QUrl("http://thetvdb.com/banners/"+bannerPath));
                else if(bannerType=="season")
                {
                    auto i=std::find_if(mSeasons.constBegin(),mSeasons.constEnd(),[season](Season * a){return a->number()==season;});
                    if(bannerType2=="seasonwide") (*i)->setBanner(QUrl("http://thetvdb.com/banners/"+bannerPath));
                    else if(bannerType2=="season") (*i)->setPoster(QUrl("http://thetvdb.com/banners/"+bannerPath));
                }
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
    QString currentSeasonNumber="";
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
            if(seasonNumber!=currentSeasonNumber)
            {
                currentSeasonNumber=seasonNumber;
                currentSeason=new Season(currentSeasonNumber.toInt(),banner(),QUrl());
                addSeason(currentSeason);
            }
            currentSeason->addEpisode(new Episode(episodeNumber.toInt(),episodeName,episodeOverview,QUrl(episodeBanner=="" ? currentSeason->banner() : "http://thetvdb.com/banners/"+episodeBanner),QDate::fromString(firstAired,"yyyy-MM-dd")));
        }
        root = root.nextSiblingElement();
    }
    loadLocallyOrRemotely(Controller::cachePath+"/"+mId+"_banners.xml",QUrl("http://thetvdb.com/api/CDD6BACEDE53AF9F/series/"+mId+"/banners.xml"),std::bind(&Series::loadBanners,this,std::placeholders::_1));
}



void Series::addSeason(Season * season)
{
    mSeasons.append(season);
    emit seasonCountChanged();
}


Season * Series::getSeason(int row) const
{
    return mSeasons.get(row);
}

SignalList<Season *> *Series::seasons()
{
    return &mSeasons;
}

QString Series::overview() const
{
    return mOverview;
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

