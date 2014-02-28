#ifndef SEASON_H
#define SEASON_H

#include <QObject>
#include <QAbstractItemModel>
#include <QtQml>
#include <QQmlEngine>


#include "episode.h"
#include "model/signallist.h"
#include "adapter/signallistadapter.h"

class Season : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int number READ number NOTIFY numberChanged)
    Q_PROPERTY(QUrl banner READ banner NOTIFY bannerChanged)
    Q_PROPERTY(QUrl poster READ poster NOTIFY posterChanged)
    Q_PROPERTY(QAbstractItemModel * seasonModel READ seasonModel NOTIFY seasonModelChanged)
    Q_PROPERTY(bool seen READ seen WRITE setSeen NOTIFY seenChanged)
    Q_PROPERTY(double seenRatio READ seenRatio NOTIFY seenRatioChanged)
    Q_PROPERTY(int episodeCount READ episodeCount NOTIFY episodeCountChanged)
    Q_PROPERTY(int episodeSeenCount READ episodeSeenCount NOTIFY episodeSeenCountChanged)
    Q_PROPERTY(QDate firstAired READ firstAired NOTIFY firstAiredChanged)
    Q_PROPERTY(double airedRatio READ airedRatio NOTIFY airedRatioChanged)
    Q_PROPERTY(int episodeAiredCount READ episodeAiredCount NOTIFY episodeAiredCountChanged)

public:
    explicit Season(int number,QUrl banner,QUrl poster,QObject *parent = 0);
    void addEpisode(Episode * episode);
    Episode *getEpisode(int row) const;
    int number() const;
    QUrl banner() const;
    QUrl poster() const;
    QAbstractItemModel *seasonModel();
    bool seen() const;
    int episodeSeenCount() const;
    int episodeCount() const;
    double seenRatio() const;
    QDate firstAired() const;
    double airedRatio() const;
    int episodeAiredCount() const;

    void setSeen(bool seen);
    void setBanner(QUrl banner);
    void setPoster(QUrl poster);

    SignalList<Episode *> * episodes();

    Episode* findEpisode(int episodeNumber);

signals:
    void numberChanged();
    void bannerChanged();
    void posterChanged();
    void seasonModelChanged();
    void seenChanged();
    void seenRatioChanged();
    void episodeCountChanged();
    void episodeSeenCountChanged();
    void firstAiredChanged();
    void airedRatioChanged();
    void episodeAiredCountChanged();

public slots:

private:
    int mNumber;
    QUrl mBanner;
    QUrl mPoster;
    SignalList<Episode *> mEpisodes;

};
Q_DECLARE_METATYPE (Season*)
QML_DECLARE_TYPE (SignalListAdapter<Episode *>*)

#endif // SEASON_H
