#ifndef DRONE_H
#define DRONE_H

#include <QObject>
#include <QString>

/**
 * @brief Enum for GPS fix status
 */
enum class GPSFixStatus
{
    NO_FIX,   // No GPS fix
    FIX_2D,   // 2D GPS fix
    FIX_3D    // 3D GPS fix
};

/**
 * @brief Drone Class Represents a drone with telemetry data and failure simulations
 */
class Drone : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Drone object
     * @param id: The drone's unique identifier
     * @param parent: The parent QObject
     */
    explicit Drone(const QString& id, QObject* parent = nullptr);
    
    /**
     * @brief Get the drone's ID
     */
    QString getId() const
    {
        return _id;
    }

    /**
     * @brief Get the latitude
     */
    double getLatitude() const
    {
        return _latitude;
    }

    /**
     * @brief Get the longitude
     */
    double getLongitude() const
    {
        return _longitude;
    }

    /**
     * @brief Get the altitude
     */
    double getAltitude() const
    {
        return _altitude;
    }

    /**
     * @brief Get the heading
     */
    double getHeading() const
    {
        return _heading;
    }

    /**
     * @brief Get the speed
     */
    double getSpeed() const
    {
        return _speed;
    }

    /**
     * @brief Get the battery percentage
     */
    int getBattery() const
    {
        return _battery;
    }

    /**
     * @brief Get the GPS fix status
     */
    GPSFixStatus getGpsFixStatus() const
    {
        return _gpsFixStatus;
    }
    
    /**
     * @brief Set the latitude
     */
    void setLatitude(double latitude);

    /**
     * @brief Set the longitude
     */
    void setLongitude(double longitude);

    /**
     * @brief Set the altitude
     */
    void setAltitude(double altitude);

    /**
     * @brief Set the heading
     */
    void setHeading(double heading);

    /**
     * @brief Set the speed
     */
    void setSpeed(double speed);

    /**
     * @brief Set the battery percentage
     */
    void setBattery(int battery);

    /**
     * @brief Set the GPS fix status
     */
    void setGpsFixStatus(GPSFixStatus status);
    
    /**
     * @brief Simulate battery drain
     */
    void drainBattery();

    /**
     * @brief Simulate failure mode (GPS loss, rapid battery drain)
     */
    void simulateFailure();

    /**
     * @brief Reset failure mode
     */
    void resetFailure();

    /**
     * @brief Get the GPS fix status as a string
     */
    QString getGpsFixStatusString() const;
    
signals:
    /**
     * @brief Emitted when telemetry data is updated
     */
    void telemetryUpdated();

    /**
     * @brief Emitted when battery is low
     */
    void batteryLow(int battery);

    /**
     * @brief Emitted when GPS fix is lost
     */
    void gpsFixLost();

    /**
     * @brief Emitted when failure mode is simulated
     */
    void failureSimulated();

    /**
     * @brief Emitted when failure mode is reset
     */
    void failureReset();

private:
    QString _id;              // Drone ID
    double _latitude;         // Latitude
    double _longitude;        // Longitude
    double _altitude;         // Altitude
    double _heading;          // Heading (degrees)
    double _speed;            // Speed (m/s)
    int _battery;             // Battery percentage
    GPSFixStatus _gpsFixStatus; // GPS fix status
    bool _failureMode;        // Failure mode flag
};

#endif // DRONE_H 
