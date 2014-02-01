import QtQuick 2.0

Rectangle
{
    id:seasonDetails
    width: 360
    height: 360
    color: "#EAEAEA"
    signal episodeClicked(int episodeNumber)

    ListView
    {
        id: listView
        anchors.fill: parent
        model: season
        delegate: Episode{}
    }
}
