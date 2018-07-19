#ifndef BWOEXPERIMENT_H
#define BWOEXPERIMENT_H

#include "IExperiment.h"

class BWOExperiment : public IExperiment
{
public:
    BWOExperiment();
    void toDo() override;
    void toDo(QObject *expSettings) override;
};

#endif // BWOEXPERIMENT_H
