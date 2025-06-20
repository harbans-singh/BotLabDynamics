#ifndef HOVERSTRATEGY_H
#define HOVERSTRATEGY_H

#include "movementstrategy.h"

/**
 * @brief Implements a hover movement strategy for the drone
 * The drone performs minimal movement, simulating hovering in place
 */
class HoverStrategy : public MovementStrategy
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new HoverStrategy object
     * @param parent The parent QObject
     */
    explicit HoverStrategy(QObject* parent = nullptr);
    
    /**
     * @brief Update the drone's position to simulate hovering
     * @param drone Pointer to the drone to update
     */
    void updatePosition(Drone* drone) override;

    /**
     * @brief Get the name of this strategy
     * @return Name of the strategy as a QString
     */
    QString getStrategyName() const override;
};

#endif // HOVERSTRATEGY_H 
