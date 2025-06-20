#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QComboBox>
#include <QAction>

class TelemetryModel;
class DroneSimulator;

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief Main application window for the Drone Telemetry Simulator
 * Handles the UI, connects to the telemetry model, and responds to user actions
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new MainWindow object
     * @param parent The parent widget
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor
     */
    ~MainWindow();

private slots:
    /**
     * @brief Update the UI when telemetry data changes
     */
    void onTelemetryUpdated();

    /**
     * @brief Handle simulation started event
     */
    void onSimulationStarted();

    /**
     * @brief Handle simulation stopped event
     */
    void onSimulationStopped();

    /**
     * @brief Handle failure simulation toggled event
     */
    void onFailureSimulationToggled(bool active);

    /**
     * @brief Handle movement strategy change event
     */
    void onStrategyChanged(const QString& strategyName);
    
    /**
     * @brief Handle start/stop button click
     */
    void onStartStopButtonClicked();

    /**
     * @brief Handle failure simulation button click
     */
    void onFailureButtonClicked();

    /**
     * @brief Handle movement strategy combo box change
     */
    void onStrategyComboBoxChanged(int index);

    /**
     * @brief Handle low battery event
     */
    void onBatteryLow(int battery);

    /**
     * @brief Handle GPS fix lost event
     */
    void onGpsFixLost();
    
    /**
     * @brief Handle exit menu action
     */
    void onActionExit();

    /**
     * @brief Handle about menu action
     */
    void onActionAbout();

private:
    Ui::MainWindow* ui;                // UI object generated by Qt Designer
    TelemetryModel* _telemetryModel;   // Pointer to the telemetry model
    DroneSimulator* _simulator;        // Pointer to the drone simulator
    
    // Observer pattern implementation
    /**
     * @brief Set up signal-slot connections for the UI and model
     */
    void setupConnections();

    /**
     * @brief Update all telemetry display fields in the UI
     */
    void updateTelemetryDisplay();

    /**
     * @brief Update the status display in the UI
     */
    void updateStatusDisplay();

    /**
     * @brief Update the battery display in the UI
     */
    void updateBatteryDisplay();

    /**
     * @brief Update the GPS fix display in the UI
     */
    void updateGpsFixDisplay();
    
    /**
     * @brief Set the status message in the UI
     */
    void setStatusMessage(const QString& message, const QString& color = "#6C757D");

    /**
     * @brief Show a warning message box
     */
    void showWarningMessage(const QString& message);
};

#endif // MAINWINDOW_H 
