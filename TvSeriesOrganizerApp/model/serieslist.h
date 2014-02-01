#ifndef SERIESLIST_H
#define SERIESLIST_H

#include <QObject>

#include "series.h"
#include "model/signallist.h"

class SeriesList : public QObject
{
    Q_OBJECT
public:
    explicit SeriesList(QObject *parent = 0);
    void addSeries(Series * series);
    Series *getSeries(int row) const;
    SignalList<Series *> &series();

signals:

public slots:

private:
    SignalList<Series*> mSeries;

};

#endif // SERIESLIST_H
