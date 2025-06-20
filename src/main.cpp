#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include "logger.h"

int main(int argc, char *argv[])
{
    try
    {
        QApplication app(argc, argv);

        // Set application properties
        app.setApplicationName("Drone Telemetry Simulator");
        app.setApplicationVersion("1.0.0");
        app.setOrganizationName("BoltLab Dynamics");

        // Set modern style
        app.setStyle(QStyleFactory::create("Fusion"));

        qDebug() << "Application initialized successfully";
        try
        {
            Logger::getInstance();
            qDebug() << "Logger initialized successfully";
        }
        catch (const std::exception& e)
        {
            qWarning() << "Logger initialization failed:" << e.what();
        }
        
        qDebug() << "Creating main window...";
        
        // Create and show main window
        MainWindow window;
        window.show();
        qDebug() << "Main window displayed successfully";
        int result = app.exec();
        qDebug() << "Application shutting down";
        return result;
    }
    catch (const std::exception& e)
    {
        qCritical() << "Fatal error:" << e.what();
        QMessageBox::critical(nullptr, "Fatal Error", 
                             QString("Application failed to start: %1").arg(e.what()));
        return 1;
    }
    catch (...)
    {
        qCritical() << "Unknown fatal error occurred";
        QMessageBox::critical(nullptr, "Fatal Error", 
                             "Application failed to start due to an unknown error");
        return 1;
    }
} 
