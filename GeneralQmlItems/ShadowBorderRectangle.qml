import QtQuick 2.0
import QtGraphicalEffects 1.0


Item
{
    id:root
    width: parent.width
    height:container.height
    property alias mouseX : mouseArea.mouseX
    property alias mouseY : mouseArea.mouseY
    default property alias children : insideItem.children
    signal clicked
    signal pressAndHold

    function isMouseIn(rect)
    {
        return rect.x<mouseX-10 && mouseX-10<rect.x+rect.width && rect.y<mouseY-10 && mouseY-10<rect.y+rect.height;
    }

    Item
    {
        id: container
        anchors.centerIn: parent
        width:  parent.width
        height: rect.height + (2 * rectShadow.radius)

        Rectangle
        {
            id: rect
            height: insideItem.childrenRect.height +insideItem.y+5
            width: parent.width-(2 * rectShadow.radius)
            color: "white"
            radius: 2
            antialiasing: true
            border
            {
                width: 1
                color: "#EAEAEA"
            }
            anchors.centerIn: parent
            Item
            {
                id:insideItem
                x: 5;
                y: 5;
                width:parent.width-5
            }
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
        onClicked: parent.clicked()
        onPressAndHold:parent.pressAndHold()
    }
}
