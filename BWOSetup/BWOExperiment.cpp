#include "BWOExperiment.h"
#include "qmlBackEnd/BWOExpModel.h"

// For debugging
#include <QDebug>
#include <QThread>

// Current realization of the error detection
// DAQmxFailer returns true when functionCall returns the value < 0
// Values > 0 are warnings
#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) throw error

#include "qmlBackEnd/BWOExpModel.h"

BWOExperiment::BWOExperiment()
    : IExperiment()
{
}

BWOExperiment::BWOExperiment(QObject *expSettings)
    : IExperiment (expSettings)
{
    QObject::connect(this, &BWOExperiment::ProgressChanged, this, &BWOExperiment::onProgressChanged);

    // Concept of working with NI DAQmx: Create Task ->
    // -> Configurate its channel(s) -> Start Task ->
    // -> Write/Read/other actions with the channel(s) ->
    // -> Stop Task -> Clear Task


    // Configuration
    DAQmxErrChk (DAQmxCreateTask("Input Voltage Task", &hTaskInput));
    DAQmxErrChk (DAQmxCreateAIVoltageChan(hTaskInput, PIN_AI, "", DAQmx_Val_Cfg_Default, MIN_VOLTAGE_VALUE, MAX_VOLTAGE_VALUE, DAQmx_Val_Volts, NULL));
    DAQmxErrChk (DAQmxStartTask(hTaskInput));

    DAQmxErrChk (DAQmxCreateTask("Output Voltage Task", &hTaskOutput));
    DAQmxErrChk (DAQmxCreateAOVoltageChan(hTaskOutput, PIN_AO, "", MIN_VOLTAGE_VALUE, MAX_VOLTAGE_VALUE, DAQmx_Val_Volts, ""));
    DAQmxErrChk (DAQmxStartTask(hTaskOutput));
}

BWOExperiment::~BWOExperiment()
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
        Q_UNUSED(error)
        DAQmxGetExtendedErrorInfo(errBuff,2048);
        qDebug() << "DAQmx Error: " << errBuff << endl;
    }
    catch (...)
    {
        qDebug() << "Unknown exception caught in stop()\n";
    }
    QThread::msleep(500);
    if( hTaskInput!=nullptr )  {
        DAQmxStopTask(hTaskInput);
        DAQmxClearTask(hTaskInput);
    }
    if( hTaskOutput!=nullptr )  {
        DAQmxStopTask(hTaskOutput);
        DAQmxClearTask(hTaskOutput);
    }
    qDebug() << "Voltage was reset. Tasks are cleaned.";

    stop();
}

void BWOExperiment::toDo(QObject *expSettings)
{
    qDebug() << "Entering TO DO method...";

    BWOExpModel *model = qobject_cast<BWOExpModel*>(expSettings);

    // Sending signal that experiment has been started
    emit ExperimentStarted();
    mExperimentIsRunning = true;
    try
    {
        // TO DO:
        // Get this information from the Window
        float64   lowestVoltage = model->startValue();
        float64   hightesVoltage = model->stopValue();
        int32     numberPoints = model->nDataPoints();
        int32     averageCycles = model->nAverages();
        double    delayBetweenMeasurements = model->delayTime();

        qDebug() << "Start Volt " << lowestVoltage << " end volt " << hightesVoltage << " num points " << numberPoints;

        // Helpful variables in the algorythm
        float64         average = 0;
        float64         voltageReadValue = 0;
        float64         frequencyWriteVoltage = 0;

        float64 delta = (hightesVoltage - lowestVoltage) / (numberPoints - 1);
        for(int32 i = 0; i < numberPoints; i++)
        {
            if (mExperimentIsRunning) {
                frequencyWriteVoltage = lowestVoltage + delta * i;
                DAQmxErrChk (DAQmxWriteAnalogScalarF64(hTaskOutput, false, TIMEOUT, frequencyWriteVoltage, NULL));
                QThread::msleep(500);
                qDebug() << "Current output voltage value is " << frequencyWriteVoltage;
                average = 0;
                for(int32 j = 1; j <= averageCycles; j++)
                {
                    if (mExperimentIsRunning) {
                        DAQmxErrChk (DAQmxReadAnalogScalarF64(hTaskInput, TIMEOUT, &voltageReadValue, NULL));
                        average += voltageReadValue;
                        qDebug() << "Current read voltage value is " << voltageReadValue;
                        QThread::msleep(static_cast<unsigned long>(delayBetweenMeasurements * 1000.0));
                    }
                    else
                        break;
                }
                average /= averageCycles;
                qDebug() << "Averaged value is " << average;
                double progress = static_cast<double>(i + 1) / static_cast<double>(numberPoints) * 100.0;
                emit ProgressChanged(progress);
            }
            else
                break;
        }
    }
    catch(int error)
    {
        Q_UNUSED(error)

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

void BWOExperiment::onProgressChanged(double progress)
{
    qDebug() << "Current progress is " << progress;
}
