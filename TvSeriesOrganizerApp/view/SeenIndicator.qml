import QtQuick 2.0

Rectangle
{
    id:seenRectangle
    property bool seen
    signal seenHasChanged

    property bool pressed

    function clicked()
    {
        seenRectangle.state=seenRectangle.state=="Seen" ? "NotSeen" : "Seen"
        seen=seenRectangle.state=="Seen"
        seenHasChanged()
    }

    states:[
        State
        {
            name:"Seen"
            PropertyChanges{target:seenRectangle; color:pressed ? "#e9967a" : "orange";}
            PropertyChanges{target:seenText;text:qsTr("Seen");}
        },

        State
        {
            name:"NotSeen"
            PropertyChanges{target:seenRectangle; color:pressed ? "#CCCCEE" : "#A0A0A0";}
            PropertyChanges{target:seenText;text:qsTr("Not seen");}
        }
    ]

    state:seen ? "Seen" : "NotSeen"
    y:0
    width:seenText.contentWidth
    height:seenText.contentHeight
    color:"orange"
    Text
    {
        id:seenText
        text:qsTr("Seen")
        color:"white"
        font.pointSize: 14
        anchors.centerIn: parent
    }
}
