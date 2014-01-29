#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "qtquick2applicationviewer.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);


    void run();

signals:

public slots:

private:
    QtQuick2ApplicationViewer mViewer;

};

#endif // CONTROLLER_H
