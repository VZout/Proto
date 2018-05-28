cmake_minimum_required(VERSION 3.9.2)

set(TARGETNAME Graphics)
project(${TARGETNAME})

include_directories(${MAIN_INCLUDE_FOLDER}Graphics)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/Helpers)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/RenderPasses)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/Scene)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/Techniques)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/Viewer)

#external dependencies

#header files
set(${TARGETNAME}_CORE_HEADERS
	../../../Code/Include/Graphics/Light.h
	../../../Code/Include/Graphics/Material.h
	../../../Code/Include/Graphics/Mesh.h
	../../../Code/Include/Graphics/Model.h
	../../../Code/Include/Graphics/Renderer.h
	../../../Code/Include/Graphics/RenderingTechnique.h
	../../../Code/Include/Graphics/RenderPass.h)

source_group("Header Files" FILES ${${TARGETNAME}_CORE_HEADERS})

set(${TARGETNAME}_HELPERS_HEADERS
	../../../Code/Include/Graphics/Helpers/CreateGeometry.h)

source_group("Header Files\\Helpers" FILES ${${TARGETNAME}_HELPERS_HEADERS})

set(${TARGETNAME}_RENDERPASSES_HEADERS
	../../../Code/Include/Graphics/RenderPasses/OpaqueRenderPass.h)

source_group("Header Files\\RenderPasses" FILES ${${TARGETNAME}_RENDERPASSES_HEADERS})

set(${TARGETNAME}_SCENE_HEADERS
	../../../Code/Include/Graphics/Scene/LightSceneNode.h
	../../../Code/Include/Graphics/Scene/ModelSceneNode.h
	../../../Code/Include/Graphics/Scene/Scene.h
	../../../Code/Include/Graphics/Scene/SceneGraph.h
	../../../Code/Include/Graphics/Scene/SceneGraphVisitor.h
	../../../Code/Include/Graphics/Scene/SceneNode.h
	../../../Code/Include/Graphics/Scene/SceneNodes.h
	../../../Code/Include/Graphics/Scene/SceneNodeVisitor.h
	../../../Code/Include/Graphics/Scene/TransformNode.h)

source_group("Header Files\\Scene" FILES ${${TARGETNAME}_SCENE_HEADERS})

set(${TARGETNAME}_TECHNIQUES_HEADERS
	../../../Code/Include/Graphics/Techniques/ForwardRendering.h)

source_group("Header Files\\Techniques" FILES ${${TARGETNAME}_TECHNIQUES_HEADERS})

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
	${${TARGETNAME}_HELPERS_HEADERS}
	${${TARGETNAME}_RENDERPASSES_HEADERS}
	${${TARGETNAME}_SCENE_HEADERS}
	${${TARGETNAME}_TECHNIQUES_HEADERS}
	${${TARGETNAME}_VIEWER_HEADERS})

# source files
set(${TARGETNAME}_CORE_SOURCES
	../../../Code/Source/Graphics/Light.cpp
	../../../Code/Source/Graphics/Mesh.cpp
	../../../Code/Source/Graphics/Model.cpp
	../../../Code/Source/Graphics/Renderer.cpp
	../../../Code/Source/Graphics/RenderingTechnique.cpp
	../../../Code/Source/Graphics/RenderPass.cpp)

source_group("Source Files" FILES ${${TARGETNAME}_CORE_SOURCES})

set(${TARGETNAME}_HELPERS_SOURCES
	../../../Code/Source/Graphics/Helpers/CreateGeometry.cpp)

source_group("Source Files\\Helpers" FILES ${${TARGETNAME}_HELPERS_SOURCES})

set(${TARGETNAME}_RENDERPASSES_SOURCES
	../../../Code/Source/Graphics/RenderPasses/OpaqueRenderPass.cpp)

source_group("Source Files\\RenderPasses" FILES ${${TARGETNAME}_RENDERPASSES_SOURCES})

set(${TARGETNAME}_SCENE_SOURCES
	../../../Code/Source/Graphics/Scene/LightSceneNode.cpp
	../../../Code/Source/Graphics/Scene/ModelSceneNode.cpp
	../../../Code/Source/Graphics/Scene/Scene.cpp
	../../../Code/Source/Graphics/Scene/SceneGraph.cpp
	../../../Code/Source/Graphics/Scene/SceneGraphVisitor.cpp
	../../../Code/Source/Graphics/Scene/SceneNode.cpp
	../../../Code/Source/Graphics/Scene/SceneNodeVisitor.cpp
	../../../Code/Source/Graphics/Scene/TransformNode.cpp)

source_group("Source Files\\Scene" FILES ${${TARGETNAME}_SCENE_SOURCES})

set(${TARGETNAME}_TECHNIQUES_SOURCES
	../../../Code/Source/Graphics/Techniques/ForwardRendering.cpp)

source_group("Header Files\\Techniques" FILES ${${TARGETNAME}_TECHNIQUES_SOURCES})

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
	${${TARGETNAME}_CORE_SOURCES}
	${${TARGETNAME}_HELPERS_SOURCES}
	${${TARGETNAME}_RENDERPASSES_SOURCES}
	${${TARGETNAME}_SCENE_SOURCES}
	${${TARGETNAME}_TECHNIQUES_SOURCES}
	${${TARGETNAME}_VIEWER_SOURCES})

# setup target
add_library(${TARGETNAME} STATIC ${${TARGETNAME}_AGGREGATE_HEADERS} ${${TARGETNAME}_AGGREGATE_SOURCES})

set_target_properties(${TARGETNAME} PROPERTIES FOLDER "Libraries")

install(TARGETS ${TARGETNAME} DESTINATION lib)
