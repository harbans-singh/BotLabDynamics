# Drone Telemetry Simulator

A real-time drone telemetry simulator built with Qt (Widgets) that demonstrates modular, multithreaded architecture and common design patterns. This application simulates and displays real-time telemetry data from a single drone with realistic movement patterns and failure simulation capabilities.

![image_alt](https://github.com/harbans-singh/BotLabDynamics/blob/46de27e49b4e68c9f0a9bdc27e0e80d9ce5d1d1b/Img1.png)
![image_alt](https://github.com/harbans-singh/BotLabDynamics/blob/46de27e49b4e68c9f0a9bdc27e0e80d9ce5d1d1b/Img2.png)
![image_alt](https://github.com/harbans-singh/BotLabDynamics/blob/46de27e49b4e68c9f0a9bdc27e0e80d9ce5d1d1b/Img3.png)
![image_alt](https://github.com/harbans-singh/BotLabDynamics/blob/46de27e49b4e68c9f0a9bdc27e0e80d9ce5d1d1b/Img4.png)
![image_alt](https://github.com/harbans-singh/BotLabDynamics/blob/46de27e49b4e68c9f0a9bdc27e0e80d9ce5d1d1b/Img5.png)

## Features

### Telemetry Display
- **Drone ID**: Unique identifier for the drone
- **Latitude & Longitude**: GPS coordinates with 6 decimal precision
- **Altitude**: Height in meters with 1 decimal precision
- **Heading**: Direction in degrees (0-360°)
- **Speed**: Velocity in meters per second
- **Battery**: Percentage with visual progress bar and color coding
- **GPS Fix Status**: No Fix / 2D Fix / 3D Fix with status indicators

### Real-time Simulation
- Updates every 500 milliseconds using a worker thread
- Realistic movement patterns with location shifts, speed variations, and heading drift
- Battery drain simulation with accelerated drain in failure mode
- GPS fix status changes

### Failure Simulation
- **GPS Fix Loss**: Drops GPS fix status to "No Fix"
- **Rapid Battery Drain**: Accelerates battery consumption
- **Toggle Control**: Easy activation/deactivation of failure mode

### Movement Strategies
- **Hover Strategy**: Minimal movement with low speed
- **Random Walk Strategy**: More dynamic movement patterns
- **Strategy Pattern**: Easy to extend with new movement behaviors

## Design Patterns Implementation

### 1. Observer Pattern
**Purpose**: UI updates from drone data model
**Implementation**: 
- `TelemetryModel` acts as the Subject
- `MainWindow` acts as the Observer
- Qt's signal-slot mechanism provides the notification system
- When telemetry data changes, the model emits signals that the UI observes and responds to

**Files**: `src/telemetrymodel.h/cpp`, `src/mainwindow.h/cpp`

### 2. Factory Pattern
**Purpose**: Create the drone simulator object
**Implementation**:
- `DroneFactory` provides static factory methods
- Encapsulates drone creation logic
- Supports different initialization parameters
- Centralizes object creation and configuration

**Files**: `src/dronefactory.h/cpp`

### 3. Strategy Pattern
**Purpose**: Implement different drone movement behaviors
**Implementation**:
- `MovementStrategy` abstract base class
- `HoverStrategy` and `RandomWalkStrategy` concrete implementations
- Runtime strategy switching via UI controls
- Each strategy encapsulates different movement algorithms

**Files**: `src/movementstrategy.h/cpp`, `src/hoverstrategy.h/cpp`, `src/randomwalkstrategy.h/cpp`

### 4. Singleton Pattern
**Purpose**: Centralized Logger for system events
**Implementation**:
- `Logger` class with private constructor and static instance
- Thread-safe logging with mutex protection
- File-based logging with timestamps and log levels
- Global access via `Logger::getInstance()`

**Files**: `src/logger.h/cpp`

## Architecture

### Multithreaded Design
- **Main Thread**: UI rendering and user interaction
- **Worker Thread**: Simulation execution and telemetry updates
- **Thread Safety**: Mutex-protected shared resources
- **Signal-Slot Communication**: Thread-safe communication between components

### Modular Structure
```
src/
├── main.cpp                 # Application entry point
├── mainwindow.cpp           # Main UI implementation (Observer pattern)
├── mainwindow.ui           # Qt Designer UI file
├── telemetrymodel.cpp       # Data model implementation (Subject in Observer pattern)
├── dronesimulator.cpp       # Simulation controller
├── drone.cpp               # Drone entity
├── dronefactory.cpp        # Factory pattern implementation
├── movementstrategy.cpp     # Strategy pattern base class
├── hoverstrategy.cpp       # Concrete strategy implementation
├── randomwalkstrategy.cpp   # Concrete strategy implementation
├── logger.cpp              # Singleton logger
└── include/                # Header files
    ├── mainwindow.h        # Main UI header
    ├── telemetrymodel.h    # Data model header
    ├── dronesimulator.h    # Simulation controller header
    ├── drone.h            # Drone entity header
    ├── dronefactory.h     # Factory pattern header
    ├── movementstrategy.h  # Strategy pattern base class header
    ├── hoverstrategy.h    # Concrete strategy header
    ├── randomwalkstrategy.h # Concrete strategy header
    └── logger.h           # Singleton logger header
```

## Build & Run Instructions

### Prerequisites
- **Qt 6.x** (Core and Widgets modules)
- **CMake 3.16+**
- **C++17 compatible compiler**

### Building the Application

**Option 1: Using the build script (Recommended)**
```bash
# Windows
.\build.bat

# Linux/macOS
./build.sh
```

**Option 2: Manual build**
1. **Clone the repository**:
   ```bash
   git clone <repository-url>
   cd DroneTelemetrySimulator
   ```
2. **Build the project**:
   ```bash
   Run build.bat
   ```

3. **Run the application**:
   ```bash
   cd bin
   ./DroneTelemetrySimulator.exe
   ```

### Platform-Specific Notes

**Windows**:
- Qt 6.9.0 with MinGW is installed at `C:\Qt\6.9.0\mingw_64`
- MinGW tools are available at `C:\Qt\Tools\mingw1310_64\bin`
- Use the provided `build.bat` script for easy building
- Run from build directory: `DroneTelemetrySimulator.exe`

**Linux**:
- Install Qt6 development packages: `sudo apt install qt6-base-dev`
- May need to set `LD_LIBRARY_PATH` to Qt libraries

**macOS**:
- Install Qt6 via Homebrew: `brew install qt6`
- Ensure Xcode command line tools are installed

## Usage

1. **Start the Application**: Launch the executable from `build/bin/DroneTelemetrySimulator.exe`
2. **Start Simulation**: Click "Start Simulation" button
3. **Change Movement Strategy**: Use the dropdown to switch between Hover and Random Walk
4. **Simulate Failure**: Click "Simulate Failure" to activate failure mode
5. **Monitor Telemetry**: Watch real-time updates of all drone parameters
6. **View Logs**: Check log files in the `build/bin/logs` folder

## Manual Testing

Manual test cases for simulation and logic layers are provided in the file **TestCases.txt** in the project root. These cover:

- Drone creation and initialization
- Simulation start/stop
- Movement strategies
- Battery drain and warnings
- Failure simulation (GPS loss, rapid battery drain)
- Logger functionality
- UI status and warnings
- Application stability
- Default location (New Delhi)

Please refer to **TestCases.txt** for step-by-step instructions and expected results for each test case.

## Logging

The application uses a centralized logging system:
- **Location**: `build/bin/logs/` folder (next to the executable)
- **Levels**: DEBUG, INFO, WARNING, ERROR
- **Format**: `[Timestamp] [Level] Message`
- **Thread Safety**: Mutex-protected logging operations

## Contributing

1. Follow the existing code style and patterns
2. Add unit tests for new functionality
3. Update documentation for new features
4. Ensure thread safety for multithreaded components

## License

This project is created for the BoltLab Dynamics assignment. All rights reserved.

## Contact

For questions about this implementation, please refer to the assignment requirements or contact the development team. 
