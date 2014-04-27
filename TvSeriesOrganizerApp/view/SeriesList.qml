import QtQuick 2.0

ListView
{
    signal seriesClicked(int index,var series)
    signal seriesRemoved(var series)
    Keys.onDownPressed: listview.incrementCurrentIndex()
    Keys.onUpPressed: listview.decrementCurrentIndex()
    Keys.onReturnPressed:listview.currentItem.Keys.onReturnPressed(event)
    delegate: Series
    {
        onSeriesClicked: listview.seriesClicked(index,series)
        onSeriesRemoved: listview.seriesRemoved(series)
    }
    focus:true
    clip:true
    highlightRangeMode:ListView.StrictlyEnforceRange
    id:listview
}
