#ifndef SERIESLIST_H
#define SERIESLIST_H

#include <QObject>

#include "series.h"
#include "model/signallist.h"

class SeriesList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel * seriesListModel READ seriesListModel NOTIFY seriesListModelChanged)

public:
    explicit SeriesList(QObject *parent = 0);
    void addSeries(Series * series);
    SignalList<Series *> *series();
    void saveSeries(QString fileName="") const;
    void loadSeries(QString fileName="");
    void addSeries(const QString &seriesName);
    void removeSeries(int row);

    QAbstractItemModel * seriesListModel();

signals:
    void seriesListModelChanged();

public slots:
    Series *getSeries(int row) const;
    void addSaveSeries(const QString &seriesName);
    void removeSaveSeries(int row);

private:
    SignalList<Series*> mSeries;
    QString mSaveFileName;

};
Q_DECLARE_METATYPE (SeriesList*)

#endif // SERIESLIST_H
