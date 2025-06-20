#include "randomwalkstrategy.h"
#include "drone.h"
#include "logger.h"
#include <QRandomGenerator>
#include <QtMath>

RandomWalkStrategy::RandomWalkStrategy(QObject* parent)
    : MovementStrategy(parent)
{
    LOG_DEBUG("RandomWalkStrategy created");
}

void RandomWalkStrategy::updatePosition(Drone* drone)
{
    if (!drone)
    {
        return;
    }

    // Random walk behavior: more significant movement
    double latChange = (QRandomGenerator::global()->bounded(200) - 100) * 0.00001; // Larger changes
    double lonChange = (QRandomGenerator::global()->bounded(200) - 100) * 0.00001;
    double altChange = (QRandomGenerator::global()->bounded(50) - 25) * 0.5; // Moderate altitude changes
    
    drone->setLatitude(drone->getLatitude() + latChange);
    drone->setLongitude(drone->getLongitude() + lonChange);
    drone->setAltitude(drone->getAltitude() + altChange);
    
    // More significant heading changes
    double headingChange = (QRandomGenerator::global()->bounded(60) - 30);
    drone->setHeading(drone->getHeading() + headingChange);
    
    // Normalize heading to 0-360 range
    while (drone->getHeading() >= 360.0) drone->setHeading(drone->getHeading() - 360.0);
    while (drone->getHeading() < 0.0) drone->setHeading(drone->getHeading() + 360.0);
    
    // Variable speed for random walk
    double speed = QRandomGenerator::global()->bounded(15) + 5; // 5-20 m/s
    drone->setSpeed(speed);
}

QString RandomWalkStrategy::getStrategyName() const
{
    return "Random Walk";
}
