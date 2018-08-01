#include "IExperiment.h"

#include <QThread>                      // for pauses
#include <QtConcurrent/QtConcurrent>    // makes it possible to write multi-threaded programs

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
    if(mExperimentIsRunning)
        stop();
}

void IExperiment::start()
{
    if (mExpSettings != nullptr)
        mExpThreadRes = QtConcurrent::run(this, &IExperiment::toDo, mExpSettings);
    // To DO: Implement no argument exception
    // one way to do it is to get rid of the constructor without parameters
    else throw;
}

void IExperiment::stop()
{
    mExperimentIsRunning = false;
    QThread::msleep(2000);                  // give time to get out of the toDo method
    while (mExpThreadRes.isRunning()) {     // otherwise, force termination
        mExpThreadRes.cancel();
        mExpThreadRes.waitForFinished();
    }
}
