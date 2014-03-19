import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

ShadowBorderRectangle
{
    id:seriesItem
    signal seriesClicked(int index)
    Keys.onReturnPressed:seriesClicked(index)

    onClicked:
    {
        if(removeButton.enabled&& isMouseIn(removeButton)) removeButton.clicked()
        else if(isMouseIn(seenRectangle,50)) seenRectangle.clicked()
        else seriesClicked(index)
    }

    onPressAndHold: state="expanded"
    TitleImageDescriptionItem
    {
        id:content
        title:series.name
        imageSource:series.poster
        description:series.overview
    }

    onPressedChanged:
    {
        if(!pressed || isMouseIn(seenRectangle,50)) seenRectangle.pressed=pressed
        if(removeButton.enabled && (!pressed || isMouseIn(removeButton))) removeButton.pressed=pressed
        if(!(pressed && (isMouseIn(seenRectangle,50) || isMouseIn(removeButton)))) rectColor=pressed ? "#EEEEEE" : "white"
    }

    TextButton
    {
        id:removeButton
        text:qsTr("Remove")
        font.pointSize: 14
        x:parent.width/2
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
