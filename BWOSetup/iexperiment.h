#ifndef IEXPERIMENT_H
#define IEXPERIMENT_H

#include <QFuture>
#include <QMutex>
#include <QObject>

class IExperiment : public QObject
{
    Q_OBJECT
public:
    IExperiment();
    IExperiment(QObject *expSettings);
    ~IExperiment();

    virtual void start();
    virtual void stop();
    virtual void toDo() = 0;
    virtual void toDo(QObject *expSettings) = 0;

    bool    mExperimentIsRunning;
    QObject *mExpSettings;

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
