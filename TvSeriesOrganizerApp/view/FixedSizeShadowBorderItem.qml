import QtQuick 2.0
import QtGraphicalEffects 1.0

Item
{
    id:root
    width: parent.width
    height: parent.height
    default property alias children : insideItem.children

    Item
    {
        id: container
        anchors.centerIn: parent
        width:  parent.width
        height: parent.height
        Item
        {
            height: parent.height-(2 * rectShadow.radius)
            width: parent.width-(2 * rectShadow.radius)
            antialiasing: true
            anchors.centerIn: parent
            id:insideItem
            visible:false
        }
        Rectangle
        {
            height: parent.height-(2 * rectShadow.radius)
            width: parent.width-(2 * rectShadow.radius)
            antialiasing: true
            anchors.centerIn: parent
            id:rect
            radius:3
            visible:false
        }
        OpacityMask
        {
            anchors.fill: insideItem
            source: insideItem
            maskSource: rect
        }
    }
    DropShadow
    {
        id: rectShadow
        anchors.fill: source
        cached: true
        horizontalOffset: 1.5
        verticalOffset: 1.5
        radius: 8.0
        samples: 16
        color: "#80000000"
        smooth: true
        source: container
    }
}
