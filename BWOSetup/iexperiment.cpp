#include "IExperiment.h"

#include <QtConcurrent/QtConcurrent>

IExperiment::IExperiment()
    : mExpSettings(NULL)
{
}

IExperiment::IExperiment(QObject *expSettings)
    : mExpSettings(expSettings)
{
}

IExperiment::~IExperiment()
{
    stop();
}

void IExperiment::start()
{
    mExpThreadRes = QtConcurrent::run(this, &this->toDo, mExpSettings);
}

void IExperiment::stop()
{
    while (mExpThreadRes.isRunning()) {
        mExpThreadRes.cancel();
        mExpThreadRes.waitForFinished();
    }
}
