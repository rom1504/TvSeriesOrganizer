#include "controller/controller.h"
#include "serieslistlist.h"

SeriesListList::SeriesListList(SeriesList *alreadyAddedSeriesList, QObject *parent) :
    QObject(parent),
    mTraktTvAPI(new TraktTvAPI(Controller::cachePath,alreadyAddedSeriesList,"http://api.trakt.tv","f9201fd7c6183a624a27ccba01555310",this))
{
    mTraktTvAPI->loadSeriesListList(&mSeriesListList);
}

QAbstractItemModel * SeriesListList::seriesListListModel()
{
    return new SignalListAdapter<SeriesList*>(&mSeriesListList,"seriesList");
}
