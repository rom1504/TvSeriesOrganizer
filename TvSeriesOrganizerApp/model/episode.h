#ifndef EPISODE_H
#define EPISODE_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QDate>

#include "model/image.h"

class Season;
class Episode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int number READ number NOTIFY numberChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString overview READ overview NOTIFY overviewChanged)
    Q_PROPERTY(Image* banner READ banner NOTIFY bannerChanged)
    Q_PROPERTY(QDate firstAired READ firstAired NOTIFY firstAiredChanged)
    Q_PROPERTY(bool seen READ seen WRITE setSeen NOTIFY seenChanged)
    Q_PROPERTY(bool aired READ aired NOTIFY airedChanged)

public:
    explicit Episode(int number, const QString & name, const QString& overview, Image* banner,QDate firstAired, Season *parent);
    int number() const;
    QString name() const;
    QString overview() const;
    Image* banner() const;
    QDate firstAired() const;
    bool seen() const;
    bool aired() const;
    Season* season() const;


    void setSeen(bool seen);

signals:
    void numberChanged();
    void nameChanged();
    void overviewChanged();
    void bannerChanged();
    void firstAiredChanged();
    void seenChanged();
    void airedChanged();

public slots:

private:
    int mNumber;
    QString mName;
    QString mOverview;
    Image* mBanner;
    QDate mFirstAired;
    bool mSeen;
    Season* mSeason;
};

Q_DECLARE_METATYPE (Episode*)

#endif // EPISODE_H
