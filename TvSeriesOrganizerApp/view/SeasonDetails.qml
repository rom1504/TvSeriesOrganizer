import QtQuick 2.0

ListPage
{
    id:seasonDetails
    signal episodeClicked(int episodeNumber)
    imageSource:"qrc:/images/season.jpg"
    pageDelegate: Episode{}
    pageModel: season
}
