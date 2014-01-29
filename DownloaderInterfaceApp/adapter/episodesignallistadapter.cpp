#include "episodesignallistadapter.h"

SignalListAdapter<Episode*>::SignalListAdapter(SignalList<Episode *> *list, QObject *parent) :
    SignalListAdapterBase(list,parent)
{
}

QVariant SignalListAdapter<Episode*>::data ( const QModelIndex & index, int role ) const
{
    if (!index.isValid())
     return QVariant();

    if (index.row() >= mList->size())
       return QVariant();

    if(role==FullItemRole) return QVariant::fromValue(mList->get(index.row()));

    if (role == NumberRole) return mList->get(index.row())->number();
    if (role == NameRole) return mList->get(index.row())->name();
    if (role == DescriptionRole) return mList->get(index.row())->description();

    return QVariant();
}

Qt::ItemFlags SignalListAdapter<Episode*>::flags(const QModelIndex &) const
{
    return Qt::ItemIsEnabled|Qt::ItemIsSelectable;
}

QHash<int, QByteArray> SignalListAdapter<Episode*>::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NumberRole] = "number";
    roles[NameRole] = "name";
    roles[DescriptionRole] = "description";
    return roles;
}
