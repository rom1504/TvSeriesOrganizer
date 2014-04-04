#ifndef SERIE_H
#define SERIE_H

#include <QObject>
#include <QDomElement>

#include "season.h"
#include "model/signallist.h"

class Series : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QUrl banner READ banner NOTIFY bannerChanged)
    Q_PROPERTY(QUrl poster READ poster NOTIFY posterChanged)
    Q_PROPERTY(QString overview READ overview NOTIFY overviewChanged)
    Q_PROPERTY(int seasonCount READ seasonCount NOTIFY seasonCountChanged)
    Q_PROPERTY(QDate firstAired READ firstAired NOTIFY firstAiredChanged)
    Q_PROPERTY(QString network READ network NOTIFY networkChanged)
    Q_PROPERTY(QAbstractItemModel * fanArts READ fanArts NOTIFY fanArtsChanged)
    Q_PROPERTY(QAbstractItemModel * posters READ posters NOTIFY postersChanged)
    Q_PROPERTY(bool seen READ seen WRITE setSeen NOTIFY seenChanged)
    Q_PROPERTY(double seenRatio READ seenRatio NOTIFY seenRatioChanged)
    Q_PROPERTY(QAbstractItemModel * seriesModel READ seriesModel NOTIFY seriesModelChanged)
    Q_PROPERTY(QAbstractItemModel * seriesUpcomingModel READ seriesUpcomingModel NOTIFY seriesUpcomingModelChanged)
    Q_PROPERTY(QString shortOverview READ shortOverview NOTIFY shortOverviewChanged)

public:
    explicit Series(QObject *parent=0);
    explicit Series(int id, QObject *parent = 0);
    explicit Series(const QDomElement & element, QObject*parent=0);
    void addSeason(Season * season);
    SignalList<Season *> *seasons();

    void complete();

    void setName(QString name);
    void setOverview(QString overview);
    void setPoster(QUrl poster);
    void setId(int id);
    void setBanner(QUrl banner);

    QString name() const;
    QUrl banner() const;
    QUrl poster() const;
    QString overview() const;
    int seasonCount() const;
    QDate firstAired() const;
    QString network() const;
    QAbstractItemModel * fanArts();
    QAbstractItemModel * posters();
    bool seen() const;
    double seenRatio() const;
    int episodeSeenCount() const;
    int episodeCount() const;
    QAbstractItemModel * seriesModel();
    QAbstractItemModel * seriesUpcomingModel();
    QString shortOverview() const;

    int id() const;



    void setSeen(bool seen);

    static void loadLocallyOrRemotely(QString localFileName, QUrl remoteUrl, std::function<void(QString)> load, int numberOfDaysBeforeDownloadingAgain=-1);


private:
    SignalListAdapter<Season*> * seriesModelT();


signals:
    void nameChanged();
    void bannerChanged();
    void posterChanged();
    void overviewChanged();
    void seasonCountChanged();
    void firstAiredChanged();
    void networkChanged();
    void fanArtsChanged();
    void postersChanged();
    void seenChanged();
    void seenRatioChanged();
    void seriesModelChanged();
    void seriesUpcomingModelChanged();
    void shortOverviewChanged();

    void completed();

public slots:
    Season *getSeason(int row) const;

private:
    void loadSeriesSeenFile();
    void saveSeriesSeenFile();
    void loadSeries(QString xmlFileContent);
    void loadBanners(QString xmlFileContent);
    Season* findSeason(int seasonNumber);

private:
    QString mName;
    QUrl mBanner;
    QUrl mPoster;
    SignalList<Season*> mSeasons;
    int mId;
    QString mOverview;
    QDate mFirstAired;
    QString mNetwork;
    SignalList<QUrl> mFanArts;
    SignalList<QUrl> mPosters;
    QString mShortOverview;

};
Q_DECLARE_METATYPE (Series*)

#endif // SERIE_H
