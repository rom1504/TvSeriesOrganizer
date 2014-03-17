import QtQuick 2.2
import "qrc:/GeneralQmlItems/"

Column
{
    Keys.onDownPressed: searchListView.incrementCurrentIndex()
    Keys.onUpPressed: searchListView.decrementCurrentIndex()
    id:seriesSearch
    property var seriesList

    signal searchFinished(int addIndex)

    Connections
    {
        target: seriesList
        onSearchCompleted:searchListView.model=searchListModel
        onSeriesAdded:
        {
            searchListView.model=null
            searchFinished(addIndex)
        }
    }

    spacing:20
    Row
    {
        width: parent.width
        height:childrenRect.height
        spacing:20
        LineInput
        {
            id:lineInput
            font.pointSize:14
            width:seriesSearch.width/1.3
            onReturnText: seriesList.searchSeries(text);
            hint:"Tv series name"
        }

        Button
        {
            id:searchButton
            onClicked:lineInput.accepted()
            text:"Search"
        }
    }
    ListView
    {
        id:searchListView
        delegate:
            ShadowBorderRectangle
            {
                id:seriesItem

                onClicked: if(addButton.enabled==true && isMouseIn(addButton)) addButton.clicked()
                TitleImageDescriptionItem
                {
                    id:content
                    title:series.name
                    imageSource:series.poster
                    description:series.overview
                }

                Button
                {
                    id:addButton
                    text:"Add"
                    x:parent.width-width
                    focus:true
                    onClicked: seriesList.completeAddSaveSeries(series)
                }
            }

        width: seriesSearch.width
        height: seriesSearch.height
        currentIndex: 0
        focus:true
        clip:true


        highlightRangeMode:ListView.StrictlyEnforceRange
    }
}
