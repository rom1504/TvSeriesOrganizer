import QtQuick 2.0

SimplePage
{
    property alias pageModel: listview.model
    property alias pageDelegate: listview.delegate
    property alias listView:listview
    ListView
    {
        id:listview
        x:20
        y:250
        width: parent.width-40
        height: 600
    }
}
