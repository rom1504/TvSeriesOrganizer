import QtQuick 2.0

SimplePage
{
    id:page
    property alias pageModel: listview.model
    property alias pageDelegate: listview.delegate
    property alias listView:listview
    property int beginIndex:0
    ListView
    {
        id:listview
        currentIndex: beginIndex
        width: page.width-40
        height: parent.height
        clip: true
        focus:true
        highlightRangeMode:ListView.StrictlyEnforceRange

        Keys.onDownPressed: listview.incrementCurrentIndex()
        Keys.onUpPressed: listview.decrementCurrentIndex()
    }
}
