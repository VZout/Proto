cmake_minimum_required(VERSION 3.9.2)

set(TARGETNAME GFXAPI)
project(${TARGETNAME})

include_directories(${MAIN_INCLUDE_FOLDER}Graphics)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/Helpers)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/Helpers)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/Viewer)

#external dependencies

#header files
set(${TARGETNAME}_CORE_HEADERS
	../../../Code/include/Graphics/Material.h)

source_group("Header Files" FILES ${${TARGETNAME}_CORE_HEADERS})

set(${TARGETNAME}_API_HEADERS
	../../../Code/include/Graphics/API/Defines.h
	../../../Code/include/Graphics/API/Enums.h
	../../../Code/include/Graphics/API/GFX.h
	../../../Code/include/Graphics/API/GFXIncludes.h
	../../../Code/include/Graphics/API/Handles.h)

source_group("Header Files\\API" FILES ${${TARGETNAME}_API_HEADERS})

set(${TARGETNAME}_API_HELPERS_HEADERS
	../../../Code/include/Graphics/API/Helpers/DataTypeByteSize.h
	../../../Code/include/Graphics/API/Helpers/TransposeData.h)

source_group("Header Files\\API\\Helpers" FILES ${${TARGETNAME}_API_HELPERS_HEADERS})

set(${TARGETNAME}_HELPERS_HEADERS
	../../../Code/include/Graphics/Helpers/CreateGeometry.h)

source_group("Header Files\\Helpers" FILES ${${TARGETNAME}_HELPERS_HEADERS})

set(${TARGETNAME}_VIEWER_HEADERS
	../../../Code/Include/Graphics/Viewer/Camera.h
	../../../Code/Include/Graphics/Viewer/CreateFrustum.h
	../../../Code/Include/Graphics/Viewer/CreateViewMatrix.h
	../../../Code/Include/Graphics/Viewer/EProjectionMatrix.h
	../../../Code/Include/Graphics/Viewer/Frustum.h
	../../../Code/Include/Graphics/Viewer/Frustum2D.h
	../../../Code/Include/Graphics/Viewer/Frustum3D.h
	../../../Code/Include/Graphics/Viewer/OrthographicProjectionMatrix.h
	../../../Code/Include/Graphics/Viewer/PerspectiveProjectionMatrix.h
	../../../Code/Include/Graphics/Viewer/ProjectionMatrix.h)

source_group("Header Files\\Viewer" FILES ${${TARGETNAME}_VIEWER_HEADERS})

set(${TARGETNAME}_AGGREGATE_HEADERS
	${${TARGETNAME}_CORE_HEADERS}
	${${TARGETNAME}_API_HEADERS}
	${${TARGETNAME}_API_HELPERS_HEADERS}
	${${TARGETNAME}_HELPERS_HEADERS}
	${${TARGETNAME}_VIEWER_HEADERS})

# source files
set(${TARGETNAME}_API_HELPERS_SOURCES
	../../../Code/source/Graphics/API/Helpers/DataTypeByteSize.c
	../../../Code/source/Graphics/API/Helpers/TransposeData.c)

source_group("Source Files\\API\\Helpers" FILES ${${TARGETNAME}_API_HELPERS_SOURCES})

set(${TARGETNAME}_HELPERS_SOURCES
	../../../Code/source/Graphics/Helpers/CreateGeometry.cpp)

source_group("Source Files\\Helpers" FILES ${${TARGETNAME}_HELPERS_SOURCES})

set(${TARGETNAME}_VIEWER_SOURCES
	../../../Code/Source/Graphics/Viewer/Camera.cpp
	../../../Code/Source/Graphics/Viewer/CreateFrustum.cpp
	../../../Code/Source/Graphics/Viewer/CreateViewMatrix.cpp
	../../../Code/Source/Graphics/Viewer/Frustum.cpp
	../../../Code/Source/Graphics/Viewer/Frustum2D.cpp
	../../../Code/Source/Graphics/Viewer/Frustum3D.cpp
	../../../Code/Source/Graphics/Viewer/OrthographicProjectionMatrix.cpp
	../../../Code/Source/Graphics/Viewer/PerspectiveProjectionMatrix.cpp
	../../../Code/Source/Graphics/Viewer/ProjectionMatrix.cpp)

source_group("Source Files\\Viewer" FILES ${${TARGETNAME}_VIEWER_SOURCES})

set(${TARGETNAME}_AGGREGATE_SOURCES
	${${TARGETNAME}_API_HELPERS_SOURCES}
	${${TARGETNAME}_HELPERS_SOURCES}
	${${TARGETNAME}_VIEWER_SOURCES})

# setup target
add_library(${TARGETNAME} STATIC ${${TARGETNAME}_AGGREGATE_HEADERS} ${${TARGETNAME}_AGGREGATE_SOURCES})

set_target_properties(${TARGETNAME} PROPERTIES FOLDER "GFXAPI")

install(TARGETS ${TARGETNAME} DESTINATION lib)
