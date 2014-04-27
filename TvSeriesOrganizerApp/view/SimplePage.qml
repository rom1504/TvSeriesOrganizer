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
    property int buttonBarHeight:0
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
        //height:100
        state:""

        property url newSource
        onNewSourceChanged:
        {
            if(image.opacity==1)
            {
                nbc.enabled=true
                nbc.visible=true
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
    }
    BrightnessContrast {

            opacity:image.opacity
            anchors.fill: image
            source: image
            brightness: -0.3
        }
    Image
    {
        visible:false
        opacity:0
        id:nextImage
        x:0
        y:0
        width:parent.width
        height:width*sourceSize.height/sourceSize.width


    }


    BrightnessContrast {
            id:nbc
            visible:false
            anchors.fill: nextImage
            source: nextImage
            brightness: -0.3
            opacity:nextImage.opacity
        }


    Button
    {
        id:backContainer
        width: button.width +5
        height: button.height +5
        onClicked: simplePage.back()
        Image
        {
            source:"qrc:/images/back.png"
            width:image.width/7
            height:width
            id:button
        }
    }
    Item
    {
        id:insidePageItem
        x:20
        y:image.height+image.y+5
        height:simplePage.height-image.y-image.height
    }
}
