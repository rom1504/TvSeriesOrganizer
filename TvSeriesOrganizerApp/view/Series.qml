import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

ShadowBorderRectangle
{
    id:seriesItem
    Keys.onReturnPressed: seriesListPage.seriesClicked(index)

    onClicked:
    {
        if(removeButton.enabled==true && isMouseIn(removeButton)) removeButton.clicked()
        else if(isMouseIn(seenRectangle)) seenRectangle.clicked()
        else seriesListPage.seriesClicked(index)
    }
    onPressAndHold: state="expanded"
    TitleImageDescriptionItem
    {
        id:content
        title:series.name
        imageSource:series.poster
        description:series.overview
    }

    Button
    {
        id:removeButton
        text:"Remove"
        x:parent.width/1.4
        focus:true
        onClicked: seriesListPage.removeSeries(index)
    }

    SeenIndicator
    {
        id:seenRectangle
        seen:series.seen
        onSeenHasChanged: series.seen=seenRectangle.seen
        x:parent.width-width-5
    }

    Slider
    {
        id:seenRatioSlider
        value:series.seenRatio
        y:content.height+5
        height:5
        width:parent.width-5
    }


    states:[
        State
        {
            name:"simple"
            PropertyChanges { target: removeButton ; enabled:false; opacity:0;}
        }
        ,
        State
        {
            name:"expanded"
            PropertyChanges { target: removeButton ; enabled:true; opacity:1;}
        }
    ]
    state:"simple"
}
