import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

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
    function goRight() {listview.goRight()}
    function goLeft() {listview.goLeft()}
    onLeft:listview.Keys.onLeftPressed(event)
    onRight:listview.Keys.onRightPressed(event)

    onUp:listview.currentItem.Keys.onUpPressed(event)
    onDown:listview.currentItem.Keys.onDownPressed(event)


    onEnter:listview.currentItem.Keys.onReturnPressed(event)

    onTabClicked: listview.goTo(index)


    ListView
    {

        function goTo(index)
        {
            if(index<0) return
            if(index>count-1) return
            listview.positionViewAtIndex(index,index===0 ? ListView.Left : (index===count-1 ? ListView.Right : ListView.Center));
            listview.currentIndex=index
        }

        function goLeft()
        {
            goTo(currentIndex-1)
        }
        function goRight()
        {

            goTo(currentIndex+1)
        }

        id:listview
        width: tabPage.width-40
        height: tabPage.height
        Component.onCompleted: goTo(beginIndex)
        clip: true
        focus:true
        orientation:ListView.Horizontal
        snapMode:ListView.SnapOneItem

        onContentXChanged:
        {
            var newX=(listview.contentX/(tabPage.width-40)-1)*tabbar.width/3
            if(newX<0) marquer.x=newX+tabbar.width/3;
            else if(newX>tabbar.width/3*(count-3) && count>2) marquer.x=newX+tabbar.width/3-tabbar.width/3*(count-3);
            else
            {
                marquer.x=tabbar.width/3;
                tabList.contentX=newX
            }
            currentIndex=Math.round(listview.contentX/listview.width)
        }
        onCurrentIndexChanged:
        {
            tabPage.currentTabChanged(listview.currentIndex,listview.currentItem)
            tabChanged(listview.currentIndex)
        }
        Keys.onLeftPressed: goLeft()
        Keys.onRightPressed: goRight()
    }
    Item
    {
        id:tabbar
        height:50
        width:tabPage.width-40

        clip:true
        y:-5-citem.height

        Column
        {
            id:citem
            spacing: 2
            width:parent.width
            ListView
            {
                interactive:false
                Component.onCompleted: positionViewAtIndex(beginIndex==count-1 && count>2 ? beginIndex-1 : beginIndex,ListView.Center);
                snapMode:ListView.SnapOneItem

                height:contentItem.childrenRect.height
                id:tabList
                width:parent.width
                model:tabModel
                orientation:ListView.Horizontal
            }

            Rectangle
            {
                id:marquer
                width:tabbar.width/3
                height:5
                color:"#EAEAEA"
                Component.onCompleted:
                {
                    if(beginIndex==0) x=0;
                    else if(beginIndex==tabList.count-1) x=2*tabbar.width/3;
                    else x=tabbar.width/3;
                }
            }
        }
    }

}
