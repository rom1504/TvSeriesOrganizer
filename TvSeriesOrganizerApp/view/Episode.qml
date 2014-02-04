import QtQuick 2.0

ShadowBorderRectangle
{
    text:"Number: " + episode.number + "\nName: " + episode.name + "\nDescription: "+ episode.description+"\n"
    onClicked: listView.parent.episodeClicked(index)
}

