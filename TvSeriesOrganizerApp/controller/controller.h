#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>

#include "qtquick2applicationviewer.h"
#include "model/serieslist.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

    static QString cachePath;


    void run();

signals:

private slots:
    void willShowSeriesList();
    void showSeriesList();
    void willShowSeriesDetails(const int row=-1);
    void showSeriesDetails(const int row);
    void willShowSeasonDetails(const int row=-1);
    void willShowEpisodeDetails(const int row);
    void showEpisodeDetails(const int row);
    void showSeasonDetails(const int row);
    void changeCurrentSeason(int row);

private:
    void disconnectConnections();

private:
    QtQuick2ApplicationViewer mViewer;
    SeriesList * mSeriesList;
    Series * mCurrentSeries;
    Season * mCurrentSeason;
    int mCurrentSeasonRow;
    QTimer mTimer;
    QList<QMetaObject::Connection> mConnections;

};

#endif // CONTROLLER_H
