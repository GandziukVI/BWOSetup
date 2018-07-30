#ifndef IEXPERIMENT_H
#define IEXPERIMENT_H

#include <QFuture>
#include <QMutex>
#include <QObject>

class IExperiment : public QObject
{
    Q_OBJECT
public:
    IExperiment(QObject *expSettings);
    ~IExperiment();

    virtual void start();
    virtual void stop();

protected:
    bool    mExperimentIsRunning;
    QObject *mExpSettings;

    IExperiment();
    virtual void toDo(QObject *expSettings) = 0;

private:
    mutable QMutex mIExperimentMutex;
    QFuture<void>  mExpThreadRes;

signals:
    void StatusChanged(QString &stautusString);
    void ProgressChanged(double progressValue);
    void ExperimentStarted();
    void ExperimentFinished();
};

#endif // IEXPERIMENT_H
