import QtQuick 2.0

TabPage
{
    id:seasonDetails
    imageSource:season.banner
    signal episodeClicked(int episodeNumber)
    signal seasonChanged(int row)
    onTabChanged: seasonChanged(column)
    onCurrentTabChanged:seasonDetails.imageSource=currentItem.myData.banner;
    tabContentModel: seriesModel
    property int listBeginIndex:episodeIndex
    tabContentDelegate:
        ListView
        {
            property variant myData:season
            delegate:Episode{}
            model:season.seasonModel
            width: seasonDetails.width-40
            height: parent.height
            currentIndex: listBeginIndex
            highlightRangeMode:ListView.StrictlyEnforceRange
            id:listview
            Keys.onDownPressed: listview.incrementCurrentIndex()
            Keys.onUpPressed: listview.decrementCurrentIndex()
        }
    tabDelegate:TabItem{tabText:"Season "+season.number;tabPage:seasonDetails}

    beginIndex:seasonIndex
}
