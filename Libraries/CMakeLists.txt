cmake_minimum_required(VERSION 3.9.2)
project (Libraries)

include_directories(${CMAKE_SOURCE_DIR}/Code/Include)

if (${CMAKE_GENERATOR_PLATFORM} MATCHES "ORBIS")
	# project include paths for Orbis (PS4) platform

	# include projects built for Orbis (PS4) platform
	add_subdirectory(Math)
	add_subdirectory(Memory)
	add_subdirectory(Platform)
	add_subdirectory(Utility)
elseif (${CMAKE_GENERATOR_PLATFORM} MATCHES "PSVita")
	# project include paths for PSVita platform

	# include projects built for PSVita platform
	add_subdirectory(Math)
	add_subdirectory(Memory)
	add_subdirectory(Platform)
	add_subdirectory(Utility)
elseif (${CMAKE_GENERATOR} MATCHES "Visual Studio 15 2017 Win64")
	# project include paths for Windows platform
	#include_directories(${CODE_REPOSITORY}boost_1_65_1)
	#include_directories(${CODE_REPOSITORY}glm)

	# include projects built for Windows platform
	add_subdirectory(AI)
	add_subdirectory(Graphics)
	add_subdirectory(Io)
	add_subdirectory(Math)
	add_subdirectory(Memory)
	add_subdirectory(Platform)
	add_subdirectory(Utility)
else()
	message(FATAL_ERROR "[BUILD SYSTEM] Unknown generator (platform) encountered!")
endif()
