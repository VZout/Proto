cmake_minimum_required(VERSION 3.9.2)
project (Applications)

include_directories(${CMAKE_SOURCE_DIR}/Code/Include)
if (ORBIS)
	# project include paths for Orbis (PS4) platform

	# include projects built for Orbis (PS4) platform
	add_subdirectory(MemManager)
	add_subdirectory(TempRenderer)
elseif (PSP2)
	# project include paths for PSVita platform

	# include projects built for PSVita platform
	add_subdirectory(MemManager)
	add_subdirectory(TempRenderer)
elseif (${CMAKE_GENERATOR} MATCHES "Visual Studio 15 2017 Win64")
	# project include paths for Windows platform
	include_directories(${CMAKE_SOURCE_DIR}/libraries/ai/include)
	include_directories(${CMAKE_SOURCE_DIR}/libraries/architecture/include)
	include_directories(${CMAKE_SOURCE_DIR}/libraries/audio/include)
	include_directories(${CMAKE_SOURCE_DIR}/libraries/graphics/include)
	include_directories(${CMAKE_SOURCE_DIR}/libraries/io/include)
	include_directories(${CMAKE_SOURCE_DIR}/libraries/math/include)
	include_directories(${CMAKE_SOURCE_DIR}/libraries/memory/include)
	include_directories(${CMAKE_SOURCE_DIR}/libraries/platform/include)
	include_directories(${CMAKE_SOURCE_DIR}/libraries/procedural/include)
	include_directories(${CMAKE_SOURCE_DIR}/libraries/resources/include)
	include_directories(${CMAKE_SOURCE_DIR}/libraries/scripting/include)
	include_directories(${CMAKE_SOURCE_DIR}/libraries/thirdparty/include)
	include_directories(${CMAKE_SOURCE_DIR}/libraries/threading/include)
	include_directories(${CMAKE_SOURCE_DIR}/libraries/utility/include)

	# include projects built for Windows platform
	add_subdirectory(pathtracer)
	add_subdirectory(rasterizer)
	add_subdirectory(raymarcher)
	add_subdirectory(raytracer)
	add_subdirectory(renderer)
	add_subdirectory(DataStructures)
	add_subdirectory(MemManager)
	add_subdirectory(TempRenderer)
else()
	message(FATAL_ERROR "[PROTO BUILD SYSTEM] Unknown generator (platform) encountered!")
endif()
