import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtCharts 2.2

Window {
    id: root

    width: 1280
    height: 720

    visible: true

    title: qsTr("Backward Wave Oscillator (BWO)")

    MouseArea {
        anchors.fill: parent
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 10
        columns: 2

        // BWO Chart
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
                                Layout.fillWidth: true

                                height: 40
                                text: qsTr("10")
                                validator: DoubleValidator { locale: qsTr("en_US") }
                                units: qsTr("")
                            }

                            // Stop Value
                            Label {
                                Layout.margins: 2.5
                                text: qsTr("Stop Value")
                            }
                            CExtendedNumberInput {
                                Layout.fillWidth: true

                                height: 40
                                text: qsTr("100")
                                validator: DoubleValidator { locale: qsTr("en_US") }
                                units: qsTr("")
                            }

                            // Nomber of Points
                            Label {
                                Layout.margins: 2.5
                                text: qsTr("Points Number")
                            }
                            CExtendedNumberInput {
                                Layout.fillWidth: true

                                height: 40
                                text: qsTr("100")
                                validator: IntValidator { locale: qsTr("en_US") }
                                units: qsTr("")
                            }

                            // Averaging
                            Label {
                                Layout.margins: 2.5
                                text: qsTr("Averaging Number")
                            }
                            CExtendedNumberInput {
                                Layout.fillWidth: true

                                height: 40
                                text: qsTr("5")
                                validator: IntValidator { locale: qsTr("en_US") }
                                units: qsTr("")
                            }

                            // Delay Time
                            Label {
                                Layout.margins: 2.5
                                text: qsTr("Delay Time")
                            }
                            CExtendedNumberInput {
                                Layout.fillWidth: true

                                height: 40
                                text: qsTr("2")
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
                        }
                        Button {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            text: qsTr("Stop")
                        }
                    }
                }
            }
        }
    }
}
