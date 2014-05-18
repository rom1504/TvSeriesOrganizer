import QtQuick 2.0
import com.rom1504.TvSeriesOrganizer 1.0

CollectionView
{
       id:seriesCollection
       viewType:settings.seriesCollectionStyle
       signal seriesClicked(int seriesIndex,var series)
       signal seriesRemoved(var series)
       property int cardType: settings.seriesCardType

       function cardTypeToComponent(cardType)
       {
           if(cardType===SettingsModel.LargeCard) return largeSeriesCard;
           if(cardType===SettingsModel.SmallCard) return smallSeriesCard;
           return null;
       }

       function cardTypeToGridColumnNumber(cardType)
       {
           if(cardType===SettingsModel.LargeCard) return 1;
           if(cardType===SettingsModel.SmallCard) return 3;
           return null;
       }

       function cardTypeToGridCellRatio(cardType)
       {
           if(cardType===SettingsModel.LargeCard) return 2/5
           if(cardType===SettingsModel.SmallCard) return 1/138*203*0.99
           return null;
       }



       function cardTypeToGridCellAdditionalHeightMargin(cardType)
       {
           if(cardType===SettingsModel.LargeCard) return 5
           if(cardType===SettingsModel.SmallCard) return 0
           return null;
       }

       gridCellRatio:cardTypeToGridCellRatio(cardType)
       gridCellAdditionalHeightMargin:cardTypeToGridCellAdditionalHeightMargin(cardType)

       Component
       {
           id:largeSeriesCard
           Series
           {
               id:a
               width:seriesCollection.viewCellWidth+(seriesCollection.viewType===SettingsModel.GridView ? 10 : 0)
               height:seriesCollection.viewType===SettingsModel.GridView ? seriesCollection.viewCellHeight+15 : defaultHeight
               onSeriesClicked: seriesCollection.seriesClicked(index,series)
               onSeriesRemoved: seriesCollection.seriesRemoved(series)

           }
       }

       Component
       {
           id:smallSeriesCard
           ThumbnailSeries
           {
               width:seriesCollection.viewCellWidth
               height:seriesCollection.viewCellHeight
               onClicked:seriesCollection.seriesClicked(index,series)
               addition:ThumbnailSeriesAddition
               {
                   onRemoveSeries: seriesCollection.seriesRemoved(series)
               }
           }
       }

       listDelegate:cardTypeToComponent(cardType)
       gridDelegate:cardTypeToComponent(cardType)
       defaultGridColumnNumber:cardTypeToGridColumnNumber(cardType)
}
