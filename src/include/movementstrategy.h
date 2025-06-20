#ifndef MOVEMENTSTRATEGY_H
#define MOVEMENTSTRATEGY_H

#include <QObject>
#include <QString>

// Forward declarations
class Drone;

/**
 * @brief Abstract base class for drone movement strategies (Strategy Pattern)
 * Subclasses implement specific movement behaviors for the drone simulation
 */
class MovementStrategy : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new MovementStrategy object
     * @param parent The parent QObject
     */
    explicit MovementStrategy(QObject* parent = nullptr);

    /**
     * @brief Virtual destructor
     */
    virtual ~MovementStrategy() = default;
    
    /**
     * @brief Update the drone's position according to the strategy
     * @param drone Pointer to the drone to update
     */
    virtual void updatePosition(Drone* drone) = 0;

    /**
     * @brief Get the name of the strategy
     * @return Name of the strategy as a QString
     */
    virtual QString getStrategyName() const = 0;
    
signals:
    /**
     * @brief Emitted when the strategy changes
     * @param strategyName The new strategy name
     */
    void strategyChanged(const QString& strategyName);
};

#endif // MOVEMENTSTRATEGY_H 
