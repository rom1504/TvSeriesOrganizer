import QtQuick 2.0

SimplePage
{
    id: episodeDetails
    ShadowBorderRectangle
    {
        text:"Number: " + episode.number + "\nName: " + episode.name + "\nDescription: "+ episode.description+"\n"
        height: 80
        width:300
        x:30
        y:10
    }
}
