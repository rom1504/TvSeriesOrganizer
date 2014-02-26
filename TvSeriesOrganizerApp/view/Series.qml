import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

ShadowBorderRectangle
{
    Keys.onReturnPressed: seriesListPage.seriesClicked(index)
    onClicked:
    {
        if(removeButton.enabled==true && removeButton.x<mouseX && mouseX<removeButton.x+removeButton.width && removeButton.y<mouseY && mouseY<removeButton.y+removeButton.height) removeButton.clicked()
        else seriesListPage.seriesClicked(index)
    }
    onPressAndHold: state="expanded"
    TitleImageDescriptionItem
    {
        title:series.name
        imageSource:series.poster
        description:series.overview
    }

    Button
    {
        id:removeButton
        text:"Remove"
        x:parent.width-width
        focus:true
        onClicked: seriesListPage.removeSeries(index)
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
