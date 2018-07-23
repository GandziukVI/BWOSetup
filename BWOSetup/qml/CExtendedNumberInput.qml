import QtQuick 2.2
import QtQuick.Controls 2.2

import QtQuick.Layouts 1.3

Rectangle {
    id: root

    property double multiplier: 1.0
    property double inputValue: 1.0
    property double realValue: inputValue * multiplier
    property string units: "V"

    property alias input: input
    property alias text: input.text
    property alias placeholderText: input.placeholderText
    property alias validator: input.validator
    property alias multiplierIndex: multiplierSelector.currentIndex
    property alias multiplierModel: multiplierSelector.multiplierModel
    property alias multiplierCoefficients: multiplierSelector.multiplierCoefficients

    signal editingFinished()

    width: 150
    height: 30

    property int multiplierWidth: 75
    property int inputWidth: 75
    property int multiplierSelectedIndex: 0

    GridLayout {
        anchors.fill: parent
        columns: 2

        CTextField {
            id: input

            width: inputWidth
            height: parent.height

            Layout.fillWidth: true

            onTextChanged: {
                inputValue = parseFloat(text);
                root.editingFinished
            }
        }
        ComboBox {
            id: multiplierSelector

            width: multiplierWidth
            height: parent.height

            Layout.maximumWidth: multiplierWidth
            Layout.fillWidth: true

            currentIndex: multiplierSelectedIndex

            property variant multiplierModel: ListModel {
                ListElement { text: qsTr("") }
                ListElement { text: qsTr("m") }
                ListElement { text: qsTr("μ") }
                ListElement { text: qsTr("n") }
            }

            property var multiplierCoefficients: [ 1.0, 1.0e-3, 1.0e-6, 1.0e-9 ]

            model: ListModel {
                id: multiplierSelectorModel
            }

            onCurrentIndexChanged: {
                multiplier = parseFloat(multiplierCoefficients[currentIndex]);
            }
        }
    }
    Component.onCompleted: {
        inputValue = parseFloat(text)

        var i = 0;
        for(i = 0; i < multiplierModel.count; i++) {
            multiplierSelectorModel.append({ "text": multiplierModel.get(i).text + units });
        }
        multiplierSelector.currentIndex = multiplierSelectedIndex;
    }

    onUnitsChanged: {
        var i = 0;
        for(i = 0; i < multiplierSelectorModel.count; i++) {
            multiplierSelectorModel.get(i).text = multiplierModel.get(i).text + units;
        }
    }
}
