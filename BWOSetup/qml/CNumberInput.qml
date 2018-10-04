import QtQuick 2.2
import QtQuick.Controls 2.2

import QtQuick.Layouts 1.3

Rectangle {
    id: root

    property alias input: input
    property alias text: input.text
    property alias placeholderText: input.placeholderText
    property alias validator: input.validator

    signal editingFinished()

    width: 150
    height: 30
    property double inputValue: 1.0

    property int multiplierWidth: 75
    property int inputWidth: 75
    property int multiplierSelectedIndex: 5


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

}
