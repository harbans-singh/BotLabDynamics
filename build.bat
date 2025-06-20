@echo off
echo Building Drone Telemetry Simulator...

REM Set Qt path for MinGW
set CMAKE_PREFIX_PATH=C:\Qt\6.9.0\mingw_64

REM Add MinGW to PATH
set PATH=C:\Qt\Tools\mingw1310_64\bin;%PATH%

REM Clean and create build directory
if exist "build" rmdir /s /q "build"
mkdir build
cd build

REM Configure with CMake using MinGW
echo Configuring with CMake...
cmake .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=%CMAKE_PREFIX_PATH%
if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

REM Build the project
echo Building project...
cmake --build .
if %ERRORLEVEL% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo Build completed successfully!
echo.
echo To run the application:
echo   cd build\bin
echo   DroneTelemetrySimulator.exe
echo.
pause 