cmake_minimum_required(VERSION 3.9.2)
project (Proto)

set(THIRD_PARTY_FOLDER ${CMAKE_SOURCE_DIR}/ThirdParty/)
set(MAIN_INCLUDE_FOLDER ${CMAKE_SOURCE_DIR}/Code/Include/)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # Output directory for static lib
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Output directory for shared lib
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Output directory for executables

set(PROJECT_USER_TEMPLATE_FILE ${CMAKE_SOURCE_DIR}/Scripts/VSProjectTemplateUserFile.in)

set(PROTO_ASSET_DIR ${CMAKE_SOURCE_DIR}/Data)

set(CMAKE_DEBUG_POSTFIX "_d")

include_directories(${MAIN_INCLUDE_FOLDER})

# preprocessor directives
add_definitions(-DPROTO_CUSTOM_ALLOCATORS)
add_definitions(-DPROTO_PLATFORM_WIN32)
add_definitions(-DGFX_API_DX11)
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	add_definitions(-DVK_USE_PLATFORM_WIN32_KHR)
endif()
add_definitions(-DUNICODE)

# general compiler settings
if(MSVC)
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
endif()

# add project directories
add_subdirectory(libraries)
add_subdirectory(applications)
