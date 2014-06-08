#ifndef TRAKTTVAPI_H
#define TRAKTTVAPI_H

#include <QObject>
#include "model/signallist.h"
#include "model/serieslist.h"

class TraktTvAPI : public QObject
{
    Q_OBJECT
public:
    // server="http://api.trakt.tv", APIKey="f9201fd7c6183a624a27ccba01555310" can be used
    explicit TraktTvAPI(QString cachePath, SeriesList *alreadyAddedSeriesList, QString server, QString APIKey,TheTvDBAPI * theTVDBAPI, DiskCache * diskCache, QObject *parent);

    void loadSeriesListList(SignalList<SeriesList*>* seriesListList,std::function<void(void)> callback=[](){});

signals:

public slots:

private:
    QString mCachePath;
    QString mServer;
    QString mAPIKey;
    SeriesList* mAlreadyAddedSeriesList;
    DiskCache * mDiskCache;
    TheTvDBAPI * mTheTVDBAPI;
};

#endif // TRAKTTVAPI_H
