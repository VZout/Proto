cmake_minimum_required(VERSION 3.9.2)

set(TARGETNAME GFXAPIOpenGLES)
project(${TARGETNAME} LANGUAGES CXX)

include_directories(${MAIN_INCLUDE_FOLDER}Graphics)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/OpenGLES)

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

set(Graphics_API_OpenGLES_HEADERS
	../../../Code/include/Graphics/API/OpenGLES/OpenGLESAPI.h
	../../../Code/include/Graphics/API/OpenGLES/OpenGLESIncludes.h
	../../../Code/include/Graphics/API/OpenGLES/OpenGLESStructs.h
	../../../Code/include/Graphics/API/OpenGLES/OpenGLESTranslators.h)

source_group("Header Files\\OpenGLES" FILES ${Graphics_API_OpenGLES_HEADERS})

set(${TARGETNAME}_AGGREGATE_HEADERS
	${Graphics_API_HEADERS}
	${Graphics_API_OpenGLES_HEADERS}
	${Graphics_API_OpenGLES_HELPERS_HEADERS})

# source files
set(Graphics_API_OpenGLES_SOURCES
	../../../Code/source/Graphics/API/OpenGLES/OpenGLESAPI.c
	../../../Code/source/Graphics/API/OpenGLES/OpenGLESTranslators.c)

source_group("Source Files\\OpenGLES" FILES ${Graphics_API_OpenGLES_SOURCES})

set(${TARGETNAME}_AGGREGATE_SOURCES
	${Graphics_API_OpenGLES_SOURCES})

# setup target
add_definitions(-DGFX_API_OpenGLES)
add_definitions(-DPROTO_DLL_EXPORT)

add_library(${TARGETNAME} SHARED ${${TARGETNAME}_AGGREGATE_HEADERS} ${${TARGETNAME}_AGGREGATE_SOURCES})

set_target_properties(${TARGETNAME} PROPERTIES FOLDER "GFXAPI")

install(TARGETS ${TARGETNAME} DESTINATION bin)
