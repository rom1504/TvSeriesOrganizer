#ifndef SERIE_H
#define SERIE_H

#include <QObject>

#include "season.h"
#include "model/signallist.h"
#include "model/actor.h"
#include "model/image.h"

class Series : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(Image* banner READ banner NOTIFY bannerChanged)
    Q_PROPERTY(Image* poster READ poster NOTIFY posterChanged)
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
    Q_PROPERTY(QAbstractItemModel * actorListModel READ actorListModel NOTIFY actorListModelChanged)

public:
    explicit Series(QObject *parent=0);
    explicit Series(int id, QObject *parent = 0);
    void addSeason(Season * season);
    SignalList<Season *> *seasons();

    void setName(QString name);
    void setOverview(QString overview);
    void setPoster(Image* poster);
    void setId(int id);
    void setBanner(Image* banner);
    void setFirstAired(QDate firstAired);
    void setNetwork(QString network);

    void addPoster(Image* poster);
    void addFanArt(Image* fanArt);
    void addActor(Actor* actor);

    QString name() const;
    Image* banner() const;
    Image* poster() const;
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
    QAbstractItemModel * actorListModel();
    QString shortOverview() const;

    int id() const;
    Season* findSeason(int seasonNumber);



    void setSeen(bool seen);


    void loadSeriesSeenFile();


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
    void actorListModelChanged();

    void completed();

public slots:
    Season *getSeason(int row) const;

private:
    void saveSeriesSeenFile();

private:
    QString mName;
    Image* mPoster;
    Image* mBanner;
    SignalList<Season*> mSeasons;
    int mId;
    QString mOverview;
    QDate mFirstAired;
    QString mNetwork;
    SignalList<Image*> mFanArts;
    SignalList<Image*> mPosters;
    QString mShortOverview;
    SignalList<Actor*> mActorList;

};
Q_DECLARE_METATYPE (Series*)

#endif // SERIE_H
