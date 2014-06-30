#include "actor.h"

Actor::Actor(int id, Image* image, QString name, QString role, int sortOrder, QObject *parent) :
    QObject(parent),mId(id),mImage(image),mName(name),mRole(role),mSortOrder(sortOrder)
{
}

QString Actor::name() const
{
    return mName;
}

Image *Actor::image() const
{
    return mImage;
}

int Actor::id() const
{
    return mId;
}


int Actor::sortOrder() const
{
    return mSortOrder;
}


QString Actor::role() const
{
    return mRole;
}


