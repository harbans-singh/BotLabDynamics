#ifndef RANDOMWALKSTRATEGY_H
#define RANDOMWALKSTRATEGY_H

#include "movementstrategy.h"

/**
 * @brief Implements a random walk movement strategy for the drone
 * The drone moves in a more dynamic, random pattern when this strategy is used
 */
class RandomWalkStrategy : public MovementStrategy
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new RandomWalkStrategy object
     * @param parent The parent QObject
     */
    explicit RandomWalkStrategy(QObject* parent = nullptr);
    
    /**
     * @brief Update the drone's position using a random walk algorithm
     * @param drone Pointer to the drone to update
     */
    void updatePosition(Drone* drone) override;

    /**
     * @brief Get the name of this strategy
     * @return Name of the strategy as a QString
     */
    QString getStrategyName() const override;
};

#endif // RANDOMWALKSTRATEGY_H 
