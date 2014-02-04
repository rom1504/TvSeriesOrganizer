import QtQuick 2.0

ShadowBorderRectangle
{
    text:"Season " + season.number
    onClicked:listView.parent.seasonClicked(index)
}
