import QtQuick 2.1
import QtQuick.Controls 1.1
import QtGraphicalEffects 1.0


TabPage
{
    id:seriesDetails
    imageSource:series.banner
    signal seasonClicked(int seasonNumber)
    property int listBeginIndex:seasonIndex
    tabContentModel: VisualItemModel
    {
        ListView
        {
            delegate:Season{}
            model:seriesModel
            width: seriesDetails.width-40
            height: seriesDetails.height
            currentIndex: listBeginIndex

            highlightRangeMode:ListView.StrictlyEnforceRange
            id:listview
            Keys.onDownPressed: listview.incrementCurrentIndex()
            Keys.onUpPressed: listview.decrementCurrentIndex()
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

            delegate:
                FixedSizeShadowBorderItem
                {
                    width:fanArtsView.cellWidth-fanArtsView.itemMargin
                    height:fanArtsView.cellHeight-fanArtsView.itemMargin
                    Image
                    {
                        id:fanArtImage
                        width:parent.width
                        height:parent.height
                        source:fanArt
                    }
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

            delegate:
                FixedSizeShadowBorderItem
                {
                    width:postersView.cellWidth-postersView.itemMargin
                    height:postersView.cellHeight-postersView.itemMargin
                    Image
                    {
                        id:posterImage
                        width:parent.width
                        height:parent.height
                        source:poster
                    }
                }
        }
    }
    tabModel:["Seasons","Info","Fan arts","Posters"]
    tabDelegate:TabItem{tabText:modelData;tabPage:seriesDetails}

    beginIndex:0
}
