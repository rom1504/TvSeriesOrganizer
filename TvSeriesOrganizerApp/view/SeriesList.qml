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
        x:30
        y:10
        width: 300
        height: 600
        model: seriesList
        delegate: Series{}
    }
}
