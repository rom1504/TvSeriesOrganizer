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
        stackview.pop({immediate:true})
        stackview.get(0).stimer.running=true
    }

    function seasonClicked(seasonNumber,upcoming)
    {
        seasonIndex=seasonNumber
        stackview.push
        ({
             item:"qrc:/view/SeasonDetails.qml",
             immediate:true,
             properties:
             {
                 seasonIndex:seriesDetails.seasonIndex,
                 season:series.getSeason(seasonNumber),
                 seriesModel:upcoming ? series.seriesUpcomingModel : series.seriesModel,
                 upcoming:upcoming
             }
         })
    }

    tabContentModel: VisualItemModel
    {
        ListView
        {
            delegate:Season{onSeasonClicked: seriesDetails.seasonClicked(index,upcoming)}
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
        Item
        {
            width: seriesDetails.width-40
            height:seriesDetails.height
            ShadowBorderRectangle
            {
                id:firstRect
                Title
                {
                    id:text3
                    text:"Details: "
                }
                Text
                {
                    id:labels
                    font.family: 'arial'
                    wrapMode: Text.WordWrap
                    font.pointSize:  12
                    y:text3.y+text3.height+5
                    text:"Network: \nFirst aired: "
                }
                Text
                {
                    font.family: 'arial'
                    wrapMode: Text.WordWrap
                    font.pointSize: 12
                    color: "#717171"
                    x:labels.x+labels.contentWidth+5
                    y:text3.y+text3.height+5
                    text:series.network+"\n"+Qt.formatDateTime(series.firstAired, "yyyy-MM-dd")
                }
            }
            ShadowBorderRectangle
            {
                y:firstRect.y+firstRect.height+5
                Title
                {
                    id:text1
                    text:"Plot: "
                }
                Description
                {
                    text:series.overview
                    y:text1.y+text1.height+5
                }
            }
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
    tabModel:["Seasons","Info","Fan arts","Posters"]
    tabDelegate:TabItem{tabText:modelData;tabPage:seriesDetails}

    beginIndex:0
}
