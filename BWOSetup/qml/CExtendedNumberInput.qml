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
    property int multiplierSelectedIndex: 5


    GridLayout {
        anchors.fill: parent
        columns: 2

        CTextField {
            id: input

            width: inputWidth
            height: parent.height

            Layout.fillWidth: true

            text: inputValue.toString()
            // Sometimes it is necessary to bind an object's property to that of another object that isn't directly instantiated by QML,
            // such as a property of a class exported to QML by C++.
            //You can use the Binding type to establish this dependency; binding any value to any object's property.
            Binding {
                target: root
                property: "inputValue"
                value: parseFloat(root.text)
            }
        }
        ComboBox {
            id: multiplierSelector

            width: multiplierWidth
            height: parent.height

            Layout.maximumWidth: multiplierWidth
            Layout.fillWidth: true

            currentIndex: multiplierSelectedIndex
            Binding {
                target: root
                property: "multiplierSelectedIndex"
                value: multiplierSelector.currentIndex
            }

            // A variant type property can hold any of the basic type values or array of basic type values
            // The ListModel is a simple container of ListElement definitions, each containing data roles.
            property variant multiplierModel: ListModel {
                ListElement { text: qsTr("G") }
                ListElement { text: qsTr("M") }
                ListElement { text: qsTr("k") }
                ListElement { text: qsTr("") }
                ListElement { text: qsTr("m") }
            }

            // The var type is a generic property type that can refer to any data type.
            property var multiplierCoefficients: [1.0e9, 1.0e6, 1.0e3, 1.0, 1.0e-3]

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
    }

    onUnitsChanged: {
        var i = 0;
        for(i = 0; i < multiplierSelectorModel.count; i++) {
            multiplierSelectorModel.get(i).text = multiplierModel.get(i).text + units;
        }
    }
}
