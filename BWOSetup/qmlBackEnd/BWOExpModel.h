#ifndef BWOEXPMODEL_H
#define BWOEXPMODEL_H

#include <QObject>

class BWOExpModel : public QObject
{
    Q_OBJECT

    // To declare a property, use the Q_PROPERTY() macro in a class that inherits QObject.
    // A READ accessor function is for reading the property value
    // A WRITE accessor function is for setting the property value. It must return void and must take exactly one argument
    // A NOTIFY signal should specify one existing signal in that class that is emitted whenever the value of the property changes.
    // The parameter will take the new value of the property.
    // The NOTIFY signal should only be emitted when the property has really been changed
    Q_PROPERTY(double startValue READ startValue WRITE setStartValue NOTIFY startValueChanged)
    Q_PROPERTY(double stopValue READ stopValue WRITE setStopValue NOTIFY stopValueChanged)
    Q_PROPERTY(double exactVoltageValue READ exactVoltageValue WRITE setExactVoltageValue NOTIFY exactVoltageValueChanged)
    Q_PROPERTY(int nDataPoints READ nDataPoints WRITE setNDataPoints NOTIFY nDataPointsChanged)
    Q_PROPERTY(int nAverages READ nAverages WRITE setNAverages NOTIFY nAveragesChanged)
    Q_PROPERTY(double delayTime READ delayTime WRITE setDelayTime NOTIFY delayTimeChanged)
    Q_PROPERTY(double deltaTime READ deltaTime WRITE setDeltaTime NOTIFY deltaTimeChanged)
    Q_PROPERTY(QString niDeviceName READ niDeviceName WRITE setNIDeviceName NOTIFY niDeviceNameChanged)
    Q_PROPERTY(QString pinAO READ pinAO WRITE setPinAO NOTIFY pinAOChanged)
    Q_PROPERTY(QString pinAI READ pinAI WRITE setPinAI NOTIFY pinAIChanged)
    Q_PROPERTY(double progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(double alphaCoefficient READ alphaCoefficient WRITE setAlphaCoefficient NOTIFY alphaCoefficientChanged)
    Q_PROPERTY(double betaCoefficient READ betaCoefficient WRITE setBetaCoefficient NOTIFY betaCoefficientChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(QString calibFile READ calibFile WRITE setCalibFile NOTIFY calibFileChanged)

public:
    explicit BWOExpModel(QObject *parent = nullptr);

    double  startValue();
    void    setStartValue(const double &value);

    double  stopValue();
    void    setStopValue(const double &value);

    double  exactVoltageValue();
    void    setExactVoltageValue(const double &value);

    int     nDataPoints();
    void    setNDataPoints(const int &value);

    int     nAverages();
    void    setNAverages(const int &value);

    double  delayTime();
    void    setDelayTime(const double &value);

    double  deltaTime();
    void    setDeltaTime(const double &value);

    QString niDeviceName();
    void    setNIDeviceName(const QString &value);

    QString pinAO();
    void    setPinAO(const QString &value);

    QString pinAI();
    void    setPinAI(const QString &value);

    double  alphaCoefficient();
    void    setAlphaCoefficient(const double &value);

    double  betaCoefficient();
    void    setBetaCoefficient(const double &value);

    QString fileName();
    void    setFileName(const QString &value);

    QString filePath();
    void    setFilePath(const QString &value);

    QString calibFile();
    void    setCalibFile(const QString &value);

    double  progress();
    void    setProgress(const double &value);

    // Public Methods
    void addLineSeries(const QString &chartNameString);
    void addDataPoint(const QPointF &dataPoint);

signals:
    void startValueChanged(const double&);
    void stopValueChanged(const double&);
    void exactVoltageValueChanged(const double&);
    void nDataPointsChanged(const int&);
    void nAveragesChanged(const int&);
    void delayTimeChanged(const double&);
    void deltaTimeChanged(const double&);
    void niDeviceNameChanged(const QString&);
    void pinAOChanged(const QString&);
    void pinAIChanged(const QString&);
    void alphaCoefficientChanged(const double&);
    void betaCoefficientChanged(const double&);
    void progressChanged(const double&);
    void fileNameChanged(const QString&);
    void filePathChanged(const QString&);
    void calibFileChanged(const QString&);

    void addNewLineSeries(const QString &chartNameString);
    void addNewDataPoint(const QPointF &dataPoint);

    void activateStartButton();

private:
    double  mStartValue;  // Either Voltage or Frequency
    double  mStopValue;   // Either Voltage or Frequency
    double  mExactValue;
    int     mNDataPoints;
    int     mNAverages;
    double  mDelayTime;   // Delay time in seconds
    double  mDeltaTime;   // Delta time in seconds
    QString mDeviceName;
    QString mPinAO;
    QString mPinAI;
    double  mProgress;
    double  mAlphaCoefficient;
    double  mBetaCoefficient;
    QString mFileName;
    QString mFilePath;
    QString mCalibFileName;

    QString mCurrentLineSeries;
};

#endif // BWOEXPMODEL_H
