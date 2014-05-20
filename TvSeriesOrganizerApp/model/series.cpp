#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDomDocument>
#include <QFile>
#include <functional>
#include <QCoreApplication>
#include <numeric>

#include "series.h"
#include "controller/controller.h"
#include "adapter/signallistfilter.h"

// http://thetvdb.com/wiki/index.php/Multi_Language
QSet<QString> Series::mTheTvDBSupportedLanguages={"en","sv","no","da","fi","nl","de","it","es","fr","pl","hu","el","tr","ru","he"
                                                 ,"ja","pt","zh","cs","sl","hr","ko"};


Series::Series(QObject *parent) : QObject(parent),mPoster(nullptr),mBanner(nullptr),mSeasons([](Season* a,Season* b){
    if(a->number()==0) return false;
    if(b->number()==0) return true;
    return a->number()<b->number();
})
{
    connect(this,&Series::seenChanged,this,&Series::seenRatioChanged);
}


Series::Series(int id, QObject *parent) : Series(parent)
{
    mId=id;
    complete();
}

Series::Series(const QDomElement & element, QObject*parent) : Series(parent)
{
    QDomElement root = element.firstChildElement();
    while(!root.isNull())
    {
        if(root.tagName() == "banner") mBanner=new Image(root.text());
        else if(root.tagName() == "id") mId=root.text().toInt();
        else if(root.tagName() == "SeriesName") setName(root.text());
        else if(root.tagName() == "Overview") setOverview(root.text());
        else if(root.tagName()=="FirstAired") mFirstAired=QDate::fromString(root.text(),"yyyy-MM-dd");
        else if(root.tagName()=="Network") mNetwork=root.text();
        root = root.nextSiblingElement();
    }//check here
    mPoster=new Image("posters/"+QString::number(mId)+"-1.jpg");
}

bool Series::isAThetvdbSupportedLanguages(QString language)
{
    return mTheTvDBSupportedLanguages.contains(language);
}

QString Series::currentTheTvDBLanguage()
{
    QString language=QLocale().bcp47Name();
    return isAThetvdbSupportedLanguages(language) ? language : "en";
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
                if(seriesElement.tagName() == "banner") mBanner=new Image(seriesElement.text());
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
                currentSeason=new Season(seasonNumber.toInt(),banner(),nullptr,this);
                addSeason(currentSeason);
            }
            currentSeason->addEpisode(new Episode(episodeNumber.toInt(),episodeName,episodeOverview,episodeBanner=="" ? currentSeason->banner() : new Image(episodeBanner),QDate::fromString(firstAired,"yyyy-MM-dd"),currentSeason));
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
    loadLocallyOrRemotely(Controller::cachePath+"/"+QString::number(mId)+currentTheTvDBLanguage()+".xml",QUrl("http://thetvdb.com/api/CDD6BACEDE53AF9F/series/"+QString::number(mId)+"/all/"+currentTheTvDBLanguage()+".xml"),std::bind(&Series::loadSeries,this,std::placeholders::_1));
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


QAbstractItemModel * Series::actorListModel()
{
    return mActorList.actorListModel();
}


void Series::setPoster(Image* poster)
{
    mPoster=poster;
    emit posterChanged();
}

void Series::loadLocallyOrRemotely(QString localFileName,QUrl remoteUrl,std::function<void(QString)> load,int numberOfDaysBeforeDownloadingAgain)
{
    QFile xmlFile(localFileName);
    if(!xmlFile.exists() || (numberOfDaysBeforeDownloadingAgain!=-1 && QFileInfo(xmlFile).lastModified().daysTo(QDateTime::currentDateTime())>=numberOfDaysBeforeDownloadingAgain))
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
    mPoster=nullptr;
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
            if(language=="en" || language==currentTheTvDBLanguage())
            {
                if(bannerType=="poster")
                {
                    Image * poster=new Image(bannerPath);
                    if(mPoster==nullptr) setPoster(poster);
                    mPosters.append(poster);
                }
                else if(bannerType=="season")
                {
                    Season * season=findSeason(seasonNumber);
                    if(season!=nullptr)
                    {
                        if(bannerType2=="seasonwide") season->setBanner(new Image(bannerPath));
                        else if(bannerType2=="season") season->setPoster(new Image(bannerPath));
                    }
                }
                else if(bannerType=="fanart") mFanArts.append(new Image("http://thetvdb.com/banners/"+thumbnailPath,"http://thetvdb.com/banners/"+bannerPath));
            }
        }
        root = root.nextSiblingElement();
    }

    loadLocallyOrRemotely(Controller::cachePath+"/"+QString::number(mId)+"_actors.xml",QUrl("http://thetvdb.com/api/CDD6BACEDE53AF9F/series/"+QString::number(mId)+"/actors.xml"),std::bind(&Series::loadActors,this,std::placeholders::_1));
}


void Series::loadActors(QString xmlFileContent)
{
    mActorList.loadActorList(xmlFileContent);
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
    mSeasons.append(season);
    connect(season,&Season::seenChanged,[this,season](){if(season->seen()) mSeasons.elementChanged(season);});
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

void Series::setId(int id)
{
    mId=id;
}


void Series::setBanner(Image *banner)
{
    mBanner=banner;
    emit bannerChanged();
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
    return new SignalListAdapter<Image*>(&mFanArts,"fanArt");
}


QAbstractItemModel * Series::posters()
{
    return new SignalListAdapter<Image*>(&mPosters,"poster");
}

QString Series::name() const
{
    return mName;
}

Image * Series::banner() const
{
    return mBanner;
}


Image * Series::poster() const
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
