cmake_minimum_required(VERSION 3.9.2)

set(TARGETNAME GFXAPIVulkan)
project(${TARGETNAME} LANGUAGES CXX)

include_directories(${MAIN_INCLUDE_FOLDER}Graphics)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/Vulkan)

#header files
set(Graphics_API_HEADERS
	../../../Code/include/Graphics/API/Defines.h
	../../../Code/include/Graphics/API/Descriptors.h
	../../../Code/include/Graphics/API/Enums.h
	../../../Code/include/Graphics/API/GFX.h
	../../../Code/include/Graphics/API/GFXIncludes.h
	../../../Code/include/Graphics/API/Handles.h
	../../../Code/include/Graphics/API/Translators.h)

source_group("Header Files" FILES ${Graphics_API_HEADERS})

set(Graphics_API_Vulkan_HEADERS
	../../../Code/include/Graphics/API/Vulkan/VulkanAPI.h
	../../../Code/include/Graphics/API/Vulkan/VulkanIncludes.h
	../../../Code/include/Graphics/API/Vulkan/VulkanStructs.h
	../../../Code/include/Graphics/API/Vulkan/VulkanTranslators.h)

source_group("Header Files\\Vulkan" FILES ${Graphics_API_Vulkan_HEADERS})

set(${TARGETNAME}_AGGREGATE_HEADERS
	${Graphics_API_HEADERS}
	${Graphics_API_Vulkan_HEADERS}
	${Graphics_API_Vulkan_HELPERS_HEADERS})

# source files
set(Graphics_API_Vulkan_SOURCES
	../../../Code/source/Graphics/API/Vulkan/VulkanAPI.c
	../../../Code/source/Graphics/API/Vulkan/VulkanTranslators.c)

source_group("Source Files\\Vulkan" FILES ${Graphics_API_Vulkan_SOURCES})

set(${TARGETNAME}_AGGREGATE_SOURCES
	${Graphics_API_Vulkan_SOURCES})

# setup target
add_definitions(-DGFX_API_Vulkan)
add_definitions(-DPROTO_DLL_EXPORT)

add_library(${TARGETNAME} SHARED ${${TARGETNAME}_AGGREGATE_HEADERS} ${${TARGETNAME}_AGGREGATE_SOURCES})

set_target_properties(${TARGETNAME} PROPERTIES FOLDER "GFXAPI")

install(TARGETS ${TARGETNAME} DESTINATION bin)
