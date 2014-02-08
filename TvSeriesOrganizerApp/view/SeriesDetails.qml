import QtQuick 2.0

ListPage
{
    id:seriesDetails
    signal seasonClicked(int seasonNumber)
    imageSource:"qrc:/images/series.jpg"
    pageModel: series
    pageDelegate: Season{}
}
