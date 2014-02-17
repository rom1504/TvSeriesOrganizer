import QtQuick 2.0

ShadowBorderRectangle
{
    Keys.onReturnPressed: seriesListPage.seriesClicked(index)
    onClicked:seriesListPage.seriesClicked(index)
    TitleImageDescriptionItem
    {
        title:series.name
        imageSource:series.poster
        description:series.overview
    }
}
