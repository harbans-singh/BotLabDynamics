cmake_minimum_required(VERSION 3.16)
project(DroneTelemetrySimulator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 components
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Enable automoc for Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Source files
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/drone.cpp
    src/dronesimulator.cpp
    src/telemetrymodel.cpp
    src/logger.cpp
    src/movementstrategy.cpp
    src/hoverstrategy.cpp
    src/randomwalkstrategy.cpp
    src/dronefactory.cpp
)

# Header files
set(HEADERS
    src/include/mainwindow.h
    src/include/drone.h
    src/include/dronesimulator.h
    src/include/telemetrymodel.h
    src/include/logger.h
    src/include/movementstrategy.h
    src/include/hoverstrategy.h
    src/include/randomwalkstrategy.h
    src/include/dronefactory.h
)

# UI files
set(UI_FILES
    src/mainwindow.ui
)

# Create executable
add_executable(DroneTelemetrySimulator ${SOURCES} ${HEADERS} ${UI_FILES})

# Link Qt libraries
target_link_libraries(DroneTelemetrySimulator
    Qt6::Core
    Qt6::Widgets
)

# Include directories
target_include_directories(DroneTelemetrySimulator PRIVATE src/include) 