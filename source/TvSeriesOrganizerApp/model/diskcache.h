#ifndef DISKCACHE_H
#define DISKCACHE_H

#include <QString>
#include <QUrl>
#include <QIODevice>
#include <QObject>
#include <QNetworkAccessManager>

class DiskCache : public QObject
{
    Q_OBJECT
public:
    explicit DiskCache(QNetworkAccessManager * networkAccessManager,QObject * parent);
    void loadLocallyOrRemotely(QString localFileName, QUrl remoteUrl, std::function<void(QString)> load, int numberOfDaysBeforeDownloadingAgain=-1);
    void streamLocallyOrRemotely(QString localFileName, QUrl remoteUrl, std::function<void(QIODevice*)> stream, int numberOfDaysBeforeDownloadingAgain=-1);

private:
    QNetworkAccessManager * mNetworkAccessManager;
};

#endif // DISKCACHE_H
