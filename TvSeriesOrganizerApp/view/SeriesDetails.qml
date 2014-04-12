import QtQuick 2.1
import QtGraphicalEffects 1.0
import "qrc:/GeneralQmlItems/"


TabPage
{
    id:seriesDetails
    imageSource:series.banner
    property int seasonIndex:0
    property var series
    property int listBeginIndex:seasonIndex
    property bool upcoming:false

    onBack:
    {
        stackview.get(stackview.depth-2).stimer.running=true
        stackview.pop({immediate:true})
    }

    function seasonClicked(seasonIndex,season,upcoming)
    {
        seriesDetails.seasonIndex=seasonIndex
        stackview.push
        ({
             item:"qrc:/view/SeasonDetails.qml",
             immediate:true,
             properties:
             {
                 seasonIndex:seriesDetails.seasonIndex,
                 season:season,
                 seriesModel:upcoming ? series.seriesUpcomingModel : series.seriesModel,
                 upcoming:upcoming
             }
         })
    }

    tabContentModel: VisualItemModel
    {
        ListView
        {
            delegate:Season{onSeasonClicked: seriesDetails.seasonClicked(index,season,upcoming)}
            model:upcoming ? series.seriesUpcomingModel : series.seriesModel
            width: seriesDetails.width-40
            height: seriesDetails.height
            currentIndex: listBeginIndex
            focus:true

            highlightRangeMode:ListView.StrictlyEnforceRange
            id:listview
            Keys.onDownPressed: listview.incrementCurrentIndex()
            Keys.onUpPressed: listview.decrementCurrentIndex()
            Keys.onReturnPressed:currentItem.Keys.onReturnPressed(event)
        }
        Flickable
        {
            flickableDirection:Flickable.VerticalFlick
            focus:true
            width: seriesDetails.width-40
            height:seriesDetails.height
            contentHeight: scol.height+150
            Column
            {
                id:scol
                height:childrenRect.height
                spacing:20
                ShadowBorderRectangleButton
                {
                    id:firstRect
                    width:seriesDetails.width-40
                    height:col.height+20
                    Column
                    {
                        id:col
                        spacing:1
                        Title
                        {
                            id:text3
                            text:qsTr("Details")+": "
                            width:contentWidth
                            height:contentHeight
                        }

                        Row
                        {
                            spacing:1
                            height:labels.contentHeight
                            Text
                            {
                                width:contentWidth
                                id:labels
                                font.family: 'arial'
                                wrapMode: Text.WordWrap
                                font.pointSize:  12
                                text:qsTr("Network")+": \n"+qsTr("First aired")+": "
                            }
                            Text
                            {
                                width:contentWidth
                                font.family: 'arial'
                                wrapMode: Text.WordWrap
                                font.pointSize: 12
                                color: "#717171"
                                text:series.network+"\n"+Qt.formatDateTime(series.firstAired, "yyyy-MM-dd")
                            }
                        }
                    }
                }
                ShadowBorderRectangleButton
                {
                    width:seriesDetails.width-40
                    height:col2.height
                    Column
                    {
                        width:seriesDetails.width-40
                        id:col2
                        Title
                        {
                            id:text1
                            text:qsTr("Plot")+": "

                        }
                        Description
                        {
                            width:seriesDetails.width-80
                            text:series.overview
                        }
                    }
                }
            }
        }
        ListView
        {
            delegate:ShadowBorderRectangle
            {
                TitleImageDescriptionItem
                {
                    title:actor.name
                    imageSource:actor.image
                    description:qsTr("Role")+": "+actor.role+"\n"+qsTr("Importance")+": "+
                                (actor.sortOrder===3 ? qsTr("Low") :
                                (actor.sortOrder===2 ? qsTr("Medium") :
                                (actor.sortOrder===1 ? qsTr("High") :
                                (actor.sortOrder===0 ? qsTr("Very low") : ""))))
                }
              }
            model:series.actorListModel
            width: seriesDetails.width-40
            height: seriesDetails.height
            currentIndex: 0
            focus:true

            highlightRangeMode:ListView.StrictlyEnforceRange
            Keys.onDownPressed: incrementCurrentIndex()
            Keys.onUpPressed: decrementCurrentIndex()
            Keys.onReturnPressed:currentItem.Keys.onReturnPressed(event)
        }
        GridView
        {
            id:fanArtsView
            width: seriesDetails.width-40
            height:seriesDetails.height
            cellWidth:width/2
            cellHeight: 1080/1920*cellWidth
            model:series.fanArts

            property double itemMargin: cellWidth*0.03
            highlightRangeMode:ListView.StrictlyEnforceRange
            Keys.onDownPressed: moveCurrentIndexDown()
            Keys.onUpPressed: moveCurrentIndexUp()
            Keys.onLeftPressed: seriesDetails.goLeft()
            Keys.onRightPressed: seriesDetails.goRight()

            delegate:Image
                    {
                        width:fanArtsView.cellWidth-fanArtsView.itemMargin
                        height:fanArtsView.cellHeight-fanArtsView.itemMargin
                        id:fanArtImage
                        source:fanArt
                    }
        }
        GridView
        {
            id:postersView
            width: seriesDetails.width-40
            height:seriesDetails.height
            cellWidth:width/3
            cellHeight: 1000/680*cellWidth
            model:series.posters

            property double itemMargin: cellWidth*0.03
            highlightRangeMode:ListView.StrictlyEnforceRange
            Keys.onDownPressed: moveCurrentIndexDown()
            Keys.onUpPressed: moveCurrentIndexUp()
            Keys.onLeftPressed: seriesDetails.goLeft()
            Keys.onRightPressed: seriesDetails.goRight()

            delegate:Image
                    {
                        id:posterImage
                        width:postersView.cellWidth-postersView.itemMargin
                        height:postersView.cellHeight-postersView.itemMargin
                        source:poster
                    }
        }
    }
    tabModel:[qsTr("Seasons"),qsTr("Info"),qsTr("Actors"),qsTr("Fan arts"),qsTr("Posters")]
    tabDelegate:TabItem{tabText:modelData;tabPage:seriesDetails}

    beginIndex:0
}
