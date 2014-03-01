import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

TabPage
{
    id:seasonDetails
    imageSource:season.banner
    property int episodeIndex:0
    property var seriesModel
    property var season
    property var seasonIndex
    onTabChanged: stackview.get(1).seasonIndex=column
    onCurrentTabChanged:seasonDetails.imageSource=currentItem.myData.banner;
    tabContentModel: seriesModel
    property int listBeginIndex:episodeIndex

    onBack:stackview.pop({immediate:true})


    function episodeClicked(episodeNumber)
    {
        episodeIndex=episodeNumber
        stackview.push
        ({
           item:episodeDetailsItem,
           immediate:true,
           properties:
           {
               episodeIndex:seasonDetails.episodeIndex,
               episode:season.getEpisode(episodeNumber),
               seasonModel:season.seasonModel
           }
        })
    }

    tabContentDelegate:
        ListView
        {
            property variant myData:season
            delegate:Episode{}
            model:season.seasonModel
            width: seasonDetails.width-40
            height: parent.height
            currentIndex: listBeginIndex
            highlightRangeMode:ListView.StrictlyEnforceRange
            id:listview
            Keys.onDownPressed: listview.incrementCurrentIndex()
            Keys.onUpPressed: listview.decrementCurrentIndex()
        }
    tabDelegate:TabItem{tabText:"Season "+season.number;tabPage:seasonDetails}

    beginIndex:seasonIndex
}
