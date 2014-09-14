#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>

#include "TvSeriesOrganizerPluginInterface/abstractplugin.h"
#include "episode.h"

class Plugin : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString buttonName READ buttonName NOTIFY buttonNameChanged)

public:
    explicit Plugin(AbstractPlugin * realPlugin,QObject *parent);
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
