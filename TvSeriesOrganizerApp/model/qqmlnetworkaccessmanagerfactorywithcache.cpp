#include <QNetworkAccessManager>
#include <QCoreApplication>

#include "qqmlnetworkaccessmanagerfactorywithcache.h"
#include "controller/controller.h"

QQmlNetworkAccessManagerFactoryWithCache::QQmlNetworkAccessManagerFactoryWithCache()
{

}

QNetworkAccessManager *	QQmlNetworkAccessManagerFactoryWithCache::create(QObject * parent)
{
    QNetworkAccessManager * manager=new QNetworkAccessManager(parent);
    QNetworkDiskCache * cache=new QNetworkDiskCache(parent);
    cache->setCacheDirectory(Controller::cachePath);
    manager->setCache(cache);
    return manager;
}
