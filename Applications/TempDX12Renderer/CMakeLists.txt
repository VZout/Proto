cmake_minimum_required(VERSION 3.9.2)

project(TempDX12Renderer LANGUAGES CXX)

#external dependencies

#header files
set(TempDX12Renderer_CORE_HEADERS
	./DX12Includes.h)

source_group("Header Files" FILES ${TempDX12Renderer_CORE_HEADERS})

set(TempDX12Renderer_AGGREGATE_HEADERS
	${TempDX12Renderer_CORE_HEADERS})

#source files
set(TempDX12Renderer_CORE_SOURCE
	./main.cpp)

source_group("Source Files" FILES ${TempDX12Renderer_CORE_SOURCE})

set(TempDX12Renderer_AGGREGATE_SOURCES
	${TempDX12Renderer_CORE_SOURCE})

#custom user settings
set(COMMAND_ARGUMENTS ${PROTO_ASSET_DIR})
configure_file( ${PROJECT_USER_TEMPLATE_FILE} ${CMAKE_CURRENT_BINARY_DIR}/TempDX12Renderer.vcxproj.user @ONLY )

#external dependencies
#find_library(VULKAN_STATIC_LIB vulkan-1.lib HINTS ${THIRD_PARTY_FOLDER}vulkan/lib)
#if(NOT VULKAN_STATIC_LIB)
#  message(FATAL_ERROR "Vulkan-1 static library not found!")
#endif()

#setup target
add_executable(TempDX12Renderer ${TempDX12Renderer_CORE_HEADERS} ${TempDX12Renderer_CORE_SOURCE})
#target_link_libraries(TempDX12Renderer Graphics Platform Utility ${VULKAN_STATIC_LIB})
set_target_properties(TempDX12Renderer PROPERTIES FOLDER "Applications")

install(TARGETS TempDX12Renderer DESTINATION bin)
