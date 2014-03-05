import QtQuick 2.2
import "qrc:/GeneralQmlItems/"

TabPage
{
    id:seriesListPage
    imageSource:"qrc:/images/TvSeriesOrganizer.jpg"
    property int seriesIndex:0
    property var seriesList

    function seriesClicked(seriesNumber,upcoming)
    {
        seriesIndex=seriesNumber
        stackview.push
        ({
             item:"qrc:/view/SeriesDetails.qml",
             immediate:true,
             properties:{series:seriesList.getSeries(seriesNumber),upcoming:upcoming}
        })
    }

    function removeSeries(seriesNumber)
    {
        seriesList.removeSaveSeries(seriesNumber)
    }

    function addSeries(seriesNames)
    {
        seriesList.addSaveSeries(seriesNames)
    }

    tabContentModel: VisualItemModel
    {
        Item
        {
            width:childrenRect.width
            height:childrenRect.height
            Keys.onDownPressed: listview.incrementCurrentIndex()
            Keys.onUpPressed: listview.decrementCurrentIndex()
            Keys.onReturnPressed:if(!(lineInput.activeFocus)) listview.currentItem.Keys.onReturnPressed(event)
            Column
            {
                Row
                {
                    spacing:150
                    x:20
                    LineInput
                    {
                        id:lineInput
                        width:330
                        height:25
                        onReturnText: addSeries(text)
                        hint:"Tv series name"
                    }

                    Button
                    {
                        id:add
                        onClicked:lineInput.accepted()
                        text:"Add"
                    }
                }
                ListView
                {
                    delegate: Series{onSeriesClicked: seriesListPage.seriesClicked(index,false)}
                    model:seriesList.seriesListModel
                    width: seriesListPage.width-40
                    height: seriesListPage.height
                    currentIndex: seriesIndex
                    focus:true
                    clip:true


                    highlightRangeMode:ListView.StrictlyEnforceRange
                    id:listview
                }
            }
        }

        ListView
        {
            delegate: Series{onSeriesClicked: seriesListPage.seriesClicked(index,true)}
            model:seriesList.seriesListUpcomingModel
            width: seriesListPage.width-40
            height: seriesListPage.height
            currentIndex: seriesIndex
            focus:true
            clip:true


            highlightRangeMode:ListView.StrictlyEnforceRange
            id:listviewupcoming
            Keys.onDownPressed: listviewupcoming.incrementCurrentIndex()
            Keys.onUpPressed: listviewupcoming.decrementCurrentIndex()
            Keys.onReturnPressed:listviewupcoming.currentItem.Keys.onReturnPressed(event)
        }
    }

    tabModel:["Series","Upcoming"]
    tabDelegate:TabItem{tabText:modelData;tabPage:seriesListPage}
    beginIndex: 0
}
