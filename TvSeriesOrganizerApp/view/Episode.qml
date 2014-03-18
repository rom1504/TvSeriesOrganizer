import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

ShadowBorderRectangle
{
    signal episodeClicked(int index)

    Keys.onReturnPressed: episodeClicked(index)
    onClicked:
    {
        if(isMouseIn(seenRectangle)) seenRectangle.clicked()
        else episodeClicked(index)
    }
    TitleImageDescriptionItem
    {
        title:episode.name
        imageSource:episode.banner
        description:qsTr("Episode number")+" "+episode.number+"\n"+(episode.aired ? qsTr("First aired") : qsTr("Will be aired"))+": "+Qt.formatDateTime(episode.firstAired, "yyyy-MM-dd")+"\n"+episode.overview
    }
    SeenIndicator
    {
        id:seenRectangle
        seen:episode.seen
        onSeenHasChanged:episode.seen=seenRectangle.seen
        x:parent.width-width-5
    }
}
