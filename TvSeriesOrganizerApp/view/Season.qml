import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

ShadowBorderRectangle
{
    Keys.onReturnPressed: seriesDetails.seasonClicked(index)
    onClicked:seriesDetails.seasonClicked(index)
    TitleImageDescriptionItem
    {
        title:"Season " + season.number
        imageSource:season.poster
        description:""
    }
}
