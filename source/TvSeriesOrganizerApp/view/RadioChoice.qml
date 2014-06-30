import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import com.rom1504.TvSeriesOrganizer 1.0

Column
{
    property string name
    property int currentValue
    property var values
    signal valueChanged

    Component.onCompleted: {for(var i=0;i<values.length;i++) repeater.model.append(values[i])}

    Text
    {
        text:name+" :"
        font.pointSize: 18
    }

    GroupBox {
        width:imageViewer.width-40
        Column {
            spacing:10
            ExclusiveGroup { id: group }

            Repeater
            {
                model:ListModel{}
                id:repeater
                delegate:RadioButton
                {
                    text: name
                    exclusiveGroup: group
                    checked: currentValue===value
                    style:RadioButtonStyle {label:Text {text:control.text;font.pointSize: 16}}
                    onClicked: if(checked) {currentValue=value;valueChanged();}
                }
            }
        }
    }
}

