cmake_minimum_required(VERSION 3.9.2)

set(TARGETNAME TempRenderer)
project(${TARGETNAME} LANGUAGES CXX)

#external dependencies
include_directories(${THIRD_PARTY_FOLDER}rapidxml)
include_directories(${THIRD_PARTY_FOLDER}boost_1_65_1)
include_directories(${THIRD_PARTY_FOLDER}stb)
include_directories(${THIRD_PARTY_FOLDER}tinygltf)

if (GFX_API_OPENGLES)
include_directories(${THIRD_PARTY_FOLDER}Mali_3.02/include)
endif()

#header files
set(${TARGETNAME}_CORE_HEADERS
	./Renderer.h
	./RenderPass.h
	./RenderingTechnique.h
	./SimpleScene.h)

source_group("Header Files" FILES ${${TARGETNAME}_CORE_HEADERS})

set(${TARGETNAME}_RENDERPASSES_HEADERS
	./RenderPasses/OpaqueRenderPass.h)

source_group("Header Files\\RenderPasses" FILES ${${TARGETNAME}_RENDERPASSES_HEADERS})

set(${TARGETNAME}_RESOURCES_HEADERS
	./Resources/BaseLoader.h
	./Resources/EResourceType.h
	./Resources/ILoader.h
	./Resources/LoadResources.h
	./Resources/Resource.h
	./Resources/ResourceID.h
	./Resources/ResourceManager.h)

source_group("Header Files\\Resources" FILES ${${TARGETNAME}_RESOURCES_HEADERS})

set(${TARGETNAME}_RESOURCES_RESOURCES_HEADERS
	./Resources/Resources/MeshResource.h
	./Resources/Resources/ModelResource.h
	./Resources/Resources/ShaderResource.h)

source_group("Header Files\\Resources\\Resources" FILES ${${TARGETNAME}_RESOURCES_RESOURCES_HEADERS})

set(${TARGETNAME}_RESOURCES_HELPERS_HEADERS
	./Resources/Helpers/GetInvalidResourceID.h
	./Resources/Helpers/GenerateResourceID.h
	./Resources/Helpers/LoadParameters.h)

source_group("Header Files\\Resources\\Helpers" FILES ${${TARGETNAME}_RESOURCES_HELPERS_HEADERS})

set(${TARGETNAME}_RESOURCES_LOADERS_HEADERS
	./Resources/Loaders/ModelLoader.h
	./Resources/Loaders/ShaderLoader.h)

source_group("Header Files\\Resources\\Loaders" FILES ${${TARGETNAME}_RESOURCES_LOADERS_HEADERS})

set(${TARGETNAME}_SCENE_HEADERS
	./Scene/ModelSceneNode.h
	./Scene/Scene.h
	./Scene/SceneGraph.h
	./Scene/SceneGraphVisitor.h
	./Scene/SceneNode.h
	./Scene/SceneNodes.h
	./Scene/SceneNodeVisitor.h
	./Scene/LightSceneNode.h
	./Scene/TransformNode.h)

source_group("Header Files\\Scene" FILES ${${TARGETNAME}_SCENE_HEADERS})

set(${TARGETNAME}_TECHNIQUES_HEADERS
	./Techniques/ForwardRendering.h)

source_group("Header Files\\Techniques" FILES ${${TARGETNAME}_TECHNIQUES_HEADERS})

set(${TARGETNAME}_AGGREGATE_HEADERS
	${${TARGETNAME}_CORE_HEADERS}
	${${TARGETNAME}_RENDERPASSES_HEADERS}
	${${TARGETNAME}_RESOURCES_HEADERS}
	${${TARGETNAME}_RESOURCES_LOADERS_HEADERS}
	${${TARGETNAME}_RESOURCES_RESOURCES_HEADERS}
	${${TARGETNAME}_SCENE_HEADERS}
	${${TARGETNAME}_TECHNIQUES_HEADERS})

#source files
set(${TARGETNAME}_CORE_SOURCES
	./main.cpp
	./Renderer.cpp
	./RenderPass.cpp
	./RenderingTechnique.cpp
	./SimpleScene.cpp)

source_group("Source Files" FILES ${${TARGETNAME}_CORE_SOURCES})

set(${TARGETNAME}_RENDERPASSES_SOURCES
	./RenderPasses/OpaqueRenderPass.cpp)

source_group("Source Files\\RenderPasses" FILES ${${TARGETNAME}_RENDERPASSES_SOURCES})

set(${TARGETNAME}_RESOURCES_SOURCES
	./Resources/BaseLoader.cpp
	./Resources/LoadResources.cpp
	./Resources/ResourceManager.cpp)

source_group("Source Files\\Resources" FILES ${${TARGETNAME}_RESOURCES_SOURCES})

set(${TARGETNAME}_RESOURCES_HELPERS_SOURCES
	./Resources/Helpers/GetInvalidResourceID.cpp
	./Resources/Helpers/GenerateResourceID.cpp)

source_group("Source Files\\Resources\\Helpers" FILES ${${TARGETNAME}_RESOURCES_HELPERS_SOURCES})

set(${TARGETNAME}_RESOURCES_LOADERS_SOURCES
	./Resources/Loaders/ModelLoader.cpp
	./Resources/Loaders/ShaderLoader.cpp)

source_group("Source Files\\Resources\\Loaders" FILES ${${TARGETNAME}_RESOURCES_LOADERS_SOURCES})

set(${TARGETNAME}_SCENE_SOURCES
	./Scene/Scene.cpp
	./Scene/SceneGraph.cpp
	./Scene/SceneGraphVisitor.cpp
	./Scene/SceneNode.cpp
	./Scene/SceneNodeVisitor.cpp
	./Scene/LightSceneNode.cpp
	./Scene/ModelSceneNode.cpp
	./Scene/TransformNode.cpp)

source_group("Source Files\\Scene" FILES ${${TARGETNAME}_SCENE_SOURCES})

set(${TARGETNAME}_TECHNIQUES_SOURCES
	./Techniques/ForwardRendering.cpp)

source_group("Source Files\\Techniques" FILES ${${TARGETNAME}_TECHNIQUES_SOURCES})

set(${TARGETNAME}_AGGREGATE_SOURCES
	${${TARGETNAME}_CORE_SOURCES}
	${${TARGETNAME}_RESOURCES_HELPERS_SOURCES}
	${${TARGETNAME}_RENDERPASSES_SOURCES}
	${${TARGETNAME}_RESOURCES_SOURCES}
	${${TARGETNAME}_RESOURCES_LOADERS_SOURCES}
	${${TARGETNAME}_SCENE_SOURCES}
	${${TARGETNAME}_TECHNIQUES_SOURCES})

#custom user settings
set(COMMAND_ARGUMENTS ${PROTO_ASSET_DIR})
configure_file( ${PROTO_PROJECT_USER_TEMPLATE} ${CMAKE_CURRENT_BINARY_DIR}/${TARGETNAME}.vcxproj.user @ONLY )

#setup target
add_executable(${TARGETNAME} ${${TARGETNAME}_AGGREGATE_HEADERS} ${${TARGETNAME}_AGGREGATE_SOURCES})
set_target_properties(${TARGETNAME} PROPERTIES FOLDER "Applications")
target_link_libraries(${TARGETNAME} GFXAPI IO Math Platform Utility)

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

		add_custom_command(TARGET ${TARGETNAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
			"${THIRD_PARTY_FOLDER}glew-2.1.0/bin/Release/x64/glew32.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
	elseif (GFX_API_OPENGLES)
		add_dependencies(${TARGETNAME} GFXAPIOPENGLES)
		target_link_libraries(${TARGETNAME} GFXAPIOPENGLES)
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
