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

    onTabChanged: stackview.get(stackview.depth-2).episodeIndex=column
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
            contentHeight: col.height+400
            Column
            {
                id:col
                spacing:5
                height:rect.height+rect2.height
                ShadowBorderRectangleButton
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
                ShadowBorderRectangle
                {
                    visible:!noPlugin
                    id:rect2
                    height:listviewPlugin.height
                    ListView
                    {
                        id:listviewPlugin
                        delegate:TextButton
                        {
                            text: plugin.buttonName
                            onClicked: plugin.run(episode)
                        }
                        orientation:ListView.Horizontal
                        model:pluginModel
                        width: episodeDetails.width-40
                        height: 35
                        focus:true
                        clip:true
                    }

                    width:episodeDetails.width-40
                }
            }
       }
    tabDelegate:TabItem{tabText:qsTr("Episode")+" "+episode.number;tabPage:episodeDetails}

    beginIndex:episodeIndex
}
