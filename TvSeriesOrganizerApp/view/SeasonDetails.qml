import QtQuick 2.0

Rectangle
{
    id:seasonDetails
    width: 400
    height: 800
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
