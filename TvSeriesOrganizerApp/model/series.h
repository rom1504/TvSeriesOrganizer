#ifndef SERIE_H
#define SERIE_H

#include <QObject>

#include "season.h"
#include "model/signallist.h"

class Series : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QUrl banner READ banner NOTIFY bannerChanged)
public:
    explicit Series(QString name, QUrl banner, QObject *parent = 0);
    void addSeason(Season * season);
    Season *getSeason(int row) const;
    SignalList<Season *> &seasons();

    QString name() const;
    QUrl banner() const;

signals:
    void nameChanged();
    void bannerChanged();

public slots:

private:
    QString mName;
    QUrl mBanner;
    SignalList<Season*> mSeasons;

};
Q_DECLARE_METATYPE (Series*)

#endif // SERIE_H
