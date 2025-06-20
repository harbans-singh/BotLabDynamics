#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "telemetrymodel.h"
#include "dronesimulator.h"
#include "hoverstrategy.h"
#include "randomwalkstrategy.h"
#include "drone.h"
#include "logger.h"
#include <QMessageBox>
#include <QApplication>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _telemetryModel(nullptr)
    , _simulator(nullptr)
{
    try
    {
        qDebug() << "Setting up UI...";
        ui->setupUi(this);
        
        qDebug() << "Creating telemetry model...";
        _telemetryModel = new TelemetryModel(this);
        
        qDebug() << "Creating drone simulator...";
        _simulator = new DroneSimulator(this);
        
        qDebug() << "Setting up simulator with telemetry model...";
        _simulator->setTelemetryModel(_telemetryModel);
        
        qDebug() << "Setting up observer pattern connections...";
        setupConnections();
        
        qDebug() << "Initializing display...";

        updateTelemetryDisplay();
        setStatusMessage("Ready");
        
        qDebug() << "MainWindow initialized successfully";
        
    }
    catch (const std::exception& e)
    {
        qCritical() << "MainWindow initialization failed:" << e.what();
        throw;
    }
    catch (...)
    {
        qCritical() << "Unknown error in MainWindow initialization";
        throw;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    // Observer pattern: Connect model signals to UI update slots
    connect(_telemetryModel, &TelemetryModel::telemetryUpdated,
            this, &MainWindow::onTelemetryUpdated);
    connect(_telemetryModel, &TelemetryModel::simulationStarted,
            this, &MainWindow::onSimulationStarted);
    connect(_telemetryModel, &TelemetryModel::simulationStopped,
            this, &MainWindow::onSimulationStopped);
    connect(_telemetryModel, &TelemetryModel::failureSimulationToggled,
            this, &MainWindow::onFailureSimulationToggled);
    connect(_telemetryModel, &TelemetryModel::strategyChanged,
            this, &MainWindow::onStrategyChanged);
    
    // Connect UI controls
    connect(ui->startStopButton, &QPushButton::clicked, 
            this, &MainWindow::onStartStopButtonClicked);
    connect(ui->failureButton, &QPushButton::clicked, 
            this, &MainWindow::onFailureButtonClicked);
    connect(ui->strategyComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &MainWindow::onStrategyComboBoxChanged);
    
    // Connect drone signals
    if (_telemetryModel->getDrone())
    {
        connect(_telemetryModel->getDrone(), &Drone::batteryLow,
                this, &MainWindow::onBatteryLow);
        connect(_telemetryModel->getDrone(), &Drone::gpsFixLost,
                this, &MainWindow::onGpsFixLost);
    }
    
    // Connect menu actions
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::onActionExit);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::onActionAbout);
}

void MainWindow::onTelemetryUpdated()
{
    updateTelemetryDisplay();
}

void MainWindow::onSimulationStarted()
{
    ui->startStopButton->setText("Stop Simulation");
    ui->startStopButton->setStyleSheet("background-color: #DC3545; color: white; font-weight: bold;");
    setStatusMessage("Simulation Running", "#28A745");
    LOG_INFO("Simulation started from UI");
}

void MainWindow::onSimulationStopped()
{
    ui->startStopButton->setText("Start Simulation");
    ui->startStopButton->setStyleSheet("");
    setStatusMessage("Simulation Stopped", "#6C757D");
    LOG_INFO("Simulation stopped from UI");
}

void MainWindow::onFailureSimulationToggled(bool active)
{
    if (active)
    {
        ui->failureButton->setText("Reset Failure");
        ui->failureButton->setStyleSheet("background-color: #FFC107; color: black; font-weight: bold;");
        setStatusMessage("Failure Mode Active", "#DC3545");
    }
    else
    {
        ui->failureButton->setText("Simulate Failure");
        ui->failureButton->setStyleSheet("background-color: #DC3545; color: white; font-weight: bold;");
        setStatusMessage("Normal Operation", "#28A745");
    }
}

void MainWindow::onStrategyChanged(const QString& strategyName)
{
    setStatusMessage(QString("Strategy: %1").arg(strategyName), "#17A2B8");
}

void MainWindow::onStartStopButtonClicked()
{
    if (_simulator->isSimulationRunning())
    {
        _simulator->stopSimulation();
    }
    else
    {
        _simulator->startSimulation();
    }
}

void MainWindow::onFailureButtonClicked()
{
    _telemetryModel->toggleFailureSimulation();
}

void MainWindow::onStrategyComboBoxChanged(int index)
{
    MovementStrategy* newStrategy = nullptr;
    
    switch (index)
    {
    case 0: // Hover
        newStrategy = new HoverStrategy(this);
        break;
    case 1: // Random Walk
        newStrategy = new RandomWalkStrategy(this);
        break;
    default:
        LOG_WARNING("Unknown strategy index selected");
        return;
    }
    
    if (newStrategy)
    {
        _telemetryModel->setMovementStrategy(newStrategy);
    }
}

void MainWindow::onBatteryLow(int battery)
{
    QString message = QString("Warning: Drone battery is low (%1%)").arg(battery);
    showWarningMessage(message);
    setStatusMessage(QString("Low Battery: %1%").arg(battery), "#FFC107");
}

void MainWindow::onGpsFixLost()
{
    QString message = "Warning: GPS fix has been lost!";
    showWarningMessage(message);
    setStatusMessage("GPS Fix Lost", "#DC3545");
}

void MainWindow::onActionExit()
{
    QApplication::quit();
}

void MainWindow::onActionAbout()
{
    QMessageBox::about(this, "About Drone Telemetry Simulator",
                      "Drone Telemetry Simulator v1.0\n\n"
                      "A Qt-based application that simulates real-time drone telemetry data.\n\n"
                      "Features:\n"
                      "• Real-time telemetry display\n"
                      "• Multiple movement strategies\n"
                      "• Failure simulation\n"
                      "• Multithreaded architecture\n"
                      "• Design patterns implementation\n\n"
                      "Assignment Built for BoltLab Dynamics");
}

void MainWindow::updateTelemetryDisplay()
{
    if (!_telemetryModel->getDrone())
    {
        return;
    }
    
    Drone* drone = _telemetryModel->getDrone();
    
    // Update telemetry labels
    ui->droneIdLabel->setText(drone->getId());
    ui->latitudeLabel->setText(QString::number(drone->getLatitude(), 'f', 6));
    ui->longitudeLabel->setText(QString::number(drone->getLongitude(), 'f', 6));
    ui->altitudeLabel->setText(QString("%1 m").arg(drone->getAltitude(), 0, 'f', 1));
    ui->headingLabel->setText(QString("%1°").arg(drone->getHeading(), 0, 'f', 1));
    ui->speedLabel->setText(QString("%1 m/s").arg(drone->getSpeed(), 0, 'f', 1));
    
    // Update battery and GPS fix
    updateBatteryDisplay();
    updateGpsFixDisplay();
}

void MainWindow::updateBatteryDisplay()
{
    if (!_telemetryModel->getDrone())
    {
        return;
    }
    
    int battery = _telemetryModel->getDrone()->getBattery();
    ui->batteryProgressBar->setValue(battery);
    
    // Change color based on battery level
    if (battery <= 20)
    {
        ui->batteryProgressBar->setStyleSheet("QProgressBar::chunk { background-color: #DC3545; }");
    }
    else if (battery <= 50)
    {
        ui->batteryProgressBar->setStyleSheet("QProgressBar::chunk { background-color: #FFC107; }");
    }
    else
    {
        ui->batteryProgressBar->setStyleSheet("QProgressBar::chunk { background-color: #28A745; }");
    }
}

void MainWindow::updateGpsFixDisplay()
{
    if (!_telemetryModel->getDrone())
    {
        return;
    }
    
    QString gpsStatus = _telemetryModel->getDrone()->getGpsFixStatusString();
    ui->gpsFixLabel->setText(gpsStatus);
    
    // Change color based on GPS status
    if (gpsStatus == "No Fix")
    {
        ui->gpsFixLabel->setStyleSheet("font-weight: bold; color: #DC3545;");
    }
    else if (gpsStatus == "2D Fix")
    {
        ui->gpsFixLabel->setStyleSheet("font-weight: bold; color: #FFC107;");
    }
    else
    {
        ui->gpsFixLabel->setStyleSheet("font-weight: bold; color: #28A745;");
    }
}

void MainWindow::setStatusMessage(const QString& message, const QString& color)
{
    ui->statusLabel->setText(message);
    ui->statusLabel->setStyleSheet(QString("font-weight: bold; color: %1;").arg(color));
}

void MainWindow::showWarningMessage(const QString& message)
{
    QMessageBox::warning(this, "Warning", message);
} 
