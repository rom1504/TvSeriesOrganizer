import QtQuick 2.0

ShadowBorderRectangle
{
    onClicked:seriesDetails.seasonClicked(index)
    TitleImageDescriptionItem
    {
        title:"Season " + season.number
        imageSource:season.poster
        description:""
    }
}
