import QtQuick 2.0

SimplePage
{
    id:tabPage
    signal tabChanged(int column)
    signal currentTabChanged(int currentIndex,Item currentItem)
    signal tabClicked(int index)
    property alias tabContentModel: listview.model
    property var tabModel:tabContentModel
    property alias tabContentDelegate: listview.delegate
    property alias tabDelegate:tabList.delegate
    property alias tabBar:tabbar
    property int beginIndex

    onTabClicked: {listview.positionViewAtIndex(index,ListView.Center);listview.contentXChanged();}

    ListView
    {
        id:listview
        width: tabPage.width-40
        height: tabPage.height
        Component.onCompleted: {positionViewAtIndex(beginIndex,ListView.Center); contentXChanged();}
        clip: true
        highlightRangeMode:ListView.StrictlyEnforceRange
        orientation:ListView.Horizontal
        snapMode:ListView.SnapOneItem
        onContentXChanged:
        {
            var newX=(listview.contentX/(tabPage.width-40)-1)*(tabPage.width-100)/3
            tabList.contentX=newX<0 || newX>(tabPage.width-100)/3*(count-3)? tabList.contentX : newX
            if(newX<0) marquer.x=newX+tabbar.width/3;
            else if(newX>(tabPage.width-100)/3*(count-3) && count>2) marquer.x=newX+tabbar.width/3-(tabPage.width-100)/3*(count-3);
            else marquer.x=tabbar.width/3;
        }
        onCurrentIndexChanged:
        {
            tabPage.currentTabChanged(listview.currentIndex,listview.currentItem)
            tabChanged(listview.currentIndex)
        }
    }
    Item
    {
        id:tabbar
        height:50
        width:tabPage.width-100
        clip:true
        y:-70

        ListView
        {
            id:tabList
            width:parent.width
            model:tabModel
            orientation:ListView.Horizontal
        }

        Rectangle
        {
            id:marquer
            x:tabbar.width/3
            width:tabbar.width/3
            height:8
            y:tabbar.height-21
            color:"#EAEAEA"
        }
    }

}
