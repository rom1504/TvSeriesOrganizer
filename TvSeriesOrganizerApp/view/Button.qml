import QtQuick 2.0

Item
{
    id:container
    width: button.width +5
    height: button.height +5
    signal clicked
    property alias text:button.text
    Rectangle
    {
        id: rectangle
        border.color: "white"
        anchors.fill: parent
        Text
        {
            font.pointSize: 12
            id: button
        }
    }
    MouseArea
    {
        id:area
        anchors.fill: parent
        onClicked: container.clicked()
    }
}
