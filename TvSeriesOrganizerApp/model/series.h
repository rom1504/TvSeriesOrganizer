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
    Q_PROPERTY(QUrl poster READ poster NOTIFY posterChanged)
    Q_PROPERTY(QUrl overview READ overview NOTIFY overviewChanged)


public:
    explicit Series(QString name, QUrl banner, QObject *parent = 0);
    explicit Series(QString name, QObject *parent = 0);
    void addSeason(Season * season);
    Season *getSeason(int row) const;
    SignalList<Season *> *seasons();

    void setName(QString name);
    void setOverview(QString overview);
    void setPoster(QUrl poster);

    QString name() const;
    QUrl banner() const;
    QUrl poster() const;
    QString overview() const;

signals:
    void nameChanged();
    void bannerChanged();
    void posterChanged();
    void overviewChanged();

public slots:

private:
    void loadLocallyOrRemotely(QString localFileName,QUrl remoteUrl,std::function<void(QString)> load);
    void loadSeries(QString xmlFileContent);
    void loadBanners(QString xmlFileContent);
    void beginLoadingSeries(QString xmlContent);

private:
    QString mName;
    QUrl mBanner;
    QUrl mPoster;
    SignalList<Season*> mSeasons;
    QString mId;
    QString mOverview;

};
Q_DECLARE_METATYPE (Series*)

#endif // SERIE_H
