cmake_minimum_required(VERSION 3.9.2)

project(MemManager LANGUAGES CXX)

include_directories(./include)
include_directories(${MAIN_INCLUDE_FOLDER}Memory/)

#external dependencies

#header files
set(MemManager_CORE_HEADERS
	./Classes.h)

source_group("Header Files" FILES ${MemManager_CORE_HEADERS})

set(MemManager_AGGREGATE_HEADERS
	${MemManager_CORE_HEADERS})

#source files
set(MemManager_CORE_SOURCES
	./main.cpp)

source_group("Source Files" FILES ${MemManager_CORE_SOURCES})

set(MemManager_AGGREGATE_SOURCES
	${MemManager_CORE_SOURCES})

#setup target
add_executable(MemManager ${MemManager_CORE_HEADERS} ${MemManager_CORE_SOURCES})
target_link_libraries(MemManager Memory Math Platform Utility)
set_target_properties(MemManager PROPERTIES FOLDER "Applications")

install(TARGETS MemManager DESTINATION bin)
