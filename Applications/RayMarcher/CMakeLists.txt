cmake_minimum_required(VERSION 3.9.2)

project(RayMarcher LANGUAGES CXX)

include_directories(./include)

#header files
set(RayMarcher_CORE_HEADERS
	./RayMarcher.h)

source_group("Header Files" FILES ${RayMarcher_CORE_HEADERS})

set(RayMarcher_AGGREGATE_HEADERS
	${RayMarcher_CORE_HEADERS})

#source files
set(RayMarcher_CORE_SOURCE
	./main.cpp
	./RayMarcher.cpp)

source_group("Source Files" FILES ${RayMarcher_CORE_SOURCE})

set(RayMarcher_AGGREGATE_SOURCES
	${RayMarcher_CORE_SOURCE})

#setup target
add_executable(RayMarcher ${RayMarcher_CORE_HEADERS} ${RayMarcher_CORE_SOURCE})

set_target_properties(RayMarcher PROPERTIES FOLDER "Applications")

install(TARGETS RayMarcher DESTINATION bin)
