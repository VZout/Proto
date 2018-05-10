cmake_minimum_required(VERSION 3.9.2)

set(TARGETNAME GFXAPIDX11)
project(${TARGETNAME} LANGUAGES CXX)

include_directories(${MAIN_INCLUDE_FOLDER}Graphics)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/DX11)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/DX11/Helpers)

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

set(Graphics_API_DX11_HEADERS
	../../../Code/include/Graphics/API/DX11/DX11API.h
	../../../Code/include/Graphics/API/DX11/DX11Includes.h
	../../../Code/include/Graphics/API/DX11/DX11Structs.h
	../../../Code/include/Graphics/API/DX11/DX11Translators.h)

source_group("Header Files\\DX11" FILES ${Graphics_API_DX11_HEADERS})

set(Graphics_API_DX11_HELPERS_HEADERS
	../../../Code/include/Graphics/API/DX11/Helpers/DetermineAdapterSettings.h
	../../../Code/include/Graphics/API/DX11/Helpers/DetermineConstantBuffers.h
	../../../Code/include/Graphics/API/DX11/Helpers/InspectVertexShader.h
	../../../Code/include/Graphics/API/DX11/Helpers/SafeRelease.h
	../../../Code/include/Graphics/API/DX11/Helpers/SetDebugName.h)

source_group("Header Files\\API\\DX11\\Helpers" FILES ${Graphics_API_DX11_HELPERS_HEADERS})

set(${TARGETNAME}_AGGREGATE_HEADERS
	${Graphics_API_HEADERS}
	${Graphics_API_DX11_HEADERS}
	${Graphics_API_DX11_HELPERS_HEADERS})

# source files
set(Graphics_API_DX11_SOURCES
	../../../Code/source/Graphics/API/DX11/DX11API.c
	../../../Code/source/Graphics/API/DX11/DX11Translators.c)

source_group("Source Files\\DX11" FILES ${Graphics_API_DX11_SOURCES})

set(Graphics_API_DX11_HELPERS_SOURCES
	../../../Code/source/Graphics/API/DX11/Helpers/DetermineAdapterSettings.c
	../../../Code/source/Graphics/API/DX11/Helpers/DetermineConstantBuffers.c
	../../../Code/source/Graphics/API/DX11/Helpers/InspectVertexShader.c)

source_group("Source Files\\API\\DX11\\Helpers" FILES ${Graphics_API_DX11_HELPERS_SOURCES})

set(${TARGETNAME}_AGGREGATE_SOURCES
	${Graphics_API_DX11_SOURCES}
	${Graphics_API_DX11_HELPERS_SOURCES})

# setup target
add_definitions(-DGFX_API_DX11)
add_definitions(-DPROTO_DLL_EXPORT)

add_library(${TARGETNAME} SHARED ${${TARGETNAME}_AGGREGATE_HEADERS} ${${TARGETNAME}_AGGREGATE_SOURCES})
target_link_libraries(${TARGETNAME} GFXAPI)

set_target_properties(${TARGETNAME} PROPERTIES FOLDER "GFXAPI")

install(TARGETS ${TARGETNAME} DESTINATION bin)
