import QtQuick 2.0

Rectangle
{
    id: episodeDetails
    width: 400
    height: 800
    color: "#EAEAEA"
    ShadowBorderRectangle
    {
        text:"Number: " + episode.number + "\nName: " + episode.name + "\nDescription: "+ episode.description+"\n"
        height: 80
    }
}
