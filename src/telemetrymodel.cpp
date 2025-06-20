#include "telemetrymodel.h"
#include "drone.h"
#include "movementstrategy.h"
#include "hoverstrategy.h"
#include "randomwalkstrategy.h"
#include "dronefactory.h"
#include "logger.h"
#include <QTimer>
#include <QDebug>

TelemetryModel::TelemetryModel(QObject* parent)
    : QObject(parent)
    , _drone(nullptr)
    , _currentStrategy(nullptr)
    , _simulationTimer(new QTimer(this))
    , _failureSimulationActive(false)
{
    try
    {
        LOG_DEBUG("TelemetryModel created");
        
        qDebug() << "TelemetryModel: Creating simulation timer...";
        
        // Set up simulation timer for 500ms updates
        _simulationTimer->setInterval(500);
        connect(_simulationTimer, &QTimer::timeout, this, &TelemetryModel::updateTelemetry);
        
        qDebug() << "TelemetryModel: Creating default drone...";
        
        // Create default drone using factory
        _drone = DroneFactory::createDrone("DRONE-001", this);
        connect(_drone, &Drone::telemetryUpdated, this, &TelemetryModel::onDroneTelemetryUpdated);
        
        qDebug() << "TelemetryModel: Initializing default movement strategy...";
        
        // Initialize default movement strategy
        initializeDefaultStrategy();
        
        LOG_INFO("TelemetryModel initialized with default drone and hover strategy");
        
    }
    catch (const std::exception& e)
    {
        qCritical() << "TelemetryModel initialization failed:" << e.what();
        throw;
    }
    catch (...)
    {
        qCritical() << "Unknown error in TelemetryModel initialization";
        throw;
    }
}

TelemetryModel::~TelemetryModel()
{
    stopSimulation();
    LOG_DEBUG("TelemetryModel destroyed");
}

void TelemetryModel::setDrone(Drone* drone)
{
    if (_drone != drone)
    {
        if (_drone)
        {
            disconnect(_drone, &Drone::telemetryUpdated, this, &TelemetryModel::onDroneTelemetryUpdated);
        }
        
        _drone = drone;
        
        if (_drone)
        {
            connect(_drone, &Drone::telemetryUpdated, this, &TelemetryModel::onDroneTelemetryUpdated);
            LOG_INFO(QString("Drone changed to: %1").arg(_drone->getId()));
        }
    }
}

void TelemetryModel::setMovementStrategy(MovementStrategy* strategy)
{
    if (_currentStrategy != strategy)
    {
        _currentStrategy = strategy;
        
        if (_currentStrategy)
        {
            connect(_currentStrategy, &MovementStrategy::strategyChanged,
                    this, &TelemetryModel::strategyChanged);
            
            LOG_INFO(QString("Movement strategy changed to: %1").arg(_currentStrategy->getStrategyName()));
            emit strategyChanged(_currentStrategy->getStrategyName());
        }
    }
}

void TelemetryModel::startSimulation()
{
    if (!_simulationTimer->isActive())
    {
        _simulationTimer->start();
        LOG_INFO("Simulation started");
        emit simulationStarted();
    }
}

void TelemetryModel::stopSimulation()
{
    if (_simulationTimer->isActive())
    {
        _simulationTimer->stop();
        LOG_INFO("Simulation stopped");
        emit simulationStopped();
    }
}

void TelemetryModel::toggleFailureSimulation()
{
    _failureSimulationActive = !_failureSimulationActive;
    
    if (_drone)
    {
        if (_failureSimulationActive)
        {
            _drone->simulateFailure();
        }
        else
        {
            _drone->resetFailure();
        }
    }
    
    LOG_INFO(QString("Failure simulation %1").arg(_failureSimulationActive ? "activated" : "deactivated"));
    emit failureSimulationToggled(_failureSimulationActive);
}

void TelemetryModel::updateTelemetry()
{
    if (!_drone || !_currentStrategy)
    {
        return;
    }
    
    // Update drone position using current strategy
    _currentStrategy->updatePosition(_drone);
    
    // Drain battery
    _drone->drainBattery();
    
    // Emit telemetry updated signal
    emit telemetryUpdated();
}

void TelemetryModel::onDroneTelemetryUpdated()
{
    emit telemetryUpdated();
}

void TelemetryModel::initializeDefaultStrategy()
{
    // Set default strategy to hover
    setMovementStrategy(new HoverStrategy(this));
}
