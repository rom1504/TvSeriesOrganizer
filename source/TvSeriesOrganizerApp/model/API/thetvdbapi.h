#ifndef THETVDBAPI_H
#define THETVDBAPI_H

#include <QObject>

#include "../series.h"
#include "../diskcache.h"


class TheTvDBAPI : public QObject
{
    Q_OBJECT
public:
    // server="http://thetvdb.com", APIKey="CDD6BACEDE53AF9F" can be used
    explicit TheTvDBAPI(QString cachePath, QString server, QString APIKey,QNetworkAccessManager * networkAccessManager, DiskCache * diskCache, QObject *parent);

    void loadSeries(Series* series,std::function<void(void)> almostLoaded,std::function<void(void)> loaded);
    void loadSeries(int id, QObject * parent,std::function<void(void)> almostLoaded,std::function<void(void)> loaded);
    void searchSeries(QString seriesName, std::function<void(SignalList<Series *>*)> callback);
    void liveSearchSeries(QString beginSeriesName, std::function<void(QStringList*)> callback);
    static bool isAThetvdbSupportedLanguages(QString language);
    static QString currentTheTvDBLanguage();

    void updateCache(std::function<void(void)> finishedUpdating);

private:
    qint64 getTimeOfLastUpdate();
    QString getUpdatePeriod(qint64 timeOfLastUpdate);
    void writeLastTimeOfUpdate();
    void eraseUnvalidatedCacheFiles(QString updatePeriod, qint64 timeOfLastUpdate, std::function<void(void)> finishedUpdating);


    void loadBanners(Series * series, std::function<void(void)> loaded);
    void loadActors(Series * series,std::function<void(void)> loaded);
    QMap<QString,QString>* getFields(QXmlStreamReader & xml,QString containerElementName,QSet<QString>& wantedFields);
    QString getField(QXmlStreamReader & xml,QString containerElementName,QString field);


signals:

public slots:

private:
    QString mServer;
    QString mCachePath;
    QString mAPIKey;
    QString mLastAutocompletion;
    QNetworkAccessManager * mNetworkAccessManager;
    DiskCache * mDiskCache;

private:
    static QSet<QString> mTheTvDBSupportedLanguages;

};

#endif // THETVDBAPI_H
