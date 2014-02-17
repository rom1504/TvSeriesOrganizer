import QtQuick 2.1
import QtQuick.Controls 1.1


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
                    font.pointSize: 12
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
    }
    tabModel:["Seasons","Info"]
    tabDelegate:TabItem{tabText:modelData;tabPage:seriesDetails}

    beginIndex:0
}
