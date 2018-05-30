cmake_minimum_required(VERSION 3.9.2)

set(TARGETNAME Resources)
project(${TARGETNAME})

include_directories(${MAIN_INCLUDE_FOLDER}Resources)
include_directories(${MAIN_INCLUDE_FOLDER}Resources/Helpers)
include_directories(${MAIN_INCLUDE_FOLDER}Resources/Loaders)
include_directories(${MAIN_INCLUDE_FOLDER}Resources/Resources)

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
	../../../Code/Include/Resources/BaseLoader.h
	../../../Code/Include/Resources/EResourceType.h
	../../../Code/Include/Resources/ILoader.h
	../../../Code/Include/Resources/Resource.h
	../../../Code/Include/Resources/ResourceID.h
	../../../Code/Include/Resources/ResourceManager.h)

#source_group("Header Files" FILES ${${TARGETNAME}_CORE_HEADERS})

set(${TARGETNAME}_HELPERS_HEADERS
	../../../Code/Include/Resources/Helpers/GetInvalidResourceID.h
	../../../Code/Include/Resources/Helpers/LoadParameters.h
	../../../Code/Include/Resources/Helpers/GenerateResourceID.h)

source_group("Header Files\\Helpers" FILES ${${TARGETNAME}_HELPERS_HEADERS})

set(${TARGETNAME}_LOADERS_HEADERS
	../../../Code/Include/Resources/Loaders/ModelLoader.h
	../../../Code/Include/Resources/Loaders/ShaderLoader.h)

#source_group("Header Files\\Loaders" FILES ${${TARGETNAME}_LOADERS_HEADERS})

set(${TARGETNAME}_RESOURCES_HEADERS
	../../../Code/Include/Resources/Resources/MeshResource.h
	../../../Code/Include/Resources/Resources/ModelResource.h
	../../../Code/Include/Resources/Resources/ShaderResource.h)

#source_group("Header Files\\Resources" FILES ${${TARGETNAME}_RESOURCES_HEADERS})

set(${TARGETNAME}_AGGREGATE_HEADERS
	${${TARGETNAME}_CORE_HEADERS}
	${${TARGETNAME}_HELPERS_HEADERS}
	${${TARGETNAME}_LOADERS_HEADERS}
	${${TARGETNAME}_RESOURCES_HEADERS})

# source files
set(${TARGETNAME}_CORE_SOURCES
	../../../Code/Source/Resources/BaseLoader.cpp
	../../../Code/Source/Resources/ResourceManager.cpp)

source_group("Source Files" FILES ${${TARGETNAME}_CORE_SOURCES})

set(${TARGETNAME}_HELPERS_SOURCES
	../../../Code/Source/Resources/Helpers/GenerateResourceID.cpp
	../../../Code/Source/Resources/Helpers/GetInvalidResourceID.cpp)

source_group("Source Files\\Helpers" FILES ${${TARGETNAME}_HELPERS_SOURCES})

set(${TARGETNAME}_LOADERS_SOURCES
	../../../Code/Source/Resources/Loaders/ModelLoader.cpp
	../../../Code/Source/Resources/Loaders/ShaderLoader.cpp)

source_group("Source Files\\Loaders" FILES ${${TARGETNAME}_LOADERS_SOURCES})

set(${TARGETNAME}_AGGREGATE_SOURCES
	${${TARGETNAME}_CORE_SOURCES}
	${${TARGETNAME}_HELPERS_SOURCES}
	${${TARGETNAME}_LOADERS_SOURCES})

# setup target
add_library(${TARGETNAME} STATIC ${${TARGETNAME}_AGGREGATE_HEADERS} ${${TARGETNAME}_AGGREGATE_SOURCES})

set_target_properties(${TARGETNAME} PROPERTIES FOLDER "Libraries")

install(TARGETS ${TARGETNAME} DESTINATION lib)
