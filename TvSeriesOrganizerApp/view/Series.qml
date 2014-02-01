import QtQuick 2.0

ShadowBorderRectangle
{
    text:series.name
    height: 40
    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked:listView.parent.seriesClicked(index)
    }
}
