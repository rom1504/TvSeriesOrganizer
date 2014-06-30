import QtQuick 2.0

SimplePage
{
    id:imageViewer
    onBack:stackview.pop({immediate:true})
    imageSource:"qrc:/images/TvSeriesOrganizerHeader.png"
    property alias bigImageSource:image.source
    function min(a,b) {return a>b ? b : a;}
    Image
    {
        id:image
        width:imageViewer.width-40
        fillMode:Image.PreserveAspectFit
        height:min(parent.height-40,image.sourceSize.height/image.sourceSize.width*width)
    }
}
