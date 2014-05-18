import QtQuick 2.0
import "qrc:/GeneralQmlItems/"

GridView
{
    id:grid
    property bool cellFixedSize: true
    property int defaultColumnNumber: 3
    property int maximumColumns:10
    cellWidth:cellFixedSize ? width/Math.min(maximumColumns,Math.floor(width/((580-40)/defaultColumnNumber))) : width/defaultColumnNumber
    property double itemMargin: 10
    property double itemWidthMargin:10
    property double itemHeightMargin:10
    property double realCellWidth:cellWidth-itemWidthMargin
    property double realCellHeight:cellHeight-itemHeightMargin
    property double cellRatio:1/138*203*0.99
    property double cellAdditionnalHeightMargin
    cellHeight: cellWidth*cellRatio+cellAdditionnalHeightMargin

    highlightRangeMode:GridView.StrictlyEnforceRange
    Keys.onDownPressed: moveCurrentIndexDown()
    Keys.onUpPressed: moveCurrentIndexUp()
}
