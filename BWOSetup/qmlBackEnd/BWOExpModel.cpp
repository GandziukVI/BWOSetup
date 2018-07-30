#include "BWOExpModel.h"

BWOExpModel::BWOExpModel(QObject *parent)
    : QObject (parent)
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
    emit startValueChanged();
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
    emit stopValueChanged();
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
    emit nDataPointsChanged();
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
    emit nAveragesChanged();
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
    emit delayTimeChanged();
}
