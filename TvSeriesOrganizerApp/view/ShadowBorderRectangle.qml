import QtQuick 2.0
import QtGraphicalEffects 1.0


Item
{
    id:root
    width: parent.width*0.8
    x: 10
    property alias text:insideText.text

    Item
    {
        id: container
        anchors.centerIn: parent
        width:  rect.width  + (2 * rectShadow.radius)
        height: rect.height + (2 * rectShadow.radius)

        Rectangle
        {
            id: rect
            width: 300
            height: root.height-10
            color: "white"
            radius: 2
            antialiasing: true
            border
            {
                width: 1
                color: "#EAEAEA"
            }
            anchors.centerIn: parent
        }
        Text
        {
            id:insideText
            x: 15;
            y: 15;
            font.pointSize: 12
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
    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
    }
}
