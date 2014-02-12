import QtQuick 2.0

ShadowBorderRectangle
{
    property alias text:insideText.text
    Text
    {
        id:insideText
        width:parent.width
        font { family: 'arial'}
        wrapMode: Text.WordWrap
        font.pointSize: 12
    }
}
