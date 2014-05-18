import QtQuick 2.2
import "qrc:/GeneralQmlItems/"

Column
{
    Keys.onDownPressed: searchSeriesCollection.incrementCurrentIndex()
    Keys.onUpPressed: searchSeriesCollection.decrementCurrentIndex()
    id:seriesSearch
    property var seriesList

    signal searchFinished(int addIndex)
    y:5

    Connections
    {
        target: seriesList
        onSearchCompleted:
        {
            status.text=resultsCount==0 ? qsTr("No results") : qsTr("%n result(s)","",resultsCount)
            searchSeriesCollection.model=searchListModel
        }
        onSeriesAdded:
        {
            status.text=""
            searchSeriesCollection.model=null
            searchFinished(addIndex)
        }
    }

    spacing:15
    Row
    {
        z:100
        width: parent.width
        height:childrenRect.height
        spacing:20
        AutocompleteLineInput
        {
            id:lineInput
            font.pointSize:18
            width:parent.width-searchButton.width-20
            onReturnText: {status.text=qsTr("Searching..."); seriesList.searchSeries(text);}
            hint:qsTr("Tv series name")
            fetchedModel:seriesList.autocompleteModel
            onTextChanged:seriesList.updateAutocompleteModel(text);
        }

        TextIconButton
        {
            id:searchButton
            onClicked:lineInput.accepted()
            text:qsTr("Search")
            font.pointSize: 14
            heightMargin:25
            widthMargin:25
            icon:"qrc:/images/search.png"
        }
    }
    Text
    {
        x:seriesSearch.width-contentWidth
        id:status
        font.pointSize: 16
    }

    CommonGridView
    {
        z:0
        id:searchSeriesCollection
        delegate:
            ShadowBorderRectangleButton
            {
                id:seriesItem

                width:searchSeriesCollection.realCellWidth
                height:searchSeriesCollection.realCellHeight
                onClicked: if(addButton.enabled==true && isMouseIn(addButton,50)) addButton.clicked()
                onPressedChanged:
                {
                    if(!pressed || isMouseIn(addButton,50)) addButton.pressed=pressed
                }

                TitleImageDescriptionItem
                {
                    id:content
                    title:series.name
                    imageSource:series.poster.small
                    description:series.shortOverview
                    width:parent.width-10
                    maximumDescriptionHeight: 135
                    forceDescriptionHeight:true
                }

                Button
                {
                    id:addButton
                    Image
                    {
                        source:"qrc:/images/add_black.png"
                        width:content.width/13
                        height:width
                        id:ibutton
                    }
                    width:ibutton.width
                    height:ibutton.height
                    x:parent.width-width
                    focus:true
                    onClicked: {status.text=qsTr("Adding...");seriesList.completeAddSaveSeries(series);}
                }
            }

        width: seriesSearch.width
        height: seriesSearch.height
        currentIndex: 0

        defaultColumnNumber:1
        cellRatio:3/8

    }
}
