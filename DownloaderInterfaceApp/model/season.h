#ifndef SEASON_H
#define SEASON_H

#include <QObject>

#include "episode.h"
#include "model/signallist.h"

class Season : public QObject
{
    Q_OBJECT
public:
    explicit Season(QObject *parent = 0);
    void addEpisode(Episode * episode);


    SignalList<Episode *> &episodes();
signals:

public slots:

private:
    SignalList<Episode *> mEpisodes;

};

#endif // SEASON_H
