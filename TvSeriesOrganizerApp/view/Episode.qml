import QtQuick 2.0

ShadowBorderRectangle
{
    text:"Number: " + episode.number + "\nName: " + episode.name + "\nDescription: "+ episode.description+"\n"
    height:80
    onClicked: listView.parent.episodeClicked(index)
}

