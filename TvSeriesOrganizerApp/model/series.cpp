#include <QFile>
#include <functional>
#include <QCoreApplication>
#include <numeric>

#include "series.h"
#include "adapter/signallistfilter.h"

QString Series::dataPath;

Series::Series(QObject *parent) : QObject(parent),mPoster(nullptr),mBanner(nullptr),mSeasons([](Season* a,Season* b){
    if(a->number()==0) return false;
    if(b->number()==0) return true;
    return a->number()<b->number();
}),mActorList([](Actor* a,Actor* b){return a->sortOrder()<b->sortOrder();})
{
    connect(this,&Series::seenChanged,this,&Series::seenRatioChanged);
}


Series::Series(int id, QObject *parent) : Series(parent)
{
    mId=id;
}

int Series::id() const
{
    return mId;
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


void Series::setFirstAired(QDate firstAired)
{
    mFirstAired=firstAired;
    emit firstAiredChanged();
}

void Series::setNetwork(QString network)
{
    mNetwork=network;
    emit networkChanged();
}

QAbstractItemModel * Series::actorListModel()
{
    return new SignalListAdapter<Actor*>(&mActorList,"actor");
}


void Series::setPoster(Image* poster)
{
    mPoster=poster;
    emit posterChanged();
}

void Series::addPoster(Image* poster)
{
    mPosters.append(poster);
}

void Series::addFanArt(Image* fanArt)
{
    mFanArts.append(fanArt);
}


void Series::addActor(Actor* actor)
{
    mActorList.append(actor);
}

Season* Series::findSeason(int seasonNumber)
{
    auto seasonIt=std::find_if(mSeasons.begin(),mSeasons.end(),[seasonNumber](Season* season){return season->number()==seasonNumber;});
    if(seasonIt==mSeasons.end()) return nullptr;
    return *seasonIt;
}


void Series::loadSeriesSeenFile()
{
    QString fileName=dataPath+"/"+QString::number(mId)+"_seen.xml";
    QFile seriesSeenFile(fileName);
    if(seriesSeenFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString xmlFileContent=seriesSeenFile.readAll();
        seriesSeenFile.close();

        QXmlStreamReader xml(xmlFileContent);
        while(!xml.atEnd())
        {
            xml.readNext();
            if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Season")
            {
                QString seasonNumber=xml.attributes().value("number").toString();

                Season * currentSeason=findSeason(seasonNumber.toInt());
                if(currentSeason==nullptr) {qDebug()<<"nonexistent season seen : series "+QString::number(mId)+" season "+seasonNumber;continue;}
                while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Season"))
                {
                    xml.readNext();
                    if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Episode")
                    {
                        QString seen;
                        QString episodeNumber=xml.attributes().value("number").toString();
                        Episode* currentEpisode=currentSeason->findEpisode(episodeNumber.toInt());
                        if(currentEpisode==nullptr) {qDebug()<<"nonexistent episode seen : series "+QString::number(mId)+" season "+seasonNumber+" episode "+episodeNumber;continue;}
                        seen=xml.readElementText();
                        currentEpisode->setSeen(seen=="Seen");
                    }
                }
            }
        }
    }
    else emit seenChanged();
    connect(this,&Series::seenChanged,this,&Series::saveSeriesSeenFile);
}

void Series::saveSeriesSeenFile()
{
    QString fileName=dataPath+"/"+QString::number(mId)+"_seen.xml";
    QFile seriesSeenFile(fileName);
    seriesSeenFile.open(QIODevice::WriteOnly|QIODevice::Text);
    QXmlStreamWriter stream(&seriesSeenFile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("Series");
    for(Season* season : mSeasons)
    {
        stream.writeStartElement("Season");
        stream.writeAttribute("number",QString::number(season->number()));
        for(Episode* episode : *(season->episodes()))
        {
            stream.writeStartElement("Episode");
            stream.writeAttribute("number",QString::number(episode->number()));
            stream.writeCharacters(episode->seen() ? "Seen" : "NotSeen");
            stream.writeEndElement();
        }
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
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
