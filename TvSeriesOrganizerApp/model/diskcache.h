#ifndef DISKCACHE_H
#define DISKCACHE_H

#include <QString>
#include <QUrl>
#include <QIODevice>

class DiskCache
{
public:
    static void loadLocallyOrRemotely(QString localFileName, QUrl remoteUrl, std::function<void(QString)> load, int numberOfDaysBeforeDownloadingAgain=-1);
    static void streamLocallyOrRemotely(QString localFileName, QUrl remoteUrl, std::function<void(QIODevice*)> stream, int numberOfDaysBeforeDownloadingAgain=-1);
};

#endif // DISKCACHE_H
