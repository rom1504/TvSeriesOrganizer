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
    ListView {
        width: 200; height: 250

        model: season
        delegate: Text
        {
            text: "Number: " + number + "\nName: " + name + "\nDescription: "+ description+"\n"
            font.pointSize: 14
        }
    }
}
