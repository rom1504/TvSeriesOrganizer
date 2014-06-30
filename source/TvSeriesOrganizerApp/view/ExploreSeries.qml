import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

TabPage
{
    id:exploreSeries
    imageSource:"qrc:/images/TvSeriesOrganizerHeader.png"
    tabContentModel: seriesListList.seriesListListModel()

    onBack:stackview.depth===1 ? Qt.quit() : stackview.pop({immediate:true})

    property var followedSeriesList
    title:"Tv Series Organizer"


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

    inImage: Button
    {
        id:forwardContainer
        x:exploreSeries.width-width
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
            width:50
            height:width
            id:button
        }
        visible:stackview.depth===1
    }


    tabContentDelegate:
        CommonGridView
        {
            id:gvs
            width: exploreSeries.width-40
            height: parent.height
            model:seriesList.seriesListFilteredModel
            delegate:ThumbnailSeries
            {
                width:gvs.realCellWidth
                height:gvs.realCellHeight
                addition:Button
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


        }
    tabDelegate:TabItem{tabText:seriesList.genre;tabPage:exploreSeries}

}
