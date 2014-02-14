import QtQuick 2.1

ListPage
{
    id:seriesDetails
    signal seasonClicked(int seasonNumber)
    imageSource:series.banner
    pageModel: seriesModel
    pageDelegate: Season{}
}
