import QtQuick 2.1
import QtGraphicalEffects 1.0
import com.rom1504.TvSeriesOrganizer 1.0
import "qrc:/GeneralQmlItems/"


TabPage
{
    id:seriesDetails
    imageSource:series.banner.small
    property int seasonIndex:0
    property var series
    property int listBeginIndex:seasonIndex
    property bool upcoming:false

    onBack:
    {
        stackview.get(stackview.depth-2).stimer.running=true
        stackview.pop({immediate:true})
    }

    function seasonClicked(seasonIndex,season,upcoming)
    {
        seriesDetails.seasonIndex=seasonIndex
        stackview.push
        ({
             item:"qrc:/view/SeasonDetails.qml",
             immediate:true,
             properties:
             {
                 seasonIndex:seriesDetails.seasonIndex,
                 season:season,
                 seriesModel:upcoming ? series.seriesUpcomingModel : series.seriesModel,
                 upcoming:upcoming
             }
         })
    }

    tabContentModel: VisualItemModel
    {
        CollectionView
        {
               id:seasonCollection
               viewType:settings.seasonCollectionStyle

               delegate:Season
                   {
                       fixedSize:seasonCollection.viewType===SettingsModel.GridView
                       width:seasonCollection.viewCellWidth+(seasonCollection.viewType===SettingsModel.GridView ? 10 : 0)
                       height: seasonCollection.viewType===SettingsModel.GridView ? seasonCollection.viewCellHeight+15 : defaultHeight
                       onSeasonClicked: seriesDetails.seasonClicked(index,season,upcoming)
                   }
               gridCellAdditionalHeightMargin:5
               currentIndex: listBeginIndex
               width: seriesDetails.width-40
               height: seriesDetails.height
               model:upcoming ? series.seriesUpcomingModel : series.seriesModel
               defaultGridColumnNumber:1
               gridCellRatio:3/8
        }


        Flickable
        {
            flickableDirection:Flickable.VerticalFlick
            focus:true
            width: seriesDetails.width-40
            height:seriesDetails.height
            contentHeight: scol.height+150
            Column
            {
                id:scol
                height:childrenRect.height
                spacing:20
                ShadowBorderRectangleButton
                {
                    id:firstRect
                    width:seriesDetails.width-40
                    height:col.height+20
                    Column
                    {
                        id:col
                        spacing:1
                        Title
                        {
                            id:text3
                            text:qsTr("Details")+": "
                            width:contentWidth
                            height:contentHeight
                        }

                        Row
                        {
                            spacing:1
                            height:labels.contentHeight
                            Text
                            {
                                width:contentWidth
                                id:labels
                                font.family: 'arial'
                                wrapMode: Text.WordWrap
                                font.pointSize:  12
                                text:qsTr("Network")+": \n"+qsTr("First aired")+": "
                            }
                            Text
                            {
                                width:contentWidth
                                font.family: 'arial'
                                wrapMode: Text.WordWrap
                                font.pointSize: 12
                                color: "#717171"
                                text:series.network+"\n"+Qt.formatDateTime(series.firstAired, "yyyy-MM-dd")
                            }
                        }
                    }
                }
                ShadowBorderRectangleButton
                {
                    width:seriesDetails.width-40
                    height:col2.height
                    Column
                    {
                        width:seriesDetails.width-40
                        id:col2
                        Title
                        {
                            id:text1
                            text:qsTr("Plot")+": "

                        }
                        Description
                        {
                            width:seriesDetails.width-80
                            text:series.overview
                        }
                    }
                }
            }
        }
        CommonGridView
        {
            id:actorCollection
            delegate:ShadowBorderRectangle
            {
                fixedSize:true
                width:actorCollection.realCellWidth+10
                height:actorCollection.realCellHeight+15
                TitleImageDescriptionItem
                {
                    title:actor.name
                    imageSource:actor.image.small
                    description:qsTr("Role")+": "+actor.role+"\n"+qsTr("Importance")+": "+
                                (actor.sortOrder===3 ? qsTr("Low") :
                                (actor.sortOrder===2 ? qsTr("Medium") :
                                (actor.sortOrder===1 ? qsTr("High") :
                                (actor.sortOrder===0 ? qsTr("Very High") : ""))))
                }
              }
            cellRatio:3/8
            model:series.actorListModel
            width: seriesDetails.width-40
            height: seriesDetails.height
            currentIndex: 0
            defaultColumnNumber: 1
        }
        CommonGridView
        {
            id:fanArtsView
            width: seriesDetails.width-40
            height:seriesDetails.height
            model:series.fanArts
            cellRatio:1080/1920
            defaultColumnNumber: 2

            delegate:ImageButton
                {
                    width:fanArtsView.realCellWidth
                    height:fanArtsView.realCellHeight
                    imageSource:fanArt.small
                    onClicked:stackview.push({item:"qrc:/view/ImageViewer.qml",immediate:true,properties:{bigImageSource:fanArt.big}})
                }
        }
        CommonGridView
        {
            id:postersView
            width: seriesDetails.width-40
            height:seriesDetails.height
            defaultColumnNumber: 3
            cellRatio: 1000/680
            model:series.posters


            delegate:
                 ImageButton
                {
                     width:postersView.realCellWidth
                     height:postersView.realCellHeight
                    imageSource:poster.small
                    onClicked:stackview.push({item:"qrc:/view/ImageViewer.qml",immediate:true,properties:{bigImageSource:poster.big}})
                }
        }
    }
    tabModel:[qsTr("Seasons"),qsTr("Info"),qsTr("Actors"),qsTr("Fan arts"),qsTr("Posters")]
    tabDelegate:TabItem{tabText:modelData;tabPage:seriesDetails}

    beginIndex:0
}
