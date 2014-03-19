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
    property bool isIn:false
    function entered()
    {
        isIn=true
        if(state=="Seen") color="#e9967a"
        else color="#CCCCEE"
    }
    function exited()
    {
        isIn=false
        if(state=="Seen") color="orange"
        else color="#A0A0A0"
    }

    states:[
        State
        {
            name:"Seen"
            PropertyChanges{target:seenRectangle; color:isIn ? "#e9967a" : "orange";}
            PropertyChanges{target:seenText;text:qsTr("Seen");}
        },

        State
        {
            name:"NotSeen"
            PropertyChanges{target:seenRectangle; color:isIn ? "#CCCCEE" : "#A0A0A0";}
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
