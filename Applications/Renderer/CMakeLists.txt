cmake_minimum_required(VERSION 3.9.2)

project(Renderer LANGUAGES CXX)

#external dependencies
include_directories(${THIRD_PARTY_FOLDER}stb)
include_directories(${THIRD_PARTY_FOLDER}glew-2.1.0/include)

#header files
set(Renderer_CORE_HEADERS
	./GenerateGeometry.h
	./Renderer.h
	./ResourceLoading.h)

source_group("Header Files" FILES ${Renderer_CORE_HEADERS})

set(Renderer_AGGREGATE_HEADERS
	${Renderer_CORE_HEADERS})

#source files
set(Renderer_CORE_SOURCE
	./GenerateGeometry.cpp
	./main.cpp
	./Renderer.cpp
	./ResourceLoading.cpp)

source_group("Source Files" FILES ${Renderer_CORE_SOURCE})

set(Renderer_AGGREGATE_SOURCES
	${Renderer_CORE_SOURCE})

#custom user settings
set(COMMAND_ARGUMENTS ${PROTO_ASSET_DIR})
configure_file( ${PROJECT_USER_TEMPLATE_FILE} ${CMAKE_CURRENT_BINARY_DIR}/Renderer.vcxproj.user @ONLY )

#setup target
add_executable(Renderer ${Renderer_CORE_HEADERS} ${Renderer_CORE_SOURCE})
set_target_properties(Renderer PROPERTIES FOLDER "Applications")

#external dependencies
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	find_library(GLEW32_STATIC_LIB glew32.lib HINTS ${THIRD_PARTY_FOLDER}glew-2.1.0/lib/Release/x64)
	if(NOT GLEW32_STATIC_LIB)
	  message(FATAL_ERROR "Glew32 static library not found!")
	endif()

	find_library(GLEW32S_STATIC_LIB glew32s.lib HINTS ${THIRD_PARTY_FOLDER}glew-2.1.0/lib/Release/x64)
	if(NOT GLEW32S_STATIC_LIB)
	  message(FATAL_ERROR "Glew32s static library not found!")
	endif()

	# TODO: add check for OPENGL Graphics library..?
	target_link_libraries(Renderer Graphics IO Math Platform Utility ${GLEW32_STATIC_LIB} ${GLEW32S_STATIC_LIB})

	add_custom_command(TARGET Renderer POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
		"${THIRD_PARTY_FOLDER}glew-2.1.0/bin/Release/x64/glew32.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
endif()

install(TARGETS Renderer DESTINATION bin)
