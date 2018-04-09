cmake_minimum_required(VERSION 3.9.2)

project(Memory)

include_directories(${MAIN_INCLUDE_FOLDER}Memory/)
include_directories(${MAIN_INCLUDE_FOLDER}Memory/Allocators)

# header files
set(Memory_CORE_HEADERS
    ../../Code/include/Memory/IAllocator.h)

source_group("Header Files" FILES ${Memory_CORE_HEADERS})

set(Memory_ALLOCATORS_HEADERS 
	../../Code/include/Memory/Allocators/AllocatorBase.h
	../../Code/include/Memory/Allocators/LinearAllocator.h
	../../Code/include/Memory/Allocators/PoolAllocator.h
	../../Code/include/Memory/Allocators/StackAllocator.h
	../../Code/include/Memory/Allocators/FreeListAllocator.h)

source_group("Header Files\\Allocators" FILES ${Memory_ALLOCATORS_HEADERS})

set(Memory_AGGREGATE_HEADERS
	${Memory_CORE_HEADERS}
	${Memory_ALLOCATORS_HEADERS})

# source files
set(Memory_ALLOCATORS_SOURCES
	../../Code/source/Memory/Allocators/LinearAllocator.cpp
	../../Code/source/Memory/Allocators/PoolAllocator.cpp
	../../Code/source/Memory/Allocators/StackAllocator.cpp
	../../Code/source/Memory/Allocators/AllocatorBase.cpp
	../../Code/source/Memory/Allocators/FreeListAllocator.cpp)
 
source_group("Source Files" FILES ${Memory_ALLOCATORS_SOURCES})

set(Memory_AGGREGATE_SOURCES
	${Memory_ALLOCATORS_SOURCES})

# setup target
add_library(Memory STATIC ${Memory_AGGREGATE_HEADERS} ${Memory_AGGREGATE_SOURCES})

set_target_properties(Memory PROPERTIES FOLDER "Libraries")
