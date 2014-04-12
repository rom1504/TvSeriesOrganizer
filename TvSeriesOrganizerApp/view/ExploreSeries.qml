import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

TabPage
{
    id:exploreSeries
    imageSource:"qrc:/images/TvSeriesOrganizerHeader.png"
    tabContentModel: seriesListList.seriesListListModel()

    onBack:stackview.depth===1 ? Qt.quit() : stackview.pop({immediate:true})

    property var followedSeriesList


    Item
    {
        Connections
        {
            target: followedSeriesList
            onSeriesAdded:
            {
                if(stackview.currentItem===exploreSeries)
                {
                    if(stackview.depth===1)
                    {
                        stackview.push
                       ({
                            item:"qrc:/view/SeriesList.qml",
                            immediate:true,
                            properties:{seriesList:followedSeriesList}
                       })
                    }
                    else stackview.pop({immediate:true})
                }
            }
        }
    }

    Text
    {
        x:exploreSeries.width/2-width/2
        y:-height-exploreSeries.height/20
        width:contentWidth
        height:contentHeight
        font.pointSize: 30
        color:"white"
        font.family: "georgia"
        text:"Tv Series Organizer"
    }

    Button
    {
        id:forwardContainer
        x:7/8*exploreSeries.width-width/2
        y:-height-exploreSeries.height/30
        width: button.width +5
        height: button.height +5
        onClicked: stackview.push
                   ({
                        item:"qrc:/view/SeriesList.qml",
                        immediate:true,
                        properties:{seriesList:followedSeriesList}
                   })
        Image
        {
            source:"qrc:/images/forward.png"
            width:exploreSeries.width/7
            height:width
            id:button
        }
        visible:stackview.depth===1
    }


    tabContentDelegate:
        GridView
        {
            id:seriesL
            property variant myData:seriesList
            delegate:Item
            {
                id:seriesItem
                width:seriesL.cellWidth-seriesL.itemMargin
                height:seriesL.cellHeight-seriesL.itemMargin

                Image
                {
                    id:image
                    width:parent.width
                    height: image.width/138*203
                    fillMode: Image.PreserveAspectCrop
                    source:series.poster
                }

                Button
                {
                    id:addButton
                    Image
                    {
                        source:"qrc:/images/add.png"
                        width:image.width/4
                        height:width
                        id:ibutton
                    }
                    width:ibutton.width+50
                    height:ibutton.height+50
                    x:seriesItem.width-ibutton.width
                    focus:true
                    onClicked: {followedSeriesList.completeAddSaveSeries(series);}
                }
            }
            cellWidth:width/3
            cellHeight: cellWidth/138*203*0.99
            property double itemMargin: cellWidth*0.03
            model:seriesList.seriesListFilteredModel
            width: exploreSeries.width-40
            height: parent.height
            highlightRangeMode:ListView.StrictlyEnforceRange
            Keys.onDownPressed: moveCurrentIndexDown()
            Keys.onUpPressed: moveCurrentIndexUp()
            Keys.onLeftPressed: exploreSeries.goLeft()
            Keys.onRightPressed: exploreSeries.goRight()

            Keys.onReturnPressed:currentItem.Keys.onReturnPressed(event)
        }
    tabDelegate:TabItem{tabText:seriesList.genre;tabPage:exploreSeries}

}
