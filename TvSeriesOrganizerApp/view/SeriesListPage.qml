import QtQuick 2.2
import "qrc:/GeneralQmlItems/"

TabPage
{
    id:seriesListPage
    imageSource:"qrc:/images/TvSeriesOrganizerHeader.png"
    property int seriesIndex:0
    property var seriesList
    onTabChanged: stackview.focus=true
    property alias stimer:timer
    title:"Tv Series Organizer"

    onBack:stackview.depth===1 ? Qt.quit() : stackview.pop({immediate:true})
    Component.onCompleted:if(seriesList.seriesCount>0) imageSource=seriesList.getSeries(0).banner.small

    inImage:
    Row
    {
        x:seriesListPage.width-120
        spacing:0
        ImageButton
        {
            id:exploreContainer
            width: 50
            height: width
            tolerance:5
            imageSource:"qrc:/images/add.png"
            onClicked: stackview.push
                       ({
                            item:"qrc:/view/ExploreSeries.qml",
                            immediate:true,
                            properties:{followedSeriesList:seriesList}
                       })
        }

        ImageButton
        {
            id:settingsButton
            width: 50
            height: width
            tolerance:5
            imageSource:"qrc:/images/settings_white.png"
            onClicked: stackview.push
                       ({
                            item:"qrc:/view/Settings.qml",
                            immediate:true,
                            properties:{followedSeriesList:seriesList}
                       })
        }
    }

    Item
    {

        Timer
         {
                 id:timer
                 interval: 5000
                 running: seriesList.seriesCount>0
                 repeat: true
                 onTriggered:
                 {
                     currentBannerIndex++;
                     if(currentBannerIndex>=seriesList.seriesCount) currentBannerIndex=0;
                     newImageSource=seriesList.getSeries(currentBannerIndex).banner.small;
                 }
         }
    }



    property int currentBannerIndex:0

    function seriesClicked(seriesIndex,series,upcoming)
    {
        timer.running=false
        seriesListPage.seriesIndex=seriesIndex
        stackview.push
        ({
             item:"qrc:/view/SeriesDetails.qml",
             immediate:true,
             properties:{series:series,upcoming:upcoming}
        })
    }

    function removeSeries(series)
    {
        seriesList.removeSaveSeries(series)
    }
    tabContentModel: VisualItemModel
    {
        SeriesCollection
        {
            id:seriesCollection
            model:seriesList.seriesListModel
            width: seriesListPage.width-40
            height: seriesListPage.height
            currentIndex: seriesIndex
            onSeriesClicked: seriesListPage.seriesClicked(seriesIndex,series,false)
            onSeriesRemoved: seriesListPage.removeSeries(series)
            grid:settings.seriesCollectionStyle
        }

        SeriesCollection
        {
            id:seriesCollectionUpcoming
            model:seriesList.seriesListUpcomingModel
            width: seriesListPage.width-40
            height: seriesListPage.height
            currentIndex: seriesIndex
            onSeriesClicked: seriesListPage.seriesClicked(seriesIndex,series,true)
            onSeriesRemoved: seriesListPage.removeSeries(series)
            grid:settings.seriesCollectionStyle
        }

        SeriesSearch
        {
            seriesList:seriesListPage.seriesList
            width: seriesListPage.width-40
            height: seriesListPage.height
            onSearchFinished:
            {
                seriesListPage.goTo(0)
                seriesCollection.currentIndex=addIndex;
            }
        }
    }

    tabModel:[qsTr("Series"),qsTr("Upcoming"),qsTr("Search")]
    tabDelegate:TabItem{tabText:modelData;tabPage:seriesListPage}
    beginIndex: seriesList.seriesCount===0 ? 2 : 0
}
