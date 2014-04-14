#include "actor.h"

Actor::Actor(int id, Image* image, QString name, QString role, int sortOrder, QObject *parent) :
    QObject(parent),mId(id),mImage(image),mName(name),mRole(role),mSortOrder(sortOrder)
{
}

Actor::Actor(QDomElement element, QObject *parent) : QObject(parent)
{
    if(element.tagName() == "Actor")
    {
        QDomElement actorElement=element.firstChildElement();
        while(!actorElement.isNull())
        {
            if(actorElement.tagName() == "id") mId=actorElement.text().toInt();
            else if(actorElement.tagName() == "Image") mImage=new Image(actorElement.text());
            else if(actorElement.tagName() == "Name") mName=actorElement.text();
            else if(actorElement.tagName() == "Role") mRole=actorElement.text();
            else if(actorElement.tagName() == "SortOrder") mSortOrder=actorElement.text().toInt();
            actorElement=actorElement.nextSiblingElement();
        }
    }
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


