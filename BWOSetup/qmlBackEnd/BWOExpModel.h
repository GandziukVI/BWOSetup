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

public:
    explicit BWOExpModel(QObject *parent = nullptr);

    double startValue();
    void   setStartValue(const double &value);

    double stopValue();
    void   setStopValue(const double &value);

    int    nDataPoints();
    void   setNDataPoints(const int &value);

    int    nAverages();
    void   setNAverages(const int &value);

    double delayTime();
    void   setDelayTime(const double &value);

signals:
    void startValueChanged();
    void stopValueChanged();
    void nDataPointsChanged();
    void nAveragesChanged();
    void delayTimeChanged();

private:
    double mStartValue;  // Either Voltage or Frequency
    double mStopValue;   // Either Voltage or Frequency
    int    mNDataPoints;
    int    mNAverages;
    double mDelayTime;   // Delay time in seconds
};

#endif // BWOEXPMODEL_H
