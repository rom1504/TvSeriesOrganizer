#include "actorlist.h"
#include "series.h"

ActorList::ActorList(QObject *parent) :
    QObject(parent),mActorList([](Actor* a,Actor* b){return a->sortOrder()<b->sortOrder();})
{

}

QAbstractItemModel * ActorList::actorListModel()
{
    return new SignalListAdapter<Actor*>(&mActorList,"actor");
}


void ActorList::loadActorList(QString xmlFileContent)
{
    QDomDocument doc;
    doc.setContent(xmlFileContent);
    QDomElement root = doc.documentElement();
    root = root.firstChildElement();
    while(!root.isNull())
    {
        mActorList.append(new Actor(root,this));
        root=root.nextSiblingElement();
    }
}
