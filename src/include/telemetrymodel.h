#ifndef TELEMETRYMODEL_H
#define TELEMETRYMODEL_H

#include <QObject>
#include <QList>
#include <QTimer>

// Forward declarations
class Drone;
class MovementStrategy;

/**
 * @brief Data model for drone telemetry, supports simulation and observer pattern
 */
class TelemetryModel : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new TelemetryModel object
     * @param parent The parent QObject
     */
    explicit TelemetryModel(QObject* parent = nullptr);
    ~TelemetryModel();
    
    /**
     * @brief Get the current drone
     */
    Drone* getDrone() const
    {
        return _drone;
    }

    /**
     * @brief Set the current drone
     */
    void setDrone(Drone* drone);
    
    /**
     * @brief Set the current movement strategy
     */
    void setMovementStrategy(MovementStrategy* strategy);

    /**
     * @brief Get the current movement strategy
     */
    MovementStrategy* getCurrentStrategy() const
    {
        return _currentStrategy;
    }
    
    /**
     * @brief Start the simulation timer
     */
    void startSimulation();

    /**
     * @brief Stop the simulation timer
     */
    void stopSimulation();

    /**
     * @brief Check if simulation is running
     */
    bool isSimulationRunning() const
    {
        return _simulationTimer->isActive();
    }
    
    /**
     * @brief Toggle failure simulation mode
     */
    void toggleFailureSimulation();

    /**
     * @brief Check if failure simulation is active
     */
    bool isFailureSimulationActive() const
    {
        return _failureSimulationActive;
    }
    
signals:
    /**
     * @brief Emitted when telemetry data is updated
     */
    void telemetryUpdated();

    /**
     * @brief Emitted when simulation starts
     */
    void simulationStarted();

    /**
     * @brief Emitted when simulation stops
     */
    void simulationStopped();

    /**
     * @brief Emitted when failure simulation is toggled
     */

    void failureSimulationToggled(bool active);

    /**
     * @brief Emitted when movement strategy changes
     */
    void strategyChanged(const QString& strategyName);

private slots:
    /**
     * @brief Update telemetry data (called by timer)
     */
    void updateTelemetry();

    /**
     * @brief Handle drone telemetry updates
     */
    void onDroneTelemetryUpdated();

private:
    Drone* _drone;                       // Current drone
    MovementStrategy* _currentStrategy;  // Current movement strategy
    QTimer* _simulationTimer;            // Simulation timer
    bool _failureSimulationActive;       // Failure simulation flag
    
    /**
     * @brief Initialize the default movement strategy
     */
    void initializeDefaultStrategy();
};

#endif // TELEMETRYMODEL_H 
