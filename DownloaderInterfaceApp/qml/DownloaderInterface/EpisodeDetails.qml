import QtQuick 2.0
// pas fini

Item {
    id: root
    width: parent.width
    height: 70
    Rectangle {
        id: background
        x: 2; y: 2; width: parent.width - x*2; height: parent.height - y*2
        color: "white"
        border.color: "#778899"
        radius: 5
    }
    Text
    {
        text: "Number: " + number + "\nName: " + name + "\nDescription: "+ description+"\n"
        font.pointSize: 12
    }
}
