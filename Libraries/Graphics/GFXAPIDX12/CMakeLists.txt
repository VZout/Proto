cmake_minimum_required(VERSION 3.9.2)

set(TARGETNAME GFXAPIDX12)
project(${TARGETNAME} LANGUAGES CXX)

include_directories(${MAIN_INCLUDE_FOLDER}Graphics)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/DX12)

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

set(Graphics_API_DX12_HEADERS
	../../../Code/include/Graphics/API/DX12/DX12API.h
	../../../Code/include/Graphics/API/DX12/DX12Includes.h
	../../../Code/include/Graphics/API/DX12/DX12Structs.h
	../../../Code/include/Graphics/API/DX12/DX12Translators.h)

source_group("Header Files\\DX12" FILES ${Graphics_API_DX12_HEADERS})

set(Graphics_API_DX12_HELPERS_HEADERS
	../../../Code/include/Graphics/API/DX12/Helpers/SafeRelease.h)

source_group("Header Files\\DX12\\Helpers" FILES ${Graphics_API_DX12_HELPERS_HEADERS})

set(${TARGETNAME}_AGGREGATE_HEADERS
	${Graphics_API_HEADERS}
	${Graphics_API_DX12_HEADERS}
	${Graphics_API_DX12_HELPERS_HEADERS})

# source files
set(Graphics_API_DX12_SOURCES
	../../../Code/source/Graphics/API/DX12/DX12API.c
	../../../Code/source/Graphics/API/DX12/DX12Translators.c)

source_group("Source Files\\DX12" FILES ${Graphics_API_DX12_SOURCES})

set(${TARGETNAME}_AGGREGATE_SOURCES
	${Graphics_API_DX12_SOURCES})

# setup target
add_definitions(-DGFX_API_DX12)
add_definitions(-DPROTO_DLL_EXPORT)

add_library(${TARGETNAME} SHARED ${${TARGETNAME}_AGGREGATE_HEADERS} ${${TARGETNAME}_AGGREGATE_SOURCES})

set_target_properties(${TARGETNAME} PROPERTIES FOLDER "GFXAPI")

install(TARGETS ${TARGETNAME} DESTINATION bin)
