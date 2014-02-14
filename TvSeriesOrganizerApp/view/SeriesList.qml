import QtQuick 2.1

ListPage
{
    id:seriesListPage
    signal seriesClicked(int seriesNumber)
    imageSource:"qrc:/images/TvSeriesOrganizer.jpg"
    pageModel: seriesList
    pageDelegate: Series{}

}
