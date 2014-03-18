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
    explicit Controller(QString datadir,QObject *parent = 0);

    static QString cachePath;
    static QString dataPath;


    void run();

signals:

private:
    QtQuick2ApplicationViewer mViewer;
    SeriesList * mSeriesList;

};

#endif // CONTROLLER_H
