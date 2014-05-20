import QtQuick 2.0
import "qrc:/GeneralQmlItems/"
import com.rom1504.TvSeriesOrganizer 1.0

TabPage
{
    id:seasonDetails
    imageSource:season.banner.small
    property int episodeIndex:0
    onEpisodeIndexChanged: listBeginIndex=episodeIndex
    property var seriesModel
    property var season
    property var seasonIndex
    onTabChanged: stackview.get(stackview.depth-2).seasonIndex=column
    onCurrentTabChanged:seasonDetails.imageSource=currentItem===null ? season.banner.small : currentItem.myData.banner.small
    tabContentModel: seriesModel
    property int listBeginIndex:episodeIndex
    property bool upcoming:false

    onBack:stackview.pop({immediate:true})


    function episodeClicked(episodeIndex,episode,upcoming,season)
    {
        seasonDetails.episodeIndex=episodeIndex
        stackview.push
        ({
           item:"qrc:/view/EpisodeDetails.qml",
           immediate:true,
           properties:
           {
               episodeIndex:seasonDetails.episodeIndex,
               episode:episode,
               seasonModel:upcoming ? season.seasonUpcomingModel : season.seasonModel,
               upcoming:upcoming
           }
        })
    }



    tabContentDelegate:
        CollectionView
        {
               id:episodeCollection
               viewType:settings.episodeCollectionStyle

               delegate:Episode
               {
                   fixedSize:episodeCollection.viewType===SettingsModel.GridView
                   width:episodeCollection.viewCellWidth+(episodeCollection.viewType===SettingsModel.GridView ? 10 : 0)
                   height: episodeCollection.viewType===SettingsModel.GridView ? episodeCollection.viewCellHeight+15 : defaultHeight
                   onEpisodeClicked:seasonDetails.episodeClicked(index,episode,upcoming,season)
               }
               gridCellAdditionalHeightMargin:5
               currentIndex: listBeginIndex
               width: seasonDetails.width-40
               height: seasonDetails.height
               model:upcoming ? season.seasonUpcomingModel : season.seasonModel
               defaultGridColumnNumber:1
               gridCellRatio:3/8
        }
    tabDelegate:TabItem{tabText:season.number===0 ? qsTr("Extras") : qsTr("Season")+" "+season.number;tabPage:seasonDetails}

    beginIndex:seasonIndex

}
