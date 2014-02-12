import QtQuick 2.0

Item
{
    width:parent.width
    height:childrenRect.height
    property alias title:text1.text
    property alias imageSource:image.source
    property alias description:text2.text

    Text
    {
        id:text1
        width:parent.width
        font { family: 'arial'}
        wrapMode: Text.WordWrap
        font.pointSize: 20
    }
    Image
    {
        id:image
        y:text1.y+text1.height+5
        sourceSize.height: 150
        width:100
        fillMode: Image.PreserveAspectCrop
    }
    Text
    {
        x:image.width+5
        y:text1.y+text1.height+5
        id:text2
        width:parent.width-x
        color: "#717171"
        font { family: 'arial'}
        wrapMode: Text.WordWrap
        font.pointSize: 12
    }
}
