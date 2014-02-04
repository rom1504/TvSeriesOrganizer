import QtQuick 2.0

SimplePage
{
    id:seriesDetails
    signal seasonClicked(int seasonNumber)

    ListView
    {
        id: listView
        x:30
        y:10
        width: 300
        height: 600
        model: series
        delegate: Season{}
    }
}
