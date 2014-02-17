import QtQuick 2.2

ListPage
{
    id:seriesListPage
    signal seriesClicked(int seriesNumber)
    imageSource:"qrc:/images/TvSeriesOrganizer.jpg"
    pageModel: seriesList
    pageDelegate: Series{}
    beginIndex: seriesIndex
    signal addSeries(string seriesName)

    LineInput
    {
        id:lineInput
        x:40
        y:-28
        width:330
        height:25
        onReturnText: addSeries(text)
        hint:"Tv series name"
    }

    Button
    {
        id:add
        x:380
        y:-26
        onClicked:lineInput.accepted()
        text:"Add"
    }
}
