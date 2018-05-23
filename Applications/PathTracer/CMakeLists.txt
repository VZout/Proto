cmake_minimum_required(VERSION 3.9.2)

set(TARGETNAME PathTracer)
project(${TARGETNAME} LANGUAGES CXX)

if (GFX_API_OPENGL)
include_directories(${THIRD_PARTY_FOLDER}glew-2.1.0/include)
endif()

#header files
set(PathTracer_CORE_HEADERS
	./PathTracer.h)

source_group("Header Files" FILES ${PathTracer_CORE_HEADERS})

set(PathTracer_AGGREGATE_HEADERS
	${PathTracer_CORE_HEADERS})

#source files
set(PathTracer_CORE_SOURCE
	./main.cpp
	./PathTracer.cpp)

source_group("Source Files" FILES ${PathTracer_CORE_SOURCE})

set(PathTracer_AGGREGATE_SOURCES
	${PathTracer_CORE_SOURCE})

#custom user settings
set(COMMAND_ARGUMENTS ${PROTO_ASSET_DIR})
configure_file( ${PROTO_PROJECT_USER_TEMPLATE} ${CMAKE_CURRENT_BINARY_DIR}/${TARGETNAME}.vcxproj.user @ONLY )

#setup target
add_executable(${TARGETNAME} ${PathTracer_AGGREGATE_HEADERS} ${PathTracer_AGGREGATE_SOURCES})
set_target_properties(${TARGETNAME} PROPERTIES FOLDER "Applications")
target_link_libraries(${TARGETNAME} GFXAPI Math Platform Utility)

#external dependencies
if (WIN32)
	if (GFX_API_DX11)
		add_dependencies(${TARGETNAME} GFXAPIDX11)
		target_link_libraries(${TARGETNAME} GFXAPIDX11)
	elseif (GFX_API_DX12)
		add_dependencies(${TARGETNAME} GFXAPIDX12)
		target_link_libraries(${TARGETNAME} GFXAPIDX12)
	elseif (GFX_API_OPENGL)
		add_dependencies(${TARGETNAME} GFXAPIOPENGL)
		target_link_libraries(${TARGETNAME} GFXAPIOPENGL)

		find_library(GLEW32_STATIC_LIB glew32.lib HINTS ${THIRD_PARTY_FOLDER}glew-2.1.0/lib/Release/x64)
		if(NOT GLEW32_STATIC_LIB)
		  message(FATAL_ERROR "Glew32 static library not found!")
		endif()

		find_library(GLEW32S_STATIC_LIB glew32s.lib HINTS ${THIRD_PARTY_FOLDER}glew-2.1.0/lib/Release/x64)
		if(NOT GLEW32S_STATIC_LIB)
		  message(FATAL_ERROR "Glew32s static library not found!")
		endif()

		target_link_libraries(${TARGETNAME} ${GLEW32_STATIC_LIB} ${GLEW32S_STATIC_LIB})

		add_custom_command(TARGET ${TARGETNAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
			"${THIRD_PARTY_FOLDER}glew-2.1.0/bin/Release/x64/glew32.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
	elseif (GFX_API_OPENGLES)
		#message(FATAL_ERROR "Dependencies not set yet!")
	elseif (GFX_API_VULKAN)
		find_library(VULKAN_STATIC_LIB vulkan-1.lib HINTS ${THIRD_PARTY_FOLDER}vulkan/lib)
		if(NOT VULKAN_STATIC_LIB)
		  message(FATAL_ERROR "Vulkan-1 static library not found!")
		endif()
	
		target_link_libraries(${TARGETNAME} ${VULKAN_STATIC_LIB})
	else()
		message(FATAL_ERROR "No graphics api set!")
	endif()
	target_link_libraries(${TARGETNAME} winmm)
elseif(PSP2)
	set_target_properties(${TARGETNAME} PROPERTIES SUFFIX ".self")
endif()

install(TARGETS ${TARGETNAME} DESTINATION bin)
