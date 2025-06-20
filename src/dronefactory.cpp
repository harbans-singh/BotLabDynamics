#include "dronefactory.h"
#include "drone.h"
#include "logger.h"

DroneFactory::DroneFactory(QObject* parent)
    : QObject(parent)
{
    LOG_DEBUG("DroneFactory created");
}

Drone* DroneFactory::createDrone(const QString& id, QObject* parent)
{
    LOG_INFO(QString("Creating drone with ID: %1").arg(id));
    return new Drone(id, parent);
}

Drone* DroneFactory::createDrone(const QString& id, 
                                 double latitude, 
                                 double longitude, 
                                 double altitude,
                                 QObject* parent)
{
    LOG_INFO(QString("Creating drone with ID: %1 at position lat=%2, lon=%3, alt=%4")
             .arg(id)
             .arg(latitude, 0, 'f', 6)
             .arg(longitude, 0, 'f', 6)
             .arg(altitude, 0, 'f', 1));
    
    Drone* drone = new Drone(id, parent);
    drone->setLatitude(latitude);
    drone->setLongitude(longitude);
    drone->setAltitude(altitude);
    
    return drone;
} 