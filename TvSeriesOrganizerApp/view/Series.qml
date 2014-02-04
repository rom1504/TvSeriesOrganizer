import QtQuick 2.0

ShadowBorderRectangle
{
    text:series.name
    onClicked:listView.parent.seriesClicked(index)
}
