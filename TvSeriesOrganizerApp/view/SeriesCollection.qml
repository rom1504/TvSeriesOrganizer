import QtQuick 2.0
import com.rom1504.TvSeriesOrganizer 1.0

Item
{
       id:seriesCollection
       property int grid:settings.seriesCollectionStyle
       property var model
       property int currentIndex
       signal seriesClicked(int seriesIndex,var series)
       signal seriesRemoved(var series)
       Component
       {
           id:listView
           SeriesList
           {
               model:seriesCollection.model
               width: seriesCollection.width
               height: seriesCollection.height
               currentIndex: seriesCollection.currentIndex
               onSeriesClicked: seriesCollection.seriesClicked(index,series)
               onSeriesRemoved: seriesCollection.seriesRemoved(series)
           }
       }
       Component
       {
           id:gridView
           SeriesGrid
           {
               width: seriesCollection.width
               height: seriesCollection.height
               model: seriesCollection.model
               onSeriesClicked: seriesCollection.seriesClicked(index,series)
               currentIndex: seriesCollection.currentIndex
               seriesComp:ThumbnailSeries
               {
                   onRemoveSeries: seriesCollection.seriesRemoved(series)
               }
           }
       }
       Loader
       {
           id:loader
           sourceComponent:seriesCollection.grid ? gridView : listView
       }
       Keys.onDownPressed: loader.item.Keys.onDownPressed(event)
       Keys.onUpPressed: loader.item.Keys.onUpPressed(event)

       Keys.onReturnPressed:loader.item.Keys.onReturnPressed(event)
}
