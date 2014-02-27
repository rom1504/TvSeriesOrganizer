import QtQuick 2.0

Rectangle
{
    id:seenRectangle
    property bool seen
    signal seenHasChanged
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
            PropertyChanges{target:seenRectangle; color:"orange";}
            PropertyChanges{target:seenText;text:"Seen";}
        },

        State
        {
            name:"NotSeen"
            PropertyChanges{target:seenRectangle; color:"#A0A0A0";}
            PropertyChanges{target:seenText;text:"Not seen";}
        }
    ]

    state:seen ? "Seen" : "NotSeen"
    y:0
    width:55
    height:20
    color:"orange"
    Text
    {
        id:seenText
        text:"Seen"
        color:"white"
        font.pointSize: 8
        anchors.centerIn: parent
    }
}
