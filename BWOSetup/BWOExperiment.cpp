#include "BWOExperiment.h"

// For debugging
#include <QDebug>
#include <QThread>

// current realization of the error detection
// DAQmxFailer returns true when functionCall returns the value < 0
// Values > 0 are warnings
#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) throw error

BWOExperiment::BWOExperiment()
{
    QObject::connect(this, &BWOExperiment::ProgressChanged, this, &BWOExperiment::onProgressChanged);
}

void BWOExperiment::toDo()
{
    // Concept of working with NI DAQmx: Create Task -> Configurate its channel(s) -> Start Task ->
    // -> Write/Read/other actions with the channel(s) -> Stop Task -> Clear Task */

    // Sending signal that experiment has been started
   /*emit ExperimentStarted();

    try
    {
        DAQmxErrChk (DAQmxCreateTask("",&hTaskInput));
        DAQmxErrChk (DAQmxCreateAIVoltageChan(hTaskInput,"Dev1/ai3","",DAQmx_Val_Cfg_Default,MIN_VOLTAGE_VALUE,MAX_VOLTAGE_VALUE,DAQmx_Val_Volts,NULL));
        DAQmxErrChk (DAQmxStartTask(hTaskInput));

        DAQmxErrChk (DAQmxCreateTask("Output Voltage Task",&hTaskOutput));
        DAQmxErrChk (DAQmxCreateAOVoltageChan(hTaskOutput,"Dev1/ao0","", MIN_VOLTAGE_VALUE,MAX_VOLTAGE_VALUE,DAQmx_Val_Volts,""));
        DAQmxErrChk (DAQmxStartTask(hTaskOutput));
        DAQmxErrChk (DAQmxWriteAnalogScalarF64(hTaskOutput,false,4,1.543,NULL));
        QThread::msleep(5000);
        for(int i = 1; i <= 30; i++)
        {
            DAQmxErrChk (DAQmxWriteAnalogScalarF64(hTaskOutput,false,4,i*0.1,NULL));
            QThread::msleep(500);
            qDebug() << "Current voltage value is " << i*0.1;
            //            cout << i*0.001;
            //            DAQmxErrChk (DAQmxReadAnalogScalarF64(hTaskInput,4,&voltageValue,NULL));
            //            fout << i*0.1 << "\t" << voltageValue << endl;
            //            Sleep(1000);
        }
    }
    catch(int error)
    {
        DAQmxGetExtendedErrorInfo(errBuff,2048);
        qDebug() << "DAQmx Error: " << errBuff;
    }
    catch (...)
    {
        qDebug() << "Unknown exception caught\n";
    }

    if( hTaskInput!=0 )  {
        DAQmxStopTask(hTaskInput);
        DAQmxClearTask(hTaskInput);
    }
    if( hTaskOutput!=0 )  {
        DAQmxStopTask(hTaskOutput);
        DAQmxClearTask(hTaskOutput);
    }

    // emitting signal that experiment ended
    emit ExperimentFinished();*/
    qDebug() << "To do function ended";
}

void BWOExperiment::toDo(QObject *expSettings)
{
    // Concept of working with NI DAQmx: Create Task ->
    // -> Configurate its channel(s) -> Start Task ->
    // -> Write/Read/other actions with the channel(s) ->
    // -> Stop Task -> Clear Task

    // Sending signal that experiment has been started
    emit ExperimentStarted();

    try
    {
        // Configuration
        DAQmxErrChk (DAQmxCreateTask("Input Voltage Task", &hTaskInput));
        DAQmxErrChk (DAQmxCreateAIVoltageChan(hTaskInput, "Dev1/ai3", "", DAQmx_Val_Cfg_Default, MIN_VOLTAGE_VALUE, MAX_VOLTAGE_VALUE, DAQmx_Val_Volts, NULL));
        DAQmxErrChk (DAQmxStartTask(hTaskInput));

        DAQmxErrChk (DAQmxCreateTask("Output Voltage Task", &hTaskOutput));
        DAQmxErrChk (DAQmxCreateAOVoltageChan(hTaskOutput, "Dev1/ao0", "", MIN_VOLTAGE_VALUE, MAX_VOLTAGE_VALUE, DAQmx_Val_Volts, ""));
        DAQmxErrChk (DAQmxStartTask(hTaskOutput));


        QThread::msleep(1000);
        // TO DO:
        // Get this information from the Window
        lowestVoltage = 0;
        hightesVoltage = 3;
        numberPoints = 7;
        float64 delta = (hightesVoltage - lowestVoltage) / (numberPoints - 1);

        for(int32 i = 0; i < numberPoints; i++)
        {
            //TO DO: add averaging

            average = lowestVoltage + delta * i;
            DAQmxErrChk (DAQmxWriteAnalogScalarF64(hTaskOutput, false, TIMEOUT, average, NULL));
            QThread::msleep(500);
            qDebug() << "Current voltage value is " << average;

            DAQmxErrChk (DAQmxReadAnalogScalarF64(hTaskInput, TIMEOUT, &voltageValue, NULL));

            qDebug() << "Current read voltage value is " << voltageValue;

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

    qDebug() << "To do function ended";

    this->stop();
}

void BWOExperiment::stop()
{
    // To DO:
    // Add voltage reset when experiment is finished: set to zero
    // WHERE SHOULD THIS FUNCTION BE USED???
    DAQmxErrChk (DAQmxWriteAnalogScalarF64(hTaskOutput,false,4,0,NULL));
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
