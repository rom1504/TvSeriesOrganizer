#ifndef SERIESLISTLIST_H
#define SERIESLISTLIST_H

#include <QObject>
#include <QAbstractItemModel>
#include "model/serieslist.h"


#include "model/signallist.h"

class SeriesListList : public QObject
{
    Q_OBJECT

public:
    explicit SeriesListList(QObject *parent = 0);
    void load(QString jsonFileContent="");

signals:

public slots:
    QAbstractItemModel * seriesListListModel();

private:
    SignalList<SeriesList*> mSeriesListList;
    QMap<QString,SeriesList*> mSeriesListByGenre;

};

#endif // SERIESLISTLIST_H
