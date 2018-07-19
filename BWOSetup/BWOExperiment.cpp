#include "BWOExperiment.h"

// For debugging
#include <QDebug>
#include <QThread>

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) throw error

BWOExperiment::BWOExperiment()
{

}

void BWOExperiment::toDo()
{
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

    qDebug() << "To do function ended";
}

void BWOExperiment::toDo(QObject *expSettings)
{
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
            QThread::msleep(1000);
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

    qDebug() << "To do function ended";
}

void BWOExperiment::stop()
{
    // To DO:
    // Add voltage reset when experiment is finished

    IExperiment::stop();
}
