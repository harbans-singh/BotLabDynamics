#include "hoverstrategy.h"
#include "drone.h"
#include "logger.h"
#include <QRandomGenerator>

HoverStrategy::HoverStrategy(QObject* parent)
    : MovementStrategy(parent)
{
    LOG_DEBUG("HoverStrategy created");
}

void HoverStrategy::updatePosition(Drone* drone)
{
    if (!drone) return;
    
    // Hovering behavior: minimal random movement
    double latChange = (QRandomGenerator::global()->bounded(100) - 50) * 0.000001; // Very small changes
    double lonChange = (QRandomGenerator::global()->bounded(100) - 50) * 0.000001;
    double altChange = (QRandomGenerator::global()->bounded(20) - 10) * 0.1; // Small altitude changes
    
    drone->setLatitude(drone->getLatitude() + latChange);
    drone->setLongitude(drone->getLongitude() + lonChange);
    drone->setAltitude(drone->getAltitude() + altChange);
    
    // Minimal heading drift
    double headingDrift = (QRandomGenerator::global()->bounded(20) - 10) * 0.1;
    drone->setHeading(drone->getHeading() + headingDrift);
    
    // Keep speed very low for hovering
    drone->setSpeed(QRandomGenerator::global()->bounded(5) * 0.1);
}

QString HoverStrategy::getStrategyName() const
{
    return "Hover";
} 