#ifndef QQMLNETWORKACCESSMANAGERFACTORYWITHCACHE_H
#define QQMLNETWORKACCESSMANAGERFACTORYWITHCACHE_H

#include <QQmlNetworkAccessManagerFactory>
#include <QNetworkDiskCache>

class QQmlNetworkAccessManagerFactoryWithCache : public QQmlNetworkAccessManagerFactory
{
public:
    QQmlNetworkAccessManagerFactoryWithCache(QString cachePath);
    virtual QNetworkAccessManager *	create(QObject *parent);

private:
    QString mCachePath;
};

#endif // QQMLNETWORKACCESSMANAGERFACTORYWITHCACHE_H
