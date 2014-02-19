import QtQuick 2.0


TabPage
{
    id:episodeDetails
    imageSource:episode.banner
    signal episodeChanged(int column)
    onTabChanged: episodeChanged(column)
    onCurrentTabChanged:episodeDetails.imageSource=currentItem.myData.banner;
    tabContentModel: seasonModel
    tabContentDelegate:
        ShadowBorderRectangleText
        {
            property variant myData:episode
            TitleImageDescriptionItem
            {
                title:episode.name
                imageSource:episode.banner
                description:"Episode number "+episode.number+"\n"+"First aired: "+Qt.formatDateTime(episode.firstAired, "yyyy-MM-dd")+"\n"+episode.overview
            }
            width:episodeDetails.width-40
        }
    tabDelegate:TabItem{tabText:"Episode "+episode.number;tabPage:episodeDetails}

    beginIndex:episodeIndex
}
