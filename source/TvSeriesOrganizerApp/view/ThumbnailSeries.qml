import QtQuick 2.0

Item
{
    id:seriesItem
    signal clicked()
    property bool pressed
    signal pressAndHold()
    property Component addition
    onPressAndHold:loader.item.pressAndHold()

    Image
    {
        id:image
        width:parent.width
        height: image.width/138*203
        fillMode: Image.PreserveAspectCrop
        source:series.poster.small
    }

    MouseArea
    {
        hoverEnabled:true
        id:area
        anchors.fill: parent
        onClicked: parent.clicked()
        onPressedChanged: parent.pressed=pressed

        onPressAndHold:parent.pressAndHold()
    }

    Loader
    {
        id:loader
        property Item delegateItem:seriesItem
        property Image seriesImage: image
        property var mseries:series
        sourceComponent: addition
    }
}
