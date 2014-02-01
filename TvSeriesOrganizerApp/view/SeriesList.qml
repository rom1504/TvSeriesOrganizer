import QtQuick 2.0

Rectangle
{
    id:seriesDetails
    width: 400
    height: 800
    color: "#EAEAEA"
    signal seriesClicked(int seriesNumber)

    ListView
    {
        id: listView
        anchors.fill: parent
        model: seriesList
        delegate: Series{}
    }
}
