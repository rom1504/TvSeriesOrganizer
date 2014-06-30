#include "serieslistlist.h"

SeriesListList::SeriesListList(TraktTvAPI * traktTvAPI, QObject *parent) :
    QObject(parent),
    mTraktTvAPI(traktTvAPI)
{
    mTraktTvAPI->loadSeriesListList(&mSeriesListList);
}

QAbstractItemModel * SeriesListList::seriesListListModel()
{
    return new SignalListAdapter<SeriesList*>(&mSeriesListList,"seriesList");
}
