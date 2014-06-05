#ifndef TRAKTTVAPI_H
#define TRAKTTVAPI_H

#include <QObject>
#include "model/signallist.h"
#include "model/serieslist.h"

class TraktTvAPI : public QObject
{
    Q_OBJECT
public:
    explicit TraktTvAPI(QString cachePath, SeriesList *alreadyAddedSeriesList, QString server="http://api.trakt.tv", QString APIKey="f9201fd7c6183a624a27ccba01555310", QObject *parent = 0);

    void loadSeriesListList(SignalList<SeriesList*>* seriesListList,std::function<void(void)> callback=[](){});

signals:

public slots:

private:
    QString mCachePath;
    QString mServer;
    QString mAPIKey;
    SeriesList* mAlreadyAddedSeriesList;// à fin

};

#endif // TRAKTTVAPI_H
