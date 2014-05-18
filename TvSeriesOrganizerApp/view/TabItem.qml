import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

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
    //width:tabBar.width/3

    //property bool fixedSize: true
    //property int defaultColumnNumber: 3
    //width:fixedSize ? tabBar.width/Math.floor(tabBar.width/((580-40)/defaultColumnNumber)) : tabBar.width/defaultColumnNumber
    width:tabBar.width/tabPage.tabNumber

    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: tabPage.tabClicked(index)
    }
}
