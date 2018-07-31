import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtCharts 2.2

import BWOModel 1.0

Item {
    id: root

    width: 1280
    height: 720

    visible: true

    MouseArea {
        anchors.fill: parent
    }

    signal startButtonClicked()
    signal stopButtonClicked()

    GridLayout {
        anchors.fill: parent
        anchors.margins: 10
        columns: 2

        // BWO Chart
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ChartView {
                id: bwoChart

                Layout.fillWidth: true
                Layout.fillHeight: true

                legend.visible: true

                theme: ChartView.ChartThemeBlueCerulean

                LineSeries {
                    id: noiseFETLineGraph

                    axisX: ValueAxis {
                        id: bwoXAxis
                        min: 0.0
                        max: 1.0
                        titleText: qsTr("x Axis")
                    }

                    axisY: ValueAxis {
                        id: bwoYAxis
                        labelFormat: qsTr("%.3e")
                        min: 0.0
                        max: 1.0
                        titleText: qsTr("BWO Y Axis")
                    }
                }
            }

            ProgressBar {
                id: bwoExpProgress

                Layout.fillWidth: true
                height: 20

                from: 0.0
                to: 100.0

                value: dataModel.progress
                Binding {
                    target: dataModel
                    property: "progress"
                    value: bwoExpProgress.value
                }
            }
        }

        // BWO Settings
        Item {
            Layout.preferredWidth: 400
            Layout.maximumWidth: 400

            Layout.fillWidth: true
            Layout.fillHeight: true

            ColumnLayout {
                anchors.fill: parent

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    id: bwoSettings

                    ScrollView {
                        anchors.fill: parent
                        clip: true

                        GridLayout {
                            width: bwoSettings.width
                            height: children.height

                            columns: 2

                            // NI SDA Device Name
                            Label {
                                Layout.margins: 2.5
                                text: qsTr("Device Name")
                            }
                            CTextField {
                                id: niDeviceNameInput
                                Layout.fillWidth: true
                                height: 40
                                text: dataModel.niDeviceName
                                Binding {
                                    target: dataModel
                                    property: "niDeviceName"
                                    value: niDeviceNameInput.text
                                }
                            }

                            // NI SDA Output Channel
                            Label {
                                Layout.margins: 2.5
                                text: qsTr("Analog Output Name")
                            }
                            CTextField {
                                id: niAOInput
                                Layout.fillWidth: true
                                height: 40
                                text: dataModel.pinAO
                                Binding {
                                    target: dataModel
                                    property: "pinAO"
                                    value: niAOInput.text
                                }
                            }

                            // NI SDA Input Channel
                            Label {
                                Layout.margins: 2.5
                                text: qsTr("Analog Input Name")
                            }
                            CTextField {
                                id: niAIInput
                                Layout.fillWidth: true
                                height: 40
                                text: dataModel.pinAI
                                Binding {
                                    target: dataModel
                                    property: "pinAI"
                                    value: niAIInput.text
                                }
                            }

                            // Measurement Mode: Frequency or Voltage
                            GroupBox {
                                Layout.columnSpan: 2
                                Layout.fillWidth: true

                                title: qsTr("Measurement Mode")

                                ColumnLayout {
                                    RadioButton {
                                        text: qsTr("Frequency Steps")
                                        checked: true
                                    }
                                    RadioButton {
                                        text: qsTr("Voltage Steps")
                                    }
                                }
                            }

                            // Start Value
                            Label {
                                Layout.margins: 2.5
                                text: qsTr("Start Value")
                            }
                            CExtendedNumberInput {
                                id: startValueInput
                                Layout.fillWidth: true

                                height: 40

                                inputValue: dataModel.startValue
                                Binding {
                                    target: dataModel
                                    property: "startValue"
                                    value: startValueInput.inputValue
                                }

                                validator: DoubleValidator { locale: qsTr("en_US") }
                                units: qsTr("")
                            }

                            // Stop Value
                            Label {
                                Layout.margins: 2.5
                                text: qsTr("Stop Value")
                            }
                            CExtendedNumberInput {
                                id: stopValueInput
                                Layout.fillWidth: true

                                height: 40

                                inputValue: dataModel.stopValue
                                Binding {
                                    target: dataModel
                                    property: "stopValue"
                                    value: stopValueInput.inputValue
                                }

                                validator: DoubleValidator { locale: qsTr("en_US") }
                                units: qsTr("")
                            }

                            // Nomber of Points
                            Label {
                                Layout.margins: 2.5
                                text: qsTr("Points Number")
                            }
                            CTextField {
                                id: nPointsInput
                                Layout.fillWidth: true

                                height: 40

                                text: dataModel.nDataPoints
                                Binding {
                                    target: dataModel
                                    property: "nDataPoints"
                                    value: nPointsInput.integerValue
                                }

                                validator: IntValidator { locale: qsTr("en_US") }
                            }

                            // Averaging
                            Label {
                                Layout.margins: 2.5
                                text: qsTr("Averaging Number")
                            }
                            CTextField {
                                id: nAveragingInput
                                Layout.fillWidth: true

                                height: 40

                                text: dataModel.nAverages
                                Binding {
                                    target: dataModel
                                    property: "nAverages"
                                    value: nAveragingInput.integerValue
                                }

                                validator: IntValidator { locale: qsTr("en_US") }
                            }

                            // Delay Time
                            Label {
                                Layout.margins: 2.5
                                text: qsTr("Delay Time")
                            }
                            CExtendedNumberInput {
                                id: delayTimeInput
                                Layout.fillWidth: true

                                height: 40

                                inputValue: dataModel.delayTime
                                Binding {
                                    target: dataModel
                                    property: "delayTime"
                                    value: delayTimeInput.inputValue
                                }

                                validator: DoubleValidator { locale: qsTr("en_US") }
                                units: qsTr("s")
                            }
                        }
                    }
                }

                // Start / Stop buttons
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.maximumHeight: 40

                    RowLayout {
                        anchors.fill: parent
                        Button {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            text: qsTr("Start")

                            onClicked: root.startButtonClicked()
                        }
                        Button {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            text: qsTr("Stop")

                            onClicked: root.stopButtonClicked()
                        }
                    }
                }
            }
        }
    }
}
