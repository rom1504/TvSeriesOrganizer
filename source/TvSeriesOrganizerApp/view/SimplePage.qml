import QtQuick 2.0
import QtGraphicalEffects 1.0
import "qrc:/GeneralQmlItems/"


Rectangle
{
    id: simplePage

    signal left(var event)
    signal right(var event)
    signal up(var event)
    signal down(var event)
    signal back()
    signal bback(var event)
    signal enter(var event)

    property alias imageSource:image.source
    property alias newImageSource:image.newSource
    default property alias children : insidePageItem.children
    property int buttonBarHeight:0
    property int maxImageHeight:150
    property Component inImage
    property string title:""

    width: awidth
    height: aheight
    color: "#EAEAEA"
    onBback: back()

    Keys.onBackPressed: simplePage.back()
    Keys.onPressed: if(event.key === Qt.Key_Backspace) simplePage.back()

    Rectangle
    {
        width:parent.width
        height:image.opacity===1 ? image.height : nextImage.height
        color:"#999"

    }

    Image
    {
        id:image
        x:0
        y:0
        opacity:1
        height:parent.width*sourceSize.height/sourceSize.width>maxImageHeight ? maxImageHeight : parent.width*sourceSize.height/sourceSize.width
        width:parent.width*sourceSize.height/sourceSize.width>maxImageHeight ? height*sourceSize.width/sourceSize.height : parent.width
        anchors.left: parent.Left
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

        height:parent.width*sourceSize.height/sourceSize.width>maxImageHeight ? maxImageHeight : parent.width*sourceSize.height/sourceSize.width
        width:parent.width*sourceSize.height/sourceSize.width>maxImageHeight ? height*sourceSize.width/sourceSize.height
                                                                              : parent.width


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
        width: r.width +5
        height: r.height +5
        onClicked: simplePage.back()
        Row
        {
            id:r
            spacing:5
            Image
            {
                source:"qrc:/images/previous_white.png"
                width:50
                height:width
                id:button
            }

            Text
            {
                y:5
                width:contentWidth
                height:contentHeight
                font.pointSize: 25
                color:"white"
                font.family: "georgia"
                text:simplePage.title
            }
        }
    }
    Loader
    {
        id:loader
        sourceComponent: inImage
    }
    Item
    {
        id:insidePageItem
        x:20
        y:image.height+image.y+5
        height:simplePage.height-image.y-image.height
    }
}
