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
                            item:"qrc:/view/SeriesListPage.qml",
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
                        item:"qrc:/view/SeriesListPage.qml",
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
        SeriesGrid
        {
            width: exploreSeries.width-40
            height: parent.height
            Keys.onLeftPressed: exploreSeries.goLeft()
            Keys.onRightPressed: exploreSeries.goRight()
            model:seriesList.seriesListFilteredModel
            seriesComp:Button
            {
                id:addButton
                Image
                {
                    source:"qrc:/images/add.png"
                    width:seriesImage.width/4
                    height:width
                    id:ibutton
                }
                width:ibutton.width+50
                height:ibutton.height+50
                x:delegateItem.width-ibutton.width
                focus:true
                onClicked: {followedSeriesList.completeAddSaveSeries(mseries);}
            }
        }
    tabDelegate:TabItem{tabText:seriesList.genre;tabPage:exploreSeries}

}
