import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

ShadowBorderRectangle
{
    function plural(n)
    {
        return n>1 ? "s":"";
    }

    function betterNumber(n,max)
    {
        if(n===0) return "No";
        if(n===1) return "One";
        if(n===max) return "All";
        return n;
    }

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
        description:"First aired:"+Qt.formatDateTime(season.firstAired, "yyyy-MM-dd")+"\n"+season.episodeCount+" episode"+plural(season.episodeCount)+"\n"+betterNumber(season.episodeSeenCount,season.episodeCount)+" episode"+plural(season.episodeSeenCount)+" seen"

        Column
        {
            width:parent.width-x
            height:childrenRect.height
            Slider
            {
                value:season.seenRatio
                height:5
                width:parent.width-5
            }
            Description
            {
                text:betterNumber(season.episodeAiredCount,season.episodeCount)+" episode"+plural(season.episodeAiredCount)+" aired"
            }
            Slider
            {
                value:season.airedRatio
                height:5
                width:parent.width-5
            }
        }
    }
    SeenIndicator
    {
        id:seenRectangle
        seen:season.seen
        onSeenHasChanged:season.seen=seenRectangle.seen
        x:parent.width-width-5
    }
}
