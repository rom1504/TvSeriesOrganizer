import QtQuick 2.0

ShadowBorderRectangle
{
    onClicked:seriesListPage.seriesClicked(index)
    TitleImageDescriptionItem
    {
        title:series.name
        imageSource:series.poster
        description:series.overview
    }
}
