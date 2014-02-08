import QtQuick 2.0

Rectangle
{
    id: simplePage
    width: 580
    height: 880
    color: "#EAEAEA"
    signal back()
    property alias imageSource:image.source

    Image
    {
        id:image
        x:0
        y:0
        width: parent.width
        height: 200
    }
    Item
    {
        x:parent.width-60
        y:215
        width: backButton.width +5
        height: backButton.height +5
        Rectangle
        {
            id: rectangle
            border.color: "white"
            anchors.fill: parent
            Text
            {
                font.pointSize: 12
                id: backButton
                text: "Back"
            }
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked: parent.parent.back()
        }
    }
}
