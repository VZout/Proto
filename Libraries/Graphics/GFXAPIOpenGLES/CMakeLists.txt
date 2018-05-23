cmake_minimum_required(VERSION 3.9.2)

set(TARGETNAME GFXAPIOPENGLES)
project(${TARGETNAME} LANGUAGES CXX)

include_directories(${THIRD_PARTY_FOLDER}Mali_3.02/include)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/OpenGLES)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/OpenGLES/Helpers)

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

set(Graphics_API_OPENGLES_HEADERS
	../../../Code/include/Graphics/API/OpenGLES/OpenGLESAPI.h
	../../../Code/include/Graphics/API/OpenGLES/OpenGLESIncludes.h
	../../../Code/include/Graphics/API/OpenGLES/OpenGLESStructs.h
	../../../Code/include/Graphics/API/OpenGLES/OpenGLESTranslators.h)

source_group("Header Files\\OpenGLES" FILES ${Graphics_API_OPENGLES_HEADERS})

set(Graphics_API_OPENGLES_HELPERS_HEADERS
	../../../Code/include/Graphics/API/OpenGLES/Helpers/CheckEGLError.h
	../../../Code/include/Graphics/API/OpenGLES/Helpers/CheckGLESError.h)

source_group("Header Files\\OpenGLES\\Helpers" FILES ${Graphics_API_OPENGLES_HELPERS_HEADERS})

set(${TARGETNAME}_AGGREGATE_HEADERS
	${Graphics_API_HEADERS}
	${Graphics_API_OPENGLES_HEADERS}
	${Graphics_API_OPENGLES_HELPERS_HEADERS})

# source files
set(Graphics_API_OPENGLES_SOURCES
	../../../Code/source/Graphics/API/OpenGLES/OpenGLESAPI.c
	../../../Code/source/Graphics/API/OpenGLES/OpenGLESTranslators.c)

source_group("Source Files\\OpenGLES" FILES ${Graphics_API_OPENGLES_SOURCES})

set(Graphics_API_OPENGLES_HELPERS_SOURCES
	../../../Code/source/Graphics/API/OpenGLES/Helpers/CheckEGLError.c
	../../../Code/source/Graphics/API/OpenGLES/Helpers/CheckGLESError.c)

source_group("Source Files\\OpenGLES\\Helpers" FILES ${Graphics_API_OPENGLES_HELPERS_SOURCES})

set(${TARGETNAME}_AGGREGATE_SOURCES
	${Graphics_API_OPENGLES_SOURCES}
	${Graphics_API_OPENGLES_HELPERS_SOURCES})

# setup target
add_definitions(-DGFX_API_OpenGLES)
add_definitions(-DPROTO_DLL_EXPORT)

find_library(EGL_STATIC_LIB libEGL.lib HINTS ${THIRD_PARTY_FOLDER}Mali_3.02)
if(NOT EGL_STATIC_LIB)
	message(FATAL_ERROR "EGL static library not found!")
endif()

find_library(GLESV2_STATIC_LIB libGLESv2.lib HINTS ${THIRD_PARTY_FOLDER}Mali_3.02)
if(NOT GLESV2_STATIC_LIB)
	message(FATAL_ERROR "GLESv2 static library not found!")
endif()

add_library(${TARGETNAME} SHARED ${${TARGETNAME}_AGGREGATE_HEADERS} ${${TARGETNAME}_AGGREGATE_SOURCES})
target_link_libraries(${TARGETNAME} GFXAPI)
target_link_libraries(${TARGETNAME} ${EGL_STATIC_LIB} ${GLESV2_STATIC_LIB})

set_target_properties(${TARGETNAME} PROPERTIES FOLDER "GFXAPI")

install(TARGETS ${TARGETNAME} DESTINATION bin)
