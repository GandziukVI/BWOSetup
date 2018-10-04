#ifndef IEXPERIMENT_H
#define IEXPERIMENT_H

#include <QFuture>      // allows threads to be synchronized against one or more results which will be ready at a later point in time.
#include <QObject>      // is the base class of all Qt objects.
#include <QMutex>       // is to protect an object, data structure or section of code so that only one thread can access it at a time. Delete?

// The Meta-Object Compiler (moc) tool reads a C++ header file. If it finds one or more
// class declarations that contain the Q_OBJECT macro, it produces a C++ source file
// containing the meta-object code for those classes. Meta-object code is required for
// the signals and slots mechanism, the run-time type information, and the dynamic property system.

/* IExperiment class is the basic class for a single experiment realization
 * It introduces the most important methods, signals, and slots */
class IExperiment : public QObject
{
    Q_OBJECT
public:
    IExperiment(QObject *expSettings);              // ?? Why do we need a constructor with Settings if we launch toDo with settings?
    ~IExperiment();

public slots:                                       // Slots those should react on signals/other action to run and stop the exp.
    virtual void start();
    virtual void stop();
    virtual void openFolder() = 0;                      // Cannot connect signal without this. Should be changed.
    virtual void set() = 0;

protected:
    bool    mExperimentIsRunning;
    QObject *mExpSettings;

    IExperiment();
    virtual void toDo(QObject *expSettings) = 0;    // The main logic of the experiment should be relized in this method

private:
    mutable QMutex mIExperimentMutex;               // !! Never used. What is it for?
    QFuture<void>  mExpThreadRes;                   // represents the result of an asynchronous computation

signals:
    void StatusChanged(QString &statusString);      // !! Never used. TO DO: create the field on the form to display the current status
    void ProgressChanged(double progressValue);
    void ExperimentStarted();
    void ExperimentFinished();
};

#endif // IEXPERIMENT_H
