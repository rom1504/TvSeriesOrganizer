#include <QNetworkAccessManager>
#include <QCoreApplication>

#include "qqmlnetworkaccessmanagerfactorywithcache.h"

QQmlNetworkAccessManagerFactoryWithCache::QQmlNetworkAccessManagerFactoryWithCache(QString cachePath) : QQmlNetworkAccessManagerFactory(),mCachePath(cachePath)
{

}

QNetworkAccessManager *	QQmlNetworkAccessManagerFactoryWithCache::create(QObject * parent)
{
    QNetworkAccessManager * manager=new QNetworkAccessManager(parent);
    QNetworkDiskCache * cache=new QNetworkDiskCache(parent);
    cache->setCacheDirectory(mCachePath);
    manager->setCache(cache);
    return manager;
}
