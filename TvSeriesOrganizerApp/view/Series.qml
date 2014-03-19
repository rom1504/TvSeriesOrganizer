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

    onEntered:
    {
        if(isMouseIn(seenRectangle,50)) seenRectangle.entered()
        else if(removeButton.enabled && isMouseIn(removeButton)) removeButton.entered()
    }

    onExited:
    {
        seenRectangle.exited()
        if(removeButton.enabled) removeButton.exited()
    }
    property bool isInSeen:false
    property bool isInRemove:false
    onPositionChanged:
    {
        var isInl=isMouseIn(seenRectangle,50);
        if(isInl!==isInSeen)
        {
            if(isInl) seenRectangle.entered()
            else seenRectangle.exited()
            isInSeen=isInl
        }

        if(removeButton.enabled)
        {
            var isInl2=isMouseIn(removeButton);
            if(isInl2!==isInRemove)
            {
                if(isInl2) removeButton.entered()
                else removeButton.exited()
                isInRemove=isInl2
            }
        }
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
