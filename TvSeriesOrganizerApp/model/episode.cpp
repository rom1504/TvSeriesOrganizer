#include "episode.h"

Episode::Episode(int number,const QString & name,const QString& description,QUrl banner,QObject *parent) :
    QObject(parent),mNumber(number),mName(name),mDescription(description),mBanner(banner)
{
}

int Episode::number() const
{
    return mNumber;
}

QString Episode::name() const
{
    return mName;
}

QString Episode::description() const
{
    return mDescription;
}

QUrl Episode::banner() const
{
    return mBanner;
}
