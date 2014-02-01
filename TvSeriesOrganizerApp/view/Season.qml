import QtQuick 2.0

ShadowBorderRectangle
{
    text:"Season " + season.number
    height: 40
    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked:listView.parent.seasonClicked(index)
    }
}
