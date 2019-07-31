#include "BWOExpModel.h"

BWOExpModel::BWOExpModel(QObject *parent)
    : QObject (parent),
      mStartValue(2.616605617),
      mStopValue(5),
      mExactValue(2.62),
      mNDataPoints(245),
      mNAverages(50),
      mDelayTime(2),
      mDeltaTime(0),
      mProgress(0.0),
      mAlphaCoefficient(0.16389),
      mBetaCoefficient(0.00114)
{
    mDeviceName = QString::fromLatin1("Dev1");

    mPinAO = QString::fromLatin1("ao0");
    mPinAI = QString::fromLatin1("ai3");

    mCurrentLineSeries = QString::fromLatin1("BWO Experiment");

    mFileName = QString::fromLatin1("BWO Data #00.dat");
    mCalibFileName = QString::fromLatin1("");
    mFilePath = QString::fromLatin1("");
}

double BWOExpModel::startValue()
{
    return mStartValue;
}

void BWOExpModel::setStartValue(const double &value)
{
    if (value == mStartValue)
        return;

    mStartValue = value;
    emit startValueChanged(mStartValue);
}

double BWOExpModel::stopValue()
{
    return mStopValue;
}

void BWOExpModel::setStopValue(const double &value)
{
    if (value == mStopValue)
        return;

    mStopValue = value;
    emit stopValueChanged(mStopValue);
}

double BWOExpModel::exactVoltageValue()
{
    return mExactValue;
}

void BWOExpModel::setExactVoltageValue(const double &value)
{
    if (value == mExactValue)
        return;

    mExactValue = value;
    emit exactVoltageValueChanged(mExactValue);
}

int BWOExpModel::nDataPoints()
{
    return mNDataPoints;
}

void BWOExpModel::setNDataPoints(const int &value)
{
    if (value == mNDataPoints)
        return;

    mNDataPoints = value;
    emit nDataPointsChanged(mNDataPoints);
}

int BWOExpModel::nAverages()
{
    return mNAverages;
}

void BWOExpModel::setNAverages(const int &value)
{
    if (value == mNAverages)
        return;

    mNAverages = value;
    emit nAveragesChanged(mNAverages);
}

double BWOExpModel::delayTime()
{
    return mDelayTime;
}

void BWOExpModel::setDelayTime(const double &value)
{
    if (value == mDelayTime)
        return;

    mDelayTime = value;
    emit delayTimeChanged(mDelayTime);
}

double BWOExpModel::deltaTime()
{
    return mDeltaTime;
}

void BWOExpModel::setDeltaTime(const double &value)
{
    if (value == mDeltaTime)
        return;

    mDeltaTime = value;
    emit deltaTimeChanged(mDeltaTime);
}

QString BWOExpModel::niDeviceName()
{
    return mDeviceName;
}

void BWOExpModel::setNIDeviceName(const QString &value)
{
    if (value == mDeviceName)
        return;

    mDeviceName = value;
    emit niDeviceNameChanged(mDeviceName);
}

QString BWOExpModel::pinAO()
{
    return mPinAO;
}

void BWOExpModel::setPinAO(const QString &value)
{
    if (value == mPinAO)
        return;

    mPinAO = value;
    emit pinAOChanged(mPinAO);
}

QString BWOExpModel::pinAI()
{
    return mPinAI;
}

void BWOExpModel::setPinAI(const QString &value)
{
    if (value == mPinAI)
        return;

    mPinAI = value;
    emit  pinAIChanged(mPinAI);
}

QString BWOExpModel::fileName()
{
    return mFileName;
}

void BWOExpModel::setFileName(const QString &value)
{
    if (value == mFileName)
        return;

    mFileName = value;
    emit  fileNameChanged(mFileName);
}

QString BWOExpModel::filePath()
{
    return mFilePath;
}

void BWOExpModel::setFilePath(const QString &value)
{
    if (value == mFilePath)
        return;

    mFilePath = value;
    emit filePathChanged(mFilePath);
}

QString BWOExpModel::calibFile()
{
    return mCalibFileName;
}

void BWOExpModel::setCalibFile(const QString &value)
{
    if (value == mCalibFileName)
        return;

    mCalibFileName = value;
    emit calibFileChanged(mCalibFileName);
}

double BWOExpModel::alphaCoefficient()
{
    return mAlphaCoefficient;
}

void BWOExpModel::setAlphaCoefficient(const double &value)
{
    if (value == mAlphaCoefficient)
        return;

    mAlphaCoefficient = value;
    emit alphaCoefficientChanged(mAlphaCoefficient);
}

double BWOExpModel::betaCoefficient()
{
    return mBetaCoefficient;
}

void BWOExpModel::setBetaCoefficient(const double &value)
{
    if (value == mBetaCoefficient)
        return;

    mBetaCoefficient = value;
    emit betaCoefficientChanged(mBetaCoefficient);
}

double BWOExpModel::progress()
{
    return mProgress;
}

void BWOExpModel::setProgress(const double &value)
{
    if (value == mProgress)
        return;

    mProgress = value;
    emit progressChanged(mProgress);
}

void BWOExpModel::addLineSeries(const QString &chartNameString)
{
    emit addNewLineSeries(chartNameString);
}

void BWOExpModel::addDataPoint(const QPointF &dataPoint)
{
    emit addNewDataPoint(dataPoint);
}
