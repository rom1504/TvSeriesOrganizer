#include <QFile>
#include <QFileInfo>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QBuffer>

#include "diskcache.h"


DiskCache::DiskCache(QNetworkAccessManager *networkAccessManager, QObject * parent) : QObject(parent),mNetworkAccessManager(networkAccessManager)
{

}


void DiskCache::streamLocallyOrRemotely(QString localFileName, QUrl remoteUrl, std::function<void(QIODevice*)> stream, int numberOfDaysBeforeDownloadingAgain)
{
    QFile * xmlFile=new QFile(localFileName);
    if(!xmlFile->exists() || (numberOfDaysBeforeDownloadingAgain!=-1 && QFileInfo(*xmlFile).lastModified().daysTo(QDateTime::currentDateTime())>=numberOfDaysBeforeDownloadingAgain))
    {
        xmlFile->close();
        QNetworkReply* reply=mNetworkAccessManager->get(QNetworkRequest(remoteUrl));
        connect(reply, &QNetworkReply::finished,[localFileName,stream,reply](){
            QString xmlContent=reply->readAll();
            QFile xmlFile(localFileName);
            xmlFile.open(QIODevice::WriteOnly|QIODevice::Text);
            QTextStream out(&xmlFile);
            out<<xmlContent;
            xmlFile.close();
            QByteArray * byteArray=new QByteArray(xmlContent.toUtf8());
            QBuffer * buffer=new QBuffer(byteArray);
            buffer->open(QIODevice::ReadOnly);
            stream(buffer);
        });
    }
    else
    {
        xmlFile->open(QIODevice::ReadOnly|QIODevice::Text);
        stream(xmlFile);
    }
}

void DiskCache::loadLocallyOrRemotely(QString localFileName, QUrl remoteUrl, std::function<void(QString)> load, int numberOfDaysBeforeDownloadingAgain)
{
    QFile xmlFile(localFileName);
    if(!xmlFile.exists() || (numberOfDaysBeforeDownloadingAgain!=-1 && QFileInfo(xmlFile).lastModified().daysTo(QDateTime::currentDateTime())>=numberOfDaysBeforeDownloadingAgain))
    {
        xmlFile.close();
        QNetworkReply* reply=mNetworkAccessManager->get(QNetworkRequest(remoteUrl));
        connect(reply, &QNetworkReply::finished,[localFileName,load,reply](){
            QString xmlContent=reply->readAll();
            QFile xmlFile(localFileName);
            xmlFile.open(QIODevice::WriteOnly|QIODevice::Text);
            QTextStream out(&xmlFile);
            out <<xmlContent;
            xmlFile.close();
            load(xmlContent);
        });
    }
    else
    {
        xmlFile.open(QIODevice::ReadOnly|QIODevice::Text);
        load(xmlFile.readAll());
        xmlFile.close();
    }
}
