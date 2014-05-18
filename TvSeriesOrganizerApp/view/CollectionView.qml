import QtQuick 2.0
import com.rom1504.TvSeriesOrganizer 1.0

Item
{
       id:collectionView
       property int viewType
       property var model
       property int currentIndex
       property Component delegate
       property Component listDelegate:delegate
       property Component gridDelegate:delegate
       property Item view: loader.item
       property int defaultGridColumnNumber:3
       onCurrentIndexChanged: loader.item.currentIndex=collectionView.currentIndex

       function viewTypeToCardWidth(viewType)
       {
           if(viewType===SettingsModel.GridView) return collectionView.view.realCellWidth;
           if(viewType===SettingsModel.ListView) return collectionView.view.width;
           return 0;
       }

       function viewTypeToCardHeight(viewType)
       {
           if(viewType===SettingsModel.GridView) return collectionView.view.realCellHeight;
           if(viewType===SettingsModel.ListView) return collectionView.view.height;
           return 0;
       }
       property double viewCellWidth:viewTypeToCardWidth(viewType)
       property double viewCellHeight:viewTypeToCardHeight(viewType)

       property double gridCellRatio
       property double gridCellAdditionalHeightMargin:0
       Component
       {
           id:listView
           CommonListView
           {
               model:collectionView.model
               width: collectionView.width
               height: collectionView.height
               currentIndex: collectionView.currentIndex
               delegate: collectionView.listDelegate
           }
       }
       Component
       {
           id:gridView
           CommonGridView
           {
               cellAdditionnalHeightMargin:gridCellAdditionalHeightMargin
               defaultColumnNumber: defaultGridColumnNumber
               width: collectionView.width
               height: collectionView.height
               model: collectionView.model
               currentIndex: collectionView.currentIndex
               delegate: collectionView.gridDelegate
               cellRatio: gridCellRatio
           }
       }
       Loader
       {
           id:loader
           sourceComponent:
               collectionView.viewType===SettingsModel.GridView ? gridView :
              (collectionView.viewType===SettingsModel.ListView ? listView : null)
       }
       Keys.onDownPressed: loader.item.Keys.onDownPressed(event)
       Keys.onUpPressed: loader.item.Keys.onUpPressed(event)

       Keys.onReturnPressed:loader.item.Keys.onReturnPressed(event)
}
