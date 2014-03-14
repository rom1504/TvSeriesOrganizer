import QtQuick 2.2
import "qrc:/GeneralQmlItems/"

TabPage
{
    id:seriesListPage
    imageSource:"qrc:/images/TvSeriesOrganizer.jpg"
    property int seriesIndex:0
    property var seriesList
    onTabChanged: stackview.focus=true

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
    tabContentModel: VisualItemModel
    {
        ListView
        {
            Keys.onDownPressed: listview.incrementCurrentIndex()
            Keys.onUpPressed: listview.decrementCurrentIndex()
            Keys.onReturnPressed:listview.currentItem.Keys.onReturnPressed(event)
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
        SeriesSearch
        {
            seriesList:seriesListPage.seriesList
            width: seriesListPage.width-40
            height: seriesListPage.height
            onSearchFinished:
            {
                seriesListPage.goTo(0)
                listview.currentIndex=addIndex;
            }
        }
    }

    tabModel:["Series","Upcoming","Search"]
    tabDelegate:TabItem{tabText:modelData;tabPage:seriesListPage}
    beginIndex: 0
}
