cmake_minimum_required(VERSION 3.9.2)
project (applications)

include_directories(${CMAKE_SOURCE_DIR}/libraries/include)
include_directories(${CMAKE_SOURCE_DIR}/libraries/ai/include)
include_directories(${CMAKE_SOURCE_DIR}/libraries/architecture/include)
include_directories(${CMAKE_SOURCE_DIR}/libraries/audio/include)
include_directories(${CMAKE_SOURCE_DIR}/libraries/graphics/include)
include_directories(${CMAKE_SOURCE_DIR}/libraries/io/include)
include_directories(${CMAKE_SOURCE_DIR}/libraries/math/include)
include_directories(${CMAKE_SOURCE_DIR}/libraries/memory/include)
include_directories(${CMAKE_SOURCE_DIR}/libraries/platform/include)
include_directories(${CMAKE_SOURCE_DIR}/libraries/procedural/include)
include_directories(${CMAKE_SOURCE_DIR}/libraries/resources/include)
include_directories(${CMAKE_SOURCE_DIR}/libraries/scripting/include)
include_directories(${CMAKE_SOURCE_DIR}/libraries/thirdparty/include)
include_directories(${CMAKE_SOURCE_DIR}/libraries/threading/include)
include_directories(${CMAKE_SOURCE_DIR}/libraries/utility/include)

add_subdirectory(pathtracer)
add_subdirectory(rasterizer)
add_subdirectory(raymarcher)
add_subdirectory(raytracer)
add_subdirectory(renderer)
add_subdirectory(TempVulkanRenderer)
