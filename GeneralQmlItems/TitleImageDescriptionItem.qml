import QtQuick 2.0

Item
{
    width:parent.width
    height:childrenRect.height
    property alias title:text1.text
    property alias imageSource:image.source
    property alias description:text2.text
    default property alias children : insideItem.children

    Title
    {
        id:text1
    }
    Image
    {
        id:image
        y:text1.y+text1.height+5
        sourceSize.height: 150
        width:100
        fillMode: Image.PreserveAspectCrop
    }
    Description
    {
        x:image.width+5
        y:text1.y+text1.height+5
        id:text2
    }
    Item
    {
        x:image.width+5
        y:text2.y+text2.height+5
        height:childrenRect.height
        width:parent.width-x
        id:insideItem
    }
}
