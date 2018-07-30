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
    qDebug() << "We are in a IE destructor\n";
    if(mExperimentIsRunning)
    {
        stop();
    }
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
    qDebug() << "stop IExp";
}
