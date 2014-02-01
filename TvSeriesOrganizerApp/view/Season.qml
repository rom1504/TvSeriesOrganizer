import QtQuick 2.0

ShadowBorderRectangle
{
    text:"Season " + season.number
    height: 40
    onClicked:listView.parent.seasonClicked(index)
}
