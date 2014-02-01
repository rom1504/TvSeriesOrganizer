import QtQuick 2.0

Rectangle {
    width: 360
    height: 360
    color: "#EAEAEA"
    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    SeasonDetails{}

}

