#ifndef SERIESLISTLIST_H
#define SERIESLISTLIST_H

#include <QObject>
#include <QAbstractItemModel>
#include "model/serieslist.h"
#include "model/signallist.h"
#include "model/API/trakttvapi.h"

class SeriesListList : public QObject
{
    Q_OBJECT

public:
    explicit SeriesListList(SeriesList* alreadyAddedSeriesList,QObject *parent);

signals:

public slots:
    QAbstractItemModel * seriesListListModel();

private:
    SignalList<SeriesList*> mSeriesListList;
    TraktTvAPI * mTraktTvAPI;
};

#endif // SERIESLISTLIST_H
