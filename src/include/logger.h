#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMutex>
#include <QDateTime>

/**
 * @brief Singleton Logger class for centralized, thread-safe logging
 * Provides logging functionality with different log levels
 * Logs are written to a file and the console
 */
class Logger : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Log levels for Logger
     */
    enum LogLevel {
        DEBUG,   // Debug messages
        INFO,    // Informational messages
        WARNING, // Warning messages
        ERROR    // Error messages
    };

    /**
     * @brief Get the singleton instance of Logger
     * @return Reference to the Logger instance
     */
    static Logger& getInstance();
    
    /**
     * @brief Log a message with a specific log level
     * @param level The log level
     * @param message The message to log
     */
    void log(LogLevel level, const QString& message);
    
    /**
     * @brief Log a debug message
     * @param message The message to log
     */
    void debug(const QString& message);
    
    /**
     * @brief Log an informational message
     * @param message The message to log
     */
    void info(const QString& message);
    
    /**
     * @brief Log a warning message
     * @param message The message to log
     */
    void warning(const QString& message);
    
    /**
     * @brief Log an error message
     * @param message The message to log
     */
    void error(const QString& message);

private:
    /**
     * @brief Private constructor for singleton pattern
     */
    Logger(QObject* parent = nullptr);
    
    /**
     * @brief Destructor
     */
    ~Logger();
    
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    /**
     * @brief Convert log level enum to string
     * @param level The log level
     * @return String representation of the log level
     */
    QString levelToString(LogLevel level);
    
    QFile _logFile;           // Log file handle
    QTextStream _logStream;   // Log file stream
    QMutex _mutex;            // Mutex for thread safety
    static Logger* _instance; // Singleton instance pointer
};

#define LOG_DEBUG(msg) Logger::getInstance().debug(msg)
#define LOG_INFO(msg) Logger::getInstance().info(msg)
#define LOG_WARNING(msg) Logger::getInstance().warning(msg)
#define LOG_ERROR(msg) Logger::getInstance().error(msg)

#endif // LOGGER_H 
