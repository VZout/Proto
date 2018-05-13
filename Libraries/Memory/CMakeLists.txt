cmake_minimum_required(VERSION 3.9.2)

project(Memory)

include_directories(${MAIN_INCLUDE_FOLDER}Memory/)
include_directories(${MAIN_INCLUDE_FOLDER}Memory/Allocators)
include_directories(${MAIN_INCLUDE_FOLDER}Memory/Helpers)
include_directories(${MAIN_INCLUDE_FOLDER}Memory/Mechanisms)

# header files
set(Memory_CORE_HEADERS
    ../../Code/include/Memory/CreateMemoryPool.h
    ../../Code/include/Memory/EAllocator.h
    ../../Code/include/Memory/EMechanism.h
    ../../Code/include/Memory/IAllocator.h
    ../../Code/include/Memory/IMemoryPool.h
    ../../Code/include/Memory/Memory.h
    ../../Code/include/Memory/MemoryChunk.h
    ../../Code/include/Memory/MemoryPool.h)

source_group("Header Files" FILES ${Memory_CORE_HEADERS})

set(Memory_ALLOCATORS_HEADERS 
	../../Code/include/Memory/Allocators/AllocatorBase.h
    ../../Code/include/Memory/Allocators/CreateAllocator.h
	../../Code/include/Memory/Allocators/FreeListAllocator.h
	../../Code/include/Memory/Allocators/LinearAllocator.h
	../../Code/include/Memory/Allocators/PoolAllocator.h
	../../Code/include/Memory/Allocators/SegregatedFreeListAllocator.h
	../../Code/include/Memory/Allocators/StackAllocator.h)

source_group("Header Files\\Allocators" FILES ${Memory_ALLOCATORS_HEADERS})

set(Memory_HELPERS_HEADERS 
	../../Code/include/Memory/Helpers/Alignment.h
    ../../Code/include/Memory/Helpers/MemoryChunkHelpers.h)

source_group("Header Files\\Helpers" FILES ${Memory_HELPERS_HEADERS})

set(Memory_MECHANISMS_HEADERS 
	../../Code/include/Memory/Mechanisms/BestFit.h
    ../../Code/include/Memory/Mechanisms/FirstFit.h
    ../../Code/include/Memory/Mechanisms/IMechanism.h
	../../Code/include/Memory/Mechanisms/NextFit.h
    ../../Code/include/Memory/Mechanisms/WorstFit.h)

source_group("Header Files\\Mechanisms" FILES ${Memory_MECHANISMS_HEADERS})

set(Memory_AGGREGATE_HEADERS
	${Memory_CORE_HEADERS}
	${Memory_ALLOCATORS_HEADERS}
	${Memory_HELPERS_HEADERS}
	${Memory_MECHANISMS_HEADERS})

# source files
set(Memory_CORE_SOURCES
	../../Code/source/Memory/CreateMemoryPool.cpp)
 
source_group("Source Files" FILES ${Memory_CORE_SOURCES})

set(Memory_ALLOCATORS_SOURCES
	../../Code/source/Memory/Allocators/AllocatorBase.cpp
	../../Code/source/Memory/Allocators/FreeListAllocator.cpp
	../../Code/source/Memory/Allocators/LinearAllocator.cpp
	../../Code/source/Memory/Allocators/PoolAllocator.cpp
	../../Code/source/Memory/Allocators/SegregatedFreeListAllocator.cpp
	../../Code/source/Memory/Allocators/StackAllocator.cpp)
 
source_group("Source Files\\Allocators" FILES ${Memory_ALLOCATORS_SOURCES})

set(Memory_HELPERS_SOURCES
	../../Code/source/Memory/Helpers/Alignment.cpp
    ../../Code/source/Memory/Helpers/MemoryChunkHelpers.cpp)

source_group("Source Files\\Helpers" FILES ${Memory_HELPERS_SOURCES})

set(Memory_MECHANISMS_SOURCES 
	../../Code/source/Memory/Mechanisms/BestFit.cpp
    ../../Code/source/Memory/Mechanisms/FirstFit.cpp
	../../Code/source/Memory/Mechanisms/NextFit.cpp
    ../../Code/source/Memory/Mechanisms/WorstFit.cpp)

source_group("Source Files\\Mechanisms" FILES ${Memory_MECHANISMS_SOURCES})

set(Memory_AGGREGATE_SOURCES
	${Memory_CORE_SOURCES}
	${Memory_ALLOCATORS_SOURCES}
	${Memory_HELPERS_SOURCES}
	${Memory_MECHANISMS_SOURCES})

# setup target
add_library(Memory STATIC ${Memory_AGGREGATE_HEADERS} ${Memory_AGGREGATE_SOURCES})

set_target_properties(Memory PROPERTIES FOLDER "Libraries")
