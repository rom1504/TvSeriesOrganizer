#ifndef EPISODESIGNALLISTADAPTER_H
#define EPISODESIGNALLISTADAPTER_H

#include "adapter/signallistadapter.h"
#include "model/episode.h"

template<> class SignalListAdapter<Episode*> : public SignalListAdapterBase<Episode*>
{
    enum EpisodeRoles {
        NumberRole = Qt::UserRole + 1,
        NameRole,
        DescriptionRole
    };
public:
    explicit SignalListAdapter(SignalList<Episode *> *list, QObject *parent = 0);
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    Qt::ItemFlags flags(const QModelIndex & index) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
};

#endif // EPISODESIGNALLISTADAPTER_H
