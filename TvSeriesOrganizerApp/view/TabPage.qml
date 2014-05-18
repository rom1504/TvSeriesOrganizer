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

    property int defaultTabNumber: 3
    property int maxTabNumber:10
    property int computedTabNumber: (tabPage.width-40)/540*defaultTabNumber
    property int tabNumber:computedTabNumber>maxTabNumber ? maxTabNumber : computedTabNumber
    //property int tabNumber: 17

    function goTo(index)
    {
        listview.goTo(index)
    }


    ListView
    {

        function goTo(index)
        {
            if(index<0) return
            if(index>count-1) return
            listview.currentIndex=index
            contentX=(tabPage.width-40)*index
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
        Timer{interval:10;id:timer;onTriggered:goTo(beginIndex)}
        Component.onCompleted: timer.start()
        clip: true
        focus:true
        orientation:ListView.Horizontal
        snapMode:ListView.SnapOneItem

        onContentXChanged:
        {
            currentIndex=Math.round(listview.contentX/listview.width)
            var stayOn=Math.ceil(tabNumber/2)
            var tabWidth=tabbar.width/tabNumber
            var itemWidth=tabPage.width-40
            var newX=listview.contentX/itemWidth*tabWidth
            if(newX>tabWidth*(stayOn-1) || (tabList.contentX+tabWidth*(stayOn-1)>tabWidth*(stayOn-1) && newX>tabWidth*(stayOn-2)))
            {
                if(newX>tabWidth*(count-1-(tabNumber-stayOn)) || (marker.x>tabWidth*(stayOn-1) && newX>tabWidth*(count-2-(tabNumber-stayOn))))
                {
                    //console.log("the last one")
                    marker.x=newX-tabWidth*(count-1-(tabNumber-stayOn))+(count>=tabNumber ? tabWidth*(stayOn-1) : tabWidth)
                    //useful when jumping
                    tabList.contentX=count>tabNumber ? (tabWidth*(count-tabNumber)) : 0
                }
                else
                {
                    //console.log("after the penultimate which can go in the bar")
                    tabList.contentX=newX-tabWidth*(stayOn-1)
                    //useful when jumping
                    marker.x=tabWidth*(stayOn-1)
                }
            }
            else
            {
                //console.log("before the penultimate which can go in the bar")
                marker.x=newX;
                //useful when jumping
                tabList.contentX=0
            }

            // 3 cases
            // - 1) before the penultimate which can go in the bar : the tabList doesn't move, the marker moves
            // - 2) after the penultimate which can go in the bar : the tabList moves, the marker stay on the penultimate
            // - 3) the last one : the list doesn't move, the marker moves on the last one
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
                snapMode:ListView.SnapOneItem

                height:contentItem.childrenRect.height
                id:tabList
                width:parent.width
                model:tabModel
                orientation:ListView.Horizontal
            }

            Rectangle
            {
                id:marker
                width:tabbar.width/tabNumber
                height:5
                color:"#EAEAEA"
            }
        }
    }

}
