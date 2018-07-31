#ifndef BWOEXPMODEL_H
#define BWOEXPMODEL_H

#include <QObject>

class BWOExpModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double startValue READ startValue WRITE setStartValue NOTIFY startValueChanged)
    Q_PROPERTY(double stopValue READ stopValue WRITE setStopValue NOTIFY stopValueChanged)
    Q_PROPERTY(int nDataPoints READ nDataPoints WRITE setNDataPoints NOTIFY nDataPointsChanged)
    Q_PROPERTY(int nAverages READ nAverages WRITE setNAverages NOTIFY nAveragesChanged)
    Q_PROPERTY(double delayTime READ delayTime WRITE setDelayTime NOTIFY delayTimeChanged)
    Q_PROPERTY(QString niDeviceName READ niDeviceName WRITE setNIDeviceName NOTIFY niDeviceNameChanged)
    Q_PROPERTY(QString pinAO READ pinAO WRITE setPinAO NOTIFY pinAOChanged)
    Q_PROPERTY(QString pinAI READ pinAI WRITE setPinAI NOTIFY pinAIChanged)
    Q_PROPERTY(double progress READ progress WRITE setProgress NOTIFY progressChanged)

public:
    explicit BWOExpModel(QObject *parent = nullptr);

    double  startValue();
    void    setStartValue(const double &value);

    double  stopValue();
    void    setStopValue(const double &value);

    int     nDataPoints();
    void    setNDataPoints(const int &value);

    int     nAverages();
    void    setNAverages(const int &value);

    double  delayTime();
    void    setDelayTime(const double &value);

    QString niDeviceName();
    void    setNIDeviceName(const QString &value);

    QString pinAO();
    void    setPinAO(const QString &value);

    QString pinAI();
    void    setPinAI(const QString &value);

    double  progress();
    void    setProgress(const double &value);

    // Public Methods
    void addLineSeries(const QString &chartNameString);
    void addDataPoint(const QPointF &dataPoint);

signals:
    void startValueChanged(const double&);
    void stopValueChanged(const double&);
    void nDataPointsChanged(const int&);
    void nAveragesChanged(const int&);
    void delayTimeChanged(const double&);
    void niDeviceNameChanged(const QString&);
    void pinAOChanged(const QString&);
    void pinAIChanged(const QString&);
    void progressChanged(const double&);

    void addNewLineSeries(const QString &chartNameString);
    void addNewDataPoint(const QPointF &dataPoint);

private:
    double  mStartValue;  // Either Voltage or Frequency
    double  mStopValue;   // Either Voltage or Frequency
    int     mNDataPoints;
    int     mNAverages;
    double  mDelayTime;   // Delay time in seconds
    QString mDeviceName;
    QString mPinAO;
    QString mPinAI;
    double  mProgress;

    QString mCurrentLineSeries;
};

#endif // BWOEXPMODEL_H
