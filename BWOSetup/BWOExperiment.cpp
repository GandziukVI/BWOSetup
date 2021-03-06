#include "BWOExperiment.h"
#include "qmlBackEnd/BWOExpModel.h"

#include <QDebug>   // provides an output stream for debugging information
#include <QThread>
#include <QPointF>  // defines a point in the plane using
#include <QTime>    // only for different legend titles
#include <QString>  // --||--
#include <QTextStream>
#include <QFile>
#include <cmath>
#include <QFileDialog>

// Current realization of the error detection
// DAQmxFailer returns true when functionCall returns the value < 0
// Values > 0 are warnings
#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) throw error

BWOExperiment::BWOExperiment()
    : IExperiment()
{
}

BWOExperiment::BWOExperiment(QObject *expSettings)
    : IExperiment (expSettings),
      dataFile(nullptr)
{
}

BWOExperiment::~BWOExperiment()
{
    if (dataFile != nullptr)
        delete dataFile;
}

void BWOExperiment::stop()
{
    dataFile->close();
    QThread::msleep(100);
    IExperiment::stop();
}

void BWOExperiment::initializeHardware()
{
    BWOExpModel *model = qobject_cast<BWOExpModel*>(mExpSettings);

    // Concept of working with NI DAQmx: Create Task ->
    // -> Configurate its channel(s) -> Start Task ->
    // -> Write/Read/other actions with the channel(s) ->
    // -> Stop Task -> Clear Task

    std::string PIN_AO = (model->niDeviceName() + QString::fromLatin1("/") + model->pinAO()).toStdString();
    std::string PIN_AI = (model->niDeviceName() + QString::fromLatin1("/") + model->pinAI()).toStdString();

    // Configuration
    try
    {
        // TO DO: check the datasheet to detector-LockIn - what output values it produces, perhaps, must change the range
        DAQmxErrChk (DAQmxCreateTask("Input Voltage Task", &hTaskInput));
        DAQmxErrChk (DAQmxCreateAIVoltageChan(hTaskInput, PIN_AI.c_str(), "", DAQmx_Val_Cfg_Default, MIN_VOLTAGE_VALUE, MAX_VOLTAGE_VALUE, DAQmx_Val_Volts, NULL));
        DAQmxErrChk (DAQmxStartTask(hTaskInput));

        DAQmxErrChk (DAQmxCreateTask("Output Voltage Task", &hTaskOutput));
        DAQmxErrChk (DAQmxCreateAOVoltageChan(hTaskOutput, PIN_AO.c_str(), "", MIN_VOLTAGE_VALUE, MAX_VOLTAGE_VALUE, DAQmx_Val_Volts, ""));
        DAQmxErrChk (DAQmxStartTask(hTaskOutput));
    }
    catch(int error)
    {
        DAQmxGetExtendedErrorInfo(errBuff,2048);
        qDebug() << "DAQmx Error " << error << ":" << errBuff << endl;
    }
    catch (...)
    {
        qDebug() << "Unknown exception caught in stop()\n";
    }
}

void BWOExperiment::releaseHardware()
{
    qDebug() << "Resetting voltage and cleaning tasks...";
    try
    {
        // Move this command somewhere else. Or set 1500 V as a default for warming.
        // Better to set 0 after closing the programm
        //DAQmxErrChk (DAQmxWriteAnalogScalarF64(hTaskOutput, false, TIMEOUT, 0, NULL));
    }
    catch(int error)
    {
        DAQmxGetExtendedErrorInfo(errBuff,2048);
        qDebug() << "DAQmx Error " << error << ":" << errBuff << endl;
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
    qDebug() << "/*Voltage was reset.*/ Tasks are cleaned.";
}

double linearCalib(double x, double y, QVector<double> xarr, QVector<double> yarr)
{
    // linear extrapolation. suppose that all xarr is sorted
    double y_norm;
    if (x <= xarr[0]){
        y_norm = (yarr[1] - yarr[0]) / (xarr[1] - xarr[0]) * x + (xarr[1] * yarr[0] - xarr[0] * yarr[1]) / (xarr[1] - xarr[0]);
        // y_norm = a * x + b
    }
    else
        if(x >= xarr[xarr.length() - 1])        {
            int last = xarr.length() - 1;
            y_norm = (yarr[last] - yarr[last - 1]) / (xarr[last] - xarr[last - 1]) * x + (xarr[last] * yarr[last - 1] - xarr[last - 1] * yarr[last]) / (xarr[last] - xarr[last - 1]);
            // y_norm = a * x + b
        }
        else{
            int i = 0;
            while (x > xarr[i]) i++;
            y_norm = (yarr[i] - yarr[i - 1]) / (xarr[i] - xarr[i - 1]) * x + (xarr[i] * yarr[i - 1] - xarr[i - 1] * yarr[i]) / (xarr[i] - xarr[i - 1]);
            // y_norm = a * x + b
        }
    return y / y_norm;
}

void BWOExperiment::toDo(QObject *expSettings)
{
    BWOExpModel *model = qobject_cast<BWOExpModel*>(expSettings);
    QTime currentTime = QTime::currentTime();
    // TO DO: line titles should have temperature values
    QString title = "BWO Line Series" + QString::number(currentTime.minute()) + "-" + QString::number(currentTime.second());
    model->addLineSeries(title);

    dataFile = new QFile(model->filePath() + "/" + model->fileName());

    QVector<double> Vlampcal;
    QVector<double> Voutcal;
    if (model->calibFile() == "")
    {
        // use default calibration == normalized by 1
        // create calibration data that are linear
        qDebug() << Vlampcal.length();
    }
    else
    {
        // read and create the calibration data which that will be used for in a function calibration(value, calibdata)
        calibDataFile = new QFile(model->calibFile());
        calibDataFile->open(QIODevice::ReadOnly);
        QTextStream in(calibDataFile);
        int i = 0;
        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split("\t");
            if (i != 0){
                Vlampcal.append(fields[1].toDouble());
                Voutcal.append(fields[3].toDouble());
            }
            i++;
        }
        calibDataFile->close();
    }

    initializeHardware();
    emit ExperimentStarted();
    mExperimentIsRunning = true;
    try
    {
        if (!dataFile->open(QFile::WriteOnly)) throw dataFile->error();
        QTextStream out(dataFile);
        out << "V_NI (V)\tV_cat (V)\tf (GHz)\tV_det (V)\tT_detc ()\tT (K)" << endl;

        float64   lowestVoltage = model->startValue();
        float64   hightesVoltage = model->stopValue();
        int32     numberPoints = model->nDataPoints();
        int32     averageCycles = model->nAverages();
        double    delayBetweenMeasurements = model->delayTime();
        double    delayBetweenPoints = model->deltaTime();
        double    alphaCoefficient = model->alphaCoefficient();
        double    betaCoefficient = model->betaCoefficient();

        qDebug() << "Start Volt " << lowestVoltage << " end volt " << hightesVoltage << " num points " << numberPoints;

        // Helpful variables in the algorythm
        float64     average = 0;
        float64     voltageReadValue = 0;
        float64     frequencyWriteVoltage = 0;
        float64     delta = (hightesVoltage - lowestVoltage) / (numberPoints - 1);

        for(int32 i = 0; i < numberPoints; i++)
        {
            if (mExperimentIsRunning) {
                frequencyWriteVoltage = lowestVoltage + delta * i;
                DAQmxErrChk (DAQmxWriteAnalogScalarF64(hTaskOutput, false, TIMEOUT, frequencyWriteVoltage, NULL));
                QThread::msleep(static_cast<unsigned long>(delayBetweenMeasurements * 1000.0));
                qDebug() << "Current output voltage value is " << frequencyWriteVoltage;
                average = 0;
                for(int32 j = 1; j <= averageCycles; j++)
                {
                    if (mExperimentIsRunning) {
                        DAQmxErrChk (DAQmxReadAnalogScalarF64(hTaskInput, TIMEOUT, &voltageReadValue, NULL));
                        average += voltageReadValue;
                        qDebug() << "Current read voltage value is " << voltageReadValue;
                        QThread::msleep(static_cast<unsigned long>(delayBetweenPoints * 1000.0));
                        double progress = static_cast<double>(i * averageCycles + j) / numberPoints / averageCycles * 100.0;
                        emit ProgressChanged(progress);
                        model->setProgress(progress);
                    }
                    else
                        break;
                }
                average /= averageCycles;

                out << frequencyWriteVoltage << "\t" <<
                       frequencyWriteVoltage * CONVERT_VDAQ_VBWO << "\t" <<
                       sqrt(frequencyWriteVoltage * CONVERT_VDAQ_VBWO) / (alphaCoefficient + betaCoefficient * sqrt(frequencyWriteVoltage * CONVERT_VDAQ_VBWO)) << "\t" <<
                       average << "\t" <<
                       ((Vlampcal.length() == 0)?0:linearCalib(frequencyWriteVoltage * CONVERT_VDAQ_VBWO, average, Vlampcal, Voutcal)) << "\t" <<
                       0 << endl;
                // add function for calibration. Something like calibration(average, calibdata)
                model->addDataPoint(QPointF(frequencyWriteVoltage, average));

                qDebug() << "Averaged value is " << average;
            }
            else
                break;
        }
        model->activateStartButton();
    }
    catch(int error)
    {
        DAQmxGetExtendedErrorInfo(errBuff,2048);
        qDebug() << "DAQmx Error " << error << ":" << errBuff << endl;
    }
    catch(QFile::FileError error)
    {
        Q_UNUSED(error)
        qDebug() << "Problem with file opening";
    }
    catch (...)
    {
        qDebug() << "Unknown exception caught\n";
    }

    // emitting signal that experiment ended
    emit ExperimentFinished();
    mExperimentIsRunning = false;
    dataFile->close();
    qDebug() << "Experiment is finished.";

    releaseHardware();
}

void BWOExperiment::set()
{
    BWOExpModel *model = qobject_cast<BWOExpModel*>(mExpSettings);
    initializeHardware();
    try {
        qDebug() << "Set voltage confirmed";
        DAQmxErrChk (DAQmxWriteAnalogScalarF64(hTaskOutput, false, TIMEOUT, model->exactVoltageValue(), NULL));
    }
    catch(int error)
    {
        DAQmxGetExtendedErrorInfo(errBuff,2048);
        qDebug() << "DAQmx Error " << error << ":" << errBuff << endl;
    }
    catch (...)
    {
        qDebug() << "Unknown exception caught\n";
    }
    releaseHardware();
}
