import QtQuick 2.0

ListView
{
    Keys.onDownPressed: list.incrementCurrentIndex()
    Keys.onUpPressed: list.decrementCurrentIndex()
    Keys.onReturnPressed:list.currentItem.Keys.onReturnPressed(event)
    focus:true
    clip:true
    highlightRangeMode:ListView.StrictlyEnforceRange
    id:list
}
