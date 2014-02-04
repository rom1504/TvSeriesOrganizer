import QtQuick 2.0

SimplePage
{
    id:seasonDetails
    signal episodeClicked(int episodeNumber)

    ListView
    {
        id: listView
        x:30
        y:10
        width: 300
        height: 600
        model: season
        delegate: Episode{}
    }
}
