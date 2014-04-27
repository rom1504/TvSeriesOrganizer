import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

Item
{
    signal removeSeries(var series)
    function pressAndHold() {state="expanded";}
    Button
    {
        id:removeButton
        Image
        {
            source:"qrc:/images/remove_white.png"
            width:seriesImage.width/5
            height:width
            id:ibutton
        }
        width:ibutton.width
        height:ibutton.height
        x:0
        y:0
        focus:true
        onClicked: removeSeries(mseries)
    }

    SeenIndicator
    {
        id:seenRectangle
        seen:mseries.seen
        onSeenHasChanged: mseries.seen=seenRectangle.seen
        x:delegateItem.width-width-5
    }

    Slider
    {
        id:seenRatioSlider
        value:mseries.seenRatio
        y:seriesImage.height-5
        x:0
        height:5
        width:delegateItem.width
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
