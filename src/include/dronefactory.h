#ifndef DRONEFACTORY_H
#define DRONEFACTORY_H

#include <QObject>
#include <QString>

class Drone;

class DroneFactory : public QObject
{
    Q_OBJECT

public:
    explicit DroneFactory(QObject* parent = nullptr);
    
    /**
     * @brief Factory method to create drone instances
     */
    static Drone* createDrone(const QString& id, QObject* parent = nullptr);

    /**
     * @brief Factory method to create drone with specific initial parameters
     */
    static Drone* createDrone(const QString& id, 
                             double latitude, 
                             double longitude, 
                             double altitude,
                             QObject* parent = nullptr);
};

#endif // DRONEFACTORY_H 
