import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

ShadowBorderRectangleButton
{
    id:seriesItem
    signal seriesClicked(int index)
    signal seriesRemoved()
    Keys.onReturnPressed:seriesClicked(index)

    onClicked:
    {
        if(removeButton.enabled&& isMouseIn(removeButton,50)) removeButton.clicked()
        else if(isMouseIn(seenRectangle,50)) seenRectangle.clicked()
        else seriesClicked(index)
    }

    onPressAndHold: state="expanded"
    TitleImageDescriptionItem
    {
        id:content
        title:series.name
        imageSource:series.poster.small
        description:series.shortOverview
        maximumDescriptionHeight: 115
        width:parent.width-10
    }

    onPressedChanged:
    {
        if(!pressed || isMouseIn(seenRectangle,50)) seenRectangle.pressed=pressed
        if(removeButton.enabled && (!pressed || isMouseIn(removeButton))) removeButton.pressed=pressed
        if(!(pressed && (isMouseIn(seenRectangle,50) || isMouseIn(removeButton)))) rectColor=pressed ? "#EEEEEE" : "white"
    }

    Button
    {
        id:removeButton
        Image
        {
            source:"qrc:/images/remove_black.png"
            width:content.width/13
            height:width
            id:ibutton
        }
        width:ibutton.width
        height:ibutton.height
        x:parent.width*4/6
        y:-5
        focus:true
        onClicked: seriesRemoved()
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
