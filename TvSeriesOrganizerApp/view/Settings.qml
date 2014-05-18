import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import com.rom1504.TvSeriesOrganizer 1.0

SimplePage
{
    id:imageViewer
    onBack:stackview.pop({immediate:true})
    imageSource:"qrc:/images/TvSeriesOrganizerHeader.png"
    title:qsTr("Settings")

    Column
    {
        RadioChoice
        {
            name: qsTr("Series collection style")
            currentValue: settings.seriesCollectionStyle
            values:[{"name":qsTr("Series list"),"value":SettingsModel.ListView},{"name":qsTr("Series grid"),"value":SettingsModel.GridView}]
            onValueChanged: settings.seriesCollectionStyle=currentValue
        }

        RadioChoice
        {
            id:radio2
            name: qsTr("Series card type")
            currentValue: settings.seriesCardType
            values:[{"name":qsTr("Small Card"),"value":SettingsModel.SmallCard},{"name":qsTr("Large card"),"value":SettingsModel.LargeCard}]
            onValueChanged: settings.seriesCardType=currentValue
        }

        RadioChoice
        {
            name: qsTr("Season collection style")
            currentValue: settings.seasonCollectionStyle
            values:[{"name":qsTr("Season list"),"value":SettingsModel.ListView},{"name":qsTr("Season grid"),"value":SettingsModel.GridView}]
            onValueChanged: settings.seasonCollectionStyle=currentValue
        }


        RadioChoice
        {
            name: qsTr("Episode collection style")
            currentValue: settings.episodeCollectionStyle
            values:[{"name":qsTr("Episode list"),"value":SettingsModel.ListView},{"name":qsTr("Episode grid"),"value":SettingsModel.GridView}]
            onValueChanged: settings.episodeCollectionStyle=currentValue
        }
    }
}
