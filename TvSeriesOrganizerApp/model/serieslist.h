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
    SignalList<Series *> *series();
    void saveSeries(QString fileName="") const;
    void loadSeries(QString fileName="");
    void addSeries(const QString &seriesName);
    void removeSeries(int row);

signals:

public slots:
    void addSaveSeries(const QString &seriesName);
    void removeSaveSeries(int row);

private:
    SignalList<Series*> mSeries;
    QString mSaveFileName;

};

#endif // SERIESLIST_H
