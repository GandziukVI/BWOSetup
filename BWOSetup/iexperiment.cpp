#include "IExperiment.h"

#include <QtConcurrent/QtConcurrent>

IExperiment::IExperiment()
    : mExpSettings(nullptr)
{
}

IExperiment::IExperiment(QObject *expSettings)
    : mExpSettings(expSettings)
{
}

IExperiment::~IExperiment()
{
    qDebug() << "We are in a IE destructor\n";

    if(mExperimentIsRunning)
        stop();
}

void IExperiment::start()
{
    if (mExpSettings != nullptr)
        mExpThreadRes = QtConcurrent::run(this, &this->toDo, mExpSettings);
    // To DO: Implement no argument exception
    else throw;
}

void IExperiment::stop()
{
    while (mExpThreadRes.isRunning()) {
        mExpThreadRes.cancel();
        mExpThreadRes.waitForFinished();
    }
    qDebug() << "stop IExp";
}
