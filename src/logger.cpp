#include "logger.h"
#include <QDir>
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>

Logger* Logger::_instance = nullptr;

Logger::Logger(QObject* parent) : QObject(parent)
{
    try
    {
        qDebug() << "Logger: Starting initialization...";
        QString logDir = QCoreApplication::applicationDirPath() + "/logs";
        qDebug() << "Logger: Log directory path:" << logDir;
        QDir dir;
        if (!dir.mkpath(logDir))
        {
            qWarning() << "Failed to create log directory:" << logDir;
            return;
        }

        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm-ss");
        QString logFilePath = logDir + QString("/drone_telemetry_%1.log").arg(timestamp);
        qDebug() << "Logger: Log file path:" << logFilePath;
        _logFile.setFileName(logFilePath);
        if (_logFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            _logStream.setDevice(&_logFile);
            qDebug() << "Logger: File logging initialized successfully";
        }
        else
        {
            qWarning() << "Failed to open log file:" << logFilePath;
            qWarning() << "Error:" << _logFile.errorString();
        }
        qDebug() << "Logger: Initialization completed successfully";
    }
    catch (const std::exception& e)
    {
        qCritical() << "Logger initialization failed:" << e.what();
        throw;
    }
    catch (...)
    {
        qCritical() << "Unknown error in Logger initialization";
        throw;
    }
}

Logger::~Logger()
{
    if (_logFile.isOpen())
    {
        _logFile.close();
    }
}

Logger& Logger::getInstance()
{
    if (_instance == nullptr)
    {
        try
        {
            qDebug() << "Creating Logger instance...";
            _instance = new Logger();
            qDebug() << "Logger instance created successfully";
        }
        catch (const std::exception& e)
        {
            qCritical() << "Failed to create Logger instance:" << e.what();
            throw;
        }
        catch (...)
        {
            qCritical() << "Unknown error creating Logger instance";
            throw;
        }
    }
    return *_instance;
}

void Logger::log(LogLevel level, const QString& message)
{
    try
    {
        QMutexLocker locker(&_mutex);
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        QString logMessage = QString("[%1] [%2] %3")
                            .arg(timestamp)
                            .arg(levelToString(level))
                            .arg(message);
        if (_logFile.isOpen())
        {
            _logStream << logMessage << Qt::endl;
            _logStream.flush();
        }
        qDebug().noquote() << logMessage;
    }
    catch (const std::exception& e)
    {
        qWarning() << "Logging failed:" << e.what();
    }
    catch (...)
    {
        qWarning() << "Unknown error during logging";
    }
}

void Logger::debug(const QString& message)
{
    log(DEBUG, message);
}

void Logger::info(const QString& message)
{
    log(INFO, message);
}

void Logger::warning(const QString& message)
{
    log(WARNING, message);
}

void Logger::error(const QString& message)
{
    log(ERROR, message);
}

QString Logger::levelToString(LogLevel level)
{
    switch (level)
    {
    case DEBUG:
        return "DEBUG";
    case INFO:
        return "INFO";
    case WARNING:
        return "WARNING";
    case ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}
