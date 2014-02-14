import QtQuick 2.0

SimplePage
{
    id:seasonDetails
    signal episodeClicked(int episodeNumber)
    signal seasonChanged(int row)
    imageSource:season.banner
    ListView
    {
        id:listview
        width: seasonDetails.width-40
        height: parent.height
        Component.onCompleted: positionViewAtIndex(seasonIndex,ListView.Center)
        clip: true
        highlightRangeMode:ListView.StrictlyEnforceRange
        orientation:ListView.Horizontal
        snapMode:ListView.SnapOneItem
        model:seriesModel
        delegate:
            ListView
                {
                    property variant myData:season
                    delegate:Episode{}
                    model:season.seasonModel
                    width: seasonDetails.width-40
                    height: parent.height
                }
        onContentXChanged: tabList.contentX=(listview.contentX/(seasonDetails.width-40)-1)*(seasonDetails.width-100)/3
        onCurrentIndexChanged:
            {
                seasonDetails.imageSource=listview.currentItem.myData.banner;
                seasonChanged(listview.currentIndex)
            }
    }
    Item
    {
        id:tabBar
        height:50
        width:seasonDetails.width-100
        clip:true
        y:-70

        ListView
        {
            id:tabList
            width:parent.width
            model:seriesModel
            orientation:ListView.Horizontal
            delegate:
                Text
                {
                    MouseArea
                    {
                        id: mouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: seriesDetails.seasonClicked(index)
                    }
                    text:"Season "+season.number
                    font.family: "Arial"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: "#E5E5E5"
                    font.pointSize: 15
                    width:tabBar.width/3
                }
        }

        Rectangle
        {
            x:(seasonIndex===0 ? 0 : (seasonIndex === series.seasonCount-1 ? 2 : 1))*tabBar.width/3
            width:tabBar.width/3
            height:8
            y:tabBar.height-21
            color:"#EAEAEA"
        }
    }

}
