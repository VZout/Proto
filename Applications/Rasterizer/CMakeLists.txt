cmake_minimum_required(VERSION 3.9.2)

project(Rasterizer LANGUAGES CXX)

include_directories(./include)

#header files
set(Rasterizer_CORE_HEADERS
	./Rasterizer.h)

source_group("Header Files" FILES ${Rasterizer_CORE_HEADERS})

set(Rasterizer_AGGREGATE_HEADERS
	${Rasterizer_CORE_HEADERS})

#source files
set(Rasterizer_CORE_SOURCE
	./main.cpp
	./Rasterizer.cpp)

source_group("Source Files" FILES ${Rasterizer_CORE_SOURCE})

set(Rasterizer_AGGREGATE_SOURCES
	${Rasterizer_CORE_SOURCE})

#setup target
add_executable(Rasterizer ${Rasterizer_CORE_HEADERS} ${Rasterizer_CORE_SOURCE})

set_target_properties(Rasterizer PROPERTIES FOLDER "Applications")

install(TARGETS Rasterizer DESTINATION bin)
