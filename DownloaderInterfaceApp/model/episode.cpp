#include "episode.h"

Episode::Episode(int number,const QString & name,const QString& description,QObject *parent) :
    QObject(parent),mNumber(number),mName(name),mDescription(description)
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

void Episode::setNumber(int number)
{
    mNumber=number;
}

void Episode::setName(const QString &name)
{
    mName=name;
}

void Episode::setDescription(const QString & description)
{
    mDescription=description;
}
