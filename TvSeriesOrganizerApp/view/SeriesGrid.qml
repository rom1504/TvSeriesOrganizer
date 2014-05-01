import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

GridView
{
    id:seriesL
    property Component seriesComp
    signal seriesClicked(int index,var series)
    delegate:Item
    {
        id:seriesItem
        width:seriesL.cellWidth-seriesL.itemMargin
        height:seriesL.cellHeight-seriesL.itemMargin
        signal clicked()
        property bool pressed
        signal pressAndHold()
        onClicked:seriesL.seriesClicked(index,series)
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
            sourceComponent: seriesComp
        }
    }
    property bool cellFixedSize: true
    property int defaultColumnNumber: 3
    cellWidth:cellFixedSize ? width/Math.floor(width/((580-40)/defaultColumnNumber)) : width/defaultColumnNumber
    cellHeight: cellWidth/138*203*0.99
    property double itemMargin: cellWidth*0.03
    highlightRangeMode:ListView.StrictlyEnforceRange
    Keys.onDownPressed: moveCurrentIndexDown()
    Keys.onUpPressed: moveCurrentIndexUp()

    Keys.onReturnPressed:currentItem.Keys.onReturnPressed(event)
}
