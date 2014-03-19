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

    onBack:Qt.quit()
    Component.onCompleted:if(seriesList.seriesCount>0) imageSource=seriesList.getSeries(0).banner

    Text
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
                    newImageSource=seriesList.getSeries(currentBannerIndex).banner;
                }
        }
        x:seriesListPage.width/2-width/2
        y:-height-seriesListPage.height/20
        width:contentWidth
        height:contentHeight
        font.pointSize: 35
        color:"white"
        font.family: "georgia"
        text:"Tv Series Organizer"
    }


    property int currentBannerIndex:0

    function seriesClicked(seriesNumber,upcoming)
    {
        timer.running=false
        seriesListPage.seriesIndex=seriesNumber
        stackview.push
        ({
             item:"qrc:/view/SeriesDetails.qml",
             immediate:true,
             properties:{series:seriesListPage.seriesList.getSeries(seriesNumber),upcoming:upcoming}
        })
    }

    function removeSeries(seriesNumber)
    {
        seriesList.removeSaveSeries(seriesNumber)
    }
    tabContentModel: VisualItemModel
    {
        ListView
        {
            Keys.onDownPressed: if(currentIndex-1<count) listview.incrementCurrentIndex()
            Keys.onUpPressed: if(currentIndex>0) listview.decrementCurrentIndex()
            Keys.onReturnPressed:seriesListPage.seriesClicked(currentIndex,false);
            delegate: Series{onSeriesClicked: seriesListPage.seriesClicked(index,false)}
            model:seriesList.seriesListModel
            width: seriesListPage.width-40
            height: seriesListPage.height
            currentIndex: seriesIndex
            focus:true
            clip:true


            highlightRangeMode:ListView.StrictlyEnforceRange
            id:listview
        }
        ListView
        {
            delegate: Series{onSeriesClicked: seriesListPage.seriesClicked(index,true)}
            model:seriesList.seriesListUpcomingModel
            width: seriesListPage.width-40
            height: seriesListPage.height
            currentIndex: seriesIndex
            focus:true
            clip:true


            highlightRangeMode:ListView.StrictlyEnforceRange
            id:listviewupcoming
            Keys.onDownPressed: listviewupcoming.incrementCurrentIndex()
            Keys.onUpPressed: listviewupcoming.decrementCurrentIndex()
            Keys.onReturnPressed:listviewupcoming.currentItem.Keys.onReturnPressed(event)
        }
        SeriesSearch
        {
            seriesList:seriesListPage.seriesList
            width: seriesListPage.width-40
            height: seriesListPage.height
            onSearchFinished:
            {
                seriesListPage.goTo(0)
                listview.currentIndex=addIndex;
            }
        }
    }

    tabModel:[qsTr("Series"),qsTr("Upcoming"),qsTr("Search")]
    tabDelegate:TabItem{tabText:modelData;tabPage:seriesListPage}
    beginIndex: seriesList.seriesCount===0 ? 2 : 0
}
