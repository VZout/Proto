cmake_minimum_required(VERSION 3.9.2)

project(DataStructures LANGUAGES CXX)

include_directories(./include)
include_directories(${MAIN_INCLUDE_FOLDER}DataStructures/)

#external dependencies

#header files
set(DataStructures_CORE_HEADERS)

source_group("Header Files" FILES ${MemManager_CORE_HEADERS})

set(DataStructures_AGGREGATE_HEADERS
	${DataStructures_CORE_HEADERS})

#source files
set(DataStructures_CORE_SOURCES
	./main.cpp)

source_group("Source Files" FILES ${DataStructures_CORE_SOURCES})

set(DataStructures_AGGREGATE_SOURCES
	${DataStructures_CORE_SOURCES})

#setup target
add_executable(DataStructures ${DataStructures_CORE_HEADERS} ${DataStructures_CORE_SOURCES})
target_link_libraries(DataStructures Math Platform Utility)
set_target_properties(DataStructures PROPERTIES FOLDER "Applications")

install(TARGETS DataStructures DESTINATION bin)
