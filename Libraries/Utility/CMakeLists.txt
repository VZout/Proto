cmake_minimum_required(VERSION 3.9.2)

project(utility)

include_directories(${MAIN_INCLUDE_FOLDER}Utility/Datastructures)
include_directories(${MAIN_INCLUDE_FOLDER}Utility/Patterns)

include_directories(${THIRD_PARTY_FOLDER}boost_1_65_1)

#header files
set(Utility_CORE_HEADERS
	../../Code/include/Utility/Array2D.h
	../../Code/include/Utility/Array3D.h
	../../Code/include/Utility/AutoPointer.h
	../../Code/include/Utility/BasicString.h
	../../Code/include/Utility/ClearContainerContents.h
	../../Code/include/Utility/ConcurrentQueue.h
	../../Code/include/Utility/ConsoleLogger.h
	../../Code/include/Utility/ENoInit.h
	../../Code/include/Utility/FixedString.h
	../../Code/include/Utility/FunctorFiveParameters.h
	../../Code/include/Utility/FunctorFourParameters.h
	../../Code/include/Utility/FunctorHelperFunctions.h
	../../Code/include/Utility/FunctorNoParameters.h
	../../Code/include/Utility/FunctorOneParameter.h
	../../Code/include/Utility/Functors.h
	../../Code/include/Utility/FunctorStore.h
	../../Code/include/Utility/FunctorThreeParameters.h
	../../Code/include/Utility/FunctorTwoParameters.h
	../../Code/include/Utility/Handle.h
	../../Code/include/Utility/HashedString.h
	../../Code/include/Utility/HashFunctions.h
	../../Code/include/Utility/IUpdatable.h
	../../Code/include/Utility/LexicalCast.h
	../../Code/include/Utility/List.h
	../../Code/include/Utility/Logger.h
	../../Code/include/Utility/NoCopy.h
	../../Code/include/Utility/ParameterList.h
	../../Code/include/Utility/Sleep.h
	../../Code/include/Utility/Stopwatch.h
	../../Code/include/Utility/String.h
	../../Code/include/Utility/TokenizeString.h
	../../Code/include/Utility/UnionCast.h
	../../Code/include/Utility/UpdateEvent.h
	../../Code/include/Utility/Vector.h
	../../Code/include/Utility/WideString.h)

source_group("Header Files" FILES ${Utility_CORE_HEADERS})

set(Utility_DATASTRUCTURES_HEADERS
	../../Code/include/Utility/Datastructures/BinarySearchTree.h
	../../Code/include/Utility/Datastructures/BinaryTree.h
	../../Code/include/Utility/Datastructures/DoublyLinkedList.h
	../../Code/include/Utility/Datastructures/OrderedList.h
	../../Code/include/Utility/Datastructures/RedBlackTree.h
	../../Code/include/Utility/Datastructures/SinglyLinkedList.h
	../../Code/include/Utility/Datastructures/Tree.h)

source_group("Header Files\\DataStructures" FILES ${Utility_DATASTRUCTURES_HEADERS})

set(Utility_PATTERNS_HEADERS
	../../Code/include/Utility/Patterns/IVisitable.h
	../../Code/include/Utility/Patterns/IVisitor.h)

source_group("Header Files\\Patterns" FILES ${Utility_PATTERNS_HEADERS})

set(Utility_AGGREGATE_HEADERS
	${Utility_CORE_HEADERS}
	${Utility_PATTERNS_HEADERS}
	${Utility_DATASTRUCTURES_HEADERS})

# source files
set(Utility_CORE_SOURCES
	../../Code/source/Utility/ConsoleLogger.cpp
	../../Code/source/Utility/FixedString.cpp
	../../Code/source/Utility/HashedString.cpp
	../../Code/source/Utility/Sleep.cpp
	../../Code/source/Utility/Stopwatch.cpp
	../../Code/source/Utility/String.cpp
	../../Code/source/Utility/TokenizeString.cpp
	../../Code/source/Utility/WideString.cpp)

source_group("Source Files" FILES ${Utility_CORE_SOURCES})

set(Utility_AGGREGATE_SOURCES
	${Utility_CORE_SOURCES})

# setup target
add_library(Utility STATIC ${Utility_AGGREGATE_HEADERS} ${Utility_AGGREGATE_SOURCES})

set_target_properties(Utility PROPERTIES FOLDER "Libraries")

install(TARGETS Utility DESTINATION lib)
