import QtQuick 2.0

Rectangle
{
    id: simplePage
    width: 400
    height: 800
    color: "#EAEAEA"
    signal back()

    Item
    {
        x:350
        y:10
        width:40
        height:20
        Rectangle
        {
            id: rectangle
            border.color: "white"
            anchors.fill: parent
        }
        Text
        {
            font.pointSize: 12
            id: backButton
            text: "Back"
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked: parent.parent.back()
        }
    }
}
