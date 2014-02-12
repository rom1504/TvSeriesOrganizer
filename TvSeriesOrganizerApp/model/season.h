#ifndef SEASON_H
#define SEASON_H

#include <QObject>

#include "episode.h"
#include "model/signallist.h"

class Season : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int number READ number NOTIFY numberChanged)
    Q_PROPERTY(QUrl banner READ banner NOTIFY bannerChanged)
    Q_PROPERTY(QUrl poster READ poster NOTIFY posterChanged)
public:
    explicit Season(int number,QUrl banner,QUrl poster,QObject *parent = 0);
    void addEpisode(Episode * episode);
    Episode *getEpisode(int row) const;
    int number() const;
    QUrl banner() const;
    QUrl poster() const;


    void setBanner(QUrl banner);
    void setPoster(QUrl poster);

    SignalList<Episode *> * episodes();

signals:
    void numberChanged();
    void bannerChanged();
    void posterChanged();

public slots:

private:
    int mNumber;
    QUrl mBanner;
    QUrl mPoster;
    SignalList<Episode *> mEpisodes;

};
Q_DECLARE_METATYPE (Season*)

#endif // SEASON_H
