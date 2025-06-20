#ifndef DRONESIMULATOR_H
#define DRONESIMULATOR_H

#include <QObject>
#include <QThread>
#include <QMutex>

class TelemetryModel;

/**
 * @brief DroneSimulator class manages the simulation worker thread for drone telemetry
 */
class DroneSimulator : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new DroneSimulator object
     * @param parent The parent QObject
     */
    explicit DroneSimulator(QObject* parent = nullptr);
    ~DroneSimulator();
    
    /**
     * @brief Start the simulation in a worker thread
     */
    void startSimulation();

    /**
     * @brief Stop the simulation
     */
    void stopSimulation();

    /**
     * @brief Check if simulation is running
     */
    bool isSimulationRunning() const;
    
    /**
     * @brief Set the telemetry model to simulate
     */
    void setTelemetryModel(TelemetryModel* model);

    /**
     * @brief Get the current telemetry model
     */
    TelemetryModel* getTelemetryModel() const { return _telemetryModel; }
    
signals:
    /**
     * @brief Emitted when simulation starts
     */
    void simulationStarted();

    /**
     * @brief Emitted when simulation stops
     */
    void simulationStopped();

    /**
     * @brief Emitted when an error occurs
     */
    void error(const QString& errorMessage);

private slots:
    /**
     * @brief Run the simulation (worker thread entry point)
     */
    void runSimulation();

    /**
     * @brief Handle telemetry model updates
     */
    void onModelTelemetryUpdated();

private:
    TelemetryModel* _telemetryModel; // Telemetry model pointer
    QThread* _simulationThread;      // Worker thread
    mutable QMutex _mutex;           // Mutex for thread safety
    bool _running;                   // Simulation running flag
    
    /**
     * @brief Move this object to the worker thread
     */
    void moveToThread();
};

#endif // DRONESIMULATOR_H 
