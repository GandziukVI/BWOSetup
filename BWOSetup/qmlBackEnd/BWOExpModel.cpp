#include "BWOExpModel.h"

BWOExpModel::BWOExpModel(QObject *parent)
    : QObject (parent),
      mStartValue(0),
      mStopValue(3),
      mNDataPoints(7),
      mNAverages(3),
      mDelayTime(0.5)
{

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
