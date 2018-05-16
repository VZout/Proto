cmake_minimum_required(VERSION 3.9.2)

set(TARGETNAME GFXAPIOPENGL)
project(${TARGETNAME} LANGUAGES CXX)

include_directories(${MAIN_INCLUDE_FOLDER}Graphics)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/OpenGL)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/OpenGL/Helpers)
if (GFX_API_OPENGL)
include_directories(${THIRD_PARTY_FOLDER}glew-2.1.0/include)
endif()

#header files
set(Graphics_API_CORE_HEADERS
	../../../Code/include/Graphics/API/Defines.h
	../../../Code/include/Graphics/API/Descriptors.h
	../../../Code/include/Graphics/API/Enums.h
	../../../Code/include/Graphics/API/GFX.h
	../../../Code/include/Graphics/API/GFXIncludes.h
	../../../Code/include/Graphics/API/Handles.h
	../../../Code/include/Graphics/API/Translators.h)

source_group("Header Files" FILES ${Graphics_API_CORE_HEADERS})

set(Graphics_API_OPENGL_HEADERS
	../../../Code/include/Graphics/API/OpenGL/OpenGLAPI.h
	../../../Code/include/Graphics/API/OpenGL/OpenGLIncludes.h
	../../../Code/include/Graphics/API/OpenGL/OpenGLStructs.h
	../../../Code/include/Graphics/API/OpenGL/OpenGLShaderReflection.h
	../../../Code/include/Graphics/API/OpenGL/OpenGLTranslators.h)

source_group("Header Files\\OpenGL" FILES ${Graphics_API_OPENGL_HEADERS})

set(Graphics_API_OPENGL_HELPERS_HEADERS
	../../../Code/include/Graphics/API/OpenGL/Helpers/CheckGLError.h)

source_group("Header Files\\OPENGL\\Helpers" FILES ${Graphics_API_OPENGL_HELPERS_HEADERS})

set(${TARGETNAME}_AGGREGATE_HEADERS
	${Graphics_API_CORE_HEADERS}
	${Graphics_API_OPENGL_HEADERS}
	${Graphics_API_OPENGL_HELPERS_HEADERS})

# source files
set(Graphics_API_OPENGL_CORE_SOURCES
	../../../Code/source/Graphics/API/OpenGL/OpenGLAPI.c
	../../../Code/source/Graphics/API/OpenGL/OpenGLShaderReflection.c
	../../../Code/source/Graphics/API/OpenGL/OpenGLTranslators.c)

source_group("Source Files\\OPENGL" FILES ${Graphics_API_OPENGL_CORE_SOURCES})

set(Graphics_API_OPENGL_HELPERS_SOURCES
	../../../Code/source/Graphics/API/OpenGL/Helpers/CheckGLError.c)

source_group("Source Files\\OPENGL" FILES ${Graphics_API_OPENGL_HELPERS_SOURCES})

set(${TARGETNAME}_AGGREGATE_SOURCES
	${Graphics_API_OPENGL_CORE_SOURCES}
	${Graphics_API_OPENGL_HELPERS_SOURCES})

# setup target
add_definitions(-DGFX_API_OPENGL)
add_definitions(-DPROTO_DLL_EXPORT)

find_library(GLEW32_STATIC_LIB glew32.lib HINTS ${THIRD_PARTY_FOLDER}glew-2.1.0/lib/Release/x64)
if(NOT GLEW32_STATIC_LIB)
	message(FATAL_ERROR "Glew32 static library not found!")
endif()

find_library(GLEW32S_STATIC_LIB glew32s.lib HINTS ${THIRD_PARTY_FOLDER}glew-2.1.0/lib/Release/x64)
if(NOT GLEW32S_STATIC_LIB)
	message(FATAL_ERROR "Glew32s static library not found!")
endif()

add_library(${TARGETNAME} SHARED ${${TARGETNAME}_AGGREGATE_HEADERS} ${${TARGETNAME}_AGGREGATE_SOURCES})
target_link_libraries(${TARGETNAME} GFXAPI)
target_link_libraries(${TARGETNAME} ${GLEW32_STATIC_LIB} ${GLEW32S_STATIC_LIB} "OpenGL32.lib")

set_target_properties(${TARGETNAME} PROPERTIES FOLDER "GFXAPI")

install(TARGETS ${TARGETNAME} DESTINATION bin)
