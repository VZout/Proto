cmake_minimum_required(VERSION 3.9.2)

project (Graphics)
include_directories(${CMAKE_SOURCE_DIR}/Code/Include)

if (ORBIS)
	# project include paths for Orbis (PS4) platform

	# include projects built for Orbis (PS4) platform
	add_subdirectory(GFXAPIORBIS)
elseif (PSP2)
	# project include paths for PSVita platform

	# include projects built for PSVita platform
	add_subdirectory(GFXAPIPSP2)
elseif (${CMAKE_GENERATOR} MATCHES "Visual Studio 15 2017 Win64")
	# project include paths for Windows platform

	# include projects built for Windows platform
	add_subdirectory(GFXAPI)
	add_subdirectory(GFXAPIDX11)
	add_subdirectory(GFXAPIDX12)
	add_subdirectory(GFXAPIOpenGL)
	add_subdirectory(GFXAPIOpenGLES)
	add_subdirectory(GFXAPIVulkan)
else()
	message(FATAL_ERROR "[BUILD SYSTEM] Unknown generator (platform) encountered!")
endif()
