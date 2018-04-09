cmake_minimum_required(VERSION 3.9.2)

project(RayTracer LANGUAGES CXX)

include_directories(./include)

#header files
set(RayTracer_CORE_HEADERS
	./RayTracer.h)

source_group("Header Files" FILES ${RayTracer_CORE_HEADERS})

set(RayTracer_AGGREGATE_HEADERS
	${RayTracer_CORE_HEADERS})

#source files
set(RayTracer_CORE_SOURCE
	./main.cpp
	./RayTracer.cpp)

source_group("Source Files" FILES ${RayTracer_CORE_SOURCE})

set(RayTracer_AGGREGATE_SOURCES
	${RayTracer_CORE_SOURCE})

#setup target
add_executable(RayTracer ${RayTracer_CORE_HEADERS} ${RayTracer_CORE_SOURCE})

set_target_properties(RayTracer PROPERTIES FOLDER "Applications")

install(TARGETS RayTracer DESTINATION bin)
