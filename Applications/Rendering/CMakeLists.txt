cmake_minimum_required(VERSION 3.9.2)

set(TARGETNAME Rendering)
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
	./SimpleScene.h)

source_group("Header Files" FILES ${${TARGETNAME}_CORE_HEADERS})

set(${TARGETNAME}_AGGREGATE_HEADERS
	${${TARGETNAME}_CORE_HEADERS})

#source files
set(${TARGETNAME}_CORE_SOURCES
	./main.cpp
	./SimpleScene.cpp)

source_group("Source Files" FILES ${${TARGETNAME}_CORE_SOURCES})

set(${TARGETNAME}_AGGREGATE_SOURCES
	${${TARGETNAME}_CORE_SOURCES})

#custom user settings
set(COMMAND_ARGUMENTS ${PROTO_ASSET_DIR})
configure_file( ${PROTO_PROJECT_USER_TEMPLATE} ${CMAKE_CURRENT_BINARY_DIR}/${TARGETNAME}.vcxproj.user @ONLY )

#setup target
add_executable(${TARGETNAME} ${${TARGETNAME}_AGGREGATE_HEADERS} ${${TARGETNAME}_AGGREGATE_SOURCES})
set_target_properties(${TARGETNAME} PROPERTIES FOLDER "Applications")
target_link_libraries(${TARGETNAME} GFXAPI Graphics IO Math Platform Resources Utility)

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
