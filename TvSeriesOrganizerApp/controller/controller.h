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

private:
    QtQuick2ApplicationViewer mViewer;
    SeriesList * mSeriesList;
    Series * mCurrentSeries;
    Season * mCurrentSeason;
    QTimer mTimer;

};

#endif // CONTROLLER_H
