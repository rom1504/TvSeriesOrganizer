import QtQuick 2.0
import QtGraphicalEffects 1.0
import "qrc:/GeneralQmlItems/"


Rectangle
{
    id: simplePage

    width: awidth
    height: aheight
    color: "#EAEAEA"
    signal left(var event)
    signal right(var event)
    signal up(var event)
    signal down(var event)
    signal back()
    signal bback(var event)
    signal enter(var event)
    onBback: back()

    property alias imageSource:image.source
    property alias newImageSource:image.newSource
    default property alias children : insidePageItem.children
    property alias buttonBarHeight:backContainer.height
    Keys.onBackPressed: simplePage.back()
    Keys.onPressed: if(event.key === Qt.Key_Backspace) simplePage.back()
    Image
    {
        id:image
        x:0
        y:0
        opacity:1
        width:parent.width
        height:width*sourceSize.height/sourceSize.width
        property url newSource
        onNewSourceChanged:
        {
            if(image.opacity==1)
            {
                nextImage.source=image.newSource
                state="forward"
            }
            else
            {
                image.source=image.newSource
                state="backward"
            }
        }

        states:[
            State
            {
                name:"forward"
                PropertyChanges { target: image;  opacity:0; }
                PropertyChanges { target: nextImage; opacity:1; }
            },
            State
            {
                name:"backward"
                PropertyChanges { target: image; opacity:1; }
                PropertyChanges { target: nextImage;  opacity:0; }
            }
        ]

        transitions: [
            Transition {
                id:test
                    NumberAnimation { target:image; properties: "opacity"; duration: 2000 ;easing.type: Easing.Linear  }
                    NumberAnimation { target:nextImage; properties: "opacity"; duration: 2000;easing.type: Easing.Linear  }
            }
        ]

        BrightnessContrast {

                anchors.fill: image
                source: image
                brightness: -0.3
            }

    }
    Image
    {
        opacity:0
        id:nextImage
        x:0
        y:0
        width:parent.width
        height:width*sourceSize.height/sourceSize.width

        BrightnessContrast {
                anchors.fill: nextImage
                source: nextImage
                brightness: -0.3
            }

    }




    Button
    {
        id:backContainer
        x:parent.width-60
        y:image.height+5
        onClicked:simplePage.back()
        text:"Back"
    }
    Item
    {
        id:insidePageItem
        x:20
        y:backContainer.height+backContainer.y+5
        height:simplePage.height-backContainer.y-backContainer.height
    }
}
