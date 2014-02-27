import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

ShadowBorderRectangle
{
    Keys.onReturnPressed: seriesDetails.seasonClicked(index)
    onClicked:
    {
        if(isMouseIn(seenRectangle)) seenRectangle.clicked()
        else seriesDetails.seasonClicked(index)
    }
    TitleImageDescriptionItem
    {
        id:content
        title:"Season " + season.number
        imageSource:season.poster
        description:season.episodeCount+" episode"+(season.episodeCount>1 ? "s" : "")+"\n"+season.episodeSeenCount+" episode"+(season.episodeSeenCount>1 ? "s" : "")+" seen"
    }

    SeenIndicator
    {
        id:seenRectangle
        seen:season.seen
        onSeenHasChanged:season.seen=seenRectangle.seen
    }
    Slider
    {
        id:seenRatioSlider
        value:season.seenRatio
        y:content.height+5
        height:5
        width:parent.width-5
    }

}
