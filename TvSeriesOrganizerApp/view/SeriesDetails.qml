import QtQuick 2.0

Rectangle
{
    id:seriesDetails
    width: 400
    height: 800
    color: "#EAEAEA"
    signal seasonClicked(int seasonNumber)

    ListView
    {
        id: listView
        anchors.fill: parent
        model: series
        delegate: Season{}
    }
}
