#include <numeric>

#include "season.h"
#include "adapter/signallistfilter.h"



Season::Season(int number, Image *banner, Image *poster, Series *parent) :
    QObject((QObject*)parent),mNumber(number),mBanner(banner),mPoster(poster),mSeries(parent)
{
    connect(this,&Season::seenChanged,this,&Season::seenRatioChanged);
    connect(this,&Season::seenChanged,this,&Season::episodeSeenCountChanged);
}


void Season::addEpisode(Episode * episode)
{
    mEpisodes.append(episode);
    connect(episode,&Episode::seenChanged,this,&Season::seenChanged);
    connect(episode,&Episode::seenChanged,[episode,this](){emit mEpisodes.elementChanged(episode);});
}


Series * Season::series() const
{
    return mSeries;
}


void Season::setBanner(Image *banner)
{
    mBanner=banner;
    emit bannerChanged();
}


QAbstractItemModel *Season::seasonModel()
{
    return seasonModelT();
}


QAbstractItemModel *Season::seasonUpcomingModel()
{
    SignalListFilter<Episode*> * filter=new SignalListFilter<Episode*>();
    filter->setFilter([](Episode* episode){return !episode->seen();});
    filter->setSourceModel(seasonModelT());
    return filter;
}

SignalListAdapter<Episode *> *Season::seasonModelT()
{
    return  new SignalListAdapter<Episode*>(episodes(),"episode");
}


Episode* Season::findEpisode(int episodeNumber)
{
    auto episodeIt=std::find_if(mEpisodes.begin(),mEpisodes.end(),[episodeNumber](Episode* episode){return episode->number()==episodeNumber;});
    if(episodeIt==mEpisodes.end()) return nullptr;
    return *episodeIt;
}


void Season::setPoster(Image *poster)
{
    mPoster=poster;
    emit posterChanged();
}

Episode * Season::getEpisode(int row) const
{
    return mEpisodes.get(row);
}

SignalList<Episode *> *Season::episodes()
{
    return &mEpisodes;
}

int Season::number() const
{
    return mNumber;
}

Image *Season::banner() const
{
    return mBanner;
}

Image *Season::poster() const
{
    return mPoster;
}


QDate Season::firstAired() const
{
    Episode * firstEpisode=*(std::min_element(mEpisodes.begin(),mEpisodes.end(),[](Episode *const& a,Episode * const& b)
    {
        if(!(a->firstAired().isValid())) return false;
        if(!(b->firstAired().isValid())) return true;
        return a->firstAired()<b->firstAired();
    }));
    return firstEpisode->firstAired();
}

int Season::episodeSeenCount() const
{
    return std::accumulate(mEpisodes.begin(),mEpisodes.end(),0,[](int acc,Episode* episode){return acc+episode->seen();});
}

int Season::episodeAiredCount() const
{
    return std::accumulate(mEpisodes.begin(),mEpisodes.end(),0,[](int acc,Episode* episode){return acc+episode->aired();});
}

int Season::episodeCount() const
{
    return mEpisodes.size();
}

double Season::seenRatio() const
{
    return double(episodeSeenCount())/double(episodeCount());
}

double Season::airedRatio() const
{
    return double(episodeAiredCount())/double(episodeCount());
}

bool Season::seen() const
{
    for(Episode * episode : mEpisodes) if(!episode->seen()) return false;
    return true;
}


void Season::setSeen(bool seen)
{
    for(Episode * episode : mEpisodes)
    {
        disconnect(episode,&Episode::seenChanged,this,&Season::seenChanged);
        episode->setSeen(seen);
        connect(episode,&Episode::seenChanged,this,&Season::seenChanged);
    }
    emit seenChanged();
}
