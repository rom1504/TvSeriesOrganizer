import QtQuick 2.0

Item {
    id: episodeDetails
    width: 300
    height: 150
    Rectangle {
        id: background
        x: 2; y: 2; width: parent.width - x*2; height: parent.height - y*2
        color: "white"
        border.color: "#778899"
        radius: 5
    }
    Text
    {
        x:10
        y:10
        text: "Number: " + episode.number + "\nName: " + episode.name + "\nDescription: "+ episode.description+"\n"
        font.pointSize: 12
    }
}
