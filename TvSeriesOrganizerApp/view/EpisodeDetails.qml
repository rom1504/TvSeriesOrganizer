import QtQuick 2.0

SimplePage
{
    id: episodeDetails
    imageSource:"qrc:/images/episode.jpg"
    ShadowBorderRectangle
    {
        text:"Number: " + episode.number + "\nName: " + episode.name + "\nDescription: "+ episode.description+"\n"
        width:parent.width-40
        x:20
        y:250
    }
}
