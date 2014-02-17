import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle
{
    id: simplePage
    width: 580
    height: 880
    color: "#EAEAEA"
    signal back()
    property alias imageSource:image.source
    default property alias children : insidePageItem.children

    Image
    {
        id:image
        x:0
        y:0
        //sourceSize.width: parent.width
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
