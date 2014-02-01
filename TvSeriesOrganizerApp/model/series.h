#ifndef SERIE_H
#define SERIE_H

#include <QObject>

#include "season.h"
#include "model/signallist.h"

class Series : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
public:
    explicit Series(QString name,QObject *parent = 0);
    void addSeason(Season * season);
    Season *getSeason(int row) const;
    SignalList<Season *> &seasons();

    QString name() const;

signals:
    void nameChanged();

public slots:

private:
    QString mName;
    SignalList<Season*> mSeasons;

};
Q_DECLARE_METATYPE (Series*)

#endif // SERIE_H
