cmake_minimum_required(VERSION 3.9.2)

project(TempVulkanRenderer LANGUAGES CXX)

#external dependencies
include_directories(${THIRD_PARTY_FOLDER}vulkan/include)
#include_directories(${THIRD_PARTY_FOLDER}glew-2.1.0/include)

#header files
set(TempVulkanRenderer_CORE_HEADERS
	./VulkanIncludes.h)

source_group("Header Files" FILES ${TempVulkanRenderer_CORE_HEADERS})

set(TempVulkanRenderer_AGGREGATE_HEADERS
	${TempVulkanRenderer_CORE_HEADERS})

#source files
set(TempVulkanRenderer_CORE_SOURCE
	./main.cpp)

source_group("Source Files" FILES ${TempVulkanRenderer_CORE_SOURCE})

set(TempVulkanRenderer_AGGREGATE_SOURCES
	${TempVulkanRenderer_CORE_SOURCE})

#custom user settings
set(COMMAND_ARGUMENTS ${PROTO_ASSET_DIR})
configure_file( ${PROJECT_USER_TEMPLATE_FILE} ${CMAKE_CURRENT_BINARY_DIR}/TempVulkanRenderer.vcxproj.user @ONLY )

#external dependencies
find_library(VULKAN_STATIC_LIB vulkan-1.lib HINTS ${THIRD_PARTY_FOLDER}vulkan/lib)
if(NOT VULKAN_STATIC_LIB)
  message(FATAL_ERROR "Vulkan-1 static library not found!")
endif()

#setup target
add_executable(TempVulkanRenderer ${TempVulkanRenderer_CORE_HEADERS} ${TempVulkanRenderer_CORE_SOURCE})
target_link_libraries(TempVulkanRenderer Graphics Platform Utility ${VULKAN_STATIC_LIB})
set_target_properties(TempVulkanRenderer PROPERTIES FOLDER "Applications")

#add_custom_command(TARGET TempVulkanRenderer POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
#	"${THIRD_PARTY_FOLDER}glew-2.1.0/bin/Release/x64/glew32.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)

install(TARGETS TempVulkanRenderer DESTINATION bin)
