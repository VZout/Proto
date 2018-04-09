cmake_minimum_required(VERSION 3.9.2)

project(platform)

include_directories(${MAIN_INCLUDE_FOLDER}Platform)
include_directories(${MAIN_INCLUDE_FOLDER}Platform/Debug)
include_directories(${MAIN_INCLUDE_FOLDER}Platform/Helpers)
include_directories(${MAIN_INCLUDE_FOLDER}Platform/Pi)
include_directories(${MAIN_INCLUDE_FOLDER}Platform/Win32)

include_directories(${THIRD_PARTY_FOLDER})
include_directories(${THIRD_PARTY_FOLDER}boost_1_65_1)
include_directories(${THIRD_PARTY_FOLDER}glew-2.1.0/include)

# header files
set(Platform_CORE_HEADERS 
    ../../Code/include/Platform/CommandLine.h
    ../../Code/include/Platform/CommandLineParser.h
    ../../Code/include/Platform/Window.h)

source_group("Header Files" FILES ${Platform_DEBUG_HEADERS})

set(Platform_DEBUG_HEADERS
    ../../Code/include/Platform/Debug/Inspector.h
    ../../Code/include/Platform/Debug/Profiler.h
    ../../Code/include/Platform/Debug/AssertMessage.h
    ../../Code/include/Platform/Debug/DebugConsole.h
    ../../Code/include/Platform/Debug/GetLastErrorAsString.h
    ../../Code/include/Platform/Debug/Inspect.h)

source_group("Header Files\\Debug" FILES ${Platform_DEBUG_HEADERS})

set(Platform_HELPERS_HEADERS
    ../../Code/include/Platform/Helpers/DateTimeFunctions.h
    ../../Code/include/Platform/Helpers/EDisplayResolution.h
	../../Code/include/Platform/Helpers/SetWorkingDirectory.h
    ../../Code/include/Platform/Helpers/StringFunctions.h
    ../../Code/include/Platform/Helpers/SystemInfo.h
    ../../Code/include/Platform/Helpers/TranslateDisplayResolution.h
    ../../Code/include/Platform/Helpers/WindowFunctions.h)

source_group("Header Files\\Helpers" FILES ${Platform_HELPERS_HEADERS})

if(UNIX)
set(Platform_PLATFORM_HEADERS
    ../../Code/include/Platform/Pi/PlatformDefines.h
    ../../Code/include/Platform/Pi/ApplicationLoop.h)

source_group("Header Files\\Pi" FILES ${Platform_PLATFORM_HEADERS})
elseif(WIN32)
set(Platform_PLATFORM_HEADERS
    ../../Code/include/Platform/Win32/ApplicationLoop.h
    ../../Code/include/Platform/Win32/PlatformDefines.h
    ../../Code/include/Platform/Win32/WindowProcedure.h
    ../../Code/include/Platform/Win32/WinIncludes.h)

source_group("Header Files\\Win32" FILES ${Platform_PLATFORM_HEADERS})
endif()

set(Platform_AGGREGATE_HEADERS
	${Platform_CORE_HEADERS}
	${Platform_DEBUG_HEADERS}
	${Platform_HELPERS_HEADERS}
	${Platform_PLATFORM_HEADERS})

# source files
set(Platform_CORE_SOURCES
    ../../Code/source/Platform/CommandLine.cpp
    ../../Code/source/Platform/CommandLineParser.cpp
    ../../Code/source/Platform/Window.cpp)

source_group("Source Files" FILES ${Platform_CORE_SOURCES})

set(Platform_DEBUG_SOURCES
    ../../Code/source/Platform/Debug/AssertMessage.cpp
    ../../Code/source/Platform/Debug/DebugConsole.cpp
    ../../Code/source/Platform/Debug/GetLastErrorAsString.cpp
    ../../Code/source/Platform/Debug/Inspector.cpp
    ../../Code/source/Platform/Debug/Profiler.cpp)

source_group("Source Files\\Debug" FILES ${Platform_DEBUG_SOURCES})

set(Platform_HELPERS_SOURCES
    ../../Code/source/Platform/Helpers/DateTimeFunctions.cpp
    ../../Code/source/Platform/Helpers/StringFunctions.cpp
    ../../Code/source/Platform/Helpers/SystemInfo.cpp
    ../../Code/source/Platform/Helpers/TranslateDisplayResolution.cpp
    ../../Code/source/Platform/Helpers/WindowFunctions.cpp)

source_group("Source Files\\Helpers" FILES ${Platform_HELPERS_SOURCES})

if(UNIX)
set(Platform_PLATFORM_SOURCES
    ../../Code/source/Platform/Pi/ApplicationLoop.cpp)

source_group("Source Files\\Pi" FILES ${Platform_PLATFORM_SOURCES})
elseif(WIN32)
set(Platform_PLATFORM_SOURCES
    ../../Code/source/Platform/Win32/ApplicationLoop.cpp
	../../Code/source/Platform/Win32/SetWorkingDirectory.cpp
    ../../Code/source/Platform/Win32/WindowProcedure.cpp)

source_group("Source Files\\Win32" FILES ${Platform_PLATFORM_SOURCES})
endif()

set(Platform_AGGREGATE_SOURCES
	${Platform_CORE_SOURCES}
	${Platform_DEBUG_SOURCES}
	${Platform_HELPERS_SOURCES}
	${Platform_PLATFORM_SOURCES})

# setup target
add_library(Platform STATIC ${Platform_AGGREGATE_HEADERS} ${Platform_AGGREGATE_SOURCES})

IF(WIN32)
    target_compile_definitions(Platform PUBLIC WIN32 UNICODE)
ELSE(WIN32)
    message(FATAL_ERROR "No other platforms supported")
ENDIF(WIN32)

set_target_properties(Platform PROPERTIES FOLDER "Libraries")
