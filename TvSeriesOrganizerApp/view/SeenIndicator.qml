import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

Button
{
    property bool seen
    signal seenHasChanged
    id:seenIndicator
    property bool pressed

    onClicked:
    {
        seenIndicator.state=seenIndicator.state=="Seen" ? "NotSeen" : "Seen"
        seen=seenIndicator.state=="Seen"
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
    Rectangle
    {
        width:seenText.contentWidth
        height:seenText.contentHeight
        id:seenRectangle
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
}
