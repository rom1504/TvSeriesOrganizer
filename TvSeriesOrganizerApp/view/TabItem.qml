import QtQuick 2.0

Text
{
    id:tabItem
    property TabPage tabPage
    property alias tabText:tabItem.text
    font.family: "Arial"
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    color: "#E5E5E5"
    font.pointSize: 14
    width:tabBar.width/3
    //y:-contentHeight/5

    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: tabPage.tabClicked(index)
    }
}
