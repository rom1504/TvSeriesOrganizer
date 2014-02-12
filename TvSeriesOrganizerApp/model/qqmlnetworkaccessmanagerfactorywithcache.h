#ifndef QQMLNETWORKACCESSMANAGERFACTORYWITHCACHE_H
#define QQMLNETWORKACCESSMANAGERFACTORYWITHCACHE_H

#include <QQmlNetworkAccessManagerFactory>
#include <QNetworkDiskCache>

class QQmlNetworkAccessManagerFactoryWithCache : public QQmlNetworkAccessManagerFactory
{
public:
    QQmlNetworkAccessManagerFactoryWithCache();
    virtual QNetworkAccessManager *	create(QObject *parent);

};

#endif // QQMLNETWORKACCESSMANAGERFACTORYWITHCACHE_H
