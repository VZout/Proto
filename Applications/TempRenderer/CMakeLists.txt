cmake_minimum_required(VERSION 3.9.2)

set(TARGETNAME TempRenderer)
project(${TARGETNAME} LANGUAGES CXX)

#external dependencies
#include_directories(${THIRD_PARTY_FOLDER}glew-2.1.0/include)
#include_directories(${THIRD_PARTY_FOLDER}vulkan/include)
include_directories(${THIRD_PARTY_FOLDER}boost_1_65_1)

#header files
set(${TARGETNAME}_CORE_HEADERS
	./Renderer.h
	./RenderPass.h
	./RenderTechnique.h)

source_group("Header Files" FILES ${${TARGETNAME}_CORE_HEADERS})

set(${TARGETNAME}_SCENE_HEADERS
	./Scene/ModelSceneNode.h
	./Scene/SceneGraph.h
	./Scene/SceneGraphVisitor.h
	./Scene/SceneNode.h
	./Scene/SceneNodes.h
	./Scene/SceneNodeVisitor.h
	./Scene/LightSceneNode.h
	./Scene/TransformNode.h)

source_group("Header Files\\Scene" FILES ${${TARGETNAME}_SCENE_HEADERS})

set(${TARGETNAME}_AGGREGATE_HEADERS
	${${TARGETNAME}_CORE_HEADERS}
	${${TARGETNAME}_SCENE_HEADERS})

#source files
set(${TARGETNAME}_CORE_SOURCES
	./main.cpp
	./Renderer.cpp
	./RenderPass.cpp
	./RenderTechnique.cpp)

source_group("Source Files" FILES ${${TARGETNAME}_CORE_SOURCES})

set(${TARGETNAME}_SCENE_SOURCES
	./Scene/SceneGraph.cpp
	./Scene/SceneGraphVisitor.cpp
	./Scene/SceneNode.cpp
	./Scene/SceneNodeVisitor.cpp
	./Scene/LightSceneNode.cpp
	./Scene/ModelSceneNode.cpp
	./Scene/TransformNode.cpp)

source_group("Source Files\\Scene" FILES ${${TARGETNAME}_SCENE_SOURCES})

set(${TARGETNAME}_AGGREGATE_SOURCES
	${${TARGETNAME}_CORE_SOURCES}
	${${TARGETNAME}_SCENE_SOURCES})

#custom user settings
set(COMMAND_ARGUMENTS ${PROTO_ASSET_DIR})
configure_file( ${PROTO_PROJECT_USER_TEMPLATE} ${CMAKE_CURRENT_BINARY_DIR}/${TARGETNAME}.vcxproj.user @ONLY )

#setup target
add_executable(${TARGETNAME} ${${TARGETNAME}_AGGREGATE_HEADERS} ${${TARGETNAME}_AGGREGATE_SOURCES})
set_target_properties(${TARGETNAME} PROPERTIES FOLDER "Applications")
target_link_libraries(${TARGETNAME} GFXAPI Math Platform Utility)

#external dependencies
if (WIN32)
	add_dependencies(${TARGETNAME} GFXAPIDX12)
	target_link_libraries(${TARGETNAME} GFXAPIDX12)

	find_library(VULKAN_STATIC_LIB vulkan-1.lib HINTS ${THIRD_PARTY_FOLDER}vulkan/lib)
	if(NOT VULKAN_STATIC_LIB)
	  message(FATAL_ERROR "Vulkan-1 static library not found!")
	endif()
	
	target_link_libraries(${TARGETNAME} ${VULKAN_STATIC_LIB})

	#add_custom_command(TARGET ${TARGETNAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
	#	"${THIRD_PARTY_FOLDER}glew-2.1.0/bin/Release/x64/glew32.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
endif()

if(PSP2)
	set_target_properties(${TARGETNAME} PROPERTIES SUFFIX ".self")
endif()

install(TARGETS ${TARGETNAME} DESTINATION bin)
