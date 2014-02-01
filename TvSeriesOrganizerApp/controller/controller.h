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
    void showSeriesList();
    void willShowSeriesDetails(const int row);
    void showSeriesDetails(const int row);
    void willShowSeasonDetails(const int row);
    void willShowEpisodeDetails(const int row);
    void showEpisodeDetails(const int row);
    void showSeasonDetails(const int row);

private:
    QQuickView mViewer;
    SeriesList * mSeriesList;
    Series * mCurrentSeries;
    Season * mCurrentSeason;
    QTimer mTimer;

};

#endif // CONTROLLER_H
