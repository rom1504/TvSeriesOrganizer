import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

ShadowBorderRectangle
{
    Keys.onReturnPressed: seasonDetails.episodeClicked(index)
    onClicked: seasonDetails.episodeClicked(index)
    TitleImageDescriptionItem
    {
        title:episode.name
        imageSource:episode.banner
        description:"Episode number "+episode.number+"\n"+"First aired: "+Qt.formatDateTime(episode.firstAired, "yyyy-MM-dd")+"\n"+episode.overview
    }
}
