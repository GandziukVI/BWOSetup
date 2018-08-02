import QtQuick 2.2

import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

Rectangle {
    // Arbitrary elements inside a QML document can be accessed by using their id (an unquoted identifier)
    // it’s good practice to name your root element “root” using id: root
    id: root
    width: 150
    height: 30

    //  (property alias <name> : <reference>). The alias keyword allows us to forward a property of
    // an object or an object itself from within the type to an outer scope.
    property alias input: input
    property alias horizontalAlignment: input.horizontalAlignment
    property alias placeholderText: input.placeholderText
    property alias text: input.text
    property alias validator: input.validator

    signal editingFinished()

    // A property can depend on one or many other properties. This is called binding.
    // A bound property is updated, when its dependent properties change. It works like a contract

    // custom property to an element is done using (property <type> <name> : <value>).
    // If no initial value is given a system initial value is chosen.
    property int integerValue: parseInt(input.text, 10)
    property double doubleValue: parseFloat(input.text)

    TextField {
        // The parent element can be accessed using the parent keyword
        id: input
        anchors.fill: parent
        autoScroll: true
        focus: true
        horizontalAlignment: TextField.AlignRight
        leftPadding: 10
        rightPadding: 10
        selectByMouse: true

        background: Rectangle {
            border.color: "gray"
        }

        onEditingFinished: root.editingFinished
    }
}
