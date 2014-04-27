import QtQuick 2.0
import QtQuick.Controls 1.1

StackView
{
    id:stackview
    width:awidth
    height:aheight

    focus:true
    Keys.onLeftPressed: currentItem.left(event)
    Keys.onRightPressed: currentItem.right(event)
    Keys.onUpPressed: currentItem.up(event);
    Keys.onDownPressed: currentItem.down(event)
    Keys.onBackPressed: currentItem.bback(event)
    Keys.onPressed: if(event.key === Qt.Key_Backspace) currentItem.bback(event)
    Keys.onReturnPressed: currentItem.enter(event)


    initialItem: seriesList.seriesCount===0 ? {"item":"qrc:/view/ExploreSeries.qml","properties":{followedSeriesList:seriesList}} : {"item":"qrc:/view/SeriesListPage.qml","properties":{seriesList:seriesList}}
}
