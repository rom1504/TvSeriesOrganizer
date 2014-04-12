#ifndef ACTORLIST_H
#define ACTORLIST_H

#include <QObject>

#include "model/actor.h"
#include "model/signallist.h"
#include "adapter/signallistadapter.h"

class ActorList : public QObject
{
    Q_OBJECT
public:
    explicit ActorList(QObject *parent = 0);
    QAbstractItemModel *actorListModel();
    void loadActorList(QString xmlFileContent);

private:
    SignalList<Actor*> mActorList;
};

#endif // ACTORLIST_H
