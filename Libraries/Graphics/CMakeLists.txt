cmake_minimum_required(VERSION 3.9.2)

project(graphics)

include_directories(${MAIN_INCLUDE_FOLDER}Graphics)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/DX11)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/DX11/Helpers)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/DX12)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/Helpers)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/OpenGL)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/OpenGL/Helpers)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/OpenGLES)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/OpenGLES/Helpers)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/OpenGLES/Pi)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/OpenGLES/Win32)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/ORBIS)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/PSP2)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/API/Vulkan)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/Helpers)
include_directories(${MAIN_INCLUDE_FOLDER}Graphics/Viewer)

#external dependencies
include_directories(${THIRD_PARTY_FOLDER}glew-2.1.0/include)
include_directories(${THIRD_PARTY_FOLDER}glm-0.9.8.5)
include_directories(${THIRD_PARTY_FOLDER}vulkan/include)

#header files
set(Graphics_HEADERS
	../../Code/include/Graphics/Material.h)

source_group("Header Files" FILES ${Graphics_HEADERS})

set(Graphics_API_HEADERS
	../../Code/include/Graphics/API/Defines.h
	../../Code/include/Graphics/API/Descriptors.h
	../../Code/include/Graphics/API/Enums.h
	../../Code/include/Graphics/API/GFX.h
	../../Code/include/Graphics/API/GFXIncludes.h
	../../Code/include/Graphics/API/Handles.h
	../../Code/include/Graphics/API/Translators.h)

source_group("Header Files\\API" FILES ${Graphics_API_HEADERS})

set(Graphics_API_DX11_HEADERS
	../../Code/include/Graphics/API/DX11/DX11API.h
	../../Code/include/Graphics/API/DX11/DX11Includes.h
	../../Code/include/Graphics/API/DX11/DX11Structs.h
	../../Code/include/Graphics/API/DX11/DX11Translators.h)

source_group("Header Files\\API\\DX11" FILES ${Graphics_API_DX11_HEADERS})

set(Graphics_API_DX11_HELPERS_HEADERS
	../../Code/include/Graphics/API/DX11/Helpers/DetermineAdapterSettings.h
	../../Code/include/Graphics/API/DX11/Helpers/DetermineConstantBuffers.h
	../../Code/include/Graphics/API/DX11/Helpers/InspectVertexShader.h
	../../Code/include/Graphics/API/DX11/Helpers/SafeRelease.h
	../../Code/include/Graphics/API/DX11/Helpers/SetDebugName.h)

source_group("Header Files\\API\\DX11\\Helpers" FILES ${Graphics_API_DX11_HELPERS_HEADERS})

set(Graphics_API_DX12_HEADERS
	../../Code/include/Graphics/API/DX12/DX12API.h
	../../Code/include/Graphics/API/DX12/DX12Includes.h
	../../Code/include/Graphics/API/DX12/DX12Translators.h)

source_group("Header Files\\API\\DX12" FILES ${Graphics_API_DX12_HEADERS})

set(Graphics_API_HELPERS_HEADERS
	../../Code/include/Graphics/API/Helpers/DataTypeByteSize.h
	../../Code/include/Graphics/API/Helpers/TransposeData.h)

source_group("Header Files\\API\\Helpers" FILES ${Graphics_API_HELPERS_HEADERS})

set(Graphics_API_OPENGL_HEADERS
	../../Code/include/Graphics/API/OpenGL/OpenGLAPI.h
	../../Code/include/Graphics/API/OpenGL/OpenGLIncludes.h
	../../Code/include/Graphics/API/OpenGL/OpenGLShaderReflection.h
	../../Code/include/Graphics/API/OpenGL/OpenGLStructs.h
	../../Code/include/Graphics/API/OpenGL/OpenGLTranslators.h)

source_group("Header Files\\API\\OpenGL" FILES ${Graphics_API_OPENGL_HEADERS})

set(Graphics_API_OPENGL_HELPERS_HEADERS
	../../Code/include/Graphics/API/OpenGL/Helpers/CheckGLError.h)

source_group("Header Files\\API\\OpenGL\\Helpers" FILES ${Graphics_API_OPENGL_HELPERS_HEADERS})

set(Graphics_API_OPENGLES_HEADERS
	../../Code/include/Graphics/API/OpenGLES/OpenGLESAPI.h
	../../Code/include/Graphics/API/OpenGLES/OpenGLESIncludes.h
	../../Code/include/Graphics/API/OpenGLES/OpenGLESStructs.h
	../../Code/include/Graphics/API/OpenGLES/OpenGLESTranslators.h)

source_group("Header Files\\API\\OpenGLES" FILES ${Graphics_API_OPENGLES_HEADERS})

set(Graphics_API_OPENGLES_HELPERS_HEADERS
	../../Code/include/Graphics/API/OpenGLES/Helpers/CheckEGLError.h
	../../Code/include/Graphics/API/OpenGLES/Helpers/CheckGLESError.h)

source_group("Header Files\\API\\OpenGLES\\Helpers" FILES ${Graphics_API_OPENGLES_HELPERS_HEADERS})

set(Graphics_API_ORBIS_HEADERS
	../../Code/include/Graphics/API/ORBIS/ORBISAPI.h
	../../Code/include/Graphics/API/ORBIS/ORBISIncludes.h
	../../Code/include/Graphics/API/ORBIS/ORBISTranslators.h)

source_group("Header Files\\API\\ORBIS" FILES ${Graphics_API_ORBIS_HEADERS})

set(Graphics_API_PSP2_HEADERS
	../../Code/include/Graphics/API/PSP2/PSP2API.h
	../../Code/include/Graphics/API/PSP2/PSP2Includes.h
	../../Code/include/Graphics/API/PSP2/PSP2Translators.h)

source_group("Header Files\\API\\PSP2" FILES ${Graphics_API_PSP2_HEADERS})

set(Graphics_API_VULKAN_HEADERS
	../../Code/include/Graphics/API/Vulkan/VulkanAPI.h
	../../Code/include/Graphics/API/Vulkan/VulkanIncludes.h
	../../Code/include/Graphics/API/Vulkan/VulkanTranslators.h)

source_group("Header Files\\API\\Vulkan" FILES ${Graphics_API_VULKAN_HEADERS})

set(Graphics_HELPERS_HEADERS
	../../Code/include/Graphics/Helpers/CreateGeometry.h)

source_group("Header Files\\Helpers" FILES ${Graphics_HELPERS_HEADERS})

set(Graphics_VIEWER_HEADERS
	../../Code/Include/Graphics/Viewer/Camera.h
	../../Code/Include/Graphics/Viewer/CreateFrustum.h
	../../Code/Include/Graphics/Viewer/CreateViewMatrix.h
	../../Code/Include/Graphics/Viewer/EProjectionMatrix.h
	../../Code/Include/Graphics/Viewer/Frustum.h
	../../Code/Include/Graphics/Viewer/Frustum2D.h
	../../Code/Include/Graphics/Viewer/Frustum3D.h
	../../Code/Include/Graphics/Viewer/OrthographicProjectionMatrix.h
	../../Code/Include/Graphics/Viewer/PerspectiveProjectionMatrix.h
	../../Code/Include/Graphics/Viewer/ProjectionMatrix.h)

source_group("Header Files\\Viewer" FILES ${Graphics_VIEWER_HEADERS})

set(Graphics_AGGREGATE_HEADERS
	${Graphics_HEADERS}
	${Graphics_API_HEADERS}
	${Graphics_API_DX11_HEADERS}
	${Graphics_API_DX11_HELPERS_HEADERS}
	${Graphics_API_DX12_HEADERS}
	${Graphics_API_HELPERS_HEADERS}
	${Graphics_API_OPENGL_HEADERS}
	${Graphics_API_OPENGL_HELPERS_HEADERS}
	${Graphics_API_OPENGLES_HEADERS}
	${Graphics_API_OPENGLES_HELPERS_HEADERS}
	${Graphics_API_PSP2_HEADERS}
	${Graphics_API_ORBIS_HEADERS}
	${Graphics_API_VULKAN_HEADERS}
	${Graphics_HELPERS_HEADERS}
	${Graphics_VIEWER_HEADERS})

# source files
set(Graphics_API_DX11_SOURCES
	../../Code/source/Graphics/API/DX11/DX11API.c
	../../Code/source/Graphics/API/DX11/DX11Translators.c)

source_group("Source Files\\API\\DX11" FILES ${Graphics_API_DX11_SOURCES})

set(Graphics_API_DX11_HELPERS_SOURCES
	../../Code/source/Graphics/API/DX11/Helpers/DetermineAdapterSettings.c
	../../Code/source/Graphics/API/DX11/Helpers/DetermineConstantBuffers.c
	../../Code/source/Graphics/API/DX11/Helpers/InspectVertexShader.c)

source_group("Source Files\\API\\DX11\\Helpers" FILES ${Graphics_API_DX11_HELPERS_SOURCES})

set(Graphics_API_DX12_SOURCES
	../../Code/source/Graphics/API/DX12/DX12API.c
	../../Code/source/Graphics/API/DX12/DX12Translators.c)

source_group("Source Files\\API\\DX12" FILES ${Graphics_API_DX12_SOURCES})

set(Graphics_API_HELPERS_SOURCES
	../../Code/source/Graphics/API/Helpers/DataTypeByteSize.c
	../../Code/source/Graphics/API/Helpers/TransposeData.c)

source_group("Source Files\\API\\Helpers" FILES ${Graphics_API_HELPERS_SOURCES})

set(Graphics_API_OPENGL_SOURCES
	../../Code/source/Graphics/API/OpenGL/OpenGLAPI.c
	../../Code/source/Graphics/API/OpenGL/OpenGLShaderReflection.c
	../../Code/source/Graphics/API/OpenGL/OpenGLTranslators.c)

source_group("Source Files\\API\\OpenGL" FILES ${Graphics_API_OPENGL_SOURCES})

set(Graphics_API_OPENGL_HELPERS_SOURCES
	../../Code/source/Graphics/API/OpenGL/Helpers/CheckGLError.c)

source_group("Source Files\\API\\OpenGL\\Helpers" FILES ${Graphics_API_OPENGL_HELPERS_SOURCES})

set(Graphics_API_OPENGLES_SOURCES
	../../Code/source/Graphics/API/OpenGLES/OpenGLESAPI.c
	../../Code/source/Graphics/API/OpenGLES/OpenGLESTranslators.c)

source_group("Source Files\\API\\OpenGLES" FILES ${Graphics_API_OPENGLES_SOURCES})

set(Graphics_API_OPENGLES_HELPERS_SOURCES
	../../Code/source/Graphics/API/OpenGLES/Helpers/CheckEGLError.c
	../../Code/source/Graphics/API/OpenGLES/Helpers/CheckGLESError.c)

source_group("Source Files\\API\\OpenGLES\\Helpers" FILES ${Graphics_API_OPENGLES_HELPERS_SOURCES})

set(Graphics_API_ORBIS_SOURCES
	../../Code/source/Graphics/API/ORBIS/ORBISAPI.c
	../../Code/source/Graphics/API/ORBIS/ORBISTranslators.c)

source_group("Source Files\\API\\ORBIS" FILES ${Graphics_API_ORBIS_SOURCES})

set(Graphics_API_PSP2_SOURCES
	../../Code/source/Graphics/API/PSP2/PSP2API.c
	../../Code/source/Graphics/API/PSP2/PSP2Translators.c)

source_group("Source Files\\API\\PSP2" FILES ${Graphics_API_PSP2_SOURCES})

set(Graphics_API_VULKAN_SOURCES
	../../Code/source/Graphics/API/Vulkan/VulkanAPI.c
	../../Code/source/Graphics/API/Vulkan/VulkanTranslators.c)

source_group("Source Files\\API\\Vulkan" FILES ${Graphics_API_VULKAN_SOURCES})

set(Graphics_HELPERS_SOURCES
	../../Code/source/Graphics/Helpers/CreateGeometry.cpp)

source_group("Source Files\\Helpers" FILES ${Graphics_HELPERS_HEADERS})

set(Graphics_VIEWER_SOURCES
	../../Code/Source/Graphics/Viewer/Camera.cpp
	../../Code/Source/Graphics/Viewer/CreateFrustum.cpp
	../../Code/Source/Graphics/Viewer/CreateViewMatrix.cpp
	../../Code/Source/Graphics/Viewer/Frustum.cpp
	../../Code/Source/Graphics/Viewer/Frustum2D.cpp
	../../Code/Source/Graphics/Viewer/Frustum3D.cpp
	../../Code/Source/Graphics/Viewer/OrthographicProjectionMatrix.cpp
	../../Code/Source/Graphics/Viewer/PerspectiveProjectionMatrix.cpp
	../../Code/Source/Graphics/Viewer/ProjectionMatrix.cpp)

source_group("Header Files\\Viewer" FILES ${Graphics_VIEWER_SOURCES})

set(Graphics_AGGREGATE_SOURCES
	${Graphics_API_DX11_SOURCES}
	${Graphics_API_DX11_HELPERS_SOURCES}
	${Graphics_API_DX12_SOURCES}
	${Graphics_API_HELPERS_SOURCES}
	${Graphics_API_OPENGL_SOURCES}
	${Graphics_API_OPENGL_HELPERS_SOURCES}
	${Graphics_API_OPENGLES_SOURCES}
	${Graphics_API_OPENGLES_HELPERS_SOURCES}
	${Graphics_API_ORBIS_SOURCES}
	${Graphics_API_PSP2_SOURCES}
	${Graphics_API_VULKAN_SOURCES}
	${Graphics_VIEWER_SOURCES})

# setup target
add_library(Graphics STATIC ${Graphics_AGGREGATE_HEADERS} ${Graphics_AGGREGATE_SOURCES})

#IF(WIN32)
#    target_compile_definitions(Graphics PUBLIC GFX_API_OPENGL)
#ELSE(WIN32)
#    message(FATAL_ERROR "No other platforms supported")
#ENDIF(WIN32)

set_target_properties(Graphics PROPERTIES FOLDER "Libraries")

install(TARGETS Graphics DESTINATION lib)
