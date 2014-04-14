import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

ShadowBorderRectangleButton
{

    function betterNumber(n,max,no,one,medium,all)
    {
        if(n===0) return no;
        if(n===1) return one;
        if(n===max) return all;
        return medium;
    }
    signal seasonClicked(int index)

    Keys.onReturnPressed: seasonClicked(index)
    onClicked:
    {
        if(isMouseIn(seenRectangle,50)) seenRectangle.clicked()
        else seasonClicked(index)
    }

    onPressedChanged:
    {
        if(!pressed || isMouseIn(seenRectangle,50)) seenRectangle.pressed=pressed
        if(!(pressed && isMouseIn(seenRectangle,50))) rectColor=pressed ? "#EEEEEE" : "white"
    }

    TitleImageDescriptionItem
    {
        width:parent.width
        id:content
        title:season.number===0 ? qsTr("Extras") : qsTr("Season")+" " + season.number
        imageSource:season.poster.small
        description:qsTr("First aired")+":"+Qt.formatDateTime(season.firstAired, "yyyy-MM-dd")+"\n"+qsTr("%n episode(s)","",season.episodeCount)+"\n"+betterNumber(season.episodeSeenCount,season.episodeCount,qsTr("No episode seen"),qsTr("One episode seen"),qsTr("%n episode(s) seen","",season.episodeSeenCount),qsTr("All episodes seen"))

        Column
        {
            spacing:1
            width:parent.width
            height:childrenRect.height
            Slider
            {
                value:season.seenRatio
                height:5
                width:parent.width-5
            }
            Description
            {
                text:betterNumber(season.episodeAiredCount,season.episodeCount,qsTr("No episode aired"),qsTr("One episode aired"),qsTr("%n episode(s) aired","",season.episodeAiredCount),qsTr("All episodes aired"))
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
