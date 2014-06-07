#ifndef THETVDBAPI_H
#define THETVDBAPI_H

#include <QObject>

#include "../series.h"

class TheTvDBAPI : public QObject
{
    Q_OBJECT
public:
    // server="http://thetvdb.com", APIKey="CDD6BACEDE53AF9F" can be used
    explicit TheTvDBAPI(QString cachePath, QString server, QString APIKey, QObject *parent);

    void loadSeries(Series* series,std::function<void(void)> almostLoaded,std::function<void(void)> loaded);
    void loadSeries(int id, QObject * parent,std::function<void(void)> almostLoaded,std::function<void(void)> loaded);
    void searchSeries(QString seriesName, std::function<void(SignalList<Series *>*)> callback);
    void liveSearchSeries(QString beginSeriesName, std::function<void(QStringList*)> callback);
    static bool isAThetvdbSupportedLanguages(QString language);
    static QString currentTheTvDBLanguage();


private:
    void loadBanners(Series * series, std::function<void(void)> loaded);
    void loadActors(Series * series,std::function<void(void)> loaded);
    QMap<QString,QString>* getFields(QXmlStreamReader & xml,QString containerElementName,QSet<QString>& wantedFields);


signals:

public slots:

private:
    QString mServer;
    QString mCachePath;
    QString mAPIKey;
    QString mLastAutocompletion;

private:
    static QSet<QString> mTheTvDBSupportedLanguages;

};

#endif // THETVDBAPI_H
