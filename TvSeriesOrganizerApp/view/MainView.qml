import QtQuick 2.0
import QtQuick.Controls 1.1

StackView
{
    id:stackview
    width:awidth
    height:aheight

    Component{id:seriesListItem;SeriesList{}}
    Component{id:seriesDetailsItem;SeriesDetails{}}
    Component{id:seasonDetailsItem;SeasonDetails{}}
    Component{id:episodeDetailsItem;EpisodeDetails{}}
    initialItem: {"item":seriesListItem,"properties":{seriesList:seriesList}}
}
