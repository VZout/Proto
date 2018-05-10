cmake_minimum_required(VERSION 3.9.2)

set(TARGETNAME GFXAPIOpenGL)
project(${TARGETNAME} LANGUAGES CXX)

include_directories(${MAIN_INCLUDE_FOLDER}Graphics)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/OpenGL)

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

set(Graphics_API_OpenGL_HEADERS
	../../../Code/include/Graphics/API/OpenGL/OpenGLAPI.h
	../../../Code/include/Graphics/API/OpenGL/OpenGLIncludes.h
	../../../Code/include/Graphics/API/OpenGL/OpenGLStructs.h
	../../../Code/include/Graphics/API/OpenGL/OpenGLTranslators.h)

source_group("Header Files\\OpenGL" FILES ${Graphics_API_OpenGL_HEADERS})

set(${TARGETNAME}_AGGREGATE_HEADERS
	${Graphics_API_HEADERS}
	${Graphics_API_OpenGL_HEADERS}
	${Graphics_API_OpenGL_HELPERS_HEADERS})

# source files
set(Graphics_API_OpenGL_SOURCES
	../../../Code/source/Graphics/API/OpenGL/OpenGLAPI.c
	../../../Code/source/Graphics/API/OpenGL/OpenGLTranslators.c)

source_group("Source Files\\OpenGL" FILES ${Graphics_API_OpenGL_SOURCES})

set(${TARGETNAME}_AGGREGATE_SOURCES
	${Graphics_API_OpenGL_SOURCES})

# setup target
add_definitions(-DGFX_API_OpenGL)
add_definitions(-DPROTO_DLL_EXPORT)

add_library(${TARGETNAME} SHARED ${${TARGETNAME}_AGGREGATE_HEADERS} ${${TARGETNAME}_AGGREGATE_SOURCES})

set_target_properties(${TARGETNAME} PROPERTIES FOLDER "GFXAPI")

install(TARGETS ${TARGETNAME} DESTINATION bin)
