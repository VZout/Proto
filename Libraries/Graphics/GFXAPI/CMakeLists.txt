cmake_minimum_required(VERSION 3.9.2)

set(TARGETNAME GFXAPI)
project(${TARGETNAME})

include_directories(${MAIN_INCLUDE_FOLDER}Graphics)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/Helpers)
if (GFX_API_OPENGL)
include_directories(${THIRD_PARTY_FOLDER}glew-2.1.0/include)
elseif (GFX_API_OPENGLES)
include_directories(${THIRD_PARTY_FOLDER}Mali_3.02/include)
endif()
include_directories(${THIRD_PARTY_FOLDER}imgui)

#external dependencies

#header files
set(${TARGETNAME}_API_HEADERS
	../../../Code/Include/Graphics/API/Defines.h
	../../../Code/Include/Graphics/API/Enums.h
	../../../Code/Include/Graphics/API/GFX.h
	../../../Code/Include/Graphics/API/GFXIncludes.h
	../../../Code/Include/Graphics/API/Handles.h)

source_group("Header Files\\API" FILES ${${TARGETNAME}_API_HEADERS})

set(${TARGETNAME}_API_HELPERS_HEADERS
	../../../Code/Include/Graphics/API/Helpers/DataTypeByteSize.h
	../../../Code/Include/Graphics/API/Helpers/InitializeImGui.h
	../../../Code/Include/Graphics/API/Helpers/NewFrameImGui.h
	../../../Code/Include/Graphics/API/Helpers/TransposeData.h)

source_group("Header Files\\API\\Helpers" FILES ${${TARGETNAME}_API_HELPERS_HEADERS})

set(${TARGETNAME}_AGGREGATE_HEADERS
	${${TARGETNAME}_API_HEADERS}
	${${TARGETNAME}_API_HELPERS_HEADERS})

# source files
set(${TARGETNAME}_API_HELPERS_SOURCES
	../../../Code/Source/Graphics/API/Helpers/DataTypeByteSize.c
	../../../Code/Source/Graphics/API/Helpers/InitializeImGui.cpp
	../../../Code/Source/Graphics/API/Helpers/NewFrameImGui.cpp
	../../../Code/Source/Graphics/API/Helpers/TransposeData.c)

source_group("Source Files\\API\\Helpers" FILES ${${TARGETNAME}_API_HELPERS_SOURCES})

set(${TARGETNAME}_HELPERS_SOURCES
	../../../Code/Source/Graphics/Helpers/CreateGeometry.cpp)

source_group("Source Files\\Helpers" FILES ${${TARGETNAME}_HELPERS_SOURCES})

set(${TARGETNAME}_AGGREGATE_SOURCES
	${${TARGETNAME}_API_HELPERS_SOURCES})

# setup target
add_library(${TARGETNAME} STATIC ${${TARGETNAME}_AGGREGATE_HEADERS} ${${TARGETNAME}_AGGREGATE_SOURCES})

set_target_properties(${TARGETNAME} PROPERTIES FOLDER "GFXAPI")

install(TARGETS ${TARGETNAME} DESTINATION lib)
