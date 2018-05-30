cmake_minimum_required(VERSION 3.9.2)

project(AI)

include_directories(${MAIN_INCLUDE_FOLDER}AI/)
include_directories(${MAIN_INCLUDE_FOLDER}AI/)
include_directories(${MAIN_INCLUDE_FOLDER}AI/GeneticAlgorithm)
include_directories(${MAIN_INCLUDE_FOLDER}AI/Navigation/Locomotion)

# header files
set(AI_GENETIC_ALGORITHM_HEADERS 
	../../Code/Include/AI/GeneticAlgorithm/Crossover.h
	../../Code/Include/AI/GeneticAlgorithm/Gene.h
	../../Code/Include/AI/GeneticAlgorithm/Genome.h
	../../Code/Include/AI/GeneticAlgorithm/Mutation.h
	../../Code/Include/AI/GeneticAlgorithm/Operator.h
	../../Code/Include/AI/GeneticAlgorithm/Selection.h)

source_group("Header Files\\GeneticAlgorithm" FILES ${AI_GENETIC_ALGORITHM_HEADERS})

set(AI_LOCOMOTION_HEADERS 
    ../../Code/include/AI/Navigation/Locomotion/Vehicle.h)

source_group("Header Files\\Navigation\\Locomotion" FILES ${AI_LOCOMOTION_HEADERS})

set(AI_AGGREGATE_HEADERS
	${AI_GENETIC_ALGORITHM_HEADERS}
	${AI_LOCOMOTION_HEADERS})

# source files
set(AI_GENETIC_ALGORITHM_SOURCES
	../../Code/Source/AI/GeneticAlgorithm/Gene.cpp
	../../Code/Source/AI/GeneticAlgorithm/Genome.cpp
	../../Code/Source/AI/GeneticAlgorithm/Selection.cpp)
 
source_group("Source Files\\GeneticAlgorithm" FILES ${AI_GENETIC_ALGORITHM_SOURCES})

set(AI_LOCOMOTION_SOURCES
    ../../Code/Source/AI/Navigation/Locomotion/Vehicle.cpp)
 
source_group("Source Files\\Navigation\\Locomotion" FILES ${AI_LOCOMOTION_SOURCES})

set(AI_AGGREGATE_SOURCES
	${AI_GENETIC_ALGORITHM_SOURCES}
	${AI_LOCOMOTION_SOURCES})

# setup target
add_library(AI STATIC ${AI_AGGREGATE_HEADERS} ${AI_AGGREGATE_SOURCES})

set_target_properties(AI PROPERTIES FOLDER "Libraries")
