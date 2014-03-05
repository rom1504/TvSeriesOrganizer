import QtQuick 2.0
import "qrc:/GeneralQmlItems/"


TabPage
{
    id:episodeDetails
    imageSource:episode.banner

    property int episodeIndex
    property var seasonModel
    property var episode
    property bool upcoming:false
// à fin

    onTabChanged: stackview.get(2).episodeIndex=column
    onCurrentTabChanged:episodeDetails.imageSource=currentItem.myData.banner;

    onBack:stackview.pop({immediate:true})

    tabContentModel: seasonModel
    tabContentDelegate:
        ShadowBorderRectangleText
        {
            property variant myData:episode
            onClicked:
            {
                if(isMouseIn(seenRectangle)) seenRectangle.clicked()
            }
            TitleImageDescriptionItem
            {
                title:episode.name
                imageSource:episode.banner
                description:"Episode number "+episode.number+"\n"+"First aired: "+Qt.formatDateTime(episode.firstAired, "yyyy-MM-dd")+"\n"+episode.overview
            }
            SeenIndicator
            {
                id:seenRectangle
                seen:episode.seen
                onSeenHasChanged:episode.seen=seenRectangle.seen
                x:parent.width-width-5
            }
            width:episodeDetails.width-40
        }
    tabDelegate:TabItem{tabText:"Episode "+episode.number;tabPage:episodeDetails}

    beginIndex:episodeIndex
}
