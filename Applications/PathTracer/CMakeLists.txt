cmake_minimum_required(VERSION 3.9.2)

project(PathTracer LANGUAGES CXX)

include_directories(./include)

#header files
set(PathTracer_CORE_HEADERS
	./PathTracer.h)

source_group("Header Files" FILES ${PathTracer_CORE_HEADERS})

set(PathTracer_AGGREGATE_HEADERS
	${PathTracer_CORE_HEADERS})

#source files
set(PathTracer_CORE_SOURCE
	./main.cpp
	./PathTracer.cpp)

source_group("Source Files" FILES ${PathTracer_CORE_SOURCE})

set(PathTracer_AGGREGATE_SOURCES
	${PathTracer_CORE_SOURCE})

#setup target
add_executable(PathTracer ${PathTracer_CORE_HEADERS} ${PathTracer_CORE_SOURCE})

set_target_properties(PathTracer PROPERTIES FOLDER "Applications")

install(TARGETS PathTracer DESTINATION bin)
