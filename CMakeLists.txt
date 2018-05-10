cmake_minimum_required(VERSION 3.9.2)
project (Proto)

# build system information:
message(STATUS "CMAKE_SYSTEM_NAME       : " ${CMAKE_SYSTEM_NAME})
message(STATUS "CMAKE_SYSTEM_VERSION    : " ${CMAKE_SYSTEM_VERSION})
message(STATUS "CMAKE_VS_PLATFORM_NAME  : " ${CMAKE_VS_PLATFORM_NAME})
message(STATUS "CMAKE_GENERATOR_PLATFORM: " ${CMAKE_GENERATOR_PLATFORM})

# global settings
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# cmake settings
set(CMAKE_DEBUG_POSTFIX "_d")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # Output directory for static lib
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Output directory for shared lib
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Output directory for executables

# folder settings
set(PROTO_ASSET_DIR ${CMAKE_SOURCE_DIR}/Data)
set(THIRD_PARTY_FOLDER ${CMAKE_SOURCE_DIR}/ThirdParty/)
set(MAIN_INCLUDE_FOLDER ${CMAKE_SOURCE_DIR}/Code/Include/)

# project templates
set(PROTO_PROJECT_USER_TEMPLATE ${CMAKE_SOURCE_DIR}/Scripts/VSProjectTemplateUserFile.in)

# preprocessor directives
add_definitions(-DPROTO_CUSTOM_ALLOCATORS)
add_definitions(-DUNICODE)
if (${CMAKE_GENERATOR_PLATFORM} MATCHES "ORBIS")
	# ORBIS (PS4) specific defines
	add_definitions(-DPROTO_PLATFORM_ORBIS)
	add_definitions(-DPROTO_CPP03)
	set(ORBIS TRUE)

elseif (${CMAKE_GENERATOR_PLATFORM} MATCHES "PSVita")
	# PSVita specific defines
	add_definitions(-DPROTO_PLATFORM_PSP2)
	add_definitions(-DPROTO_CPP03)
	set(PSP2 TRUE)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	# windows specific defines
	add_definitions(-DPROTO_PLATFORM_WIN32)
	add_definitions(-DPROTO_CPP14)
	add_definitions(-DPROTO_BOOST_ENABLED)
	#add_definitions(-DPROTO_GLM_ENABLED)
	#add_definitions(-DGFX_API_DX12)

	# vulkan only settings
	add_definitions(-DVK_USE_PLATFORM_WIN32_KHR)

else()
	message(FATAL_ERROR "[BUILD SYSTEM] Unknown generator (platform) encountered!")
endif()

# general compiler settings
if(MSVC)
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Werror")
	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-missing-braces")
endif()

# add project directories
add_subdirectory(Libraries)
add_subdirectory(Applications)
