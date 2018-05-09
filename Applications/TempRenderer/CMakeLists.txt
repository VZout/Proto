cmake_minimum_required(VERSION 3.9.2)

set(TARGETNAME TempRenderer)

project(${TARGETNAME} LANGUAGES CXX)

#external dependencies
include_directories(${THIRD_PARTY_FOLDER}vulkan/include)
#include_directories(${THIRD_PARTY_FOLDER}glew-2.1.0/include)

#header files
set(TempRenderer_CORE_HEADERS
	./Renderer.h
	./RenderPass.h
	./RenderTechnique.h)

source_group("Header Files" FILES ${TempRenderer_CORE_HEADERS})

set(TempRenderer_AGGREGATE_HEADERS
	${TempRenderer_CORE_HEADERS})

#source files
set(TempRenderer_CORE_SOURCE
	./main.cpp
	./Renderer.cpp
	./RenderPass.cpp
	./RenderTechnique.cpp)

source_group("Source Files" FILES ${TempRenderer_CORE_SOURCE})

set(TempRenderer_AGGREGATE_SOURCES
	${TempRenderer_CORE_SOURCE})

#custom user settings
set(COMMAND_ARGUMENTS ${PROTO_ASSET_DIR})
configure_file( ${PROJECT_USER_TEMPLATE_FILE} ${CMAKE_CURRENT_BINARY_DIR}/TempRenderer.vcxproj.user @ONLY )

#external dependencies
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	find_library(VULKAN_STATIC_LIB vulkan-1.lib HINTS ${THIRD_PARTY_FOLDER}vulkan/lib)
	if(NOT VULKAN_STATIC_LIB)
	  message(FATAL_ERROR "Vulkan-1 static library not found!")
	endif()

	target_link_libraries(${TARGETNAME} Graphics Math Platform Utility ${VULKAN_STATIC_LIB})

	#add_custom_command(TARGET ${TARGETNAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
	#	"${THIRD_PARTY_FOLDER}glew-2.1.0/bin/Release/x64/glew32.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
endif()

#setup target
add_executable(${TARGETNAME} ${TempRenderer_CORE_HEADERS} ${TempRenderer_CORE_SOURCE})
set_target_properties(${TARGETNAME} PROPERTIES FOLDER "Applications")

if(${CMAKE_VS_PLATFORM_NAME} MATCHES "PSVita")
	set_target_properties(${TARGETNAME} PROPERTIES SUFFIX ".self")
endif()

install(TARGETS ${TARGETNAME} DESTINATION bin)
