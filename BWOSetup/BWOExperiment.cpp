#include "BWOExperiment.h"

// For debugging
#include <QDebug>
#include <QThread>

// Current realization of the error detection
// DAQmxFailer returns true when functionCall returns the value < 0
// Values > 0 are warnings
#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) throw error

BWOExperiment::BWOExperiment()
{
    QObject::connect(this, &BWOExperiment::ProgressChanged, this, &BWOExperiment::onProgressChanged);
}

BWOExperiment::~BWOExperiment()
{
    stop();
}

void BWOExperiment::toDo()
{
    qDebug() << "To do() function ended";
}

void BWOExperiment::toDo(QObject *expSettings)
{
    // Concept of working with NI DAQmx: Create Task ->
    // -> Configurate its channel(s) -> Start Task ->
    // -> Write/Read/other actions with the channel(s) ->
    // -> Stop Task -> Clear Task

    // Sending signal that experiment has been started
    emit ExperimentStarted();
    mExperimentIsRunning = true;
    try
    {
        // Configuration
        DAQmxErrChk (DAQmxCreateTask("Input Voltage Task", &hTaskInput));
        DAQmxErrChk (DAQmxCreateAIVoltageChan(hTaskInput, PIN_AI, "", DAQmx_Val_Cfg_Default, MIN_VOLTAGE_VALUE, MAX_VOLTAGE_VALUE, DAQmx_Val_Volts, NULL));
        DAQmxErrChk (DAQmxStartTask(hTaskInput));

        DAQmxErrChk (DAQmxCreateTask("Output Voltage Task", &hTaskOutput));
        DAQmxErrChk (DAQmxCreateAOVoltageChan(hTaskOutput, PIN_AO, "", MIN_VOLTAGE_VALUE, MAX_VOLTAGE_VALUE, DAQmx_Val_Volts, ""));
        DAQmxErrChk (DAQmxStartTask(hTaskOutput));

        QThread::msleep(1000);

        // TO DO:
        // Get this information from the Window
        lowestVoltage = 0;
        hightesVoltage = 3;
        numberPoints = 7;
        averageCycles = 3;
        float64 delta = (hightesVoltage - lowestVoltage) / (numberPoints - 1);
        for(int32 i = 0; i < numberPoints; i++)
        {
            frequencyWriteVoltage = lowestVoltage + delta * i;
            DAQmxErrChk (DAQmxWriteAnalogScalarF64(hTaskOutput, false, TIMEOUT, frequencyWriteVoltage, NULL));
            QThread::msleep(500);
            qDebug() << "Current output voltage value is " << frequencyWriteVoltage;
            average = 0;
            for(int32 j = 1; j <= averageCycles; j++)
            {
                DAQmxErrChk (DAQmxReadAnalogScalarF64(hTaskInput, TIMEOUT, &voltageReadValue, NULL));
                average += voltageReadValue;
                qDebug() << "Current read voltage value is " << voltageReadValue;
                QThread::msleep(500);
            }
            average /= averageCycles;
            qDebug() << "Averaged value is " << average;
            double progress = (i + 1) / numberPoints * 100.0;
            emit ProgressChanged(progress);
        }
    }
    catch(int error)
    {
        DAQmxGetExtendedErrorInfo(errBuff,2048);
        qDebug() << "DAQmx Error: " << errBuff << endl;
    }
    catch (...)
    {
        qDebug() << "Unknown exception caught\n";
    }    

    // emitting signal that experiment ended
    emit ExperimentFinished();
    mExperimentIsRunning = false;
    qDebug() << "To do() function with arguments ended";
}

void BWOExperiment::stop()
{
    // To DO:
    // Add voltage reset when experiment is finished: set to zero
    // WHERE SHOULD THIS FUNCTION BE USED???
    try
    {
        DAQmxErrChk (DAQmxWriteAnalogScalarF64(hTaskOutput,false,4,0,NULL));
    }
    catch(int error)
    {
        DAQmxGetExtendedErrorInfo(errBuff,2048);
        qDebug() << "DAQmx Error: " << errBuff << endl;
    }
    catch (...)
    {
        qDebug() << "Unknown exception caught in stop()\n";
    }
    QThread::msleep(500);
    if( hTaskInput!=0 )  {
        DAQmxStopTask(hTaskInput);
        DAQmxClearTask(hTaskInput);
    }
    if( hTaskOutput!=0 )  {
        DAQmxStopTask(hTaskOutput);
        DAQmxClearTask(hTaskOutput);
    }
    qDebug() << "Voltage was reset. Tasks are cleaned.";
    IExperiment::stop();
}

void BWOExperiment::onProgressChanged(double progress)
{
    qDebug() << "Current progress is " << progress;
}
