cmake_minimum_required(VERSION 3.9.2)

project(AI)

include_directories(${MAIN_INCLUDE_FOLDER}AI/)
include_directories(${MAIN_INCLUDE_FOLDER}AI/Navigation)
include_directories(${MAIN_INCLUDE_FOLDER}AI/Navigation/Locomotion)

# header files
set(AI_LOCOMOTION_HEADERS 
    ../../Code/include/AI/Navigation/Locomotion/Vehicle.h)

source_group("Header Files\\Navigation\\Locomotion" FILES ${AI_LOCOMOTION_HEADERS})

set(AI_AGGREGATE_HEADERS
	${AI_LOCOMOTION_HEADERS})

# source files
set(AI_LOCOMOTION_SOURCES
    ../../Code/source/AI/Navigation/Locomotion/Vehicle.cpp)
 
source_group("Source Files\\Navigation\\Locomotion" FILES ${AI_LOCOMOTION_SOURCES})

set(AI_AGGREGATE_SOURCES
	${AI_LOCOMOTION_SOURCES})

# setup target
add_library(AI STATIC ${AI_AGGREGATE_HEADERS} ${AI_AGGREGATE_SOURCES})

set_target_properties(AI PROPERTIES FOLDER "Libraries")
