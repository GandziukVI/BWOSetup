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

    property variant measUnit: qsTr("Hz");
    property variant measType: qsTr("Frequency, Hz")

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
                objectName: "bwoChart"

                Layout.fillWidth: true
                Layout.fillHeight: true

                legend.visible: true

                theme: ChartView.ChartThemeBlueCerulean

                ValueAxis {
                    id: bwoChartXAxis

                    min: dataModel.startValue
                    max: dataModel.stopValue
                }

                ValueAxis {
                    id: bwoChartYAxis

                    min: 0
                    max: 2
                }

                function createAxis(min, max) {
                    // The following creates a ValueAxis object that can be then set as a x or y axis for a series
                    return Qt.createQmlObject("import QtQuick 2.0; import QtCharts 2.0; ValueAxis { min: "
                                              + min + "; max: " + max + " }", bwoChart);
                }
                function addLineSeries (seriesName) {
                    bwoChartXAxis.titleText = root.measType
                    bwoChartYAxis.titleText = qsTr("BWO System Response")

                    var newSeries = bwoChart.createSeries(ChartView.SeriesTypeLine, seriesName, bwoChartXAxis, bwoChartYAxis);
                    newSeries.useOpenGL = true;
                }

                Connections {
                    target: dataModel
                    onAddNewLineSeries: {
                        bwoChart.addLineSeries(chartNameString);
                    }
                }

                Connections {
                    target:  dataModel
                    onAddNewDataPoint: {
                        bwoChart.series(bwoChart.count - 1).append(dataPoint.x, dataPoint.y);
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true

                Layout.topMargin: 2.5
                Layout.bottomMargin: 2.5
                Layout.leftMargin: 5
                Layout.rightMargin: 5

                Label {
                    text: qsTr("Progress:")
                }

                ProgressBar {
                    id: bwoExpProgress

                    Layout.fillWidth: true

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
        }

        // BWO Settings
        Item {
            id: bwoMeasSettings

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

                            // BWO lamp coefficients
                            Label {
                                Layout.margins: 2.5
                                text: qsTr("BWO coefficient alpha")
                            }
                            CTextField {
                                id: alphaCoefficient
                                Layout.fillWidth: true
                                height: 40
                                text: dataModel.alphaCoefficient
                                Binding {
                                    target: dataModel
                                    property: "alphaCoefficient"
                                    value: alphaCoefficient.text
                                }
                            }

                            Label {
                                Layout.margins: 2.5
                                text: qsTr("BWO coefficient beta")
                            }
                            CTextField {
                                id: betaCoefficient
                                Layout.fillWidth: true
                                height: 40
                                text: dataModel.betaCoefficient
                                Binding {
                                    target: dataModel
                                    property: "betaCoefficient"
                                    value: betaCoefficient.text
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

                                        onCheckedChanged: {
                                            if (checked) {
                                                root.measUnit = qsTr("Hz");
                                                root.measType = qsTr("Frequency, Hz");
                                                bwoChart.update();
                                            }
                                        }
                                    }
                                    RadioButton {
                                        text: qsTr("Voltage Steps")

                                        onCheckedChanged: {
                                            if (checked) {
                                                root.measUnit = qsTr("V");
                                                root.measType = qsTr("Voltage, V");
                                                bwoChart.update();
                                            }
                                        }
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
                                units: root.measUnit
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
                                units: root.measUnit
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
                    id: startStopItem
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.maximumHeight: 40
                    property variant enabledState: true

                    RowLayout {
                        anchors.fill: parent
                        Button {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            text: qsTr("Start")
                            enabled: startStopItem.enabledState
                            onClicked: {
                                root.startButtonClicked();
                                startStopItem.enabledState = !startStopItem.enabledState;
                            }
                        }
                        Button {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            text: qsTr("Stop")
                            enabled: !startStopItem.enabledState
                            onClicked: {
                                root.stopButtonClicked()
                                startStopItem.enabledState = !startStopItem.enabledState;
                            }
                        }
                    }
                }
            }
        }
    }
}
