import QtQuick 2.0

ListView {
    id: listView
    anchors.fill: parent
    model: season
    delegate: Episode{}
}
