#include <QNetworkAccessManager>
#include <QCoreApplication>

#include "qqmlnetworkaccessmanagerfactorywithcache.h"

QQmlNetworkAccessManagerFactoryWithCache::QQmlNetworkAccessManagerFactoryWithCache()
{

}

QNetworkAccessManager *	QQmlNetworkAccessManagerFactoryWithCache::create(QObject * parent)
{
    QNetworkAccessManager * manager=new QNetworkAccessManager(parent);
    QNetworkDiskCache * cache=new QNetworkDiskCache(parent);
    cache->setCacheDirectory(QCoreApplication::applicationDirPath());
    manager->setCache(cache);
    return manager;
}
