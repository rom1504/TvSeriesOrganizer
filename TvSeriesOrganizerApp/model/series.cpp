#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>

#include "series.h"



Series::Series(QString name, QUrl banner, QObject *parent) :
    QObject(parent),mName(name),mBanner(banner)
{
}

Series::Series(QString name, QObject *parent) : QObject(parent),mName(name)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,[this](QNetworkReply* reply){
        QString xmlContent=reply->readAll();
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
            root = root.nextSiblingElement();
        }
        loadFullSeries();
    });
    manager->get(QNetworkRequest(QUrl("http://thetvdb.com/api/GetSeries.php?seriesname="+mName)));

}


void Series::loadFullSeries()
{
    QFile xmlFile(mId+".xml");
    if(!xmlFile.exists())
    {
        xmlFile.close();
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        connect(manager, &QNetworkAccessManager::finished,[this](QNetworkReply* reply){
            QString xmlContent=reply->readAll();
            QFile xmlFile(mId+".xml");
            xmlFile.open(QIODevice::WriteOnly|QIODevice::Text);
            QTextStream out(&xmlFile);
            out <<xmlContent;
            xmlFile.close();
            loadSeries(xmlContent);
        });
        manager->get(QNetworkRequest(QUrl("http://thetvdb.com/api/CDD6BACEDE53AF9F/series/"+mId+"/all/en.xml")));
    }
    else
    {
        xmlFile.open(QIODevice::ReadOnly|QIODevice::Text);
        loadSeries(xmlFile.readAll());
        xmlFile.close();
    }
}


void Series::loadSeries(QString xmlFileContent)
{
    QDomDocument doc;
    doc.setContent(xmlFileContent);
    QDomElement root = doc.documentElement();
    root = root.firstChildElement();
    QString currentSeasonNumber="";
    Season * currentSeason;
    while(!root.isNull())
    {
        if(root.tagName() == "Episode")
        {
            QDomElement episodeElement=root.firstChildElement();
            QString seasonNumber;
            QString episodeNumber;
            QString episodeName;
            QString episodeDescription;
            QString episodeBanner;
            while(!episodeElement.isNull())
            {
                if(episodeElement.tagName()=="Combined_season") seasonNumber=episodeElement.text();
                else if(episodeElement.tagName()=="EpisodeNumber") episodeNumber=episodeElement.text();
                else if(episodeElement.tagName()=="EpisodeName") episodeName=episodeElement.text();
                else if(episodeElement.tagName()=="Overview") episodeDescription=episodeElement.text();
                else if(episodeElement.tagName()=="filename") episodeBanner=episodeElement.text();
                episodeElement=episodeElement.nextSiblingElement();
            }
            if(seasonNumber!=currentSeasonNumber)
            {
                currentSeasonNumber=seasonNumber;
                currentSeason=new Season(currentSeasonNumber.toInt(),QUrl("qrc:/images/season.jpg"));
                addSeason(currentSeason);
            }
            currentSeason->addEpisode(new Episode(episodeNumber.toInt(),episodeName,episodeDescription,QUrl(episodeBanner=="" ? "qrc:/images/episode.jpg" : "http://thetvdb.com/banners/"+episodeBanner)));
        }
        root = root.nextSiblingElement();
    }
}

void Series::addSeason(Season * season)
{
    mSeasons.append(season);
}


Season * Series::getSeason(int row) const
{
    return mSeasons.get(row);
}

SignalList<Season *> & Series::seasons()
{
    return mSeasons;
}
QString Series::name() const
{
    return mName;
}

QUrl Series::banner() const
{
    return mBanner;
}
