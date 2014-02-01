import QtQuick 2.0

ShadowBorderRectangle
{
    text:series.name
    height: 40
    onClicked:listView.parent.seriesClicked(index)
}
