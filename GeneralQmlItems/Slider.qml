import QtQuick 2.0

Item
{
    property double value
    property color fullColor:"#4DB5DB"
    property color emptyColor:"#B2B2B2"

    Rectangle
    {
        width: parent.width*value
        height: parent.height
        color:fullColor
    }
    Rectangle
    {
        x:parent.width*value
        width: parent.width*(1-value)
        height: parent.height
        color:emptyColor
    }
}
