import QtQuick 2.0

Rectangle {
    width: 360
    height: 360
    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Component {
        id: episodeDelegate
        Item {
            id: episode
            width: listView.width
            height: 70
            Rectangle {
                id: background
                x: 2; y: 2; width: parent.width - x*2; height: parent.height - y*2
                color: "#f0ffff"
                border.color: "#778899"
                radius: 5
            }
            Text
            {
                text: "Number: " + number + "\nName: " + name + "\nDescription: "+ description+"\n"
                font.pointSize: 12
            }
        }
    }


    ListView {
        id: listView
        anchors.fill: parent
        model: season
        delegate: episodeDelegate
    }
}
