#ifndef SEASON_H
#define SEASON_H

#include <QObject>

#include "episode.h"
#include "model/signallist.h"

class Season : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int number READ number NOTIFY numberChanged)
public:
    explicit Season(int number,QObject *parent = 0);
    void addEpisode(Episode * episode);
    Episode *getEpisode(int row) const;
    int number() const;

    SignalList<Episode *> &episodes();

signals:
    void numberChanged();

public slots:

private:
    int mNumber;
    SignalList<Episode *> mEpisodes;

};
Q_DECLARE_METATYPE (Season*)

#endif // SEASON_H
