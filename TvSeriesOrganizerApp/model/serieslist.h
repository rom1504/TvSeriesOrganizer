#ifndef SERIESLIST_H
#define SERIESLIST_H

#include <QObject>

#include "series.h"
#include "model/signallist.h"

class SeriesList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel * seriesListModel READ seriesListModel NOTIFY seriesListModelChanged)
    Q_PROPERTY(QAbstractItemModel * seriesListUpcomingModel READ seriesListUpcomingModel NOTIFY seriesListUpcomingModelChanged)
    Q_PROPERTY(int seriesCount READ seriesCount NOTIFY seriesCountChanged)

public:
    explicit SeriesList(QObject *parent = 0);
    int addSeries(Series * series);
    SignalList<Series *> *series();
    void saveSeries(QString fileName="") const;
    void loadSeries(QString fileName="");
    void removeSeries(int row);
    int seriesCount() const;


    QAbstractItemModel * seriesListModel();
    QAbstractItemModel * seriesListUpcomingModel();

private:
    SignalListAdapter<Series*> * seriesListModelT();

signals:
    void seriesListModelChanged();
    void seriesListUpcomingModelChanged();
    void searchCompleted(QAbstractItemModel * searchListModel,int resultsCount);
    void seriesAdded(int addIndex);
    void seriesCountChanged();

public slots:
    Series *getSeries(int row) const;
    void completeAddSaveSeries(Series* series);
    void removeSaveSeries(int row);
    void searchSeries(const QString &seriesName);

private:
    SignalList<Series*> mSeries;
    QString mSaveFileName;
    QSet<int> mIds;

};
Q_DECLARE_METATYPE (SeriesList*)

#endif // SERIESLIST_H
