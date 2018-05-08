@ECHO OFF

REM PUSHD %~dp0

REM Update these lines if the currently installed version of Visual Studio is not 2017.
SET CMAKE="C:\Program Files\CMake\bin\cmake.exe"
SET CMAKE_GENERATOR="Visual Studio 15 2017"
SET CMAKE_BINARY_DIR=Build
SET CMAKE_TOOLCHAIN_FILE="-DCMAKE_TOOLCHAIN_FILE=Scripts\toolchain.PSP2.cmake"

MKDIR %CMAKE_BINARY_DIR% 2>NUL
PUSHD %CMAKE_BINARY_DIR%

%CMAKE% -G %CMAKE_GENERATOR% %CMAKE_TOOLCHAIN_FILE% -Wno-dev "%~dp0"

IF ERRORLEVEL 1 (
    PAUSE
) ELSE (
    START Proto.sln
)

POPD
POPD