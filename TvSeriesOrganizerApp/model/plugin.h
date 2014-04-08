#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>

#include "TvSeriesOrganizerPluginInterface/abstractplugin.h"
#include "model/episode.h"

class Plugin : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString buttonName READ buttonName NOTIFY buttonNameChanged)

public:
    explicit Plugin(AbstractPlugin * realPlugin,QObject *parent = 0);
    QString buttonName() const;

signals:
    void buttonNameChanged();

public slots:
    void run(Episode * episode);

private:
    AbstractPlugin * mRealPlugin;

};

Q_DECLARE_METATYPE (Plugin*)


#endif // PLUGIN_H
