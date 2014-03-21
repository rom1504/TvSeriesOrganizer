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

    onTabChanged: stackview.get(2).episodeIndex=column
    onCurrentTabChanged:episodeDetails.imageSource=currentItem.myData.banner

    onBack:stackview.pop({immediate:true})

    tabContentModel: seasonModel
    tabContentDelegate:
        Flickable
        {
            property variant myData:episode
            flickableDirection:Flickable.VerticalFlick
            focus:true
            width: episodeDetails.width-40
            height:episodeDetails.height
            contentHeight: rect.height+400
            ShadowBorderRectangleText
            {
                id:rect
                height:tidi.height+seenRectangle.height
                onClicked:
                {
                    if(isMouseIn(seenRectangle)) seenRectangle.clicked()
                }
                TitleImageDescriptionItem
                {
                    id:tidi
                    title:episode.name
                    imageSource:episode.banner
                    description:qsTr("Episode number")+" "+episode.number+"\n"+qsTr("First aired")+": "+Qt.formatDateTime(episode.firstAired, "yyyy-MM-dd")+"\n"+episode.overview
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
       }
    tabDelegate:TabItem{tabText:qsTr("Episode")+" "+episode.number;tabPage:episodeDetails}

    beginIndex:episodeIndex
}
