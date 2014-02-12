import QtQuick 2.0

SimplePage
{
    id: episodeDetails
    imageSource:episode.banner
    ShadowBorderRectangleText
    {
        TitleImageDescriptionItem
        {
            title:episode.name
            imageSource:episode.banner
            description:"Episode number "+episode.number+"\n"+"First aired: "+Qt.formatDateTime(episode.firstAired, "yyyy-MM-dd")+"\n"+episode.overview
        }
        width:episodeDetails.width-40
    }

}
