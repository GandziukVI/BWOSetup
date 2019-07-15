#ifndef BWOEXPERIMENT_H
#define BWOEXPERIMENT_H

#include "IExperiment.h"
#include <NIDAQmx.h>        // Working with NI DAQmx
#include <QFile>
#include <QString>

class BWOExperiment : public IExperiment
{
public:
    BWOExperiment(QObject *expSettings);
    void toDo(QObject *expSettings) override;
    ~BWOExperiment() override;                  // ?? What should we override? Should we make the IExp destructor virtual then?
    void stop() override;
    void set();
private:
    BWOExperiment();

    const float64   MAX_VOLTAGE_VALUE = 5.0;    // 0 V .. +5 V is output range
    const float64   MIN_VOLTAGE_VALUE = 0.0;    // Probably we need to use another ranges for the input range (Single-ended ±10 V in specifications to USB-6008)
    const float64   TIMEOUT = 4.0;              // Waiting time for one read/write action in seconds
    const float64   CONVERT_VDAQ_VBWO = 572;    // Ratio between applied voltage from DAQ and what is applied on the lamp. Found experimentally

    int32       error = 0;
    char        errBuff[2048] = {'\0'};

    TaskHandle  hTaskInput = nullptr;
    TaskHandle  hTaskOutput = nullptr;

    QFile       *dataFile;
    QString     folderPath;

private:
    void initializeHardware();
    void releaseHardware();
};

#endif // BWOEXPERIMENT_H
