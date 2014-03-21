#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDomDocument>
#include <QFile>
#include <functional>
#include <QCoreApplication>

#include "series.h"
#include "controller/controller.h"
#include "adapter/signallistfilter.h"



Series::Series(int id, QObject *parent) : QObject(parent),mSeasons([](Season* a,Season* b){
    if(a->number()==0) return false;
    if(b->number()==0) return true;
    return a->number()<b->number();
}),mId(id)
{
    connect(this,&Series::seenChanged,this,&Series::seenRatioChanged);
    complete();
}

Series::Series(const QDomElement & element, QObject*parent) : QObject(parent),mSeasons([](Season* a,Season* b){
    if(a->number()==0) return false;
    if(b->number()==0) return true;
    return a->number()<b->number();
})
{
    QDomElement root = element.firstChildElement();
    while(!root.isNull())
    {
        if(root.tagName() == "banner") mBanner="http://thetvdb.com/banners/_cache/"+root.text();
        else if(root.tagName() == "id") mId=root.text().toInt();
        else if(root.tagName() == "SeriesName") setName(root.text());
        else if(root.tagName() == "Overview") setOverview(root.text());
        else if(root.tagName()=="FirstAired") mFirstAired=QDate::fromString(root.text(),"yyyy-MM-dd");
        else if(root.tagName()=="Network") mNetwork=root.text();
        root = root.nextSiblingElement();
    }
    mPoster="http://thetvdb.com/banners/_cache/posters/"+QString::number(mId)+"-1.jpg";
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
        if(root.tagName() == "Series")
        {
            QDomElement seriesElement=root.firstChildElement();
            while(!seriesElement.isNull())
            {
                if(seriesElement.tagName() == "banner") mBanner="http://thetvdb.com/banners/_cache/"+seriesElement.text();
                else if(seriesElement.tagName() == "SeriesName") setName(seriesElement.text());
                else if(seriesElement.tagName() == "Overview") setOverview(seriesElement.text());
                else if(seriesElement.tagName()=="FirstAired") mFirstAired=QDate::fromString(seriesElement.text(),"yyyy-MM-dd");
                else if(seriesElement.tagName()=="Network") mNetwork=seriesElement.text();
                seriesElement=seriesElement.nextSiblingElement();
            }
        }
        else if(root.tagName() == "Episode")
        {
            QDomElement episodeElement=root.firstChildElement();
            QString seasonNumber="-1";
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
                Q_ASSERT(seasonNumber!="-1");
                currentSeason=new Season(seasonNumber.toInt(),banner(),QUrl(),this);
                addSeason(currentSeason);
            }
            currentSeason->addEpisode(new Episode(episodeNumber.toInt(),episodeName,episodeOverview,QUrl(episodeBanner=="" ? currentSeason->banner() : "http://thetvdb.com/banners/"+episodeBanner),QDate::fromString(firstAired,"yyyy-MM-dd"),currentSeason));
        }
        root = root.nextSiblingElement();
    }
    loadSeriesSeenFile();
    loadLocallyOrRemotely(Controller::cachePath+"/"+QString::number(mId)+"_banners.xml",QUrl("http://thetvdb.com/api/CDD6BACEDE53AF9F/series/"+QString::number(mId)+"/banners.xml"),std::bind(&Series::loadBanners,this,std::placeholders::_1));
}


int Series::id() const
{
    return mId;
}

void Series::complete()
{
    loadLocallyOrRemotely(Controller::cachePath+"/"+QString::number(mId)+QLocale().bcp47Name()+".xml",QUrl("http://thetvdb.com/api/CDD6BACEDE53AF9F/series/"+QString::number(mId)+"/all/"+QLocale().bcp47Name()+".xml"),std::bind(&Series::loadSeries,this,std::placeholders::_1));
}

void Series::setName(QString name)
{
    mName=name;
    emit nameChanged();
}

void Series::setOverview(QString overview)
{
    mOverview=overview;
    mShortOverview=mOverview.left(500)+(mOverview.size()>500 ? "..." : "");
    emit shortOverviewChanged();
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
        QNetworkAccessManager *manager = new QNetworkAccessManager();
        connect(manager, &QNetworkAccessManager::finished,[localFileName,load](QNetworkReply* reply){
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
    mPoster=QUrl();
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
            if(language=="en" || language==QLocale().bcp47Name())
            {
                if(bannerType=="poster")
                {
                    if(!mPoster.isValid()) setPoster(QUrl("http://thetvdb.com/banners/_cache/"+bannerPath));
                    mPosters.append(QUrl("http://thetvdb.com/banners/_cache/"+bannerPath));
                }
                else if(bannerType=="season")
                {
                    Season * season=findSeason(seasonNumber);
                    if(season!=nullptr)
                    {
                        if(bannerType2=="seasonwide") season->setBanner(QUrl("http://thetvdb.com/banners/_cache/"+bannerPath));
                        else if(bannerType2=="season") season->setPoster(QUrl("http://thetvdb.com/banners/_cache/"+bannerPath));
                    }
                }
                else if(bannerType=="fanart") mFanArts.append(QUrl("http://thetvdb.com/banners/"+thumbnailPath));
            }
        }
        root = root.nextSiblingElement();
    }
    emit completed();
}




Season* Series::findSeason(int seasonNumber)
{
    auto seasonIt=std::find_if(mSeasons.begin(),mSeasons.end(),[seasonNumber](Season* season){return season->number()==seasonNumber;});
    if(seasonIt==mSeasons.end()) return nullptr;
    return *seasonIt;
}


void Series::loadSeriesSeenFile()
{
    QString fileName=Controller::dataPath+"/"+QString::number(mId)+"_seen.xml";
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


    QString fileName=Controller::dataPath+"/"+QString::number(mId)+"_seen.xml";
    QFile seriesSeenFile(fileName);
    seriesSeenFile.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&seriesSeenFile);
    out<<xmlContent;
    seriesSeenFile.close();
}

void Series::addSeason(Season * season)
{
    int insertionIndex=mSeasons.append(season);
    connect(season,&Season::seenChanged,[insertionIndex,this,season](){if(season->seen()) emit mSeasons.dataChanged(insertionIndex,insertionIndex);});
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

QString Series::shortOverview() const
{
    return mShortOverview;
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
