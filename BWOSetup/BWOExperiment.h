#ifndef BWOEXPERIMENT_H
#define BWOEXPERIMENT_H

#include "IExperiment.h"

// Working with NI DAQmx
#include<NIDAQmx.h>

class BWOExperiment : public IExperiment
{
public:
    BWOExperiment();
    void toDo() override;
    void toDo(QObject *expSettings) override;
    void stop() override;

private:
    const float64   MAX_VOLTAGE_VALUE = 5.0;    // 0 V .. +5 V is output range
    const float64   MIN_VOLTAGE_VALUE = 0.0;    // Probably we need to use another ranges for the input range (Single-ended ±10 V in specifications to USB-6008)
    const float64   TIMEOUT = 4.0;              // Waiting time for one read/write action in seconds

    int32       error=0;
    char        errBuff[2048]={'\0'};

    TaskHandle  hTaskInput = 0;
    TaskHandle  hTaskOutput = 0;

    float64     average = 0;
    float64     voltageValue = 0;
    float64     lowestVoltage = 0;
    float64     hightesVoltage = 0;
    int32       numberPoints = 0;

    int i, l;
    int32 read;
    int vStart, vStop, step = 10, nPoints;

public slots:
    void onProgressChanged(double progress);
};

#endif // BWOEXPERIMENT_H
