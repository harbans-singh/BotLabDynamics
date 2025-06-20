#include "drone.h"
#include "logger.h"
#include <QRandomGenerator>

Drone::Drone(const QString& id, QObject* parent)
    : QObject(parent)
    , _id(id)
    , _latitude(28.6139) // Default to New Delhi coordinates
    , _longitude(77.2090)
    , _altitude(100.0)
    , _heading(0.0)
    , _speed(0.0)
    , _battery(100)
    , _gpsFixStatus(GPSFixStatus::FIX_3D)
    , _failureMode(false)
{
    LOG_INFO(QString("Drone %1 created with initial position: lat=%2, lon=%3, alt=%4")
             .arg(_id)
             .arg(_latitude, 0, 'f', 6)
             .arg(_longitude, 0, 'f', 6)
             .arg(_altitude, 0, 'f', 1));
}

void Drone::setLatitude(double latitude)
{
    if (_latitude != latitude)
    {
        _latitude = latitude;
        emit telemetryUpdated();
    }
}

void Drone::setLongitude(double longitude)
{
    if (_longitude != longitude)
    {
        _longitude = longitude;
        emit telemetryUpdated();
    }
}

void Drone::setAltitude(double altitude)
{
    if (_altitude != altitude)
    {
        _altitude = altitude;
        emit telemetryUpdated();
    }
}

void Drone::setHeading(double heading)
{
    if (_heading != heading)
    {
        _heading = heading;
        emit telemetryUpdated();
    }
}

void Drone::setSpeed(double speed)
{
    if (_speed != speed)
    {
        _speed = speed;
        emit telemetryUpdated();
    }
}

void Drone::setBattery(int battery)
{
    if (_battery != battery)
    {
        int oldBattery = _battery;
        _battery = qBound(0, battery, 100);
        
        if (_battery <= 20 && oldBattery > 20)
        {
            emit batteryLow(_battery);
            LOG_WARNING(QString("Drone %1 battery low: %2%").arg(_id).arg(_battery));
        }
        
        emit telemetryUpdated();
    }
}

void Drone::setGpsFixStatus(GPSFixStatus status)
{
    if (_gpsFixStatus != status)
    {
        GPSFixStatus oldStatus = _gpsFixStatus;
        _gpsFixStatus = status;
        
        if (oldStatus != GPSFixStatus::NO_FIX && status == GPSFixStatus::NO_FIX)
        {
            emit gpsFixLost();
            LOG_WARNING(QString("Drone %1 GPS fix lost").arg(_id));
        }
        
        emit telemetryUpdated();
    }
}

void Drone::drainBattery()
{
    int drainAmount = _failureMode ? 5 : 1; // Faster drain in failure mode
    setBattery(_battery - drainAmount);
}

void Drone::simulateFailure()
{
    if (!_failureMode)
    {
        _failureMode = true;
        setGpsFixStatus(GPSFixStatus::NO_FIX);
        LOG_WARNING(QString("Drone %1 failure mode activated").arg(_id));
        emit failureSimulated();
    }
}

void Drone::resetFailure()
{
    if (_failureMode)
    {
        _failureMode = false;
        setGpsFixStatus(GPSFixStatus::FIX_3D);
        LOG_INFO(QString("Drone %1 failure mode reset").arg(_id));
        emit failureReset();
    }
}

QString Drone::getGpsFixStatusString() const
{
    switch (_gpsFixStatus)
    {
    case GPSFixStatus::NO_FIX:
        return "No Fix";
    case GPSFixStatus::FIX_2D:
        return "2D Fix";
    case GPSFixStatus::FIX_3D:
        return "3D Fix";
    default:
        return "Unknown";
    }
} 
