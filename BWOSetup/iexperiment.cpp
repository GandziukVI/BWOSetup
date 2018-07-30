#include "IExperiment.h"

#include <QThread>
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
        mExpThreadRes = QtConcurrent::run(this, &IExperiment::toDo, mExpSettings);
    // To DO: Implement no argument exception
    else throw;
}

void IExperiment::stop()
{
    mExperimentIsRunning = false;
    QThread::msleep(500);

    while (mExpThreadRes.isRunning()) {
        mExpThreadRes.cancel();
        mExpThreadRes.waitForFinished();
    }
}
