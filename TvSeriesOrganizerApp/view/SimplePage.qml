import QtQuick 2.0
import QtGraphicalEffects 1.0
import "qrc:/GeneralQmlItems/"


Rectangle
{
    id: simplePage

    width: awidth
    height: aheight
    color: "#EAEAEA"
    signal left(var event)
    signal right(var event)
    signal up(var event)
    signal down(var event)
    signal back()
    signal bback(var event)
    signal enter(var event)
    onBback: back()

    property alias imageSource:image.source
    default property alias children : insidePageItem.children
    property alias buttonBarHeight:backContainer.height
    Keys.onBackPressed: simplePage.back()
    Keys.onPressed: if(event.key === Qt.Key_Backspace) simplePage.back()
    Image
    {
        id:image
        x:0
        y:0
        width:parent.width
        height:width*sourceSize.height/sourceSize.width
    }

    BrightnessContrast {
            anchors.fill: image
            source: image
            brightness: -0.3
        }

    Button
    {
        id:backContainer
        x:parent.width-60
        y:image.height+5
        onClicked:simplePage.back()
        text:"Back"
    }
    Item
    {
        id:insidePageItem
        x:20
        y:backContainer.height+backContainer.y+5
        height:simplePage.height-backContainer.y-backContainer.height
    }
}
