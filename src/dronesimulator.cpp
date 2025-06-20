#include "dronesimulator.h"
#include "telemetrymodel.h"
#include "logger.h"
#include <QTimer>

DroneSimulator::DroneSimulator(QObject* parent)
    : QObject(parent)
    , _telemetryModel(nullptr)
    , _simulationThread(new QThread(this))
    , _running(false)
{
    LOG_DEBUG("DroneSimulator created");
    
    // Move simulator to worker thread
    moveToThread();
    connect(_simulationThread, &QThread::started, this, &DroneSimulator::runSimulation);
    connect(_simulationThread, &QThread::finished, this, [this]() {
        LOG_DEBUG("Simulation thread finished");
    });
}

DroneSimulator::~DroneSimulator()
{
    stopSimulation();
    
    if (_simulationThread->isRunning())
    {
        _simulationThread->quit();
        _simulationThread->wait();
    }
    
    LOG_DEBUG("DroneSimulator destroyed");
}

void DroneSimulator::startSimulation()
{
    QMutexLocker locker(&_mutex);
    
    if (!_running)
    {
        _running = true;
        
        if (!_simulationThread->isRunning())
        {
            _simulationThread->start();
        }
        
        if (_telemetryModel)
        {
            _telemetryModel->startSimulation();
        }
        
        LOG_INFO("DroneSimulator simulation started");
        emit simulationStarted();
    }
}

void DroneSimulator::stopSimulation()
{
    QMutexLocker locker(&_mutex);
    
    if (_running)
    {
        _running = false;
        
        if (_telemetryModel)
        {
            _telemetryModel->stopSimulation();
        }
        
        LOG_INFO("DroneSimulator simulation stopped");
        emit simulationStopped();
    }
}

bool DroneSimulator::isSimulationRunning() const
{
    QMutexLocker locker(&_mutex);
    return _running && _simulationThread->isRunning();
}

void DroneSimulator::setTelemetryModel(TelemetryModel* model)
{
    if (_telemetryModel != model)
    {
        if (_telemetryModel)
        {
            disconnect(_telemetryModel, &TelemetryModel::telemetryUpdated,
                      this, &DroneSimulator::onModelTelemetryUpdated);
        }
        
        _telemetryModel = model;
        
        if (_telemetryModel)
        {
            connect(_telemetryModel, &TelemetryModel::telemetryUpdated,
                    this, &DroneSimulator::onModelTelemetryUpdated);
            LOG_INFO("TelemetryModel set in DroneSimulator");
        }
    }
}

void DroneSimulator::runSimulation()
{
    LOG_DEBUG("Simulation thread started");
    
    // This method runs in the worker thread
    // The actual simulation is handled by the TelemetryModel timer
    // This thread just manages the simulation lifecycle
}

void DroneSimulator::onModelTelemetryUpdated()
{
    // Handle telemetry updates from the model
    // This could be used for additional processing if needed
}

void DroneSimulator::moveToThread()
{
    QObject::moveToThread(_simulationThread);
} 
