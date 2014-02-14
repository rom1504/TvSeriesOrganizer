#include "season.h"

Season::Season(int number, QUrl banner,QUrl poster, QObject *parent) :
    QObject(parent),mNumber(number),mBanner(banner),mPoster(poster)
{
}


void Season::addEpisode(Episode * episode)
{
    mEpisodes.append(episode);
}


void Season::setBanner(QUrl banner)
{
    mBanner=banner;
    emit bannerChanged();
}


QAbstractItemModel *Season::seasonModel()
{
    return  new SignalListAdapter<Episode*>(episodes(),"episode");
}


void Season::setPoster(QUrl poster)
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

QUrl Season::banner() const
{
    return mBanner;
}

QUrl Season::poster() const
{
    return mPoster;
}
