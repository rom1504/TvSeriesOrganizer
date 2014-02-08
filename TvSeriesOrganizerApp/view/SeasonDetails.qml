import QtQuick 2.0

ListPage
{
    id:seasonDetails
    signal episodeClicked(int episodeNumber)
    imageSource:season.banner
    pageDelegate: Episode{}
    pageModel: seasonModel
}
