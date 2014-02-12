import QtQuick 2.0

SimplePage
{
    id:page
    property alias pageModel: listview.model
    property alias pageDelegate: listview.delegate
    property alias listView:listview
    ListView
    {
        id:listview
        width: page.width-40
        height: parent.height
        clip: true
    }
}
