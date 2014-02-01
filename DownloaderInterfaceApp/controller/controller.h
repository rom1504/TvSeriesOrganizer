#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>

#include "qtquick2applicationviewer.h"
#include "model/season.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);


    void run();

signals:

private slots:
    void willShowEpisodeDetails(const int row);
    void showEpisodeDetails(const int row);
    void showSeasonDetails();

private:
    QQuickView mViewer;
    Season mSeason1;
    QTimer mTimer;

};

#endif // CONTROLLER_H
