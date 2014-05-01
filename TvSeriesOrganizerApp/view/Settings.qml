import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import com.rom1504.TvSeriesOrganizer 1.0

SimplePage
{
    id:imageViewer
    onBack:stackview.pop({immediate:true})
    imageSource:"qrc:/images/TvSeriesOrganizerHeader.png"
    title:"Settings"
    Column
    {
        Text
        {
            text:"Series collection style :"
            font.pointSize: 18
        }

        GroupBox {
            width:imageViewer.width-40
            Column {
                spacing:10
                ExclusiveGroup { id: group }
                RadioButton {
                    text: qsTr("Series list")
                    exclusiveGroup: group
                    checked: settings.seriesCollectionStyle===SettingsModel.SeriesList
                    style:RadioButtonStyle {
                            label:Text {text:control.text;font.pointSize: 16}
                    }
                    onClicked: if(checked) settings.seriesCollectionStyle=SettingsModel.SeriesList
                }
                RadioButton {
                    text: qsTr("Series grid")
                    exclusiveGroup: group
                    checked: settings.seriesCollectionStyle===SettingsModel.SeriesGrid
                    style:RadioButtonStyle {
                            label:Text {text:control.text;font.pointSize: 16}
                    }
                    onClicked: if(checked) settings.seriesCollectionStyle=SettingsModel.SeriesGrid
                }
            }
        }
    }
}

// list de settings (bool ou string ou ?)
