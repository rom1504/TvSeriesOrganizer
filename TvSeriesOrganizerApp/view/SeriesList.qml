import QtQuick 2.2
import "qrc:/GeneralQmlItems/"

ListPage
{
    id:seriesListPage
    imageSource:"qrc:/images/TvSeriesOrganizer.jpg"
    property int seriesIndex:0
    property var seriesList
    pageModel: seriesList.seriesListModel
    pageDelegate: Series{}
    beginIndex: seriesIndex
    onEnter:if(!(lineInput.activeFocus)) listView.currentItem.Keys.onReturnPressed(event)


    function seriesClicked(seriesNumber)
    {
        seriesIndex=seriesNumber
        stackview.push({item:"qrc:/view/SeriesDetails.qml",immediate:true,
                                        properties:{series:seriesList.getSeries(seriesNumber)}})
    }

    function removeSeries(seriesNumber)
    {
        seriesList.removeSaveSeries(seriesNumber)
    }

    function addSeries(seriesNames)
    {
        seriesList.addSaveSeries(seriesNames)
    }

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
