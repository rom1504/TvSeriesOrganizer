#ifndef SERIE_H
#define SERIE_H

#include <QObject>

#include "season.h"
#include "model/signallist.h"

class Serie : public QObject
{
    Q_OBJECT
public:
    explicit Serie(QObject *parent = 0);
    void addSeason(Season * season);

signals:

public slots:

private:
    SignalList<Season*> mSeasons;

};

#endif // SERIE_H
